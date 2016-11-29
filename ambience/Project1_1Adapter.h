#ifndef PROJECT1_1ADAPTER_H
#define PROJECT1_1ADAPTER_H

#include "AmbienceVersion.h"


class Project1_1Adapter
{
public:
    struct Music1_1
    {
        bool m_muted;
        unsigned int m_volume;
        QList<QString> m_playlist;
    };

    struct BackgroundInstance1_1
    {
        bool m_muted;
        unsigned int m_volume;
        QString m_title;
    };

    struct Background1_1
    {
        bool m_muted;
        unsigned int m_volume;

    };

    struct Random1_1
    {
    };

    struct Soundboard1_1
    {
    };

    struct State1_1
    {
        QString m_title;
        Music1_1        m_music;
        Background1_1   m_background;
        Random1_1       m_random;
        Soundboard1_1   m_sndboard;
    };

    struct Scene1_1
    {
        QString m_title;
        QList<State1_1> m_states;
    };

    struct Project1_1
    {
        QList<QPair<QString, QString> > m_limports;
        QList<QPair<QString, QString> > m_simports;
        QList<Scene1_1> m_scenes;
    };

    Project1_1* LoadProjectFromElement(const QDomElement& root);

private:
    void LoadStreamImportList(
        Project* parent,
        const QDomElement& longImports );
    void LoadSampleImportList(
        Project* parent,
        const QDomElement& shortImports );
    void LoadProjectBody(Project* proj, const QDomElement& project);
    void LoadScene(
        Project* proj,
        Scene* newScene,
        const QDomElement& scene );
    void LoadState(
        Project* proj,
        State* newState,
        const QDomElement& state );
    void LoadMusicData(
        Project* proj,
        State* parent,
        const QDomElement& musicData );
    void LoadBackgroundData(
        Project* proj,
        State* parent,
        const QDomElement& bgData );
    void LoadRandomData(
        Project* proj,
        State* parent,
        const QDomElement& randData );
    void LoadSoundboardData(
        Project* proj,
        State* parent,
        const QDomElement& sndboardData );

    static const AmbienceVersion VERSION_1_1;

};

#endif
