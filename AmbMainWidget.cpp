#include <QDomElement>
#include <QMessageBox>
#include <QTimer>

#include <cmath>
#include <cstdlib>

#include "Background.h"
#include "BackgroundCtrl.h"
#include "BackgroundCtrlUi.h"
#include "MusicCtrl.h"
#include "MusicCtrlUi.h"
#include "RandomCtrl.h"
#include "RandomCtrlUi.h"
#include "RandomSound.h"
#include "Soundboard.h"
#include "SoundboardLayout.h"
#include "State.h"

#include "AmbMainWidget.h"


AmbMainWidget::AmbMainWidget(QWidget* parent)
:   QWidget(parent),
    m_backgroundObj(NULL),
    m_musicObj(NULL),
    m_randomObj(NULL),
    m_sndboardObj(NULL),
    m_curState(NULL)
{
    m_backgroundObj = new Ui::BackgroundCtrlUi;
    m_musicObj = new Ui::MusicCtrlUi;
    m_randomObj = new Ui::RandomCtrlUi;
    m_sndboardObj = new SoundboardLayout;

    setupUi(this);
    m_backgroundObj->setupUi(m_backgroundCtrl);
    m_musicObj->setupUi(m_musicCtrl);
    m_randomObj->setupUi(m_randomCtrl);
    m_sndboardObj->setupUiWithButtons(m_sndboardCtrl);

    m_musicCtrl->setEnabled(false);
    m_backgroundCtrl->setEnabled(false);
    m_randomCtrl->setEnabled(false);
    m_sndboardCtrl->setEnabled(false);

    // Connect the signals & slots.
    connect( m_leftExpandBtn,   SIGNAL( clicked(bool)    ),
             this,              SLOT  ( ExpandLeft(bool) ) );

    connect( m_musicObj->m_addBtn,         SIGNAL( clicked()                           ),
             this,                         SIGNAL( AddSongSelected()                   ) );
    connect( m_musicObj->m_deleteBtn,      SIGNAL( clicked()                           ),
             this,                         SLOT  ( RemoveSelectedSong()                ) );
    connect( m_musicObj->m_playlistCbo,    SIGNAL( editTextChanged(const QString&)     ),
             this,                         SIGNAL( SongChanged(const QString&)         ) );
    connect( m_musicObj->m_playlistCbo,    SIGNAL( currentIndexChanged(const QString&) ),
             this,                         SIGNAL( SongChanged(const QString&)         ) );
    connect( m_musicObj->m_musicVolumeSld, SIGNAL( valueChanged(int)                   ),
             this,                         SIGNAL( SongVolumeChanged(int)              ) );
    connect( m_musicObj->m_musicMuteChk,   SIGNAL( stateChanged(int)                   ),
             this,                         SLOT  ( SetMusicMute()                      ) );

    connect( m_backgroundObj->m_addBtn,             SIGNAL( clicked()                            ),
             this,                                  SLOT  ( AddBackground()                      ) );
    connect( m_backgroundObj->m_deleteBtn,          SIGNAL( clicked()                            ),
             this,                                  SLOT  ( RemoveSelectedBackgroundEffects()    ) );
    connect( m_backgroundObj->m_selectAllBtn,       SIGNAL( clicked()                            ),
             m_backgroundObj->m_effectList,         SLOT  ( selectAll()                          ) );
    connect( m_backgroundObj->m_deselectAllBtn,     SIGNAL( clicked()                            ),
             m_backgroundObj->m_effectList,         SLOT  ( clearSelection()                     ) );
    connect( m_backgroundObj->m_selectionVolSld,    SIGNAL( valueChanged(int)                    ),
             this,                                  SIGNAL( BackgroundInstanceVolumeChanged(int) ) );
    connect( m_backgroundObj->m_selectionMuteChk,   SIGNAL( stateChanged(int)                    ),
             this,                                  SLOT  ( SetBackgroundSelectionMute()         ) );
    connect( m_backgroundObj->m_globalVolSld,       SIGNAL( valueChanged(int)                    ),
             this,                                  SIGNAL( BackgroundVolumeChanged(int)         ) );
    connect( m_backgroundObj->m_backgroundGlobMute, SIGNAL( stateChanged(int)                    ),
             this,                                  SLOT  ( SetBackgroundMute()                  ) );

    connect( m_randomObj->m_addBtn,           SIGNAL( clicked()                        ),
             this,                            SLOT  ( AddRandom()                      ) );
    connect( m_randomObj->m_deleteBtn,        SIGNAL( clicked()                        ),
             this,                            SLOT  ( RemoveSelectedRandomEffects()    ) );
    connect( m_randomObj->m_selectAllBtn,     SIGNAL( clicked()                        ),
             m_randomObj->m_effectList,       SLOT  ( selectAll()                      ) );
    connect( m_randomObj->m_deselectAllBtn,   SIGNAL( clicked()                        ),
             m_randomObj->m_effectList,       SLOT  ( clearSelection()                 ) );
    connect( m_randomObj->m_selectionVolSld,  SIGNAL( valueChanged(int)                ),
             this,                            SIGNAL( RandomInstanceVolumeChanged(int) ) );
    connect( m_randomObj->m_selectionPerSld,  SIGNAL( valueChanged(int)                ),
             this,                            SIGNAL( RandomPeriodChanged(int)         ) );
    connect( m_randomObj->m_selectionVarSld,  SIGNAL( valueChanged(int)                ),
             this,                            SIGNAL( RandomVarianceChanged(int)       ) );
    connect( m_randomObj->m_selectionMuteChk, SIGNAL( stateChanged(int)                ),
             this,                            SLOT  ( SetRandomSelectionMute()         ) );
    connect( m_randomObj->m_globalVolSld,     SIGNAL( valueChanged(int)                ),
             this,                            SIGNAL( RandomVolumeChanged(int)         ) );
    connect( m_randomObj->m_globalMuteChk,    SIGNAL( stateChanged(int)                ),
             this,                            SLOT  ( SetRandomMute()                  ) );

    connect( m_sndboardObj, SIGNAL( SoundRequested(int,int) ),
             this,          SLOT  ( AddInstant(int,int)     ) );
    connect( m_sndboardObj, SIGNAL( SoundRemoved(int,int)   ),
             this,          SLOT  ( RemoveInstant(int,int)  ) );

    // Initialize the left expander.
    ExpandLeft(false);
    UpdateBackgroundControls();
    UpdateRandomControls();
}

AmbMainWidget::~AmbMainWidget()
{
    delete m_backgroundObj;
    delete m_musicObj;
    delete m_randomObj;
    delete m_sndboardObj;
}

void AmbMainWidget::Associate(State* newState)
{
    bool sharedMusic = false;
    QString curSong;

    m_backgroundObj->m_effectList->clearSelection();
    m_randomObj->m_effectList->clearSelection();

    m_musicCtrl->setEnabled(false);
    m_backgroundCtrl->setEnabled(false);
    m_randomCtrl->setEnabled(false);
    m_sndboardCtrl->setEnabled(false);

    if (m_curState)
    {
        MusicCtrl* curMusic = m_curState->GetMusicController();
        BackgroundCtrl* curBg = m_curState->GetBackgroundController();
        RandomCtrl* curRand = m_curState->GetRandomController();
        Soundboard* curBoard = m_curState->GetSoundboard();

        disconnect(curBg->SelectionModel());
        disconnect(curRand->SelectionModel());

        disconnect(curMusic);
        disconnect(curBg);
        disconnect(curRand);
        disconnect(curBoard);

        disconnect(this, 0, m_curState, 0);

        QStringList sharedBg;
        if (newState)
        {
            MusicCtrl* newMusic = newState->GetMusicController();
            BackgroundCtrl* newBg = newState->GetBackgroundController();

            sharedMusic = curMusic->SharesCurrentSongWith(*newMusic);
            sharedBg = curBg->SharedWith(*newBg);

            if (sharedMusic)
                curSong = curMusic->CurrentSong();
        }

        curMusic->Halt(sharedMusic);
        curBg->Halt(sharedBg);
        curRand->Halt();
        m_sndboardObj->Associate(NULL);
    }

    if (newState)
    {
        MusicCtrl* newMusic = newState->GetMusicController();
        BackgroundCtrl* newBg = newState->GetBackgroundController();
        RandomCtrl* newRand = newState->GetRandomController();
        Soundboard* newBoard = newState->GetSoundboard();

        m_musicObj->m_playlistCbo->setModel(newMusic->Model());
        m_backgroundObj->m_effectList->setModel(newBg->Model());
        m_randomObj->m_effectList->setModel(newRand->Model());

        m_backgroundObj->m_effectList->setSelectionModel(newBg->SelectionModel());
        m_randomObj->m_effectList->setSelectionModel(newRand->SelectionModel());

        m_musicObj->m_musicVolumeSld->setValue(newMusic->GetVolume());
        m_musicObj->m_musicMuteChk->
            setChecked(newMusic->IsMuted()?Qt::Checked:Qt::Unchecked);

        m_backgroundObj->m_globalVolSld->setValue(newBg->GetMasterVolume());
        m_backgroundObj->m_backgroundGlobMute->
            setChecked(newBg->IsMasterMuted()?Qt::Checked:Qt::Unchecked);

        m_randomObj->m_globalVolSld->setValue(newRand->GetMasterVolume());
        m_randomObj->m_globalMuteChk->
            setChecked(newRand->IsMasterMuted()?Qt::Checked:Qt::Unchecked);

        connect(this,     SIGNAL( RemoveSongRequested(const QString&) ),
                newMusic, SLOT  ( RemoveSong(const QString&)          ));
        connect(this,     SIGNAL( SongChanged(const QString&)         ),
                newMusic, SLOT  ( SetSong(const QString&)             ));
        connect(this,     SIGNAL( SongMuteToggled(bool)               ),
                newMusic, SLOT  ( SetMuted(bool)                      ));
        connect(this,     SIGNAL( SongVolumeChanged(int)              ),
                newMusic, SLOT  ( SetVolume(int)                      ));

        connect(this,  SIGNAL( RemoveBackgroundRequested(const QString&) ),
                newBg, SLOT  ( RemoveBackground(const QString&)          ));
        connect(this,  SIGNAL( BackgroundMuteToggled(bool)               ),
                newBg, SLOT  ( SetMasterMuted(bool)                      ));
        connect(this,  SIGNAL( BackgroundVolumeChanged(int)              ),
                newBg, SLOT  ( SetMasterVolume(int)                      ));

        connect(this,    SIGNAL( RemoveRandomRequested(const QString&) ),
                newRand, SLOT  ( RemoveRandom(const QString&)          ));
        connect(this,    SIGNAL( RandomMuteToggled(bool)               ),
                newRand, SLOT  ( SetMasterMuted(bool)                   ));
        connect(this,    SIGNAL( RandomVolumeChanged(int)              ),
                newRand, SLOT  ( SetMasterVolume(int)                  ));

        connect( newMusic,  SIGNAL( SongSelected(const QString&) ),
                 this,      SLOT  ( SelectSong(const QString&)   ) );
        connect( newBg->SelectionModel(),
                 SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) ),
                 this,
                 SLOT  ( UpdateBackgroundControls()                                     ) );
        connect( newRand->SelectionModel(),
                 SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) ),
                 this,
                 SLOT  ( UpdateRandomControls()                                         ) );

        connect( newState, SIGNAL( destroyed() ), this, SLOT( OnCurrentStateDeletion() ));

        m_musicCtrl->setEnabled(true);
        m_backgroundCtrl->setEnabled(true);
        m_randomCtrl->setEnabled(true);
        m_sndboardCtrl->setEnabled(true);

        newMusic->Resume(sharedMusic, curSong);
        newBg->Resume();
        newRand->Resume();
        m_sndboardObj->Associate(newBoard);
    }

    m_curState = newState;
    UpdateBackgroundControls();
    UpdateRandomControls();
}

State* AmbMainWidget::CurrentState()
{
    return m_curState;
}

void AmbMainWidget::RemoveSelectedSong()
{
    QMessageBox::StandardButtons result =
        QMessageBox::warning(
            this,
            "Remove song",
            "Are you sure you want to remove the song from the playlist?",
            QMessageBox::Yes | QMessageBox::No );
    if (result == QMessageBox::Yes)
        emit RemoveSongRequested(m_musicObj->m_playlistCbo->currentText());
}

void AmbMainWidget::RemoveSelectedBackgroundEffects()
{
    QMessageBox::StandardButtons result =
        QMessageBox::warning(
            this,
            "Remove sound",
            "Are you sure you want to remove the selected sounds from the playlist?",
            QMessageBox::Yes | QMessageBox::No );
    if (result != QMessageBox::Yes)
        return;

    QModelIndexList selected =
        m_backgroundObj->m_effectList->selectionModel()->selectedIndexes();
    QStringList selectedTitles;
    for ( QModelIndexList::iterator it = selected.begin();
          it != selected.end();
          it++ )
    {
        selectedTitles.append( (*it).data().toString() );
    }

    for ( QStringList::iterator titleIt = selectedTitles.begin();
          titleIt != selectedTitles.end();
          titleIt++ )
    {
        emit RemoveBackgroundRequested(*titleIt);
    }
}

void AmbMainWidget::RemoveSelectedRandomEffects()
{
    QMessageBox::StandardButtons result =
        QMessageBox::warning(
            this,
            "Remove sound",
            "Are you sure you want to remove the selected sounds from the playlist?",
            QMessageBox::Yes | QMessageBox::No );
    if (result != QMessageBox::Yes)
        return;

    QModelIndexList selected =
        m_randomObj->m_effectList->selectionModel()->selectedIndexes();
    QStringList selectedTitles;
    for ( QModelIndexList::iterator it = selected.begin();
          it != selected.end();
          it++ )
    {
        selectedTitles.append( (*it).data().toString() );
    }

    for ( QStringList::iterator titleIt = selectedTitles.begin();
          titleIt != selectedTitles.end();
          titleIt++ )
    {
        emit RemoveRandomRequested(*titleIt);
    }
}

void AmbMainWidget::SelectSong(const QString& title)
{
    int songIndex = m_musicObj->m_playlistCbo->findData(title, Qt::DisplayRole);
    if (songIndex < 0)
        return;

    if (m_musicObj->m_playlistCbo->currentIndex() == songIndex)
        emit SongChanged(title);
    else
        m_musicObj->m_playlistCbo->setCurrentIndex(songIndex);
}

void AmbMainWidget::ExpandLeft(bool expand)
{
    m_backgroundGrp->setVisible(expand);
    m_musicGrp->setVisible(expand);
    m_randomGrp->setVisible(expand);
    m_leftExpandBtn->setText(expand?"<<":">>");
    m_leftExpandBtn->setChecked(expand);

    emit ExpandLeftToggled(expand);
}

void AmbMainWidget::AddBackground()
{
    emit AddBackgroundSelected();

    m_backgroundObj->m_effectList->reset();
}

void AmbMainWidget::AddRandom()
{
    emit AddRandomSelected();

    m_randomObj->m_effectList->reset();
}

void AmbMainWidget::AddInstant(int row, int col)
{
    if (!m_curState)
        return;

    Soundboard* sndboard = m_curState->GetSoundboard();
    if (!sndboard)
        return;

    emit AddInstantSelected(row, col);

    m_sndboardObj->
        AssignSoundToButton(
            row,
            col,
            sndboard->GetTitle(row,col),
            sndboard->GetEntry(row,col) );
}

void AmbMainWidget::RemoveInstant(int row, int col)
{
    if (!m_curState)
        return;

    Soundboard* sndboard = m_curState->GetSoundboard();
    if (!sndboard)
        return;

    sndboard->RemoveEntry(row, col);
}

void AmbMainWidget::UpdateBackgroundControls()
{
    if (!m_backgroundObj->m_effectList->selectionModel())
    {
        m_backgroundObj->m_selectionVolSld->setValue(0);
        m_backgroundObj->m_selectionMuteChk->setChecked(false);

        m_backgroundObj->m_selectionVolSld->setEnabled(false);
        m_backgroundObj->m_selectionMuteChk->setEnabled(false);

        return;
    }

    QModelIndexList selection =
        m_backgroundObj->m_effectList->selectionModel()->selectedIndexes();

    disconnect(this, SIGNAL( BackgroundInstanceMuteToggled(bool) ), 0, 0);
    disconnect(this, SIGNAL( BackgroundInstanceVolumeChanged(int) ), 0, 0);

    if (selection.size() == 0)
    {
        m_backgroundObj->m_selectionVolSld->setValue(0);
        m_backgroundObj->m_selectionMuteChk->setChecked(false);

        m_backgroundObj->m_selectionVolSld->setEnabled(false);
        m_backgroundObj->m_selectionMuteChk->setEnabled(false);
    }
    else
    {
        m_backgroundObj->m_selectionVolSld->setEnabled(true);
        m_backgroundObj->m_selectionMuteChk->setEnabled(true);

        BackgroundCtrl* bgCtrl =
            m_curState->GetBackgroundController();

        if (selection.size() == 1)
        {
            Background* bgSel = bgCtrl->GetInstance(selection[0].data().toString());

            m_backgroundObj->m_selectionVolSld->setValue(bgSel->GetInstanceVolume());
            m_backgroundObj->m_selectionMuteChk->setChecked(bgSel->IsInstancePaused());
        }

        for ( QModelIndexList::iterator it = selection.begin();
              it != selection.end();
              it++ )
        {
            Background* bgSel = bgCtrl->GetInstance((*it).data().toString());

            connect(this,  SIGNAL( BackgroundInstanceMuteToggled(bool)  ),
                    bgSel, SLOT  ( SetInstancePaused(bool)              ) );
            connect(this,  SIGNAL( BackgroundInstanceVolumeChanged(int) ),
                    bgSel, SLOT  ( SetInstanceVolume(int)               ) );
        }
    }
}

void AmbMainWidget::UpdateRandomControls()
{
    if (!m_randomObj->m_effectList->selectionModel())
    {
        m_randomObj->m_selectionVolSld->setValue(0);
        m_randomObj->m_selectionPerSld->setValue(0);
        m_randomObj->m_selectionVarSld->setValue(0);
        m_randomObj->m_selectionMuteChk->setChecked(false);

        m_randomObj->m_selectionVolSld->setEnabled(false);
        m_randomObj->m_selectionPerSld->setEnabled(false);
        m_randomObj->m_selectionVarSld->setEnabled(false);
        m_randomObj->m_selectionMuteChk->setEnabled(false);

        return;
    }

    QModelIndexList selection =
        m_randomObj->m_effectList->selectionModel()->selectedIndexes();

    disconnect(this, SIGNAL( RandomInstanceMuteToggled(bool) ), 0, 0);
    disconnect(this, SIGNAL( RandomInstanceVolumeChanged(int) ), 0, 0);
    disconnect(this, SIGNAL( RandomPeriodChanged(int) ), 0, 0);
    disconnect(this, SIGNAL( RandomVarianceChanged(int) ), 0, 0);

    if (selection.size() == 0)
    {
        m_randomObj->m_selectionVolSld->setValue(0);
        m_randomObj->m_selectionPerSld->setValue(0);
        m_randomObj->m_selectionVarSld->setValue(0);
        m_randomObj->m_selectionMuteChk->setChecked(false);

        m_randomObj->m_selectionVolSld->setEnabled(false);
        m_randomObj->m_selectionPerSld->setEnabled(false);
        m_randomObj->m_selectionVarSld->setEnabled(false);
        m_randomObj->m_selectionMuteChk->setEnabled(false);
    }
    else
    {
        m_randomObj->m_selectionVolSld->setEnabled(true);
        m_randomObj->m_selectionPerSld->setEnabled(true);
        m_randomObj->m_selectionVarSld->setEnabled(true);
        m_randomObj->m_selectionMuteChk->setEnabled(true);

        RandomCtrl* randCtrl =
            m_curState->GetRandomController();

        if (selection.size() == 1)
        {
            RandomSound* randSel = randCtrl->GetInstance(selection[0].data().toString());

            m_randomObj->m_selectionVolSld->setValue(randSel->GetInstanceVolume());
            m_randomObj->m_selectionPerSld->setValue(randSel->GetPeriod());
            m_randomObj->m_selectionVarSld->setValue(randSel->GetVariance());
            m_randomObj->m_selectionMuteChk->setChecked(!randSel->IsInstanceActive());
        }

        for ( QModelIndexList::iterator it = selection.begin();
              it != selection.end();
              it++ )
        {
            RandomSound* randSel = randCtrl->GetInstance((*it).data().toString());

            connect(this,    SIGNAL( RandomInstanceMuteToggled(bool)  ),
                    randSel, SLOT  ( SetInstanceInactive(bool)        ) );
            connect(this,    SIGNAL( RandomInstanceVolumeChanged(int) ),
                    randSel, SLOT  ( SetInstanceVolume(int)           ) );
            connect(this,    SIGNAL( RandomPeriodChanged(int)         ),
                    randSel, SLOT  ( SetPeriod(int)                   ) );
            connect(this,    SIGNAL( RandomVarianceChanged(int)       ),
                    randSel, SLOT  ( SetVariance(int)                 ) );
        }
    }
}

void AmbMainWidget::SetMusicMute()
{
    emit SongMuteToggled(m_musicObj->m_musicMuteChk->isChecked());
}

void AmbMainWidget::SetBackgroundMute()
{
    emit BackgroundMuteToggled(m_backgroundObj->m_backgroundGlobMute->isChecked());
}

void AmbMainWidget::SetBackgroundSelectionMute()
{
    emit BackgroundInstanceMuteToggled(m_backgroundObj->m_selectionMuteChk->isChecked());
}

void AmbMainWidget::SetRandomMute()
{
    emit RandomMuteToggled(m_randomObj->m_globalMuteChk->isChecked());
}

void AmbMainWidget::SetRandomSelectionMute()
{
    emit RandomInstanceMuteToggled(m_randomObj->m_selectionMuteChk->isChecked());
}

void AmbMainWidget::OnCurrentStateDeletion()
{
    m_curState = NULL;
    Associate(NULL);
}
