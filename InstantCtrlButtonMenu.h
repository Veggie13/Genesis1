#ifndef INSTANTCTRLBUTTONMENU_H
#define INSTANTCTRLBUTTONMENU_H

#include <QMenu>


class InstantCtrlButtonMenu : public QMenu
{
    Q_OBJECT

public:
    InstantCtrlButtonMenu(QWidget* parent = NULL);
    virtual ~InstantCtrlButtonMenu();

    QAction* UnassignAction();
    QAction* ReassignAction();

private:
    QAction* m_un;
    QAction* m_re;

};

#endif
