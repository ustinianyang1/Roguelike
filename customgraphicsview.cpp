#include "customgraphicsview.h"
#include "player.h"
#include "settings.h"
#include <QPainter>
#include <QDebug>

CustomGraphicsView::CustomGraphicsView(QWidget *parent)
    : QGraphicsView(parent), m_player(nullptr)
{
    setFixedSize(settings::startscenew, settings::startsceneh);

    setSceneRect(0, 0, settings::startscenew, settings::startsceneh);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scale(settings::scalefactor, settings::scalefactor);//放大两倍

    m_tracker.start(16);
    connect(&m_tracker, &QTimer::timeout, this, &CustomGraphicsView::updateView);
}

void CustomGraphicsView::setPlayer(Player *player)
{
    m_player = player;
}

void CustomGraphicsView::drawForeground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawForeground(painter, rect);

    painter->setPen(Qt::red);
    painter->drawRect(sceneRect());

    painter->setPen(Qt::green);
    QRectF visibleRect = mapToScene(viewport()->rect()).boundingRect();
    painter->drawRect(visibleRect);
}

void CustomGraphicsView::scrollContentsBy(int dx, int dy)
{
    Q_UNUSED(dx);
    Q_UNUSED(dy);
}

void CustomGraphicsView::updateView() {
    if (!m_player)
        return;
    QPointF playerCenter = m_player->sceneBoundingRect().center();

    QRectF visibleArea = mapToScene(viewport()->rect()).boundingRect();
    qreal halfWidth = visibleArea.width() / 2;
    qreal halfHeight = visibleArea.height() / 2;

    qreal targetX = qBound(halfWidth, playerCenter.x(), scene()->width() - halfWidth);
    qreal targetY = qBound(halfHeight, playerCenter.y(), scene()->height() - halfHeight);

    centerOn(targetX, targetY);
}
