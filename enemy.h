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
#include <QRandomGenerator>


class enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enemy(QGraphicsScene *scene, Player *player, QGraphicsItem *parent = nullptr) : QObject(), QGraphicsPixmapItem(parent), player(player)
    {
        enemywalkframes[0] = QPixmap(":/enemy/build/Slime/parts/Walk (jump)/Mini (1).png");
        enemywalkframes[1] = QPixmap(":/enemy/build/Slime/parts/Walk (jump)/Mini (2).png");
        enemywalkframes[2] = QPixmap(":/enemy/build/Slime/parts/Walk (jump)/Mini (3).png");
        enemywalkframes[3] = QPixmap(":/enemy/build/Slime/parts/Walk (jump)/Mini (4).png");
        enemywalkframes[4] = QPixmap(":/enemy/build/Slime/parts/Walk (jump)/Mini (5).png");

        enemyhitframes[0] = QPixmap(":/enemy/build/Slime/parts/Damage and death/mini (1).png");
        enemyhitframes[1] = QPixmap(":/enemy/build/Slime/parts/Damage and death/mini (2).png");
        enemyhitframes[2] = QPixmap(":/enemy/build/Slime/parts/Damage and death/mini (3).png");

        enemydieframes[0] = QPixmap(":/enemy/build/Slime/parts/Damage and death/mini (1).png");
        enemydieframes[1] = QPixmap(":/enemy/build/Slime/parts/Damage and death/mini (2).png");
        enemydieframes[2] = QPixmap(":/enemy/build/Slime/parts/Damage and death/mini (3).png");
        enemydieframes[3] = QPixmap(":/enemy/build/Slime/parts/Damage and death/mini (4).png");
        enemydieframes[4] = QPixmap(":/enemy/build/Slime/parts/Damage and death/mini (5).png");

        enemyattackframes[0] = QPixmap(":/enemy/build/Slime/parts/attacks/mini (1).png");
        enemyattackframes[1] = QPixmap(":/enemy/build/Slime/parts/attacks/mini (2).png");
        enemyattackframes[2] = QPixmap(":/enemy/build/Slime/parts/attacks/mini (3).png");
        enemyattackframes[3] = QPixmap(":/enemy/build/Slime/parts/attacks/mini (4).png");
        enemyattackframes[4] = QPixmap(":/enemy/build/Slime/parts/attacks/mini (5).png");
        enemyattackframes[5] = QPixmap(":/enemy/build/Slime/parts/attacks/mini (6).png");
        enemyattackframes[6] = QPixmap(":/enemy/build/Slime/parts/attacks/mini (7).png");
        enemyattackframes[7] = QPixmap(":/enemy/build/Slime/parts/attacks/mini (8).png");
        setTransformOriginPoint(boundingRect().center());
        setScale(settings::enemyscale);

        //初始位置生成
        QPointF enemypos;
        do
        {
            int edge = QRandomGenerator::global()->bounded(4);
            switch (edge) {
            case 0://上边缘
                enemypos = QPointF(QRandomGenerator::global()->bounded(scene->width() - boundingRect().width() * settings::enemyscale), 0);
                break;
            case 1://下边缘
                enemypos = QPointF(QRandomGenerator::global()->bounded(scene->width() - boundingRect().width() * settings::enemyscale), scene->height() - boundingRect().height() * settings::enemyscale);
                break;
            case 2://左边缘
                enemypos = QPointF(0, QRandomGenerator::global()->bounded(scene->height() - boundingRect().height() * settings::enemyscale));
                break;
            case 3://右边缘
                enemypos = QPointF(scene->width() - boundingRect().width() * settings::enemyscale, QRandomGenerator::global()->bounded(scene->height() - boundingRect().height() * settings::enemyscale));
                break;
            }
        } while (!isvalidposition(enemypos, player));
        setPos(enemypos);
        scene->addItem(this);
        this->enemywalk();
    };
    ~enemy();

    bool isvalidposition(QPointF enemypos, Player *player);
    //状态动画部分
    void enemyhit();
    void enemydie();
    void enemyattack();
    //移动+休息+移动动画+休息动画
    void enemywalk();
    void enemystill();
    void enemymove();
public slots:
    void enemyhitordie(qreal playerdamage);
signals:
    void playerhit(qreal enemydamage);
private:
    Player *player;

    QPixmap enemywalkframes[5];
    QPixmap enemyhitframes[3];
    QPixmap enemydieframes[5];
    QPixmap enemyattackframes[8];

    qreal p0 = 0.8;//起点
    qreal p1 = 7.5;//控制点
    qreal p2 = 3.5;//控制点
    qreal p3 = 0.7;//终点

    std::vector<int> enemywalkinterval = {100, 100, 100, 100, 100};//动画部分以后可以微调
    std::vector<int> enemyhitinterval = {100, 100, 100};
    std::vector<int> enemydieinterval = {100, 100, 100, 100, 100};
    std::vector<int> enemyattackinterval = {100, 100, 100, 100, 100, 100, 100, 100};

    QTimer *enemywalkTimer = nullptr;//移动定时器
    QTimer *enemystillTimer = nullptr;//休息定时器
    QTimer *enemydieTimer = nullptr;
    QTimer *enemyhitTimer = nullptr;
    QTimer *enemyattackTimer = nullptr;
    QElapsedTimer enemymoveTimer;

    qreal enemyhp = 10.0;
    qreal enemydamage = 2.0;

    size_t enemywalkcount = 0;
    size_t enemyhitcount = 0;
    size_t enemydiecount = 0;
    size_t enemyattackcount = 0;

    qreal enemymaxSpeed = 1.2;//最大速度
};

#endif // ENEMY_H
