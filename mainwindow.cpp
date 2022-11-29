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
}

void MainWindow::add_enemies()
{
    if(enemyAddCounter > enemyAddThreshold)
    {
        enemyAddCounter = 0;
        shooterWorld.add_random_enemy();
    }
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
    ui->numEnemies->display(static_cast<int>(shooterWorld.getEnemies().size()));
    ui->numEnemiesDefeated->display(shooterWorld.getNumEnemiesDefeated());

    for(int i = 0; i < shooterWorld.getEnemies().size(); i++)
    {
        ellipse = scene->addEllipse(shooterWorld.getEnemies().at(i).getX()-(playerEllipseSize/2), shooterWorld.getEnemies().at(i).getY()-(playerEllipseSize/2), playerEllipseSize, playerEllipseSize,QPen(Qt::red),QBrush(Qt::green));
    }
}

void MainWindow::draw_health()
{
    for(int i = 0; i < shooterWorld.getHealth().size(); i++)
    {
        ellipse = scene->addEllipse(shooterWorld.getHealth().at(i).getX()-(playerEllipseSize/2), shooterWorld.getHealth().at(i).getY()-(playerEllipseSize/2), playerEllipseSize, playerEllipseSize,QPen(Qt::blue),QBrush(Qt::blue));
    }
}

void MainWindow::draw_player()
{
    ui->playerHealth->display(shooterWorld.getPlayerHealth());

    update_player_color();

    ellipse = scene->addEllipse(shooterWorld.getPlayer().getX()-(playerEllipseSize/2), shooterWorld.getPlayer().getY()-(playerEllipseSize/2), playerEllipseSize, playerEllipseSize,QPen(playerColor),QBrush(playerColor));
    line = scene->addLine(shooterWorld.getPlayerGun().getLaserCoords().at(0), shooterWorld.getPlayerGun().getLaserCoords().at(1), shooterWorld.getPlayerGun().getLaserCoords().at(2), shooterWorld.getPlayerGun().getLaserCoords().at(3), QPen(Qt::red));
}

void MainWindow::get_mouse_location()
{
//    QPoint mousePosition{ui->graphicsView->cursor().pos().x() - (ui->graphicsView->size().width()/2) + ui->graphicsView->mapFromGlobal((ui->graphicsView->pos())).x(), ui->graphicsView->cursor().pos().y() - (ui->graphicsView->size().height()/2) + ui->graphicsView->mapFromGlobal((ui->graphicsView->pos())).y() + topBuffer};

//    if(ui->graphicsView->frameGeometry().contains(mousePosition))
//    {
        mouseCoords.at(0) = ui->graphicsView->cursor().pos().x() - (ui->graphicsView->size().width()/2) + ui->graphicsView->mapFromGlobal((ui->graphicsView->pos())).x();
        mouseCoords.at(1) = ui->graphicsView->cursor().pos().y() - (ui->graphicsView->size().height()/2) + ui->graphicsView->mapFromGlobal((ui->graphicsView->pos())).y() + topBuffer;
//        mouseCoords.at(1) = -(ui->graphicsView->cursor().pos().y() - (ui->graphicsView->size().height()/2) + ui->graphicsView->mapFromGlobal((ui->graphicsView->pos())).y() + topBuffer);

//    }
}

void MainWindow::sniper_shot()
{
    int laserLifespan{1000};

    Laser newLaser{shooterWorld.getPlayerGun().getLaserCoords().at(0), shooterWorld.getPlayerGun().getLaserCoords().at(1), shooterWorld.getPlayer().getAngle(), laserLifespan};
    shooterWorld.lasers.push_back(newLaser);
    scene->mouseIsPressed = false;
}

void MainWindow::shotgun_shot()
{
    int numShots{15};
    int spreadAngle{50};
    int laserLifespan{10};

    for(int i = 0; i < numShots; i++)
    {
        Laser newLaser{shooterWorld.getPlayerGun().getLaserCoords().at(0), shooterWorld.getPlayerGun().getLaserCoords().at(1), shooterWorld.getPlayer().getAngle()+ generate_random_double(spreadAngle/2), laserLifespan};
        shooterWorld.lasers.push_back(newLaser);
    }
    scene->mouseIsPressed = false;
}

void MainWindow::burst_shot()
{
    int numShots{5};
    int laserLifespan{20};
    int spreadAngle{10};

    for(int i = 0; i < numShots; i++)
    {
        Laser newLaser{shooterWorld.getPlayerGun().getLaserCoords().at(0), shooterWorld.getPlayerGun().getLaserCoords().at(1), shooterWorld.getPlayer().getAngle()+ generate_random_double(spreadAngle/2), laserLifespan};
        shooterWorld.lasers.push_back(newLaser);
    }
    scene->mouseIsPressed = false;
}

void MainWindow::minigun_shot()
{
    int spreadAngle{50};
    int laserLifespan{60};

    Laser newLaser{shooterWorld.getPlayerGun().getLaserCoords().at(0), shooterWorld.getPlayerGun().getLaserCoords().at(1), shooterWorld.getPlayer().getAngle()+ generate_random_double(spreadAngle/2), laserLifespan};
    shooterWorld.lasers.push_back(newLaser);
}

void MainWindow::rpg_shot()
{
    int numShots{50};
    int laserLifespan{10};

    for(int i = 0; i < numShots; i++)
    {
        Laser newLaser{mouseCoords.at(0), mouseCoords.at(1), generate_random_double(180), laserLifespan};
        shooterWorld.lasers.push_back(newLaser);
    }
    scene->mouseIsPressed = false;
}

void MainWindow::get_key_presses()
{
    mouseIsPressed = scene->mouseIsPressed;

    if(mouseIsPressed)
    {
        if(ui->gunSelector->currentIndex() == 0)
        {
            sniper_shot();
        }
        else if(ui->gunSelector->currentIndex() == 1)
        {
            shotgun_shot();
        }
        else if(ui->gunSelector->currentIndex() == 2)
        {
            burst_shot();
        }
        else if(ui->gunSelector->currentIndex() == 3)
        {
            minigun_shot();
        }
        else if(ui->gunSelector->currentIndex() == 4)
        {
            rpg_shot();
        }
    }
}

void MainWindow::output_player_coords()
{
    std::cout << "Player X:" << shooterWorld.getPlayer().getX() << " Y:" << shooterWorld.getPlayer().getY() << std::endl;
}

void MainWindow::output_enemy_coords()
{
    for(int i = 0; i < shooterWorld.getEnemies().size(); i++)
    {
        std::cout << "Enemy" << i << " X:" << shooterWorld.getEnemies().at(i).getX() << " Y:" << shooterWorld.getEnemies().at(i).getY() << " Angle:" << shooterWorld.getEnemies().at(i).getAngle() <<std::endl;
    }
}

void MainWindow::output_mouse_coords()
{
    std::cout << "MouseX:" << mouseCoords.at(0) << " MouseY:" << mouseCoords.at(1) << std::endl;
}

void MainWindow::update_player_color()
{
    double RColorValue{0};
    RColorValue = (((100-shooterWorld.getPlayerHealth()))*255)/100;

    if(RColorValue > 255)
    {
        RColorValue = 255;
    }
    if(RColorValue < 0)
    {
        RColorValue = 0;
    }

    playerColor = QColor(RColorValue, 0, 0,255);
}

void MainWindow::update_world() //only redraw every N updates to speed things up (minigun)
{
    shooterWorld.setRepeatAmount(timesToRunBeforeUpdatingGraphics);

    for(int i= 0; i < timesToRunBeforeUpdatingGraphics; i++)
    {
    enemyAddCounter++;

    add_enemies();

    std::vector<int> windowCoords{(ui->graphicsView->size().width()/2), (ui->graphicsView->size().height()/2), -(ui->graphicsView->size().width()/2), -(ui->graphicsView->size().height()/2)};

    get_mouse_location();

    get_key_presses();

    move_player();

    shooterWorld.update_world(mouseCoords, keyPresses, windowCoords);
    }

    ui->graphicsView->centerOn(0,0);

//    viewRect = QRect{-viewWidth/2 + static_cast<int>(shooterWorld.getPlayer().getX()), -viewHeight/2 + static_cast<int>(shooterWorld.getPlayer().getY()), viewWidth, viewHeight};

    scene->setSceneRect(viewRect);

    scene->clear();

    draw_player();

    draw_lasers();

    draw_enemies();

    draw_health();

//    output_player_coords();

//    output_mouse_coords();

//    output_enemy_coords();
}

void MainWindow::on_updateWorldButton_released()
{
    shooterWorld.add_random_enemy();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        scene->keysPressed.at(0) = true;
//        std::cout << "W pressed" << std::endl;
    }
    if(event->key() == Qt::Key_A)
    {
        scene->keysPressed.at(1) = true;
//        std::cout << "Aa pressed" << std::endl;
    }
    if(event->key() == Qt::Key_S)
    {
        scene->keysPressed.at(2) = true;
//        std::cout << "S pressed" << std::endl;
    }
    if(event->key() == Qt::Key_D)
    {
        scene->keysPressed.at(3) = true;
//        std::cout << "D pressed" << std::endl;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        scene->keysPressed.at(0) = false;
//        std::cout << "W released main" << std::endl;
    }
    if(event->key() == Qt::Key_A)
    {
        scene->keysPressed.at(1) = false;
    }
    if(event->key() == Qt::Key_S)
    {
        scene->keysPressed.at(2) = false;
    }
    if(event->key() == Qt::Key_D)
    {
        scene->keysPressed.at(3) = false;
    }
}


double MainWindow::generate_random_double()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(minRandomNumber, maxRandomNumber);
    return dis(gen);
}
double MainWindow::generate_random_double(double spreadAmount
)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-spreadAmount, spreadAmount);
    return dis(gen);
}
void MainWindow::on_enemyIntelligence_sliderMoved(int position)
{
//    shooterWorld.setEnemyIntelligence(ui->enemyIntelligence->sliderPosition());
//    shooterWorld.set_enemy_speed(ui->enemyIntelligence->sliderPosition());
    enemyAddThreshold = ui->enemyIntelligence->sliderPosition();
}

