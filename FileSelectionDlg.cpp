#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

#include "TitleDlgUi.h"

#include "FileSelectionDlg.qoh"


FileSelectionDlg::FileSelectionDlg(QWidget* parent)
:   QDialog(parent),
    m_fileMap(),
    m_fileMapModel(&m_fileMap),
    m_copyLocal(false),
    m_localPath("")
{
    setupUi(this);
    m_fileList->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_fileList->setModel(&m_fileMapModel);

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
}

void FileSelectionDlg::AddFile(const QString& title, const QString& filename)
{
    m_fileMap[title] = filename;
    m_fileList->reset();
}

void FileSelectionDlg::DeleteFile(const QString& title)
{
    QMap<QString, QString>::iterator doomed =
        m_fileMap.find(title);

    if (doomed != m_fileMap.end())
        m_fileMap.erase(doomed);

    m_fileList->reset();
}

void FileSelectionDlg::RenameFile(const QString& title, const QString& newTitle)
{
    AddFile(newTitle, m_fileMap[title]);
    DeleteFile(title);
}

void FileSelectionDlg::ReimportFile(const QString& title, const QString& newFilename)
{
    m_fileMap[title] = newFilename;
}

const QMap<QString, QString>& FileSelectionDlg::GetFileMap()
{
    return m_fileMap;
}

void FileSelectionDlg::SetLocalPath(const QString& path)
{
    m_localPath = path;
}

QString FileSelectionDlg::ExecSingleSelection()
{
    m_fileList->setSelectionMode(QAbstractItemView::SingleSelection);

    if (exec() == QDialog::Accepted)
    {
        QModelIndexList selected =
            m_fileList->selectionModel()->selectedIndexes();

        if (selected.size() < 1)
            return "";
        else
            return selected[0].data().toString();
    }
    else
        return "";
}

QStringList FileSelectionDlg::ExecMultiSelection()
{
    m_fileList->setSelectionMode(QAbstractItemView::ExtendedSelection);

    QStringList retlist;
    if (exec() == QDialog::Accepted)
    {
        QModelIndexList selected =
            m_fileList->selectionModel()->selectedIndexes();

        for ( QModelIndexList::iterator it = selected.begin();
              it != selected.end();
              it++ )
        {
            retlist << (*it).data().toString();
        }
    }

    return retlist;
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

void FileSelectionDlg::SetCopyLocal(bool copy)
{
    if (!m_copyLocal && copy)
    {
        QMessageBox::StandardButton result = QMessageBox::No;
        QStringList externalFiles;
        for ( QMap<QString,QString>::iterator it = m_fileMap.begin();
              it != m_fileMap.end();
              it++ )
        {
            QFileInfo fileInfo(*it);
            if (fileInfo.isAbsolute())
                externalFiles.append(it.key());
        }

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
            for ( QStringList::iterator fileIt = externalFiles.begin();
                  fileIt != externalFiles.end();
                  fileIt++ )
            {
                QString newFilename;
                if (!CopyFileToLocalPath(m_fileMap[*fileIt], newFilename))
                {
                    QMessageBox::warning(
                        this,
                        QString("Copy Failed"),
                        (   QString("An error occurred and the file '") +
                            (*fileIt) +
                            QString("' was not copied.\n") ) );
                }
                else
                {
                    emit ReimportRequested(*fileIt, newFilename);
                }
            }
        }
    }

    m_copyLocal = copy;
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
            QDir localPath(m_localPath);
            bool alreadyLocal =
                filename == localPath.absoluteFilePath(fileInfo.fileName());

            if (m_copyLocal && !alreadyLocal && copyChoice == QMessageBox::NoButton)
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
        emit DeleteRequested( (*it).data().toString() );
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
        emit RenameRequested( (*it).data().toString(), newTitle );
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
            for ( QMap<QString, QString>::iterator it = m_fileMap.begin();
                  it != m_fileMap.end();
                  it++ )
            {
                if (it.value() == filename)
                {
                    QMessageBox::information(
                        this,
                        QString("Duplicate import"),
                        QString("The file\n") +
                            it.value() +
                            QString("\nhas already been imported as\n") +
                            it.key() +
                            QString("\nand must be rechosen.") );

                    valid = false;
                    break;
                }
            }
        } while (!valid);

        emit ReimportRequested( (*it).data().toString(), filename );
    }
}

void FileSelectionDlg::UpdateSelectionButtons()
{
    bool cond = (m_fileList->selectionModel()->selectedIndexes().count() == 0);

    m_deleteBtn->setEnabled(!cond);
    m_renameBtn->setEnabled(!cond);
    m_reimportBtn->setEnabled(!cond);
}

void FileSelectionDlg::GetFileList(QStringList& fileList)
{
    fileList =
        QFileDialog::getOpenFileNames(
            this,
            QString("Import sounds"),
            m_localPath,
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
    for ( QMap<QString, QString>::iterator it = m_fileMap.begin();
          it != m_fileMap.end();
          it++ )
    {
        if (fileList.contains(it.value()))
        {
            QMessageBox::information(
                this,
                QString("Duplicate import"),
                QString("The file\n") +
                    it.value() +
                    QString("\nhas already been imported as\n") +
                    it.key() +
                    QString("\nand will be ignored.") );

            fileList.removeAt(fileList.lastIndexOf( it.value() ));
        }
    }
}

bool FileSelectionDlg::GetTitleForFile(const QString& filename, QString& title)
{
    QMap<QString, QString>::const_iterator checker;
    while (true)
    {
        if ( !ShowTitleDlg(filename, title) )
        {
            return false;
        }

        checker = m_fileMap.find(title);
        if (checker == m_fileMap.end())
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
    if (m_localPath == "")
        return false;

    QDir localDir(m_localPath);
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

    emit RefreshRequested(newPath);
    newFilename = fileInfo.fileName();
    return true;
}
