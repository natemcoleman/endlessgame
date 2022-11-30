#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QTimer>
#include "gridscene.h"
#include "WorldClass.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setup_graphics_view();
    void move_player();
    void update_player_color();

    void add_enemies();

    void draw_lasers();
    void draw_enemies();
    void draw_player();
    void draw_health();
    void draw_scope();

    void get_mouse_location();
    void get_key_presses();

    void sniper_shot();
    void shotgun_shot();
    void burst_shot();
    void minigun_shot();
    void rpg_shot();

    void output_player_coords();
    void output_enemy_coords();
    void output_mouse_coords();


protected:
    bool scopeOn{false};

    int numWorldUpdatesCounter{0};

    const int timesToRunBeforeUpdatingGraphics{2};

    int enemyAddCounter{0};
    int enemyAddThreshold{100};

    int topBuffer{-100};
//    int topBuffer{-68};

    WorldClass shooterWorld{};

    double playerEllipseSize{10};
    std::vector<double> mouseCoords{0,0,0,0};
    std::vector<bool> keyPresses{};

    bool mouseIsPressed{false};

    double maxRandomNumber{10};
    double minRandomNumber{-maxRandomNumber};

    int viewHeight{400};
    int viewWidth{400};
    QRect viewRect{-viewWidth/2, -viewHeight/2, viewWidth, viewHeight};

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    double generate_random_double();

    double generate_random_double(double spreadAmount);

    int timerPauseValue{40};

    QColor playerColor = QColor(0, 0, 0, 255);

    QSize originalWindowSize{800,600};


private:
    Ui::MainWindow* ui;
    GridScene* scene;
    QGraphicsEllipseItem* ellipse;
    QGraphicsLineItem* line;


public slots:
    void update_world();
private slots:

    void on_updateWorldButton_released();
    void on_enemyIntelligence_sliderMoved(int position);
    void on_scopeOn_stateChanged(int arg1);
};


#endif // MAINWINDOW_H
