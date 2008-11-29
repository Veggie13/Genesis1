#include <QMessageBox>

#include "Project.h"
#include "Scene.h"
#include "SceneNameDlgUi.h"
#include "StateNameDlgUi.h"

#include "SceneEditorDlg.h"


SceneEditorDlg::SceneEditorDlg(QWidget* parent)
:   QDialog(parent),
    m_project(NULL)
{
    setupUi(this);

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
        m_sceneCbo->setModel(proj->Model());

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

        if (!m_project->AddScene(newName))
        {
            QMessageBox::critical(
                this,
                "Add Scene",
                "Could not add the new scene." );
            continue;
        }

        m_sceneCbo->setModel(m_project->Model());
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

    Scene* curScene = m_project->GetScene(m_sceneCbo->currentText());

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
        for (int n = 0; !found && n < curScene->Model()->rowCount(); ++n)
        {
            QModelIndex i = curScene->Model()->index(n, 0);
            QVariant    v = curScene->Model()->data(i);

            found = (v.toString() == newName);
        }

        if (found)
        {
            QMessageBox::critical(
                this,
                "In use",
                "That state name is already in use." );
            continue;
        }

        if (!curScene->AddState(newName))
        {
            QMessageBox::critical(
                this,
                "Add State",
                "Could not add the new state." );
            continue;
        }

        QModelIndex newItem;
        found = false;
        for (int n = 0; !found && n < curScene->Model()->rowCount(); ++n)
        {
            newItem = curScene->Model()->index(n, 0);
            QVariant v = curScene->Model()->data(newItem);

            found = (v.toString() == newName);
        }

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
        m_project->RemoveScene(m_sceneCbo->currentText());
        m_sceneCbo->setModel(m_project->Model());
    }

    UpdateStateList();
}

void SceneEditorDlg::DeleteStates()
{
    QModelIndexList selected = m_stateList->selectionModel()->selectedIndexes();

    Scene* curScene = m_project->GetScene(m_sceneCbo->currentText());

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
            curScene->RemoveState((*it).data().toString());
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

    Scene* curScene = m_project->GetScene(m_sceneCbo->currentText());
    if (curScene)
        m_stateList->setModel(curScene->Model());

    m_stateList->reset();
}
