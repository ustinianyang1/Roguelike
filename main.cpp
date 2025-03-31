#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QIcon>
#include <QApplication>
#include <QGraphicsItem>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include "settings.h"
#include "player.h"
#include "enemy.h"
#include <QTimer>
#include <vector>
#include <QGraphicsSceneMouseEvent>
#include "customgraphicsview.h"

std::vector<enemy*> enemies;

class Scene : public QGraphicsScene
{
public:
    Scene(Player *player) : player(player)
    {
        setSceneRect(0, 0, settings::startscenew, settings::startsceneh);
        //初始化敌人生成定时器
        spawnTimer = new QTimer(this);
        spawnTimer->setInterval(settings::enemyspawninterval);
        QObject::connect(spawnTimer, &QTimer::timeout, [this, player]()
        {
            enemies.push_back(new enemy(this, player, nullptr));
        });
        spawnTimer->start();
    }
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
    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_F)
            if(!enemies.empty())
                player->playerattack();
    }
private:
    Player *player;
    QTimer *spawnTimer;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName("Roguelike");
    QApplication::setWindowIcon(QIcon(":/images/build/map.png"));

    CustomGraphicsView view;
    view.setFixedSize(settings::startsceneh, settings::startscenew);
    view.setMouseTracking(true);
    view.show();

    view.resetTransform();

    QGraphicsScene *startScene = new QGraphicsScene();
    startScene->setSceneRect(0, 0, settings::startsceneh, settings::startscenew);
    startScene->setBackgroundBrush(QColor(30, 30, 30));

    QGraphicsTextItem *title = startScene->addText("Roguelike");
    title->setDefaultTextColor(Qt::white);
    QFont titleFont("Arial", 36, QFont::Bold);
    title->setFont(titleFont);
    qreal titleX = (settings::startscenew - title->boundingRect().width()) / 2;
    qreal titleY = settings::startsceneh / 3 - title->boundingRect().height() / 2;
    title->setPos(titleX, titleY);

    QPushButton *startButton = new QPushButton("Start Game");
    startButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #4CAF50;"
        "  border: none;"
        "  color: white;"
        "  padding: 15px 32px;"
        "  text-align: center;"
        "  text-decoration: none;"
        "  font-size: 16px;"
        "  margin: 4px 2px;"
        "  border-radius: 8px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #45a049;"
        "}"
    );

    QGraphicsProxyWidget *buttonProxy = startScene->addWidget(startButton);
    qreal buttonX = (settings::startscenew - startButton->sizeHint().width()) / 2;
    qreal buttonY = settings::startsceneh * 2 / 3 - startButton->sizeHint().height() / 2;
    buttonProxy->setPos(buttonX, buttonY);
    view.setScene(startScene);

    QObject::connect(startButton, &QPushButton::clicked, [&view, startScene]()
    {
        //清理开始场景
        view.setScene(nullptr);
        startScene->deleteLater();

        //创建玩家和游戏场景
        Player *player1 = new Player();
        Scene *gameScene = new Scene(player1);
        gameScene->addItem(player1);
        gameScene->setSceneRect(0, 0, settings::startsceneh, settings::startscenew);
        gameScene->setBackgroundBrush(QImage(":/startscene/build/map.png"));
        gameScene->installEventFilter(gameScene);

        view.setScene(gameScene);
        view.setPlayer(player1);
    });

    return a.exec();
}
