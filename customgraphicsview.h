#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QTimer>

class Player;

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    CustomGraphicsView(QWidget *parent = nullptr);
    void setPlayer(Player *player);

protected:
    void drawForeground(QPainter *painter, const QRectF &rect) override;
    void scrollContentsBy(int dx, int dy) override;

private slots:
    void updateView();

private:
    Player *m_player;
    QTimer m_tracker;
};

#endif // CUSTOMGRAPHICSVIEW_H
