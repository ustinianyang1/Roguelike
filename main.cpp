#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QIcon>
#include <QApplication>
#include <QGraphicsItem>
#include "settings.h"
#include "player.h"
#include <QTimer>
#include <QGraphicsSceneMouseEvent>

class Scene : public QGraphicsScene
{
public:
    Scene(Player *player) : player(player) {}
protected:
    bool eventFilter(QObject *watched, QEvent *event) override
    {
        if (event->type() == QEvent::GraphicsSceneMousePress)
        {
            QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
            player->settarget(mouseEvent);
            return true;
        }
        return QGraphicsScene::eventFilter(watched, event);
    }
private:
    Player *player;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName("roguelike");
    QApplication::setWindowIcon(QIcon(":/images/build/map.png"));

    //创建player1
    Player *player1 = new Player();

    //启用鼠标追踪+创建初始场景
    Scene *scene = new Scene(player1);
    scene->addItem(player1);
    scene->setSceneRect(0, 0, settings::startsceneh, settings::startscenew);
    scene->setBackgroundBrush(QImage(":/startscene/build/map.png"));
    scene->installEventFilter(scene);
    QGraphicsView view(scene);
    view.setFixedSize(settings::startsceneh, settings::startscenew);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setScene(scene);
    view.setMouseTracking(true);

    //开始计时
    QTimer timer;
    timer.setInterval(16);//大约60帧每秒
    QObject::connect(&timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer.start();

    view.show();
    return a.exec();
}
