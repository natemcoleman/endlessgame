#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QDockWidget>
#include <QGraphicsView>
#include <QPainter>
#include <iostream>
#include <QLCDNumber>
#include <QTimer>
#include <QMouseEvent>
#include <random>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(originalWindowSize);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_world()));
    timer->start(timerPauseValue);

    const QIcon settingsIcon = QIcon(":myicons/ant.png");
    setWindowIcon(QIcon(settingsIcon));

    setup_graphics_view();

    setMouseTracking(true);

    ui->graphicsView->viewport()->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup_graphics_view()
{
    scene = new GridScene(this);
    ui->graphicsView->setScene(scene);
    setMouseTracking(true);
    setAcceptDrops(true);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::move_player()
{
    shooterWorld.move_player(scene->keysPressed);
    output_player_coords();
}

void MainWindow::draw_lasers()
{
    for(int i = 0; i < shooterWorld.lasers.size(); i++)
    {
        line = scene->addLine(shooterWorld.lasers.at(i).getLaserCoords().at(0), shooterWorld.lasers.at(i).getLaserCoords().at(1), shooterWorld.lasers.at(i).getLaserCoords().at(2), shooterWorld.lasers.at(i).getLaserCoords().at(3), QPen(Qt::red));
    }
}

void MainWindow::draw_enemies()
{
    for(int i = 0; i < shooterWorld.getEnemies().size(); i++)
    {
        ellipse = scene->addEllipse(shooterWorld.getEnemies().at(i).getX()-(playerEllipseSize/2), shooterWorld.getEnemies().at(i).getY()-(playerEllipseSize/2), playerEllipseSize, playerEllipseSize,QPen(Qt::red),QBrush(Qt::green));
    }
}

bool MainWindow::eventFilter(QObject * obj, QEvent * ev)
{
//    if (obj == ui->graphicsView)
//        if (ev->type() == QEvent::MouseMove)
//        {
//            QMouseEvent *mEvent = (QMouseEvent*)ev;
////            mouseCoords.at(0) = mEvent->pos().x() - (ui->graphicsView->size().width()/2);
////            mouseCoords.at(1) = mEvent->pos().y()- (ui->graphicsView->size().height()/2);
//        }
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
void MainWindow::mouseMoveEvent(QMouseEvent * ev)
{
//    mouseCoords.at(0) = ev->pos().x() - (ui->graphicsView->size().width()/2);
//    mouseCoords.at(1) = ev->pos().y() - (ui->graphicsView->size().height()/2);
}

void MainWindow::mousePressEvent(QMouseEvent * ev)
{
//    mouseIsPressed = scene->mouseIsPressed;
//    std::cout << "mouse pressed" << std::endl;


//    Laser newLaser{shooterWorld.getPlayer().getX(), shooterWorld.getPlayer().getY(), shooterWorld.getPlayer().getAngle()};
//    shooterWorld.lasers.push_back(newLaser);
}

void MainWindow::mouseReleaseEvent(QMouseEvent * ev)
{
//    mouseIsPressed = false;
    //    std::cout << "mouse released" << std::endl;
}

void MainWindow::add_player()
{
    ellipse = scene->addEllipse(shooterWorld.getPlayer().getX()-(playerEllipseSize/2), shooterWorld.getPlayer().getY()-(playerEllipseSize/2), playerEllipseSize, playerEllipseSize,QPen(Qt::black),QBrush(Qt::black));
    line = scene->addLine(shooterWorld.getPlayerGun().getLaserCoords().at(0), shooterWorld.getPlayerGun().getLaserCoords().at(1), shooterWorld.getPlayerGun().getLaserCoords().at(2), shooterWorld.getPlayerGun().getLaserCoords().at(3), QPen(Qt::red));
}

void MainWindow::get_mouse_location()
{
//    QPoint mousePosition{ui->graphicsView->cursor().pos().x()- (ui->graphicsView->size().width()/2) + ui->graphicsView->mapFromGlobal((ui->graphicsView->pos())).x(), ui->graphicsView->cursor().pos().x()- (ui->graphicsView->size().width()/2) + ui->graphicsView->mapFromGlobal((ui->graphicsView->pos())).x()};

//    if(ui->graphicsView->frameGeometry().contains(mousePosition))
//    {
    mouseCoords.at(0) = ui->graphicsView->cursor().pos().x()- (ui->graphicsView->size().width()/2) + ui->graphicsView->mapFromGlobal((ui->graphicsView->pos())).x();
    mouseCoords.at(1) = ui->graphicsView->cursor().pos().y()- (ui->graphicsView->size().width()/2) + ui->graphicsView->mapFromGlobal((ui->graphicsView->pos())).y();

    //    }
}

void MainWindow::get_key_presses()
{
    mouseIsPressed = scene->mouseIsPressed;

    if(mouseIsPressed)
    {
        if(ui->gunSelector->currentIndex() == 0)
        {
            Laser newLaser{shooterWorld.getPlayer().getX(), shooterWorld.getPlayer().getY(), shooterWorld.getPlayer().getAngle()};
            shooterWorld.lasers.push_back(newLaser);
            scene->mouseIsPressed = false;
        }
        else if(ui->gunSelector->currentIndex() == 1)
        {
            Laser newLaser{shooterWorld.getPlayer().getX(), shooterWorld.getPlayer().getY(), shooterWorld.getPlayer().getAngle()+ generate_random_double()};
            shooterWorld.lasers.push_back(newLaser);
        }
    }

}

void MainWindow::output_player_coords()
{
    std::cout << "Player X:" << shooterWorld.getPlayer().getX() << " Y:" << shooterWorld.getPlayer().getY() << std::endl;
}

void MainWindow::update_world()
{
    ui->graphicsView->centerOn(0,0);

    scene->setSceneRect(viewRect);

    std::vector<int> windowCoords{(ui->graphicsView->size().width()/2), (ui->graphicsView->size().height()/2), -(ui->graphicsView->size().width()/2), -(ui->graphicsView->size().height()/2)};

    scene->clear();

    get_mouse_location();

    get_key_presses();

    move_player();

    shooterWorld.update_world(mouseCoords, keyPresses, windowCoords);
//    std::cout << "mouseX:" << mouseCoords.at(0) << " mouseY:" << mouseCoords.at(1) << std::endl;

    add_player();

    draw_lasers();

    draw_enemies();

}

void MainWindow::on_updateWorldButton_released()
{
//    update_world();
    std::cout << "num enemies" << shooterWorld.getEnemies().size() << std::endl;
    shooterWorld.add_random_enemy();

}

double MainWindow::generate_random_double()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(minRandomNumber, maxRandomNumber);
    return dis(gen);
}
