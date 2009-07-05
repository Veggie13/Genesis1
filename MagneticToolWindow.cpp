#include <QCoreApplication>
#include <QMoveEvent>

#include "MagneticToolWindow.qoh"


const int MagneticToolWindow::DEFAULT_RANGE = 20;
const int MagneticToolWindow::DEFAULT_BUFFER = 0;

MagneticToolWindow::MagneticToolWindow(QWidget* parent, Edges magEdges)
:   QWidget(parent, Qt::Tool|Qt::WindowStaysOnTopHint|Qt::Window),
    m_parent(parent),
    m_edges(magEdges),
    m_leftRange(DEFAULT_RANGE),
    m_topRange(DEFAULT_RANGE),
    m_rightRange(DEFAULT_RANGE),
    m_bottomRange(DEFAULT_RANGE),
    m_leftBuffer(DEFAULT_BUFFER),
    m_topBuffer(DEFAULT_BUFFER),
    m_rightBuffer(DEFAULT_BUFFER),
    m_bottomBuffer(DEFAULT_BUFFER),
    m_leftMagged(false),
    m_topMagged(false),
    m_rightMagged(false),
    m_bottomMagged(false)
{
    installEventFilter(this);
}

MagneticToolWindow::~MagneticToolWindow() { }

void MagneticToolWindow::setLeftRange(int range)
{
    m_leftRange = range;
    if (isLeftMagnetic() && !m_leftMagged && isInRange(leftDistance(), m_leftRange))
    {
        QPoint newPos(frameGeometry().topLeft().x(), frameGeometry().topLeft().y());
        adjustPositionForLeft(newPos);
        move(newPos);
        m_leftMagged = true;
    }
}

void MagneticToolWindow::setTopRange(int range)
{
    m_topRange = range;
    if (isTopMagnetic() && !m_topMagged && isInRange(topDistance(), m_topRange))
    {
        QPoint newPos(frameGeometry().topLeft().x(), frameGeometry().topLeft().y());
        adjustPositionForTop(newPos);
        move(newPos);
        m_topMagged = true;
    }
}

void MagneticToolWindow::setRightRange(int range)
{
    m_rightRange = range;
    if ( isRightMagnetic() && !m_leftMagged && !m_rightMagged &&
         isInRange(rightDistance(), m_rightRange) )
    {
        QPoint newPos(frameGeometry().topLeft().x(), frameGeometry().topLeft().y());
        adjustPositionForRight(newPos);
        move(newPos);
        m_rightMagged = true;
    }
}

void MagneticToolWindow::setBottomRange(int range)
{
    m_bottomRange = range;
    if ( isBottomMagnetic() && !m_topMagged && !m_bottomMagged &&
         isInRange(bottomDistance(), m_bottomRange) )
    {
        QPoint newPos(frameGeometry().topLeft().x(), frameGeometry().topLeft().y());
        adjustPositionForBottom(newPos);
        move(newPos);
        m_bottomMagged = true;
    }
}

void MagneticToolWindow::setLeftBuffer(int buffer)
{
    m_leftBuffer = buffer;
    if (m_leftMagged)
    {
        QPoint newPos(frameGeometry().topLeft().x(), frameGeometry().topLeft().y());
        adjustPositionForLeft(newPos);
        move(newPos);
    }
}

void MagneticToolWindow::setTopBuffer(int buffer)
{
    m_topBuffer = buffer;
    if (m_topMagged)
    {
        QPoint newPos(frameGeometry().topLeft().x(), frameGeometry().topLeft().y());
        adjustPositionForTop(newPos);
        move(newPos);
    }
}

void MagneticToolWindow::setRightBuffer(int buffer)
{
    m_rightBuffer = buffer;
    if (m_rightMagged)
    {
        QPoint newPos(frameGeometry().topLeft().x(), frameGeometry().topLeft().y());
        adjustPositionForRight(newPos);
        move(newPos);
    }
}

void MagneticToolWindow::setBottomBuffer(int buffer)
{
    m_bottomBuffer = buffer;
    if (m_bottomMagged)
    {
        QPoint newPos(frameGeometry().topLeft().x(), frameGeometry().topLeft().y());
        adjustPositionForBottom(newPos);
        move(newPos);
    }
}

bool MagneticToolWindow::isLeftMagnetic()
{
    return (m_edges & LeftEdge);
}

bool MagneticToolWindow::isTopMagnetic()
{
    return (m_edges & TopEdge);
}

bool MagneticToolWindow::isRightMagnetic()
{
    return (m_edges & RightEdge);
}

bool MagneticToolWindow::isBottomMagnetic()
{
    return (m_edges & BottomEdge);
}

bool MagneticToolWindow::eventFilter(QObject* obj, QEvent* event)
{
    if (this != obj)
        return QObject::eventFilter(obj, event);

    if (m_edges != NoEdges && event->type() == QEvent::Move)
    {
        bool snapped = false;
        QPoint newPos(frameGeometry().topLeft().x(), frameGeometry().topLeft().y());
        if (isLeftMagnetic())
        {
            int dist = leftDistance();
            m_leftMagged = (dist == 0);
            if (isInRange(dist, m_leftRange))
            {
                adjustPositionForLeft(newPos);
                snapped = m_leftMagged = true;
            }
        }
        if (!m_leftMagged && isRightMagnetic())
        {
            int dist = rightDistance();
            m_rightMagged = (dist == 0);
            if (isInRange(dist, m_rightRange))
            {
                adjustPositionForRight(newPos);
                snapped = m_rightMagged = true;
            }
        }
        if (isTopMagnetic())
        {
            int dist = topDistance();
            m_topMagged = (dist == 0);
            if (isInRange(dist, m_topRange))
            {
                adjustPositionForTop(newPos);
                snapped = m_topMagged = true;
            }
        }
        if (!m_topMagged && isBottomMagnetic())
        {
            int dist = bottomDistance();
            m_bottomMagged = (dist == 0);
            if (isInRange(dist, m_bottomRange))
            {
                adjustPositionForBottom(newPos);
                snapped = m_bottomMagged = true;
            }
        }

        if (snapped)
        {
            move(newPos);
            return true;
        }
    }

    return QObject::eventFilter(obj, event);
}

void MagneticToolWindow::moveEvent(QMoveEvent* event)
{
    printf("   (%d %d)\n", event->pos().x(), event->pos().y());
}

bool MagneticToolWindow::isInRange(int dist, int range)
{
    return (dist != 0 && dist < range);
}

int MagneticToolWindow::leftDistance()
{
    return abs( frameGeometry().topLeft().x() -
                m_parent->geometry().topLeft().x() +
                m_leftBuffer );
}

int MagneticToolWindow::rightDistance()
{
    return abs( frameGeometry().topRight().x() -
                m_parent->geometry().topRight().x() +
                m_rightBuffer );
}

int MagneticToolWindow::topDistance()
{
    return abs( frameGeometry().topLeft().y() -
                m_parent->geometry().topLeft().y() +
                m_topBuffer );
}

int MagneticToolWindow::bottomDistance()
{
    return abs( frameGeometry().bottomLeft().y() -
                m_parent->geometry().bottomLeft().y() +
                m_bottomBuffer );
}

void MagneticToolWindow::adjustPositionForLeft(QPoint& pos)
{
    pos.setX( m_parent->geometry().topLeft().x() + m_leftBuffer );
}

void MagneticToolWindow::adjustPositionForTop(QPoint& pos)
{
    pos.setY( m_parent->geometry().topLeft().y() + m_topBuffer );
}

void MagneticToolWindow::adjustPositionForRight(QPoint& pos)
{
    pos.setX( m_parent->geometry().topRight().x() +
              m_rightBuffer -
              frameGeometry().width() );
}

void MagneticToolWindow::adjustPositionForBottom(QPoint& pos)
{
    pos.setY( m_parent->geometry().bottomLeft().y() +
              m_bottomBuffer -
              frameGeometry().height() );
}
