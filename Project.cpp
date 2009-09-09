#include "ImportManagers.h"
#include "MasterCtrl.qoh"
#include "MusicCtrl.qoh"
#include "QException.h"
#include "Scene.qoh"
#include "StartableSound.qoh"
#include "State.qoh"

#include "Project.qoh"


Project::Project(QObject* parent)
:   QObject(parent),
    m_scenes(),
    m_curState(NULL),
    m_streamMgr(NULL),
    m_sampleMgr(NULL)
{
    m_streamMgr = new StreamImportManager;
    m_sampleMgr = new SampleImportManager;

    connect(m_streamMgr, SIGNAL( Modified() ), this, SIGNAL( Modified() ));
    connect(m_sampleMgr, SIGNAL( Modified() ), this, SIGNAL( Modified() ));
}

Project::~Project()
{
    QList<Scene*>::iterator it;
    for (it = m_scenes.begin(); it != m_scenes.end(); it++)
    {
        (*it)->disconnect(this);
        delete (*it);
    }

    delete m_streamMgr;
    delete m_sampleMgr;
}

const QList<Scene*>& Project::SceneList()
{
    return m_scenes;
}

A_ImportManager* Project::StreamManager()
{
    return m_streamMgr;
}

A_ImportManager* Project::SampleManager()
{
    return m_sampleMgr;
}

void Project::AddScene(Scene* newScene)
{
    if (newScene == NULL)
        throw QException("Programming Error: "
                         "Tried to add NULL Scene!");

    int index = m_scenes.lastIndexOf(newScene);
    if (-1 != index)
        throw QException("Programming Error: "
                         "Tried to add a Scene that was already present!");

    connect(newScene, SIGNAL( Modified()  ), this, SIGNAL( Modified()           ));
    connect(newScene, SIGNAL( destroyed() ), this, SLOT  ( RemoveDeletedScene() ));

    m_scenes.append(newScene);
    emit Modified();
}

State* Project::CurrentState()
{
    return m_curState;
}

void Project::SetCurrentState(State* newCurState)
{
    if (m_curState == newCurState)
        return;

    if (newCurState && -1 == m_scenes.lastIndexOf(newCurState->ParentScene()))
        throw QException("Programming Error: "
                         "Tried to set current state to something not in project.");

    bool sharedMusic = false;
    StartableSound* curSong;
    QList<A_SoundInstance*> sharedBg;
    if (m_curState)
    {
        MusicCtrl* curMusic = m_curState->GetMusicController();
        MasterCtrl* curBg = m_curState->GetBackgroundController();
        MasterCtrl* curRand = m_curState->GetRandomController();

        if (newCurState)
        {
            MusicCtrl* newMusic = newCurState->GetMusicController();
            MasterCtrl* newBg = newCurState->GetBackgroundController();

            sharedMusic = curMusic->SharesCurrentSongWith(*newMusic);
            sharedBg = curBg->SharedWith(*newBg);

            if (sharedMusic)
                curSong = curMusic->CurrentSong();
        }

        curMusic->Suspend();
        curBg->Suspend();
        curRand->Suspend();

        m_curState->disconnect(this);
    }

    if (newCurState)
    {
        connect(newCurState,    SIGNAL( AboutToDie()                ),
                this,           SLOT  ( RemoveDeletedCurrentState() ) );

        MusicCtrl* newMusic = newCurState->GetMusicController();
        MasterCtrl* newBg = newCurState->GetBackgroundController();
        MasterCtrl* newRand = newCurState->GetRandomController();

        newMusic->Resume();
        newBg->Resume();
        newRand->Resume();
    }

    m_curState = newCurState;
    emit CurrentStateChanged(newCurState);
}

void Project::RemoveDeletedScene()
{
    Scene* doomed = reinterpret_cast<Scene*>(sender());
    if (doomed == NULL)
        return;

    int index = m_scenes.lastIndexOf(doomed);
    if (-1 == index)
        return;

    m_scenes.removeAt(index);
    emit Modified();
}

void Project::RemoveDeletedCurrentState()
{
    SetCurrentState(NULL);
}
