#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "player.h"
#include "enemy.h"
#include <QPointF>
#include <QTimer>
#include <QPixmap>
#include <vector>

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(QGraphicsScene* scene, Player* player) : player(player)
    {
        bulletmoveframes[0] = QPixmap(":/bullet/build/bullet/move/FB500-1.png");
        bulletmoveframes[1] = QPixmap(":/bullet/build/bullet/move/FB500-2.png");
        bulletmoveframes[2] = QPixmap(":/bullet/build/bullet/move/FB500-3.png");
        bulletmoveframes[3] = QPixmap(":/bullet/build/bullet/move/FB500-4.png");
        bulletmoveframes[4] = QPixmap(":/bullet/build/bullet/move/FB500-5.png");
        bulletexplodeframes[0] = QPixmap(":/bullet/build/bullet/explosion/B500-2.PNG");
        bulletexplodeframes[1] = QPixmap(":/bullet/build/bullet/explosion/B500-3.PNG");
        bulletexplodeframes[2] = QPixmap(":/bullet/build/bullet/explosion/B500-4.PNG");
        setScale(settings::bulletscale);
        setTransformOriginPoint(boundingRect().center());
        setPos(QPointF(player->getXpos(), player->getYpos()));
        scene->addItem(this);
    };
    ~Bullet();

    Player* player;

    size_t bulletmovecount = 0;
    size_t bulletexplodecount = 0;
    size_t bulletmovetimecount = 0;

    qreal speed = 2.0;
    qreal playerdamage = player->playerdamage;

    QTimer* bulletexplodeTimer = nullptr;
    QTimer* bulletmoveTimer = nullptr;

    void bulletlockenemy();
    void bulletmove(enemy* target);
    void bulletexplode(enemy* target);

    std::vector<int> bulletexplodeinterval = {100, 100, 100};
signals:
    void enemyhit(qreal playerdamage);
private:
    QPixmap bulletmoveframes[5];
    QPixmap bulletexplodeframes[3];
};

#endif // BULLET_H
