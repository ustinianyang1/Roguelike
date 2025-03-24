#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QObject>
#include <QTimer>
#include "settings.h"
#include <QMouseEvent>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(QGraphicsItem *parent = nullptr);
    ~Player();
    //状态动画部分
    void hitordie();
    void playerhit();
    void playerdie();
    void playerattack();
    //移动+移动动画
    void playerwalk();
    void settarget(QGraphicsSceneMouseEvent *event);
    qreal getXpos() const;
    qreal getYpos() const;

    qreal playerhp = 100.0;
    qreal playerdamage = 10.0;
public slots:
    void playerhitordie(qreal enemydamage);
private:
    QPixmap playerwalkframes[10];//行走动画帧
    QPixmap playerhitframes[12];//受击动画帧
    QPixmap playerdieframes[15];//死亡动画帧
    QPixmap playerattackframes[12];//攻击动画帧

    std::vector<int> playerwalkinterval = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100};//动画部分以后可以微调
    std::vector<int> playerhitinterval = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
    std::vector<int> playerdieinterval = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
    std::vector<int> playerattackinterval = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

    QTimer* playerhitTimer;
    QTimer* playerdieTimer;
    QTimer* playerattackTimer;

    int playerwalkTimer;//行走动画的逻辑和其他不同
    size_t playerwalkcount;
    size_t playerhitcount;
    size_t playerdiecount;
    size_t playerattackcount;

    qreal vx = 0, vy = 0;
    qreal targetX, targetY;
    qreal currentX, currentY;
    const qreal maxSpeed = settings::playerspeed;
    const qreal threshold = 1.0;//停止阈值
};

#endif
