#include "enemy.h"
#include <QPixmap>
#include "settings.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <cmath>

enemy::enemy(QGraphicsScene *scene, Player *player, QGraphicsPathItem *parent) : QObject(), QGraphicsPixmapItem(parent), player(player), p0(0, 0), p1(100, 200), p2(300, 50)
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
}

bool enemy::isvalidposition(QPointF enemypos, Player *player)
{
    qreal dx = enemypos.x() - player->getXpos();
    qreal dy = enemypos.y() - player->getYpos();
    qreal distance = std::sqrt(dx * dx + dy * dy);
    return distance >= 100;
}

void enemy::statecontrol()
{
    if(currentstate == die)
        enemy::enemydie();
    else if(currentstate == hit)
        enemy::enemyhit();
    else if(currentstate == attack)
        enemy::enemyattack();
    else
        enemy::enemywalk();
}

void enemy::enemyhit()
{
    if(enemyhitTimer && enemyhitTimer->isActive())
    {
        enemyhitTimer->stop();
        enemyhitTimer->deleteLater();
    }
    enemyhitTimer = new QTimer(this);
    enemyhitcount = 0;
    enemyhitTimer->start(enemyhitinterval[0]);
    connect(enemyhitTimer, &QTimer::timeout, [this]()
    {
        if(enemyhitcount == enemyhitinterval.size())
        {
            enemyhitTimer->stop();
            enemyhitTimer->deleteLater();
            currentstate = still;
        }
        else
        {
            setPixmap(enemyhitframes[enemyhitcount]);
            enemyhitTimer->start(enemyhitinterval[enemyhitcount]);
            enemyhitcount++;
        }
    });
}

void enemy::enemydie()
{
    if(enemydieTimer && enemydieTimer->isActive())
        return;
    enemydieTimer = new QTimer(this);
    enemydiecount = 0;
    enemydieTimer->start(enemydieinterval[0]);
    connect(enemydieTimer, &QTimer::timeout, [this]()
    {
        if(enemydiecount == enemydieinterval.size())
        {
            enemydieTimer->stop();
            enemydieTimer->deleteLater();
            scene()->removeItem(this);
            delete this;
        }
        else
        {
            setPixmap(enemydieframes[enemydiecount]);
            enemydieTimer->start(enemyattackinterval[enemydiecount]);
            enemydiecount++;
        }
    });
}

void enemy::enemyattack()
{
    if(enemyattackTimer && enemyattackTimer->isActive())
        return;
    enemyattackTimer = new QTimer(this);
    enemyattackcount = 0;
    enemyattackTimer->start(enemyattackinterval[0]);
    connect(enemyattackTimer, &QTimer::timeout, [this]()
    {
        if(enemyattackcount == enemyattackinterval.size())
        {
            enemyattackTimer->stop();
            enemyattackTimer->deleteLater();
            currentstate = still;
        }
        else
        {
            setPixmap(enemyattackframes[enemyattackcount]);
            enemyattackTimer->start(enemyattackinterval[enemyattackcount]);
            enemyattackcount++;
        }
    });

}

void enemy::enemywalk()//此处差一堆
{
    if (currentstate == still)
    {
        enemy::enemymove();
        currentstate = move;
        enemy::enemymove();
        enemywalkTimer = new QTimer(this);
        enemywalkcount = 0;
        enemywalkTimer->start(enemywalkinterval[0]);

        connect(enemywalkTimer, &QTimer::timeout, [this]()
        {
            if(enemywalkcount == enemywalkinterval.size())
            {
                enemywalkTimer->stop();
                enemywalkTimer->deleteLater();
                currentstate = still;
            }
            else
            {
                enemy::enemymove();
                setPixmap(enemywalkframes[enemywalkcount]);
                enemywalkTimer->start(enemywalkinterval[enemywalkcount]);
                enemywalkcount++;
            }
        });
    }
}

void enemy::enemymove()
{
    if(currentstate == still)
        enemymoveTimer->start();
    else
    {
        qreal t = enemymoveTimer->elapsed() / 500;
        qreal u = 1 - t;
        qreal v = p0 * pow(u, 3) + p1 * t * pow(u, 2) + p2 * pow(t, 3);
        qreal dx = std::fabs(this->pos().x() - player->getXpos());
        qreal dy = std::fabs(this->pos().y() - player->getYpos());
        qreal dis = std::sqrt(pow(dx, 2) + pow(dy, 2));
        qreal targetX = this->pos().x() + v * dx / dis;
        qreal targetY = this->pos().y() + v * dy / dis;
        qreal scaledHeight = boundingRect().height() * settings::enemyscale;
        if (targetX < boundingRect().width() * settings::enemyscale / 2)
            targetX = boundingRect().width() * settings::enemyscale / 2;
        if (targetX > settings::startscenew - boundingRect().width() * settings::enemyscale / 2)
            targetX = settings::startscenew - boundingRect().width() * settings::enemyscale / 2;
        if (targetY < scaledHeight / 2)
            targetY = scaledHeight / 2;
        if (targetY > settings::startsceneh - scaledHeight / 2)
            targetY = settings::startsceneh - scaledHeight / 2;
        setPos(targetX - boundingRect().width() * settings::enemyscale / 2, targetY - scaledHeight / 2);
    }

}

void enemy::enemystill()
{

}

enemy::~enemy()
{
    if(enemywalkTimer)
    {
        enemywalkTimer->stop();
        enemywalkTimer->deleteLater();
    }
    if(enemystillTimer)
    {
        enemystillTimer->stop();
        enemystillTimer->deleteLater();
    }
    if(enemydieTimer)
    {
        enemydieTimer->stop();
        enemydieTimer->deleteLater();
    }
    if(enemyhitTimer)
    {
        enemyhitTimer->stop();
        enemyhitTimer->deleteLater();
    }
    if(enemyattackTimer)
    {
        enemyattackTimer->stop();
        enemyattackTimer->deleteLater();
    }
    scene()->removeItem(this);
    delete this;
}
