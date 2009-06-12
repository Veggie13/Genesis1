#include "InstantCtrlButton.qoh"
#include "ResizeTableDlg.qoh"
#include "Soundboard.qoh"

#include "SoundboardLayout.qoh"


SoundboardLayout::SoundboardLayout(QObject* parent)
:   QObject(parent),
    m_resizeDlg(NULL),
    m_curBoard(NULL),
    m_swapRow(0),
    m_swapCol(0)
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
    Resize(m_buttonTbl->rowCount(), m_buttonTbl->columnCount());

    m_resizeDlg = new ResizeTableDlg(m_buttonTbl->rowCount(), m_buttonTbl->columnCount());
    connect( m_resizeBtn, SIGNAL( clicked()            ),
             m_resizeDlg, SLOT  ( exec()               ) );
    connect( m_resizeDlg, SIGNAL( SizeChanged(int,int) ),
             this,        SLOT  ( Resize(int,int)      ) );

    connect( m_sndboardVolumeSld, SIGNAL( valueChanged(int)  ),
             this,                SIGNAL( VolumeChanged(int) ) );

    Resize(0,0);
}

void SoundboardLayout::Associate(Soundboard* sndboard)
{
    if (m_curBoard)
    {
        disconnect(this, 0, m_curBoard, 0);
        disconnect(m_curBoard, 0, this, 0);
    }
    Resize(0, 0);

    m_curBoard = sndboard;
    if (!sndboard)
        return;

    Resize(sndboard->GetRowCount(), sndboard->GetColCount());

    for (int row = 0; row < sndboard->GetRowCount(); ++row)
    for (int col = 0; col < sndboard->GetColCount(); ++col)
    {
        InstantSound* snd = sndboard->GetEntry(row, col);
        if (snd)
            AssignSoundToButton(row, col, sndboard->GetTitle(row, col), snd);
    }

    m_sndboardVolumeSld->setValue(sndboard->GetVolume());

    connect( this,     SIGNAL( VolumeChanged(int)      ),
             sndboard, SLOT  ( SetVolume(int)          ) );
    connect( this,     SIGNAL( SizeChanged(int,int)    ),
             sndboard, SLOT  ( Resize(int,int)         ) );
    connect( this,     SIGNAL( SpecificSoundRequested(int,int,const QString&)   ),
             sndboard, SLOT  ( AddEntry(int,int,const QString&)                 ) );
    connect( sndboard, SIGNAL( destroyed()             ),
             this,     SLOT  ( OnSoundboardDestroyed() ) );
}

bool SoundboardLayout::AssignSoundToButton(
    int row,
    int col,
    const QString& title,
    InstantSound* sound )
{
    if (row < 0 || row >= m_buttons.size() || col < 0 || col >= m_buttons[row].size())
        return false;

    if (m_buttons[row][col]->text() != "")
        return false;

    m_buttons[row][col]->SetSound(title, sound);
    return true;
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

            btn->SetVolume(m_sndboardVolumeSld->value());

            connect( this, SIGNAL( VolumeChanged(int)           ),
                     btn,  SLOT  ( SetVolume(int)               ) );
            connect( btn,  SIGNAL( SoundRequested(int,int)      ),
                     this, SIGNAL( SoundRequested(int,int)      ) );
            connect( btn,  SIGNAL( WasReset(int,int)            ),
                     this, SIGNAL( SoundRemoved(int,int)        ) );
            connect( btn,  SIGNAL( SwapInitiated(int,int)       ),
                     this, SLOT  ( InitiateSwap(int,int)        ) );
            connect( btn,  SIGNAL( SwapDestSelected(int,int)    ),
                     this, SLOT  ( CompleteSwap(int,int)        ) );
        }
    }

    emit SizeChanged(rows, cols);
}

void SoundboardLayout::InitiateSwap(int row, int col)
{
    m_swapRow = row;
    m_swapCol = col;

    for (int nRow = 0; nRow < m_buttons.size(); ++nRow)
    for (int nCol = 0; nCol < m_buttons[nRow].size(); ++nCol)
    {
        m_buttons[nRow][nCol]->EnableSwapTarget(true);
    }
}

void SoundboardLayout::CompleteSwap(int row, int col)
{
    for (int nRow = 0; nRow < m_buttons.size(); ++nRow)
    for (int nCol = 0; nCol < m_buttons[nRow].size(); ++nCol)
    {
        m_buttons[nRow][nCol]->EnableSwapTarget(false);
    }

    if (m_swapRow == row && m_swapCol == col)
        return;

    QString srcTitle = m_buttons[m_swapRow][m_swapCol]->text();
    QString destTitle = m_buttons[row][col]->text();

    if (srcTitle == destTitle)
        return;

    emit SoundRemoved(m_swapRow, m_swapCol);
    emit SoundRemoved(row, col);

    emit SpecificSoundRequested(m_swapRow, m_swapCol, destTitle);
    emit SpecificSoundRequested(row, col, srcTitle);

    Associate(m_curBoard);
}

void SoundboardLayout::OnSoundboardDestroyed()
{
    m_curBoard = NULL;
}
