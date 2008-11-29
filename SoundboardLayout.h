#ifndef SOUNDBOARDLAYOUT_H
#define SOUNDBOARDLAYOUT_H

#include <QVector>

#include "SoundboardUi.h"

class InstantCtrlButton;
class InstantSound;
class ResizeTableDlg;
class Soundboard;


class SoundboardLayout : public QObject, public Ui::SoundboardUi
{
    Q_OBJECT

public:
    SoundboardLayout(QObject* parent=NULL);
    virtual ~SoundboardLayout();
    void setupUiWithButtons(QWidget* w);

    void Associate(Soundboard* sndboard);

    bool AssignSoundToButton(int row, int col, const QString& title, InstantSound* sound);

public slots:
    void Resize(int rows, int cols);

signals:
    void SoundRemoved(int row, int col);
    void SoundRequested(int row, int col);
    void SizeChanged(int rows, int cols);
    void VolumeChanged(int vol);

private slots:
    void OnSoundboardDestroyed();

private:
    typedef QVector<InstantCtrlButton*> ButtonRow;
    typedef QVector<ButtonRow> ButtonTable;
    ButtonTable m_buttons;

    ResizeTableDlg* m_resizeDlg;

    Soundboard* m_curBoard;

};

#endif
