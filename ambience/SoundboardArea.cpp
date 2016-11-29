#include "SoundboardArea.qoh"


SoundboardArea::SoundboardArea(QObject* parent)
:   QObject(parent),
    m_curProject(NULL),
    m_curScene(NULL)
{
}

void SoundboardArea::setupUi(QWidget* widget)
{
    Ui::SoundboardAreaUi::setupUi(widget);

    m_generalTabs->hide();
    m_sceneTabs->hide();
}

void SoundboardArea::AssociateWithProject(Project* project)
{
    if (m_curProject == project)
        return;

    if (m_curProject)
    {
        m_generalTabs->hide();
        m_generalTabs->
    }

    if (project)
    {
        m_generalTabs->show();
    }

    m_curProject = project;
}

void SoundboardArea::AssociateWithScene(Scene* scene)
{
}
