#pragma once
#include "player.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QPixmap>
#include <QTimer>
#include "qgraphicssceneevent.h"
#include "settings.h"
#include "bullet.h"
#include <QDebug>

const qreal epsilon = 1e-7;

Player::Player(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    playerwalkframes[0] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Taunt/Wraith_03_Taunt_000.png"));
    playerwalkframes[1] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Taunt/Wraith_03_Taunt_001.png"));
    playerwalkframes[2] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Taunt/Wraith_03_Taunt_002.png"));
    playerwalkframes[3] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Taunt/Wraith_03_Taunt_003.png"));
    playerwalkframes[4] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Taunt/Wraith_03_Taunt_004.png"));
    playerwalkframes[5] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Taunt/Wraith_03_Taunt_016.png"));
    playerwalkframes[6] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Taunt/Wraith_03_Taunt_017.png"));
    playerwalkframes[7] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Idle Blink/Wraith_03_Idle Blinking_008.png"));
    playerwalkframes[8] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Idle Blink/Wraith_03_Idle Blinking_010.png"));
    playerwalkframes[9] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Idle Blink/Wraith_03_Idle Blinking_011.png"));
    playerhitframes[0] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Hurt/Wraith_03_Hurt_000.png"));
    playerhitframes[1] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Hurt/Wraith_03_Hurt_001.png"));
    playerhitframes[2] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Hurt/Wraith_03_Hurt_002.png"));
    playerhitframes[3] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Hurt/Wraith_03_Hurt_003.png"));
    playerhitframes[4] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Hurt/Wraith_03_Hurt_004.png"));
    playerhitframes[5] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Hurt/Wraith_03_Hurt_005.png"));
    playerhitframes[6] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Hurt/Wraith_03_Hurt_006.png"));
    playerhitframes[7] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Hurt/Wraith_03_Hurt_007.png"));
    playerhitframes[8] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Hurt/Wraith_03_Hurt_008.png"));
    playerhitframes[9] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Hurt/Wraith_03_Hurt_009.png"));
    playerhitframes[10] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Hurt/Wraith_03_Hurt_010.png"));
    playerhitframes[11] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Hurt/Wraith_03_Hurt_011.png"));
    playerdieframes[0] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Dying/Wraith_03_Dying_000.png"));
    playerdieframes[1] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Dying/Wraith_03_Dying_001.png"));
    playerdieframes[2] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Dying/Wraith_03_Dying_002.png"));
    playerdieframes[3] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Dying/Wraith_03_Dying_003.png"));
    playerdieframes[4] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Dying/Wraith_03_Dying_004.png"));
    playerdieframes[5] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Dying/Wraith_03_Dying_005.png"));
    playerdieframes[6] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Dying/Wraith_03_Dying_006.png"));
    playerdieframes[7] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Dying/Wraith_03_Dying_007.png"));
    playerdieframes[8] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Dying/Wraith_03_Dying_008.png"));
    playerdieframes[9] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Dying/Wraith_03_Dying_009.png"));
    playerdieframes[10] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Dying/Wraith_03_Dying_010.png"));
    playerdieframes[11] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Dying/Wraith_03_Dying_011.png"));
    playerdieframes[12] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Dying/Wraith_03_Dying_012.png"));
    playerdieframes[13] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Dying/Wraith_03_Dying_013.png"));
    playerdieframes[14] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Dying/Wraith_03_Dying_014.png"));
    playerattackframes[0] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Casting Spells/Wraith_03_Attack_000.png"));
    playerattackframes[1] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Casting Spells/Wraith_03_Attack_001.png"));
    playerattackframes[2] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Casting Spells/Wraith_03_Attack_002.png"));
    playerattackframes[3] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Casting Spells/Wraith_03_Attack_003.png"));
    playerattackframes[4] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Casting Spells/Wraith_03_Attack_004.png"));
    playerattackframes[5] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Casting Spells/Wraith_03_Attack_005.png"));
    playerattackframes[6] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Casting Spells/Wraith_03_Attack_006.png"));
    playerattackframes[7] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Casting Spells/Wraith_03_Attack_007.png"));
    playerattackframes[8] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Casting Spells/Wraith_03_Attack_008.png"));
    playerattackframes[9] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Casting Spells/Wraith_03_Attack_009.png"));
    playerattackframes[10] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Casting Spells/Wraith_03_Attack_010.png"));
    playerattackframes[11] = QPixmap(QString(":/player1/build/PNG/Wraith_03/PNG Sequences/Casting Spells/Wraith_03_Attack_011.png"));

    setPixmap(playerwalkframes[0]);
    setScale(settings::playerscale);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setFocus();

    currentX = settings::startscenew / 2, currentY = settings::startsceneh / 2, targetX = settings::startscenew / 2, targetY = settings::startsceneh / 2;
    playerwalkcount = 0;
    playerwalkTimer = 0;

    QTimer *temp = new QTimer(this);
    temp->setInterval(16);
    connect(temp, &QTimer::timeout, this, &Player::playerwalk);
    temp->start();
}

void Player::playerwalk()
{
    qreal dx = targetX - currentX;
    qreal dy = targetY - currentY;
    qreal distance = std::sqrt(dx*dx + dy*dy);

    if (distance > threshold)
    {
        qreal dirX = dx/distance;//计算加速度方向
        qreal dirY = dy/distance;

        vx += settings::jiasua * dirX;
        vy += settings::jiasua * dirY;

        qreal speed = std::sqrt(vx*vx + vy*vy);
        if(speed > maxSpeed)//限制速度不超过最大速度
        {
            vx = vx/speed * maxSpeed;
            vy = vy/speed * maxSpeed;
        }
    }
    else
    {
        vx *= settings::jiansua;
        vy *= settings::jiansua;
        if(std::abs(vx) < 0.1)
            vx = 0;
        if(std::abs(vy) < 0.1)
            vy = 0;
    }
    //更新位置
    currentX += vx;
    currentY += vy;

    //边界检查
    if (currentX < boundingRect().width() * settings::playerscale / 2)
        currentX = boundingRect().width() * settings::playerscale / 2;
    if (currentX > settings::startscenew - boundingRect().width() * settings::playerscale / 2)
        currentX = settings::startscenew - boundingRect().width() * settings::playerscale / 2;
    if (currentY < boundingRect().height() * settings::playerscale / 2)
        currentY = boundingRect().height() * settings::playerscale / 2;
    if (currentY > settings::startsceneh - boundingRect().height() * settings::playerscale / 2)
        currentY = settings::startsceneh - boundingRect().height() * settings::playerscale / 2;

    setPos(currentX - boundingRect().width() * settings::playerscale / 2, currentY - boundingRect().height() * settings::playerscale / 2);

    playerwalkTimer += 16;

    if (playerwalkTimer == 112)
    {
        playerwalkTimer = 0;
        playerwalkcount = (playerwalkcount + 1) % playerwalkinterval.size();
        setPixmap(playerwalkframes[playerwalkcount]);
    }
}

void Player::playerhitordie(qreal enemydamage)
{
    this->playerhp -= enemydamage;
    //qDebug()<<this->playerhp<<Qt::endl;
    if(this->playerhp > epsilon)
        this->playerhit();
    else
        this->playerdie();
}

void Player::playerhit()//第二高优先级，需删除playerattckTimer
{
    if(playerattackTimer)
    {
        playerattackTimer->stop();
        playerattackTimer->deleteLater();
        playerattackTimer = nullptr;
    }
    if(playerhitTimer)
        return;
    playerhitTimer = new QTimer(this);
    playerhitcount = 0;
    playerhitTimer->start(playerhitinterval[0]);
    connect(playerhitTimer, &QTimer::timeout, [this]()
    {
        if(playerhitcount == playerhitinterval.size())
        {
            playerhitTimer->stop();
            playerhitTimer->deleteLater();
        }
        else
        {
            setPixmap(playerhitframes[playerhitcount]);
            playerhitTimer->start(playerhitinterval[playerhitcount]);
            playerhitcount++;
        }
    });
}

void Player::playerdie()//最高优先级，需删除playerhitTImer和playerattackTimer
{
    if(playerattackTimer)
    {
        playerattackTimer->stop();
        playerattackTimer->deleteLater();
        playerattackTimer = nullptr;
    }
    if(playerhitTimer)
    {
        playerhitTimer->stop();
        playerhitTimer->deleteLater();
        playerhitTimer = nullptr;
    }
    if(playerdieTimer)
        return;
    playerdieTimer = new QTimer(this);
    playerdiecount = 0;
    playerdieTimer->start(playerdieinterval[0]);
    connect(playerdieTimer, &QTimer::timeout, [this]()
    {
        if(playerdiecount == playerdieinterval.size())
        {
            playerdieTimer->stop();
            playerdieTimer->deleteLater();
            scene()->removeItem(this);
            this->deleteLater();
        }
        else
        {
            setPixmap(playerdieframes[playerdiecount]);
            playerdieTimer->start(playerattackinterval[playerdiecount]);
            playerdiecount++;
        }
    });
}

void Player::playerattack()
{
    if(playerattackTimer)
        return;
    playerattackTimer = new QTimer(this);
    playerattackcount = 0;
    playerattackTimer->start(playerattackinterval[0]);
    connect(playerattackTimer, &QTimer::timeout, [this]()
    {
        if(playerattackcount == playerattackinterval.size())
        {
            playerattackTimer->stop();
            playerattackTimer->deleteLater();
            playerattackTimer = nullptr;
            if(this->scene())
            {
                Bullet* bullet = new Bullet(this->scene(), this);
                bullet->bulletlockenemy();
            }
        }
        else
        {
            setPixmap(playerattackframes[playerattackcount]);
            playerattackTimer->start(playerattackinterval[playerattackcount++]);
        }
    });
}

Player::~Player()
{
    if (playerhitTimer)
    {
        playerhitTimer->stop();
        playerhitTimer->deleteLater();
        playerhitTimer = nullptr;
    }
    if (playerdieTimer)
    {
        playerdieTimer->stop();
        playerdieTimer->deleteLater();
        playerhitTimer = nullptr;
    }
    if (playerattackTimer)
    {
        playerattackTimer->stop();
        playerattackTimer->deleteLater();
        playerattackTimer = nullptr;
    }
}
//下面是移动相关的一些函数
qreal Player::getXpos() const
{
    return currentX;
}

qreal Player::getYpos() const
{
    return currentY;
}

void Player::settarget(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        this->targetX = event->scenePos().x();
        this->targetY = event->scenePos().y();
    }
}
