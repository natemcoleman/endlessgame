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

    void draw_lasers();

    void draw_enemies();

    void add_player();
    void get_mouse_location();
    void get_key_presses();

    void output_player_coords();

//    double generate_random_double();


protected:
    WorldClass shooterWorld{};

    double playerEllipseSize{10};
    std::vector<double> mouseCoords{0,0,0,0};
    std::vector<bool> keyPresses{};

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    bool eventFilter(QObject *obj, QEvent *ev);
    bool mouseIsPressed{false};
    void mouseReleaseEvent(QMouseEvent* event);

    double maxRandomNumber{10};
    double minRandomNumber{-maxRandomNumber};

    int viewHeight{400};
    int viewWidth{400};
    QRect viewRect{-viewWidth/2, -viewHeight/2, viewWidth, viewHeight};



    double generate_random_double();

    int timerPauseValue{40};

//    QColor worldColor = QColor(240, 214, 180, 255);

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
};


#endif // MAINWINDOW_H
