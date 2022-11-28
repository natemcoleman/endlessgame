#ifndef LASER_HPP
#define LASER_HPP

#include <iostream>
#include <vector>


class Laser
{
public:
    Laser();
    Laser(double x, double y, double angle);
    Laser(double x, double y, double angle, int initialLaserLifespan);

    void update_laser();
    void update_laser(int windowMaxX, int windowMaxY, int windowMinX, int windowMinY);


    void update_laser(double newx1, double newy1, double newAngle);

    void set1(double newx1, double newy1);
    void setAngle(double newAngle);
    void set2();

    std::vector<double> getLaserCoords();

    int getLaserLifespan() const;
    void setLaserLifespan(int newLaserLifespan);

protected:
    int laserLifespan{0};

    double length{10};
    double angle{0};
    double updateMoveAmount{10};

    double x1{0};
    double y1{0};
    double x2{0};
    double y2{0};
};

#endif // LASER_HPP
