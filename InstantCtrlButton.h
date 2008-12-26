#ifndef INSTANTCTRLBUTTON_H
#define INSTANTCTRLBUTTON_H

#include <QPushButton>

class InstantCtrlButtonMenu;
class InstantSound;


class InstantCtrlButton : public QPushButton
{
    Q_OBJECT

public:
    InstantCtrlButton(int row, int col, QWidget* parent=NULL);
    virtual ~InstantCtrlButton();

    void SetSound(const QString& title, InstantSound* sound);
    InstantSound* GetSound();

    void EnableSwapTarget(bool enable);

public slots:
    void Reset();
    void SetVolume(int vol);

signals:
    void PlaySound(int vol);
    void SoundRequested(int row, int col);
    void WasReset(int row, int col);
    void SwapInitiated(int row, int col);
    void SwapDestSelected(int row, int col);

protected slots:
    virtual void mouseReleaseEvent(QMouseEvent* evt);

private slots:
    void RequestSound();
    void SignalPlay();
    void PerformSwap();

private:
    int m_row;
    int m_col;

    int m_volume;

    InstantSound* m_assignment;

    InstantCtrlButtonMenu* m_popupMenu;

    bool m_swapping;

};

#endif
