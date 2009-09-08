#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

#include "A_ImportManager.qoh"
#include "A_SoundImport.qoh"
#include "I_ImportTarget.h"
#include "TitleCarrierListModel.hpp"
#include "TitleDlgUi.h"

#include "FileSelectionDlg.qoh"


FileSelectionDlg::FileSelectionDlg(QWidget* parent)
:   QDialog(parent),
    m_importMgr(NULL),
    m_importListModel(NULL)
{
    setupUi(this);
    m_fileList->setSelectionBehavior(QAbstractItemView::SelectRows);
    setEnabled(false);

    m_importListModel = new TitleCarrierListModel;
    m_fileList->setModel(m_importListModel);

    connect( m_newBtn,      SIGNAL( clicked()                ),
             this,          SLOT  ( ImportFiles()            ) );
    connect( m_deleteBtn,   SIGNAL( clicked()                ),
             this,          SLOT  ( DeleteSelectedFiles()    ) );
    connect( m_renameBtn,   SIGNAL( clicked()                ),
             this,          SLOT  ( RenameSelectedFiles()    ) );
    connect( m_reimportBtn, SIGNAL( clicked()                ),
             this,          SLOT  ( ReimportSelectedFiles()  ) );

    connect( m_fileList->selectionModel(),
             SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) ),
             this,
             SLOT  ( UpdateSelectionButtons() )
           );
}

FileSelectionDlg::~FileSelectionDlg()
{
    delete m_importListModel;
}

void FileSelectionDlg::Associate(A_ImportManager* mgr)
{
    if (mgr == m_importMgr)
        return;

    if (m_importMgr)
    {
        disconnect(m_importMgr);
        m_importMgr->disconnect(this);
    }

    m_importMgr = mgr;
    if (!mgr)
    {
        setEnabled(false);
        m_importListModel->setList( QList<A_SoundImport*>() );
        return;
    }

    setEnabled(true);
    m_importListModel->setList(mgr->ImportList());

    connect( mgr,   SIGNAL( Modified()      ),
             this,  SLOT  ( UpdateList()    ) );
    connect( mgr,   SIGNAL( CopyLocalActivated(const QList<A_SoundImport*>&)    ),
             this,  SLOT  ( RequestCopyLocal(const QList<A_SoundImport*>&)      ) );
    connect( mgr,   SIGNAL( destroyed() ),
             this,  SLOT  ( RemoveMgr() ) );

    connect(this,
            SIGNAL( ImportRequested(const QString&, const QString&) ),
            mgr,
            SLOT  ( ImportFile(const QString&, const QString&)      ) );
}

void FileSelectionDlg::ExecSingleSelection(I_ImportTarget* target)
{
    m_fileList->setSelectionMode(QAbstractItemView::SingleSelection);

    if (exec() == QDialog::Accepted)
    {
        QModelIndexList selected =
            m_fileList->selectionModel()->selectedIndexes();

        if (selected.size() == 1)
        {
            A_SoundImport* import = dynamic_cast<A_SoundImport*>(
                selected[0].data(Qt::UserRole).value<I_TitleCarrier*>()
                );
            target->AddImport(import);
        }
    }
}

void FileSelectionDlg::ExecMultiSelection(I_ImportTarget* target)
{
    m_fileList->setSelectionMode(QAbstractItemView::ExtendedSelection);

    QList<A_SoundImport*> retlist;
    if (exec() == QDialog::Accepted)
    {
        QModelIndexList selected =
            m_fileList->selectionModel()->selectedIndexes();

        for ( QModelIndexList::iterator it = selected.begin();
              it != selected.end();
              it++ )
        {
            A_SoundImport* addend = dynamic_cast<A_SoundImport*>(
                (*it).data(Qt::UserRole).value<I_TitleCarrier*>()
                );
            if (addend)
                retlist.append(addend);
        }

        for ( QList<A_SoundImport*>::iterator it = retlist.begin();
              it != retlist.end();
              it++ )
        {
            target->AddImport(*it);
        }
    }
}

int FileSelectionDlg::ExecNoSelection()
{
    QDialogButtonBox::StandardButtons bbSettings =
        buttonBox->standardButtons();
    buttonBox->setStandardButtons(QDialogButtonBox::Close);

    m_fileList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    int retval = exec();

    buttonBox->setStandardButtons(bbSettings);
    return retval;
}

void FileSelectionDlg::reject()
{
    m_fileList->clearSelection();

    QDialog::reject();
}

void FileSelectionDlg::RequestCopyLocal(QList<A_SoundImport*> externalFiles)
{
    QMessageBox::StandardButton result = QMessageBox::No;

    if (externalFiles.count() > 0)
    {
        result = QMessageBox::question(
            this,
            QString("Copy External"),
            QString("Would you like to copy all current imports to "
                    "the local folder?"),
            ( QMessageBox::Yes | QMessageBox::No ),
            QMessageBox::No );
    }
    if (result == QMessageBox::Yes)
    {
        for ( QList<A_SoundImport*>::iterator fileIt = externalFiles.begin();
              fileIt != externalFiles.end();
              fileIt++ )
        {
            QString newFilename;
            if (!CopyFileToLocalPath((*fileIt)->Filename(), newFilename))
            {
                QMessageBox::warning(
                    this,
                    QString("Copy Failed"),
                    (   QString("An error occurred and the file '") +
                        (*fileIt)->Filename() +
                        QString("' was not copied.\n") ) );
            }
            else
            {
                (*fileIt)->ReimportFrom(newFilename);
            }
        }
    }
}

void FileSelectionDlg::showEvent(QShowEvent* evt)
{
    UpdateSelectionButtons();

    QDialog::showEvent(evt);
}

void FileSelectionDlg::ImportFiles()
{
    QStringList newFiles;
    GetFileList(newFiles);
    FilterFileList(newFiles);

    QMessageBox::StandardButton copyChoice = QMessageBox::NoButton;
    for ( QStringList::iterator fileIt = newFiles.begin();
          fileIt != newFiles.end();
          fileIt++ )
    {
        QString title;
        if (GetTitleForFile(*fileIt, title))
        {
            QString filename = *fileIt;
            bool doCopy = (copyChoice == QMessageBox::YesToAll);

            QFileInfo fileInfo(filename);
            QDir localPath(m_importMgr->ProjectPath());
            bool alreadyLocal =
                filename == localPath.absoluteFilePath(fileInfo.fileName());

            if ( m_importMgr->IsCopyLocalOn() &&
                 !alreadyLocal &&
                 (copyChoice == QMessageBox::NoButton) )
            {
                QMessageBox::StandardButton result =
                    QMessageBox::question(
                        this,
                        QString("Copy Files"),
                        QString("Do you wish to copy the file "
                                "into the local project folder?"),
                        (   QMessageBox::Yes |
                            QMessageBox::No |
                            QMessageBox::YesToAll |
                            QMessageBox::NoToAll ),
                        QMessageBox::No );

                doCopy = result & (QMessageBox::Yes | QMessageBox::YesToAll);

                if ( (result == QMessageBox::YesToAll) ||
                     (result == QMessageBox::NoToAll) )
                     copyChoice = result;
            }

            if (doCopy)
            {
                if (alreadyLocal)
                {
                    filename = fileInfo.fileName();
                }
                else if (!CopyFileToLocalPath(*fileIt, filename))
                {
                    QMessageBox::warning(
                        this,
                        QString("Copy Failed"),
                        QString("An error occurred and the file was not copied.\n"
                                "Importing from original location.") );
                }
            }
            emit ImportRequested(title, filename);
        }
    }
}

void FileSelectionDlg::DeleteSelectedFiles()
{
    QModelIndexList selected =
        m_fileList->selectionModel()->selectedIndexes();

    for ( QModelIndexList::iterator it = selected.begin();
          it != selected.end();
          it++ )
    {
        delete (*it).data(Qt::UserRole).value<I_TitleCarrier*>();
    }
}

void FileSelectionDlg::RenameSelectedFiles()
{
    QModelIndexList selected =
        m_fileList->selectionModel()->selectedIndexes();

    for ( QModelIndexList::iterator it = selected.begin();
          it != selected.end();
          it++ )
    {
        QString newTitle;
        GetTitleForFile("", newTitle);
        A_SoundImport* import = dynamic_cast<A_SoundImport*>(
            (*it).data(Qt::UserRole).value<I_TitleCarrier*>()
            );
        if (import != NULL)
            import->SetTitle(newTitle);
    }
}

void FileSelectionDlg::ReimportSelectedFiles()
{
    QModelIndexList selected =
        m_fileList->selectionModel()->selectedIndexes();

    for ( QModelIndexList::iterator it = selected.begin();
          it != selected.end();
          it++ )
    {
        QString filename;
        bool valid;

        do
        {
            GetFilename(filename);

            valid = true;
            const QList<A_SoundImport*>& importList = m_importMgr->ImportList();
            for ( QList<A_SoundImport*>::const_iterator cIt = importList.begin();
                  cIt != importList.end();
                  cIt++ )
            {
                if ((*cIt)->Filename() == filename)
                {
                    QMessageBox::information(
                        this,
                        QString("Duplicate import"),
                        QString("The file\n") +
                            (*cIt)->Filename() +
                            QString("\nhas already been imported as\n") +
                            (*cIt)->Title() +
                            QString("\nand must be rechosen.") );

                    valid = false;
                    break;
                }
            }
        } while (!valid);

        A_SoundImport* import = dynamic_cast<A_SoundImport*>(
            (*it).data(Qt::UserRole).value<I_TitleCarrier*>()
            );
        if (import != NULL)
            import->ReimportFrom(filename);
    }
}

void FileSelectionDlg::UpdateSelectionButtons()
{
    bool cond = (m_fileList->selectionModel()->selectedIndexes().count() == 0);

    m_deleteBtn->setEnabled(!cond);
    m_renameBtn->setEnabled(!cond);
    m_reimportBtn->setEnabled(!cond);
}

void FileSelectionDlg::UpdateList()
{
    m_importListModel->setList(m_importMgr->ImportList());
}

void FileSelectionDlg::RemoveMgr()
{
    setEnabled(false);
    m_importMgr = NULL;
}

void FileSelectionDlg::GetFileList(QStringList& fileList)
{
    fileList =
        QFileDialog::getOpenFileNames(
            this,
            QString("Import sounds"),
            m_importMgr->ProjectPath(),
            QString("Sound files ("
                        "*.mp3;"
                        "*.mp2;"
                        "*.mp1;"
                        "*.ogg;"
                        "*.wav;"
                        "*.aif;"
                        "*.aiff;"
                        "*.aifc)") );
}

void FileSelectionDlg::GetFilename(QString& filename)
{
    filename =
        QFileDialog::getOpenFileName(
            this,
            QString("Import sound"),
            QString(),
            QString("Sound files ("
                        "*.mp3;"
                        "*.mp2;"
                        "*.mp1;"
                        "*.ogg;"
                        "*.wav;"
                        "*.aif;"
                        "*.aiff;"
                        "*.aifc)") );
}

void FileSelectionDlg::FilterFileList(QStringList& fileList)
{
    const QList<A_SoundImport*>& importList = m_importMgr->ImportList();
    for ( QList<A_SoundImport*>::const_iterator it = importList.begin();
          it != importList.end();
          it++ )
    {
        if (fileList.contains((*it)->Filename()))
        {
            QMessageBox::information(
                this,
                QString("Duplicate import"),
                QString("The file\n") +
                    (*it)->Filename() +
                    QString("\nhas already been imported as\n") +
                    (*it)->Title() +
                    QString("\nand will be ignored.") );

            fileList.removeAt(fileList.lastIndexOf( (*it)->Filename() ));
        }
    }
}

bool FileSelectionDlg::GetTitleForFile(const QString& filename, QString& title)
{
    const QStringList& titleList = m_importMgr->TitleList();
    while (true)
    {
        if ( !ShowTitleDlg(filename, title) )
        {
            return false;
        }

        if ( !titleList.contains(title) )
        {
            return true;
        }

        QMessageBox::critical(
            this,
            QString("Title in use"),
            QString("That title is already in use.\nPlease choose another.") );
    }
}

bool FileSelectionDlg::ShowTitleDlg(const QString& filename, QString& title)
{
    Ui::TitleDlgUi dlgLayout;
    QDialog dlg;
    dlgLayout.setupUi(&dlg);

    QFileInfo fileInfo(filename);
    dlgLayout.m_filenameLbl->setText(fileInfo.fileName());

    if ( !dlg.exec() )
    {
        return false;
    }

    if ( dlgLayout.m_titleEdit->text() == "" )
    {
        title = fileInfo.absoluteFilePath();
        return true;
    }

    title = dlgLayout.m_titleEdit->text();
    return true;
}

bool FileSelectionDlg::CopyFileToLocalPath(const QString& filename, QString& newFilename)
{
    const QString& localPath = m_importMgr->ProjectPath();

    if (localPath == "")
        return false;

    QDir localDir(localPath);
    QFile target(filename);
    QFileInfo fileInfo(target);
    if (!fileInfo.exists())
        return false;

    QString newPath = localDir.absoluteFilePath(fileInfo.fileName());
    if (newPath == filename)
    {
        newFilename = fileInfo.fileName();
        return true;
    }

    QFileInfo newFileInfo(newPath);
    if (newFileInfo.exists())
    {
        if ( QMessageBox::No ==
             QMessageBox::question(
                this,
                QString("Overwrite file?"),
                (   QString("'") +
                    newPath +
                    QString("' already exists.\n"
                            "Do you want to overwrite it?") ),
                ( QMessageBox::Yes | QMessageBox::No ),
                QMessageBox::No ) )
        {
            newFilename = "";
            return true;
        }
        else
        {
            QFile doomed(newPath);
            if (!doomed.remove())
                return false;
        }
    }
    if (!target.copy(newPath))
        return false;

    newFilename = fileInfo.fileName();
    return true;
}
