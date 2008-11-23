#ifndef SCENEEDITORDLG_H
#define SCENEEDITORDLG_H

#include <QDialog>

#include "SceneEditorDlgUi.h"

class Project;


class SceneEditorDlg : public QDialog, private Ui::SceneEditorDlgUi
{
    Q_OBJECT

public:
    SceneEditorDlg(QWidget* parent=NULL);
    virtual ~SceneEditorDlg();

    void Associate(Project* proj);

protected:
    virtual void showEvent(QShowEvent* evt);

private slots:
    void AddScene();
    void AddState();
    void DeleteScene();
    void DeleteStates();
    void UpdateStateList();

private:
    Project* m_project;

};

#endif
