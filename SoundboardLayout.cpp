#include "InstantCtrlButton.qoh"
#include "QException.h"
#include "ResizeTableDlg.qoh"
#include "Soundboard.qoh"
#include "SoundboardInstance.h"

#include "SoundboardLayout.qoh"


SoundboardLayout::SoundboardLayout(QObject* parent)
:   QObject(parent),
    m_resizeDlg(NULL),
    m_curBoard(NULL),
    m_swapRow(0),
    m_swapCol(0),
    m_this(NULL)
{
}

SoundboardLayout::~SoundboardLayout()
{
    for (int nRow = 0; nRow < m_buttons.size(); ++nRow)
    for (int nCol = 0; nCol < m_buttons[nRow].size(); ++nCol)
    {
        delete m_buttons[nRow][nCol];
    }

    delete m_resizeDlg;
}

void SoundboardLayout::setupUiWithButtons(QWidget* w)
{
    SoundboardUi::setupUi(w);

    m_resizeDlg = new ResizeTableDlg(m_buttonTbl->rowCount(), m_buttonTbl->columnCount());
    Resize(m_buttonTbl->rowCount(), m_buttonTbl->columnCount());
    connect( m_resizeBtn, SIGNAL( clicked()            ),
             m_resizeDlg, SLOT  ( exec()               ) );
    connect( m_resizeDlg, SIGNAL( SizeChanged(int,int) ),
             this,        SLOT  ( Resize(int,int)      ) );

    connect( m_sndboardVolumeSld, SIGNAL( valueChanged(int)  ),
             this,                SIGNAL( VolumeChanged(int) ) );

    Resize(0,0);

    w->setEnabled(false);
    m_this = w;
}

void SoundboardLayout::Associate(Soundboard* sndboard)
{
    if (m_curBoard)
    {
        disconnect(m_curBoard);
        m_curBoard->disconnect(this);
    }
    Resize(0,0);

    m_curBoard = sndboard;
    if (!sndboard)
    {
        m_this->setEnabled(false);
        return;
    }

    m_this->setEnabled(true);
    Resize(sndboard->RowCount(), sndboard->ColCount());

    for (int row = 0; row < sndboard->RowCount(); ++row)
    for (int col = 0; col < sndboard->ColCount(); ++col)
    {
        SoundboardInstance* snd = sndboard->Entry(row, col);
        if (snd != NULL)
            AssignSoundToButton(row, col, snd);
    }

    m_sndboardVolumeSld->setValue(sndboard->Volume());

    connect( this,     SIGNAL( VolumeChanged(int)      ),
             sndboard, SLOT  ( SetVolume(int)          ) );
    connect( this,     SIGNAL( SizeChanged(int,int)    ),
             sndboard, SLOT  ( Resize(int,int)         ) );
    connect( this,     SIGNAL( SpecificSoundRequested(int,int,SoundboardInstance*)  ),
             sndboard, SLOT  ( AddEntry(int,int,SoundboardInstance*)                ) );
    connect( sndboard, SIGNAL( EntryAdded(int,int,SoundboardInstance*)          ),
             this,     SLOT  ( AssignSoundToButton(int,int,SoundboardInstance*) ) );
    connect( sndboard, SIGNAL( destroyed()             ),
             this,     SLOT  ( OnSoundboardDestroyed() ) );
}

void SoundboardLayout::AssignSoundToButton(
    int row,
    int col,
    SoundboardInstance* sound )
{
    if (row < 0 || row >= m_buttons.size() || col < 0 || col >= m_buttons[row].size())
        throw QException("Programming Error: "
                         "Tried to assign sound to a button outside the dimensions!");

    m_buttons[row][col]->SetSound(sound);
}

void SoundboardLayout::Resize(int rows, int cols)
{
    int nRow, nCol;

    m_buttonTbl->setRowCount(rows);
    m_buttonTbl->setColumnCount(cols);

    int oldRows = m_buttons.size();
    for (nRow = rows; nRow < oldRows; ++nRow)
    {
        int oldCols = m_buttons[nRow].size();
        for (nCol = 0; nCol < oldCols; ++nCol)
        {
            delete m_buttons[nRow][nCol];
            m_buttons[nRow][nCol] = NULL;
        }
    }

    m_buttons.resize(rows);

    for (nRow = 0; nRow < rows; ++nRow)
    {
        int oldCols = m_buttons[nRow].size();
        for (nCol = cols; nCol < oldCols; ++nCol)
        {
            delete m_buttons[nRow][nCol];
            m_buttons[nRow][nCol] = NULL;
        }

        m_buttons[nRow].resize(cols);

        for (nCol = oldCols; nCol < cols; ++nCol)
        {
            InstantCtrlButton* btn = new InstantCtrlButton(nRow, nCol);
            m_buttons[nRow][nCol] = btn;
            m_buttonTbl->setCellWidget(nRow, nCol, btn);

            connect( btn,  SIGNAL( SoundRequested(int,int)      ),
                     this, SIGNAL( SoundRequested(int,int)      ) );
            connect( btn,  SIGNAL( WasReset(int,int)            ),
                     this, SIGNAL( SoundRemoved(int,int)        ) );
            connect( btn,  SIGNAL( SwapRequested(int,int)       ),
                     this, SIGNAL( SwapInitiated()              ) );
            connect( btn,  SIGNAL( SwapRequested(int,int)       ),
                     this, SLOT  ( InitiateSwap(int,int)        ) );
            connect( btn,  SIGNAL( SwapDestSelected(int,int)    ),
                     this, SLOT  ( CompleteSwap(int,int)        ) );
            connect( this, SIGNAL( SwapInitiated()              ),
                     btn,  SLOT  ( EnableSwapTarget()           ) );
            connect( this, SIGNAL( SwapCompleted()              ),
                     btn,  SLOT  ( DisableSwapTarget()          ) );
        }
    }

    m_resizeDlg->SetDimensions(rows, cols);
    emit SizeChanged(rows, cols);
}

void SoundboardLayout::InitiateSwap(int row, int col)
{
    m_swapRow = row;
    m_swapCol = col;
}

void SoundboardLayout::CompleteSwap(int row, int col)
{
    emit SwapCompleted();

    if (m_swapRow == row && m_swapCol == col)
        return;

    SoundboardInstance* src = m_buttons[m_swapRow][m_swapCol]->Sound();
    SoundboardInstance* dest = m_buttons[row][col]->Sound();

    if (src == dest)
        return;

    emit SoundRemoved(m_swapRow, m_swapCol);
    emit SoundRemoved(row, col);

    emit SpecificSoundRequested(m_swapRow, m_swapCol, dest);
    emit SpecificSoundRequested(row, col, src);

    Associate(m_curBoard);
}

void SoundboardLayout::OnSoundboardDestroyed()
{
    disconnect(m_curBoard);
    m_curBoard = NULL;

    Resize(0,0);
}
