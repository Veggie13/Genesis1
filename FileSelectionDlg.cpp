#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

#include "TitleDlgUi.h"

#include "FileSelectionDlg.h"


FileSelectionDlg::FileSelectionDlg(QWidget* parent)
:   QDialog(parent),
    m_fileMap(),
    m_fileMapModel(&m_fileMap)
{
    setupUi(this);
    m_fileList->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_fileList->setModel(&m_fileMapModel);

    connect( m_newBtn,    SIGNAL( clicked()                ),
             this,        SLOT  ( ImportFiles()            ) );
    connect( m_deleteBtn, SIGNAL( clicked()                ),
             this,        SLOT  ( DeleteSelectedFiles()    ) );
    connect( m_renameBtn, SIGNAL( clicked()                ),
             this,        SLOT  ( RenameSelectedFiles()    ) );
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

const QMap<QString, QString>& FileSelectionDlg::GetFileMap()
{
    return m_fileMap;
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

void FileSelectionDlg::ImportFiles()
{
    QStringList newFiles =
        QFileDialog::getOpenFileNames(
            this,
            QString("Import sounds"),
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

    for ( QMap<QString, QString>::iterator it = m_fileMap.begin();
          it != m_fileMap.end();
          it++ )
    {
        if (newFiles.contains(it.value()))
        {
            QMessageBox::information(
                this,
                QString("Duplicate import"),
                QString("The file\n") +
                    it.value() +
                    QString("\nhas already been imported as\n") +
                    it.key() +
                    QString("\nand will be ignored.") );

            newFiles.removeAt(newFiles.lastIndexOf( it.value() ));
        }
    }

    for ( QStringList::iterator fileIt = newFiles.begin();
          fileIt != newFiles.end();
          fileIt++ )
    {
        QString title;
        QMap<QString, QString>::const_iterator checker;
        bool import = true;
        while (true)
        {
            if ( !GetTitleForFile(*fileIt, title) )
            {
                import = false;
                break;
            }

            checker = m_fileMap.find(title);
            if (checker == m_fileMap.end())
            {
                break;
            }

            QMessageBox::critical(
                this,
                QString("Title in use"),
                QString("That title is already in use.\nPlease choose another.") );
        }

        if (import)
            emit ImportRequested(title, *fileIt);
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
{/*
    QModelIndexList selected =
        m_fileList->selectionModel()->selectedIndexes();

    for ( QModelIndexList::iterator it = selected.begin();
          it != selected.end();
          it++ )
    {
        emit DeleteRequested( (*it).data().toString() );
    }*/
}

bool FileSelectionDlg::GetTitleForFile(const QString& filename, QString& title)
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
