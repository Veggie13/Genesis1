#include <QMessageBox>

#include "Project.qoh"
#include "Scene.qoh"
#include "SceneNameDlgUi.h"
#include "State.qoh"
#include "StateNameDlgUi.h"
#include "TitleCarrierListModel.hpp"

#include "SceneEditorDlg.qoh"


SceneEditorDlg::SceneEditorDlg(QWidget* parent)
:   QDialog(parent),
    m_project(NULL),
    m_sceneListModel(NULL),
    m_stateListModel(NULL)
{
    setupUi(this);

    m_sceneListModel = new TitleCarrierListModel;
    m_sceneCbo->setModel(m_sceneListModel);

    m_stateListModel = new TitleCarrierListModel;
    m_stateList->setModel(m_stateListModel);

    connect( m_newSceneBtn,    SIGNAL( clicked() ), this, SLOT( AddScene()     ) );
    connect( m_newStateBtn,    SIGNAL( clicked() ), this, SLOT( AddState()     ) );
    connect( m_deleteSceneBtn, SIGNAL( clicked() ), this, SLOT( DeleteScene()  ) );
    connect( m_deleteStateBtn, SIGNAL( clicked() ), this, SLOT( DeleteStates() ) );
    connect( m_sceneCbo,       SIGNAL( currentIndexChanged(const QString&)     ),
             this,             SLOT  ( UpdateStateList()                       ) );

    m_newSceneBtn->setEnabled(false);
    m_newStateBtn->setEnabled(false);
    m_deleteSceneBtn->setEnabled(false);
    m_deleteStateBtn->setEnabled(false);
    m_sceneCbo->setEnabled(false);
    m_stateList->setEnabled(false);

    Associate(NULL);
}

SceneEditorDlg::~SceneEditorDlg()
{
    delete m_sceneListModel;
    delete m_stateListModel;
}

void SceneEditorDlg::Associate(Project* proj)
{
    if (m_project)
    {
        m_newSceneBtn->setEnabled(false);
        m_newStateBtn->setEnabled(false);
        m_deleteSceneBtn->setEnabled(false);
        m_deleteStateBtn->setEnabled(false);
        m_sceneCbo->setEnabled(false);
        m_stateList->setEnabled(false);
    }

    if (proj)
    {
        m_sceneListModel->setList(proj->SceneList());

        m_newSceneBtn->setEnabled(true);
        m_newStateBtn->setEnabled(true);
        m_deleteSceneBtn->setEnabled(true);
        m_deleteStateBtn->setEnabled(true);
        m_sceneCbo->setEnabled(true);
        m_stateList->setEnabled(true);
    }

    m_project = proj;
    UpdateStateList();
}

void SceneEditorDlg::AddScene()
{
    QDialog dlg;
    Ui::SceneNameDlgUi dlgLayout;
    dlgLayout.setupUi(&dlg);

    QString newName;
    while (dlg.exec())
    {
        newName = dlgLayout.m_sceneNameEdit->text();

        if (newName == "")
        {
            QMessageBox::critical(
                this,
                "Invalid",
                "Invalid scene name." );
            continue;
        }

        if (m_sceneCbo->findText(newName) != -1)
        {
            QMessageBox::critical(
                this,
                "In use",
                "That scene name is already in use." );
            continue;
        }

        m_project->AddScene( new Scene(newName) );

        m_sceneListModel->setList(m_project->SceneList());
        m_sceneCbo->setCurrentIndex(m_sceneCbo->findText(newName));
        break;
    }

    UpdateStateList();
}

void SceneEditorDlg::AddState()
{
    QDialog dlg;
    Ui::StateNameDlgUi dlgLayout;
    dlgLayout.setupUi(&dlg);

    Scene* curScene = dynamic_cast<Scene*>(
        m_sceneCbo->itemData(m_sceneCbo->currentIndex(), Qt::UserRole)
            .value<I_TitleCarrier*>()
        );

    QString newName;
    while (dlg.exec())
    {
        newName = dlgLayout.m_stateNameEdit->text();

        if (newName == "")
        {
            QMessageBox::critical(
                this,
                "Invalid",
                "Invalid state name." );
            continue;
        }

        bool found = false;
        const QList<State*>& stateList = curScene->StateList();
        for ( QList<State*>::const_iterator it = stateList.begin();
              !found && it != stateList.end();
              it++ )
        {
            found = ((*it)->Title() == newName);
        }

        if (found)
        {
            QMessageBox::critical(
                this,
                "In use",
                "That state name is already in use." );
            continue;
        }

        curScene->AddState( new State(newName) );

        QModelIndex newItem;
        found = false;
        for (int n = 0; !found && n < m_stateListModel->rowCount(); ++n)
        {
            newItem = m_stateListModel->index(n, 0);
            QVariant v = m_stateListModel->data(newItem);

            found = (v.toString() == newName);
        }

        if (found)
            m_stateList->setCurrentIndex(newItem);
        break;
    }

    UpdateStateList();
}

void SceneEditorDlg::DeleteScene()
{
    QMessageBox dlg(
        QMessageBox::Warning,
        "Confirm delete",
        QString("Are you sure you wish to delete \"")
              + m_sceneCbo->currentText()
              + "\"?",
        QMessageBox::Yes | QMessageBox::No,
        this );

    if (dlg.exec() == QMessageBox::Yes)
    {
        delete m_sceneCbo->itemData(m_sceneCbo->currentIndex(), Qt::UserRole)
            .value<I_TitleCarrier*>();

        m_sceneListModel->setList(m_project->SceneList());
    }

    UpdateStateList();
}

void SceneEditorDlg::DeleteStates()
{
    QModelIndexList selected = m_stateList->selectionModel()->selectedIndexes();

    for ( QModelIndexList::iterator it = selected.begin();
          it != selected.end();
          it++ )
    {
        QMessageBox dlg(
            QMessageBox::Warning,
            "Confirm delete",
            QString("Are you sure you wish to delete \"")
                  + (*it).data().toString()
                  + "\"?",
            QMessageBox::Yes | QMessageBox::No,
            this );

        if (dlg.exec() == QMessageBox::Yes)
        {
            delete (*it).data(Qt::UserRole).value<I_TitleCarrier*>();
        }
    }

    UpdateStateList();
}

void SceneEditorDlg::showEvent(QShowEvent* evt)
{
    UpdateStateList();
    QDialog::showEvent(evt);
}

void SceneEditorDlg::UpdateStateList()
{
    if (!m_project)
        return;

    if (m_sceneCbo->currentIndex() != -1)
    {
        Scene* curScene = dynamic_cast<Scene*>(
            m_sceneCbo->itemData(m_sceneCbo->currentIndex(), Qt::UserRole)
                .value<I_TitleCarrier*>()
            );

        m_statesGrp->setEnabled(true);
        m_deleteSceneBtn->setEnabled(true);
        m_stateListModel->setList(curScene->StateList());
    }
    else
    {
        m_statesGrp->setEnabled(false);
        m_deleteSceneBtn->setEnabled(false);
        m_stateListModel->setList( QList<I_TitleCarrier*>() );
    }
}
