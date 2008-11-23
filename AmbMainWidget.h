#ifndef AMBMAINWIDGET_H
#define AMBMAINWIDGET_H

#include "AmbMainWidgetUi.h"


namespace Ui
{
    class BackgroundCtrlUi;
    class MusicCtrlUi;
    class RandomCtrlUi;
}
class SoundboardLayout;
class State;

class AmbMainWidget : public QWidget, private Ui::AmbMainWidgetUi
{
    Q_OBJECT

public:
    AmbMainWidget(QWidget* parent=NULL);
    virtual ~AmbMainWidget();

    void Associate(State* newState);

    State* CurrentState();

public slots:
    void ExpandLeft(bool expand);

    void RemoveSelectedSong();
    void RemoveSelectedBackgroundEffects();
    void RemoveSelectedRandomEffects();

    void SelectSong(const QString& title);

signals:
    void AddSongSelected();
    void AddBackgroundSelected();
    void AddRandomSelected();
    void AddInstantSelected(int row, int col);

    void RemoveSongRequested(const QString& title);
    void RemoveBackgroundRequested(const QString& title);
    void RemoveRandomRequested(const QString& title);

    void SongChanged(const QString& title);
    void SongMuteToggled(bool mute);
    void SongVolumeChanged(int vol);

    void BackgroundMuteToggled(bool mute);
    void BackgroundVolumeChanged(int vol);
    void BackgroundInstanceMuteToggled(bool mute);
    void BackgroundInstanceVolumeChanged(int vol);

    void RandomMuteToggled(bool mute);
    void RandomVolumeChanged(int vol);
    void RandomInstanceMuteToggled(bool mute);
    void RandomInstanceVolumeChanged(int vol);
    void RandomPeriodChanged(int per);
    void RandomVarianceChanged(int var);

    void ExpandLeftToggled(bool expand);

private slots:
    void AddBackground();
    void AddRandom();
    void AddInstant(int row, int col);
    void RemoveInstant(int row, int col);

    void UpdateBackgroundControls();
    void UpdateRandomControls();

    void SetMusicMute();
    void SetBackgroundMute();
    void SetBackgroundSelectionMute();
    void SetRandomMute();
    void SetRandomSelectionMute();

    void OnCurrentStateDeletion();

private:
    Ui::BackgroundCtrlUi*   m_backgroundObj;
    Ui::MusicCtrlUi*        m_musicObj;
    Ui::RandomCtrlUi*       m_randomObj;
    SoundboardLayout*       m_sndboardObj;

    State* m_curState;

};

#endif
