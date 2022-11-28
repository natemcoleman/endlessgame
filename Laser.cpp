#include "Laser.hpp"
#include "Coords.hpp"

Laser::Laser()
{

}

Laser::Laser(double x, double y, double newAngle)
{
    angle = newAngle;

    x1 = x;
    y1 = y;

    set2();
}

void Laser::update_laser()
{
    x1 = x1+(updateMoveAmount*sin(angle*PI/180));
    y1 = y1-(updateMoveAmount*cos(angle*PI/180));

    set2();
}

void Laser::update_laser(int windowMaxX, int windowMaxY, int windowMinX, int windowMinY)
{
    x1 = x1+(updateMoveAmount*sin(angle*PI/180));
    y1 = y1-(updateMoveAmount*cos(angle*PI/180));

    set2();
}

void Laser::update_laser(double newx1, double newy1, double newAngle)
{
    x1 = newx1;
    y1 = newy1;
    angle = newAngle;

    set2();
}

void Laser::set1(double newx1, double newy1)
{
    x1 = newx1;
    y1 = newy1;
}

void Laser::setAngle(double newAngle)
{
    angle = newAngle;
}

void Laser::set2()
{
    x2 = x1+(length*sin(angle*PI/180));
    y2 = y1-(length*cos(angle*PI/180));

//    std::cout << std::endl;
}

std::vector<double> Laser::getLaserCoords()
{
    std::vector<double> coordsVec{x1, y1, x2, y2};
    return coordsVec;
}
