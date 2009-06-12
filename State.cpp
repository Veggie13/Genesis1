#include "BackgroundCtrl.qoh"
#include "MusicCtrl.qoh"
#include "RandomCtrl.qoh"
#include "Soundboard.qoh"

#include "State.qoh"


State::State(const QDomElement& state, QObject* parent)
:   QObject(parent),
    m_music(NULL),
    m_background(NULL),
    m_random(NULL),
    m_sndboard(NULL)
{
    if (state.isNull())
    {
        m_music = new MusicCtrl;
        m_background = new BackgroundCtrl;
        m_random = new RandomCtrl;
        m_sndboard = new Soundboard;
    }
    else
    {
        for( QDomNode n = state.firstChild();
             !n.isNull();
             n = n.nextSibling() )
        {
            QDomElement child = n.toElement();
            if ( child.isNull() )
                continue;

            if (child.tagName() == "music" && !m_music)
                m_music = new MusicCtrl(child);
            else if (child.tagName() == "background" && !m_background)
                m_background = new BackgroundCtrl(child);
            else if (child.tagName() == "random" && !m_random)
                m_random = new RandomCtrl(child);
            else if (child.tagName() == "soundboard" && !m_sndboard)
                m_sndboard = new Soundboard(child);
        }
    }

    connect(m_music,      SIGNAL( Modified() ), this, SIGNAL( Modified() ));
    connect(m_background, SIGNAL( Modified() ), this, SIGNAL( Modified() ));
    connect(m_random,     SIGNAL( Modified() ), this, SIGNAL( Modified() ));
    connect(m_sndboard,   SIGNAL( Modified() ), this, SIGNAL( Modified() ));
}

State::~State()
{
    delete m_music;
    delete m_background;
    delete m_random;
    delete m_sndboard;
}

MusicCtrl* State::GetMusicController()
{
    return m_music;
}

BackgroundCtrl* State::GetBackgroundController()
{
    return m_background;
}

RandomCtrl* State::GetRandomController()
{
    return m_random;
}

Soundboard* State::GetSoundboard()
{
    return m_sndboard;
}

void State::WriteData(QDomElement& state)
{
    QDomDocument doc = state.ownerDocument();

    QDomElement music = doc.createElement("music");
    m_music->WriteData(music);
    state.appendChild(music);

    QDomElement background = doc.createElement("background");
    m_background->WriteData(background);
    state.appendChild(background);

    QDomElement random = doc.createElement("random");
    m_random->WriteData(random);
    state.appendChild(random);

    QDomElement sndboard = doc.createElement("soundboard");
    m_sndboard->WriteData(sndboard);
    state.appendChild(sndboard);
}

void State::RenameStreamObjects(const QString& title, const QString& newTitle)
{
    m_music->RenameSong(title, newTitle);
    m_background->RenameBackground(title, newTitle);
}

void State::RenameSampleObjects(const QString& title, const QString& newTitle)
{
    m_random->RenameRandom(title, newTitle);
    m_sndboard->RenameEntries(title, newTitle);
}
