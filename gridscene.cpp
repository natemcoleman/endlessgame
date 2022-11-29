#include "gridscene.h"

void GridScene::resetClickPoint()
{
    clickPoint.setX(OUT_OF_WINDOW);
    clickPoint.setY(OUT_OF_WINDOW);
}

QPointF GridScene::getClickPoint()
{
    return clickPoint;
}

void GridScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    clickPoint.setX(mouseEvent->scenePos().x());
    clickPoint.setY(mouseEvent->scenePos().y());
    mouseIsPressed = true;

    update(sceneRect());
}

void GridScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    mouseIsPressed = false;
//    std::cout << "mouse released in gridscene" << std::endl;
}

bool GridScene::eventFilter(QObject * obj, QEvent * ev)
{
//    if (ev->type() == QEvent::MouseMove)
//    {
//        std::cout << "mouse moved" << std::endl;
//        QMouseEvent *mEvent = (QMouseEvent*)ev;
//        //            mouseCoords.at(0) = mEvent->pos().x() - (ui->graphicsView->size().width()/2);
//        //            mouseCoords.at(1) = mEvent->pos().y()- (ui->graphicsView->size().height()/2);
//    }
//    if(ev->type() == QEvent::KeyPress)
//    {
//        std::cout << "key pressed" << std::endl;
//    }
//    if(ev->type() == QEvent::KeyRelease)
//    {
//        std::cout << "key released" << std::endl;
//    }
    return false;
}

void GridScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        keysPressed.at(0) = true;
//        std::cout << "W pressed" << std::endl;
    }
    if(event->key() == Qt::Key_A)
    {
        keysPressed.at(1) = true;
//        std::cout << "Aa pressed" << std::endl;
    }
    if(event->key() == Qt::Key_S)
    {
        keysPressed.at(2) = true;
//        std::cout << "S pressed" << std::endl;
    }
    if(event->key() == Qt::Key_D)
    {
        keysPressed.at(3) = true;
//        std::cout << "D pressed" << std::endl;
    }
}

void GridScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        keysPressed.at(0) = false;
//        std::cout << "W released" << std::endl;
    }
    if(event->key() == Qt::Key_A)
    {
        keysPressed.at(1) = false;
    }
    if(event->key() == Qt::Key_S)
    {
        keysPressed.at(2) = false;
    }
    if(event->key() == Qt::Key_D)
    {
        keysPressed.at(3) = false;
    }
}


