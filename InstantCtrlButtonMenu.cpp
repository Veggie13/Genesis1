#include "InstantCtrlButtonMenu.qoh"


InstantCtrlButtonMenu::InstantCtrlButtonMenu(QWidget* parent)
:   QMenu(parent),
    m_mv(NULL),
    m_un(NULL),
    m_re(NULL)
{
    m_mv = addAction("Swap");
    addSeparator();
    m_un = addAction("Unassign");
    m_re = addAction("Reassign");
}

InstantCtrlButtonMenu::~InstantCtrlButtonMenu()
{
}

QAction* InstantCtrlButtonMenu::MoveAction()
{
    return m_mv;
}

QAction* InstantCtrlButtonMenu::UnassignAction()
{
    return m_un;
}

QAction* InstantCtrlButtonMenu::ReassignAction()
{
    return m_re;
}
