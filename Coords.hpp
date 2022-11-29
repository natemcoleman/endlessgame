#ifndef COORDS_HPP
#define COORDS_HPP

#include <iostream>
#include <vector>

#define PI 3.14159265359

class Coords
{
public:
    Coords();
    Coords(double xInit, double yInit, double angleInit): x(xInit), y(yInit), angle(angleInit){};

    void adjustAngle(const std::vector<double>& coordsToFace);
    void adjustPlayerAngle(const std::vector<double>& coordsToFace);

    void updateCoord(std::vector<double> newCoords, double newAngle);

    void moveCoordAlongAngle(double moveAmount);

    void addX(const double& deltaX);
    void addY(const double& deltaY);

    double getX() const;
    void setX(double newX);

    double getY() const;
    void setY(double newY);

    double getAngle() const;
    void setAngle(double newAngle);

    double generate_random_double();


//    double getZombieUpdateMoveAmount() const;
//    void setZombieUpdateMoveAmount(double newZombieUpdateMoveAmount);

protected:
    double maxRandomNumber{100};
    double minRandomNumber{-maxRandomNumber};
//    double zombieUpdateMoveAmount{4/5};


    double x{0.0};
    double y{0.0};
    double angle{0.0};
};

#endif // COORDS_HPP
