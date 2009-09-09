#include "MasterCtrl.qoh"
#include "MusicCtrl.qoh"
#include "Scene.qoh"
#include "Soundboard.qoh"

#include "State.qoh"


State::State(const QString& title, Scene* parent)
:   QObject(parent),
    m_music(NULL),
    m_background(NULL),
    m_random(NULL),
    m_sndboard(NULL),
    m_title(title),
    m_parent(parent)
{
    m_music = new MusicCtrl;
    m_background = new MasterCtrl;
    m_random = new MasterCtrl;
    m_sndboard = new Soundboard;

    connect(m_music,      SIGNAL( Modified() ), this, SIGNAL( Modified() ));
    connect(m_background, SIGNAL( Modified() ), this, SIGNAL( Modified() ));
    connect(m_random,     SIGNAL( Modified() ), this, SIGNAL( Modified() ));
    connect(m_sndboard,   SIGNAL( Modified() ), this, SIGNAL( Modified() ));
}

State::~State()
{
    emit AboutToDie();

    delete m_music;
    delete m_background;
    delete m_random;
    delete m_sndboard;
}

const QString& State::Title()
{
    return m_title;
}

void State::SetTitle(const QString& title)
{
    m_title = title;
    emit Modified();
}

Scene* State::ParentScene()
{
    return m_parent;
}

MusicCtrl* State::GetMusicController()
{
    return m_music;
}

MasterCtrl* State::GetBackgroundController()
{
    return m_background;
}

MasterCtrl* State::GetRandomController()
{
    return m_random;
}

Soundboard* State::GetSoundboard()
{
    return m_sndboard;
}
