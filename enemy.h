#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPathItem>
#include <QObject>
#include <QPointF>
#include <QGraphicsScene>
#include "player.h"
#include <QTimer>
#include <QElapsedTimer>

class enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum state {still, move, attack, hit, die};

    enemy(QGraphicsScene *scene, Player *player, QGraphicsPathItem *parent = nullptr);
    ~enemy();

    bool isvalidposition(QPointF pos, Player *player);
    //状态控制函数
    void statecontrol();
    //状态动画部分
    void enemyhit();
    void enemydie();
    void enemyattack();
    //移动+休息+移动动画+休息动画
    void enemywalk();
    void enemystill();
    void enemymove();
private:
    Player *player;

    QPixmap enemywalkframes[5];
    QPixmap enemyhitframes[3];
    QPixmap enemydieframes[5];
    QPixmap enemyattackframes[8];

    int p0;//起点
    int p1;//控制点
    int p2;//终点

    std::vector<int> enemywalkinterval = {100, 100, 100, 100, 100};
    std::vector<int> enemyhitinterval = {100, 100, 100};
    std::vector<int> enemydieinterval = {100, 100, 100, 100, 100};
    std::vector<int> enemyattackinterval = {100, 100, 100, 100, 100, 100, 100, 100};

    state currentstate = still;

    QTimer *enemywalkTimer;//移动定时器
    QTimer *enemystillTimer;//休息定时器
    QTimer *enemydieTimer;
    QTimer *enemyhitTimer;
    QTimer *enemyattackTimer;
    QElapsedTimer *enemymoveTimer;

    int enemyhp = 10;

    size_t enemywalkcount;
    size_t enemyhitcount;
    size_t enemydiecount;
    size_t enemyattackcount;

    bool attackcooldown = true;//攻击冷却，真为可攻击

    qreal enemymaxSpeed = 1.2;//最大速度
    const qreal enemythreshold = 1.0;//追击停止阈值
};

#endif // ENEMY_H
