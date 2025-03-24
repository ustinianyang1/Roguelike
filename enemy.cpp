#include "enemy.h"
#include <QGraphicsScene>
#include <QPixmap>
#include "settings.h"
#include <cmath>

const qreal epsilon = 1e-7;

bool enemy::isvalidposition(QPointF enemypos, Player *player)
{
    qreal dx = player->getXpos() + player->boundingRect().width() * settings::playerscale / 2 - enemypos.x() - this->boundingRect().width() * settings::enemyscale / 2;
    qreal dy = player->getYpos() + player->boundingRect().height() * settings::playerscale / 2 - enemypos.y() - this->boundingRect().height() * settings::enemyscale / 2;
    qreal distance = std::sqrt(dx * dx + dy * dy);
    return distance >= 100;
}

void enemy::enemyhitordie(qreal playerdamage)
{
    this->enemyhp -= playerdamage;
    if(this->enemyhp < epsilon)
        this->enemydie();
    else
        this->enemyhit();
}

//优先级：1.die 2.hit 3.attack 4.walk 5.still

void enemy::enemyhit()
{
    if(enemystillTimer)
    {
        enemystillTimer->stop();
        enemystillTimer->deleteLater();
        enemystillTimer = nullptr;
    }
    if(enemywalkTimer)
    {
        enemywalkTimer->stop();
        enemywalkTimer->deleteLater();
        enemywalkTimer = nullptr;
    }
    if(enemyattackTimer)
    {
        enemyattackTimer->stop();
        enemyattackTimer->deleteLater();
        enemyattackTimer = nullptr;
    }
    if(enemyhitTimer)
    {
        enemyhitTimer->stop();
        enemyhitTimer->deleteLater();
        enemyhitTimer = nullptr;
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
        }
        else
        {
            QPixmap frame = enemyhitframes[enemyhitcount];
            if(this->x() + this->boundingRect().width() * settings::enemyscale / 2 > player->getXpos())
                frame = frame.transformed(QTransform().scale(-1, 1));
            setPixmap(frame);
            enemyhitTimer->start(enemyhitinterval[enemyhitcount]);
            enemyhitcount++;
        }
    });
}

void enemy::enemydie()
{
    if(enemystillTimer)
    {
        enemystillTimer->stop();
        enemystillTimer->deleteLater();
        enemystillTimer = nullptr;
    }
    if(enemywalkTimer)
    {
        enemywalkTimer->stop();
        enemywalkTimer->deleteLater();
        enemywalkTimer = nullptr;
    }
    if(enemyattackTimer)
    {
        enemyattackTimer->stop();
        enemyattackTimer->deleteLater();
        enemyattackTimer = nullptr;
    }
    if(enemyhitTimer)
    {
        enemyhitTimer->stop();
        enemyhitTimer->deleteLater();
        enemyhitTimer = nullptr;
    }
    if(enemydieTimer)
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
            enemydieTimer = nullptr;
            scene()->removeItem(this);
            this->deleteLater();
        }
        else
        {
            QPixmap frame = enemydieframes[enemydiecount];
            if(this->x() + this->boundingRect().width() * settings::enemyscale / 2 > player->getXpos())
                frame = frame.transformed(QTransform().scale(-1, 1));
            setPixmap(frame);
            enemydieTimer->start(enemyattackinterval[enemydiecount]);
            enemydiecount++;
        }
    });
}

void enemy::enemyattack()
{
    if(enemystillTimer)
    {
        enemystillTimer->stop();
        enemystillTimer->deleteLater();
        enemystillTimer = nullptr;
    }
    if(enemywalkTimer)
    {
        enemywalkTimer->stop();
        enemywalkTimer->deleteLater();
        enemywalkTimer = nullptr;
    }
    if(enemyattackTimer)
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
            enemyattackTimer = nullptr;
            connect(this, &enemy::playerhit, player, &Player::playerhitordie);
            qreal dx = player->getXpos() + player->boundingRect().width() * settings::playerscale / 2 - this->x() - this->boundingRect().width() * settings::enemyscale / 2;
            qreal dy = player->getYpos() + player->boundingRect().height() * settings::playerscale / 2 - this->y() - this->boundingRect().height() * settings::enemyscale / 2;
            qreal distance = std::sqrt(dx * dx + dy * dy);
            if(distance < 15)
                emit playerhit(this->enemydamage);
            this->enemywalk();
        }
        else
        {
            QPixmap frame = enemyattackframes[enemyattackcount];
            if(this->x() + this->boundingRect().width() * settings::enemyscale / 2 > player->getXpos())
                frame = frame.transformed(QTransform().scale(-1, 1));
            setPixmap(frame);
            enemyattackTimer->start(enemyattackinterval[enemyattackcount]);
            enemyattackcount++;
        }
    });
}

void enemy::enemywalk()
{
    if(enemystillTimer)
    {
        enemystillTimer->stop();
        enemystillTimer->deleteLater();
        enemystillTimer = nullptr;
    }
    enemywalkTimer = new QTimer(this);
    enemywalkcount = 0;
    enemywalkTimer->start(enemywalkinterval[0]);
    connect(enemywalkTimer, &QTimer::timeout, [this]()
    {
        if(enemywalkcount == enemywalkinterval.size())
        {
            enemywalkTimer->stop();
            enemywalkTimer->deleteLater();
            this->enemystill();
        }
        else
        {
            this->enemymove();
            QPixmap frame = enemywalkframes[enemywalkcount];
            if(this->x() + this->boundingRect().width() * settings::enemyscale / 2 > player->getXpos())
                frame = frame.transformed(QTransform().scale(-1, 1));
            setPixmap(frame);
            enemywalkTimer->start(enemywalkinterval[enemywalkcount]);
            enemywalkcount++;
        }
    });
}

void enemy::enemymove()
{
    if(!enemymoveTimer.isValid())
        enemymoveTimer.start();
    else
    {
        qreal t = enemymoveTimer.elapsed() / 500.0;
        qreal u = 1 - t;
        qreal v = u * u * u * p0 + 3 * u * u * t * p1 + 3 * u * pow(t, 2) * p2 + pow(t, 3) * p3;
        qreal dx = player->getXpos() - this->x() - this->boundingRect().width() * settings::enemyscale / 2;
        qreal dy = player->getYpos() - this->y() - this->boundingRect().height() * settings::enemyscale / 2;
        qreal dis = std::sqrt(pow(dx, 2) + pow(dy, 2));
        if(dis <= 15)
        {
            enemymoveTimer.invalidate();
            if(enemywalkTimer)
            {
                enemywalkTimer->stop();
                enemywalkTimer->deleteLater();
            }
            enemywalkTimer->stop();
            enemywalkTimer->deleteLater();
            this->enemyattack();
        }
        qreal targetX = this->pos().x() + v * dx / dis;
        qreal targetY = this->pos().y() + v * dy / dis;
        if (targetX < 0)
            targetX = 0;
        if (targetX > settings::startscenew - boundingRect().width() * settings::enemyscale)
            targetX = settings::startscenew - boundingRect().width() * settings::enemyscale;
        if (targetY < 0)
            targetY = 0;
        if (targetY > settings::startsceneh - boundingRect().height() * settings::enemyscale)
            targetY = settings::startsceneh - boundingRect().height() * settings::enemyscale;
        //qDebug() << "dx:" << dx << " dy:" << dy << "t:" << t << " v:" << v << Qt::endl;
        //qDebug() << "Current pos:" << this->pos() << " Target pos:" << targetX << targetY;
        setPos(targetX, targetY);
    }
}

void enemy::enemystill()
{
    enemymoveTimer.invalidate();
    enemystillTimer = new QTimer(this);
    enemystillTimer->start(200);
    connect(enemystillTimer, &QTimer::timeout, [this]()
    {
        this->enemywalk();
        enemystillTimer->stop();
        enemystillTimer->deleteLater();
    });
}

enemy::~enemy()
{
    if(enemymoveTimer.isValid())
        enemymoveTimer.invalidate();
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
}
