#include <QDir>
#include <QFileInfo>

#include <bass_system.h>

#include "A_SoundImport.qoh"
#include "QException.h"

#include "A_ImportManager.qoh"


int A_ImportManager::g_refCount = 0;

A_ImportManager::A_ImportManager()
:   m_importList(),
    m_titleList(),
    m_fileList(),
    m_importMap(),
    m_copyLocal(false),
    m_projectPath("")
{
    if (g_refCount == 0)
        BASS::System::Get().Init(-1,44100,0,0,NULL);

    g_refCount++;
}

A_ImportManager::~A_ImportManager()
{
    for ( QList<A_SoundImport*>::iterator it = m_importList.begin();
          it != m_importList.end();
          it++ )
    {
        (*it)->disconnect(this);
        delete (*it);
    }

    g_refCount--;

    if (g_refCount == 0)
        BASS::System::Free();
}

const QList<A_SoundImport*>& A_ImportManager::ImportList()
{
    return m_importList;
}

const QStringList& A_ImportManager::TitleList()
{
    return m_titleList;
}

const QStringList& A_ImportManager::FileList()
{
    return m_fileList;
}

A_SoundImport* A_ImportManager::GetImport(const QString& title)
{
    A_SoundImport* retval = NULL;
    if (m_importMap.find(title) != m_importMap.end())
        retval = m_importMap[title];

    return retval;
}

void A_ImportManager::SetProjectPath(const QString& path)
{
    m_projectPath = path;
}

const QString& A_ImportManager::ProjectPath()
{
    return m_projectPath;
}

bool A_ImportManager::IsCopyLocalOn()
{
    return m_copyLocal;
}

A_SoundImport* A_ImportManager::ImportFile(const QString& title, const QString& filename)
{
    QString finalFilename = filename;
    QFileInfo fileInfo(filename);
    if (fileInfo.isRelative())
    {
        if (m_projectPath == "")
            throw QException("Programming error: "
                             "Cannot import relative path before saving!");

        QFileInfo projInfo(m_projectPath);
        finalFilename = projInfo.dir().absoluteFilePath(filename);
    }

    if (m_importMap.find(title) != m_importMap.end())
        throw QException("Programming error: "
                         "Tried to import using a repeat title!");

    A_SoundImport* newImport = InternalImport(title, finalFilename);
    if (newImport == NULL)
    {
        throw QException(
            QString("\"") +
            filename +
            QString("\" could not be imported.") );
    }
    else
    {
        m_importList.append(newImport);
        m_titleList.append(title);
        m_fileList.append(filename);
        m_importMap[title] = newImport;

        connect( newImport, SIGNAL( AboutToDie()        ),
                 this,      SLOT  ( OnImportDeleted()   ) );
        connect( newImport, SIGNAL( Renamed(const QString&, const QString&) ),
                 this,      SLOT  ( Rename(const QString&, const QString&)  ) );
        connect( newImport, SIGNAL( Reimported(const QString&, const QString&)  ),
                 this,      SLOT  ( ChangeFile(const QString&, const QString&)  ) );

        emit Modified();
    }

    return newImport;
}

void A_ImportManager::SetCopyLocal(bool copy)
{
    bool oldCopy = m_copyLocal;
    m_copyLocal = copy;
    if (!oldCopy && copy)
    {
        if (m_projectPath == "")
            throw QException("Programming error: "
                             "Cannot use relative path before saving!");

        QDir localPath(m_projectPath);
        QList<A_SoundImport*> externalFiles;
        for ( QList<A_SoundImport*>::iterator it = m_importList.begin();
              it != m_importList.end();
              it++ )
        {
            QString filename = (*it)->Filename();
            QFileInfo fileInfo(filename);
            if (filename == localPath.absoluteFilePath(fileInfo.fileName()))
            {
                int index = m_fileList.lastIndexOf(filename);
                if (index != -1)
                    m_fileList[index] = fileInfo.fileName();
            }
            else
                externalFiles.append(*it);
        }

        emit CopyLocalActivated(externalFiles);
        emit Modified();
    }
    else if (oldCopy && !copy)
    {
        for ( QList<A_SoundImport*>::iterator it = m_importList.begin();
              it != m_importList.end();
              it++ )
        {
            int index = m_fileList.lastIndexOf((*it)->Filename());
            if (index != -1)
                m_fileList[index] = (*it)->Filename();
        }

        emit Modified();
    }
}

void A_ImportManager::OnImportDeleted()
{
    A_SoundImport* doomed = dynamic_cast<A_SoundImport*>(sender());
    if (doomed == NULL)
        return;

    int index = m_titleList.lastIndexOf(doomed->Title());
    if (index != -1)
        m_titleList.removeAt(index);

    index = m_fileList.lastIndexOf(doomed->Filename());
    if (index != -1)
        m_fileList.removeAt(index);

    index = m_importList.lastIndexOf(doomed);
    if (index != -1)
        m_importList.removeAt(index);

    QMap<QString, A_SoundImport*>::iterator finder = m_importMap.find(doomed->Title());
    if (finder != m_importMap.end())
        m_importMap.erase(finder);
}

void A_ImportManager::Rename(const QString& oldTitle, const QString& newTitle)
{
    if (m_importMap.find(newTitle) != m_importMap.end())
        throw QException("Programmer error: "
                         "Tried to rename to an existing title!");

    int index = m_titleList.lastIndexOf(oldTitle);
    if (index != -1)
        m_titleList[index] = newTitle;

    QMap<QString, A_SoundImport*>::iterator finder = m_importMap.find(oldTitle);
    A_SoundImport* import = NULL;
    if (finder != m_importMap.end())
    {
        import = finder.value();
        m_importMap.erase(finder);
    }
    m_importMap[newTitle] = import;
}

void A_ImportManager::ChangeFile(const QString& oldFilename, const QString& newFilename)
{
    QString oldSearch = oldFilename;
    if (m_copyLocal)
    {
        if (m_projectPath == "")
            throw QException("Programming error: "
                             "Cannot use relative path before saving!");

        QDir localDir(m_projectPath);
        QFileInfo oldInfo(oldFilename);
        if (oldFilename == localDir.absoluteFilePath(oldInfo.fileName()))
            oldSearch = oldInfo.fileName();
    }

    int index = m_fileList.lastIndexOf(oldSearch);
    if (index == -1)
        return;

    m_fileList[index] = newFilename;
    if (m_copyLocal)
    {
        QDir localDir(m_projectPath);
        QFileInfo fileInfo(newFilename);
        if (newFilename == localDir.absoluteFilePath(fileInfo.fileName()))
            m_fileList[index] = fileInfo.fileName();
        else
            m_fileList[index] = newFilename;
    }
}
