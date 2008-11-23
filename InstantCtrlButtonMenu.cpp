#include "InstantCtrlButtonMenu.h"


InstantCtrlButtonMenu::InstantCtrlButtonMenu(QWidget* parent)
:   QMenu(parent),
    m_un(NULL),
    m_re(NULL)
{
    m_un = addAction("Unassign");
    m_re = addAction("Reassign");
}

InstantCtrlButtonMenu::~InstantCtrlButtonMenu()
{
}

QAction* InstantCtrlButtonMenu::UnassignAction()
{
    return m_un;
}

QAction* InstantCtrlButtonMenu::ReassignAction()
{
    return m_re;
}
