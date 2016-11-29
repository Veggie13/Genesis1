#include <QEvent>
#include <QGridLayout>
#include <QVBoxLayout>

#include "HoverLabel.qoh"
#include "QException.h"

#include "PopupToolMainWindow.qoh"


const int PopupToolMainWindow::HOVER_HEIGHT = 40;
const int PopupToolMainWindow::HOVER_MAX_WIDTH = 100;
const int PopupToolMainWindow::FADE_TIME = 500;

PopupToolMainWindow::PopupToolMainWindow(QWidget* parent, Qt::WindowFlags flags)
:   QMainWindow(parent, flags),
    m_hoverArea(NULL),
    m_mainArea(NULL),
    m_fadeTarget(NULL)
{
    connect(&m_fadeTimer, SIGNAL( timeout() ), this, SLOT( fade() ));
}

void PopupToolMainWindow::addPopupWidget(const QString& name, QWidget* popup)
{
    if (!popup)
        throw QException("Programming Error: "
                         "Tried to add NULL popup widget!");
    if (m_popups.find(name) != m_popups.end())
        throw QException("Programming Error: "
                         "Tried to add popup widget using existing name!");

    popup->setParent(this);
    popup->hide();
    m_popups[name] = popup;

    HoverLabel* hover = new HoverLabel(name);
    connect( hover, SIGNAL( entered(QString)           ),
             this,  SLOT  ( beginHover(const QString&) ) );
    connect( hover, SIGNAL( left(QString)            ),
             this,  SLOT  ( endHover(const QString&) ) );
    hover->setMouseTracking(true);

    m_hovers[name] = hover;

    m_names.append(name);

    arrangeHoverWidgets();
}

void PopupToolMainWindow::removePopupWidget(const QString& name)
{
    m_names.removeAt(m_names.indexOf(name));

    arrangeHoverWidgets();

    m_popups.erase(m_popups.find(name));
    delete m_hovers[name];
    m_hovers.erase(m_hovers.find(name));
}

QWidget* PopupToolMainWindow::mainAreaWidget()
{
    return m_mainArea;
}

bool PopupToolMainWindow::eventFilter(QObject* obj, QEvent* event)
{
    if ( event->type() == QEvent::Leave )
    {
        QWidget* popup = dynamic_cast<QWidget*>(obj);
        QPoint pt = mapFromGlobal(QCursor::pos());
        bool inside = popup->frameGeometry().contains(pt);
        if (!inside)
        {
            m_fadeTarget = popup;
            m_fadeTimer.start(FADE_TIME);
        }
    }
    else if ( event->type() == QEvent::Enter )
    {
        QWidget* popup = dynamic_cast<QWidget*>(obj);
        if (popup == m_fadeTarget)
        {
            m_fadeTimer.stop();
            m_fadeTarget = NULL;
        }
    }

    return QObject::eventFilter(obj, event);
}

void PopupToolMainWindow::setupPopupUi()
{
    QLayout* layout = new QVBoxLayout;
    layout->addWidget(m_hoverArea = new QWidget);
    layout->addWidget(m_mainArea = new QWidget);
    centralWidget()->setLayout(layout);

    m_hoverArea->hide();
    m_mainArea->show();
}

void PopupToolMainWindow::beginHover(const QString& name)
{
    QMap<QString, QWidget*>::iterator finder = m_popups.find(name);
    if (finder == m_popups.end())
        throw QException("Programming Error: "
                         "Began popup hover over invalid name!");

    m_fadeTimer.stop();
    for ( QMap<QString, QWidget*>::iterator it = m_popups.begin();
          it != m_popups.end();
          it++ )
    {
        QString curName = it.key();
        QWidget* popup = it.value();
        if (curName == name)
        {
            HoverLabel* label = m_hovers[name];
            popup->show();
            QPoint hoverPoint =
                mapFromGlobal(label->mapToGlobal(label->rect().bottomLeft()));
            QPoint areaPoint =
                mapFromGlobal(m_hoverArea->mapToGlobal(m_hoverArea->rect().bottomLeft()));
            popup->move(areaPoint.x(), hoverPoint.y());
            popup->resize(m_hoverArea->width(), popup->minimumHeight());
            popup->raise();
        }
        else
        {
            popup->hide();
        }
    }
}

void PopupToolMainWindow::endHover(const QString& name)
{
    QMap<QString, QWidget*>::iterator finder = m_popups.find(name);
    if (finder == m_popups.end())
        throw QException("Programming Error: "
                         "Ended popup hover over invalid name!");

    QWidget* popup = finder.value();
    QPoint pt = mapFromGlobal(QCursor::pos());
    if (popup->frameGeometry().contains(pt))
    {
        popup->installEventFilter(this);
    }
    else
    {
        m_fadeTarget = popup;
        m_fadeTimer.start(FADE_TIME);
    }
}

void PopupToolMainWindow::fade()
{
    if (m_fadeTarget != NULL)
    {
        m_fadeTarget->removeEventFilter(this);
        m_fadeTarget->hide();
        m_fadeTarget = NULL;
    }
}

void PopupToolMainWindow::arrangeHoverWidgets()
{
    int cols = (width() + (HOVER_MAX_WIDTH - 1)) / HOVER_MAX_WIDTH;
    int rows = (m_names.size() + (cols - 1)) / cols;

    QGridLayout* gridLayout = new QGridLayout;
    delete m_hoverArea->layout();
    m_hoverArea->setLayout(gridLayout);

    if (m_names.size() < 1)
    {
        m_hoverArea->hide();
        return;
    }

    QStringList::iterator it = m_names.begin();
    for (int row = 0; row < rows && it != m_names.end(); row++)
    for (int col = 0; col < cols && it != m_names.end(); col++, it++)
    {
        gridLayout->addWidget(m_hovers[*it], row, col);
    }

    gridLayout->setSpacing(0);

    m_hoverArea->setFixedHeight(HOVER_HEIGHT * rows);
    m_hoverArea->show();
}
