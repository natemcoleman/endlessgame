#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>
#include <QObject>
#include <QMouseEvent>
#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>

#define OUT_OF_WINDOW 100000

class GridScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GridScene(QObject *parent = nullptr){};

    void resetClickPoint();
    QPointF getClickPoint();

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool eventFilter(QObject * obj, QEvent * ev);

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);


    QPointF clickPoint{OUT_OF_WINDOW,OUT_OF_WINDOW};

    bool mouseIsPressed{false};
    std::vector<bool> keysPressed{false, false, false, false}; // WASD
};

#endif // GRIDSCENE_H
