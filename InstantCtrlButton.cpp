#include <QMouseEvent>

#include "InstantCtrlButtonMenu.qoh"
#include "InstantSound.qoh"

#include "InstantCtrlButton.qoh"


InstantCtrlButton::InstantCtrlButton(int row, int col, QWidget* parent)
:   QPushButton(parent),
    m_row(row),
    m_col(col),
    m_volume(100),
    m_assignment(NULL),
    m_popupMenu(NULL),
    m_swapping(false)
{
    connect(this, SIGNAL( clicked() ), this, SLOT( RequestSound() ));

    m_popupMenu = new InstantCtrlButtonMenu();
    connect(m_popupMenu->MoveAction(),      SIGNAL( activated()    ),
            this,                           SLOT  ( PerformSwap()  ) );
    connect(m_popupMenu->UnassignAction(),  SIGNAL( activated()    ),
            this,                           SLOT  ( Reset()        ) );
    connect(m_popupMenu->ReassignAction(),  SIGNAL( activated()    ),
            this,                           SLOT  ( RequestSound() ) );
}

InstantCtrlButton::~InstantCtrlButton()
{
    delete m_popupMenu;
}

void InstantCtrlButton::SetSound(const QString& title, InstantSound* sound)
{
    if (!sound || title == "")
        return;

    setText(title);

    disconnect(this, SIGNAL( clicked() ), 0, 0);
    disconnect(this, SIGNAL( PlaySound(int) ), 0, 0);
    if (m_assignment)
        m_assignment->disconnect(this);
    connect(this,  SIGNAL( clicked()      ), this,  SLOT( SignalPlay() ));
    connect(this,  SIGNAL( PlaySound(int) ), sound, SLOT( Play(int)    ));
    connect(sound, SIGNAL( destroyed()    ), this,  SLOT( Reset()      ));
    m_assignment = sound;
}

InstantSound* InstantCtrlButton::GetSound()
{
    return m_assignment;
}

void InstantCtrlButton::EnableSwapTarget(bool enable)
{
    m_swapping = enable;
}

void InstantCtrlButton::Reset()
{
    setText("");

    disconnect(this, SIGNAL( clicked() ), 0, 0);
    disconnect(this, SIGNAL( PlaySound(int) ), 0, 0);
    if (m_assignment)
    {
        m_assignment->disconnect(this);
        m_assignment = NULL;
    }
    connect(this, SIGNAL( clicked() ), this, SLOT( RequestSound() ));

    emit WasReset(m_row, m_col);
}

void InstantCtrlButton::SetVolume(int vol)
{
    if (vol < 0 || vol > 100)
        return;

    m_volume = vol;
}

void InstantCtrlButton::mouseReleaseEvent(QMouseEvent* evt)
{
    if (m_assignment && evt->button() == Qt::RightButton)
    {
        m_popupMenu->popup(evt->globalPos());
    }
    else
    {
        QPushButton::mouseReleaseEvent(evt);
    }
}

void InstantCtrlButton::RequestSound()
{
    if (m_swapping)
        emit SwapDestSelected(m_row, m_col);
    else
        emit SoundRequested(m_row, m_col);
}

void InstantCtrlButton::SignalPlay()
{
    if (m_swapping)
        emit SwapDestSelected(m_row, m_col);
    else
        emit PlaySound(m_volume * 100);
}

void InstantCtrlButton::PerformSwap()
{
    if (m_swapping)
        emit SwapDestSelected(m_row, m_col);
    else
        emit SwapInitiated(m_row, m_col);
}
