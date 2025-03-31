#include "Bullet.h"
#include "enemy.h"
#include <vector>
#include "global.h"

void Bullet::bulletlockenemy()
{
    qreal dis = 6405.0;
    enemy* target;
    for(size_t i = 0; i < enemies.size(); i++)
    {
        qreal temp = pow(enemies[i]->x() - player->getXpos(), 2) + pow(enemies[i]->y() - player->getYpos(), 2);
        if(dis > temp)
        {
            target = enemies[i];
            dis = temp;
        }
    }
    this->bulletmove(target);
}

void Bullet::bulletmove(enemy* target)
{
    if (!bulletmoveTimer) {
        bulletmoveTimer = new QTimer(this);
        bulletmoveTimer->setSingleShot(true);
        connect(bulletmoveTimer, &QTimer::timeout, [this, target]()
        {
            if (target) {
                qreal dx = target->x() + target->boundingRect().width() * settings::enemyscale / 2 - this->x() - this->boundingRect().width() * settings::bulletscale / 2;
                qreal dy = target->y() + target->boundingRect().height() * settings::enemyscale / 2 - this->y() - this->boundingRect().height() * settings::bulletscale / 2;
                qreal dis = sqrt(dx * dx + dy * dy);
                this->setRotation(atan2(dy, dx) * 180 / M_PI);//朝向target

                if(dis <= 5)
                {
                    bulletmovecount = 0;
                    bulletmovetimecount = 0;
                    this->bulletexplode(target);
                    return;
                }

                setPos(this->x() + dx / dis * speed, this->y() + dy / dis * speed);

                if(bulletmovetimecount >= 40)
                {
                    setPixmap(bulletmoveframes[(bulletmovecount++) % 5]);
                    bulletmovetimecount %= 40;
                }
                bulletmovetimecount += 10;

                bulletmoveTimer->start(10);
            }
        });
    }
    bulletmoveTimer->start(10);
}

void Bullet::bulletexplode(enemy* target)
{
    bulletexplodeTimer = new QTimer(this);
    bulletexplodecount = 0;
    bulletexplodeTimer->start(bulletexplodeinterval[0]);
    connect(bulletexplodeTimer, &QTimer::timeout, [this, target]()
    {
        if(bulletexplodecount == bulletexplodeinterval.size())
        {
            bulletexplodeTimer->stop();
            bulletexplodeTimer->deleteLater();
            scene()->removeItem(this);
            connect(this, &Bullet::enemyhit, target, &enemy::enemyhitordie);
            emit enemyhit(this->playerdamage);
            delete this;
        }
        else
        {
            QPixmap frame = bulletexplodeframes[bulletexplodecount];
            if(this->x() + this->boundingRect().width() * settings::bulletscale / 2 > target->x() + target->boundingRect().width() * settings::enemyscale / 2)
                frame = frame.transformed(QTransform().scale(-1, 1));
            setPixmap(frame);
            bulletexplodeTimer->start(bulletexplodeinterval[bulletexplodecount++]);
        }
    });
}

Bullet::~Bullet()
{
    if(bulletexplodeTimer)
    {
        bulletexplodeTimer->stop();
        bulletexplodeTimer->deleteLater();
    }
    if(bulletmoveTimer)
    {
        bulletmoveTimer->stop();
        bulletmoveTimer->deleteLater();
    }
    scene()->removeItem(this);
    delete this;
}
