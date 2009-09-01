#include <QMouseEvent>

#include "InstantCtrlButtonMenu.qoh"
#include "SoundboardInstance.h"

#include "InstantCtrlButton.qoh"


InstantCtrlButton::InstantCtrlButton(int row, int col, QWidget* parent)
:   QPushButton(parent),
    m_row(row),
    m_col(col),
    m_assignment(NULL),
    m_popupMenu(NULL),
    m_swapping(false)
{
    connect(this, SIGNAL( clicked() ), this, SLOT( RequestSound() ));

    m_popupMenu = new InstantCtrlButtonMenu();
    connect(m_popupMenu->MoveAction(),      SIGNAL( triggered()    ),
            this,                           SLOT  ( PerformSwap()  ) );
    connect(m_popupMenu->UnassignAction(),  SIGNAL( triggered()    ),
            this,                           SLOT  ( Reset()        ) );
    connect(m_popupMenu->ReassignAction(),  SIGNAL( triggered()    ),
            this,                           SLOT  ( RequestSound() ) );
}

InstantCtrlButton::~InstantCtrlButton()
{
    delete m_popupMenu;
}

void InstantCtrlButton::SetSound(SoundboardInstance* sound)
{
    disconnect(this, SIGNAL( clicked() ), 0, 0);
    disconnect(this, SIGNAL( PlaySound() ), 0, 0);
    if (m_assignment)
        m_assignment->disconnect(this);

    if (sound == NULL)
    {
        Reset();
        return;
    }

    setText(sound->Title());

    connect(this,  SIGNAL( clicked()   ), this,  SLOT( SignalPlay() ));
    connect(this,  SIGNAL( PlaySound() ), sound, SLOT( Play()       ));
    connect(sound, SIGNAL( Renamed(const QString&, const QString&)  ),
            this,  SLOT  ( UpdateTitle()                            ));
    connect(sound, SIGNAL( destroyed() ), this,  SLOT( Reset()      ));
    m_assignment = sound;
}

SoundboardInstance* InstantCtrlButton::Sound()
{
    return m_assignment;
}

void InstantCtrlButton::EnableSwapTarget()
{
    m_swapping = true;
}

void InstantCtrlButton::DisableSwapTarget()
{
    m_swapping = false;
}

void InstantCtrlButton::Reset()
{
    setText("");

    m_assignment = NULL;
    connect(this, SIGNAL( clicked() ), this, SLOT( RequestSound() ));

    emit WasReset(m_row, m_col);
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
        emit PlaySound();
}

void InstantCtrlButton::PerformSwap()
{
    if (m_swapping)
        emit SwapDestSelected(m_row, m_col);
    else
        emit SwapRequested(m_row, m_col);
}

void InstantCtrlButton::UpdateTitle()
{
    if (m_assignment != NULL)
        setText(m_assignment->Title());
    else
        setText("");
}
