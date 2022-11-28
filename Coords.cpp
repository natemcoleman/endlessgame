#include "Coords.hpp"
#include <random>

Coords::Coords()
{

}

void Coords::adjustAngle(const std::vector<double>& coordsToFace)
{
//    std::cout << "playerAngle1:" << angle << std::endl;

    double x2{coordsToFace.at(0)};
    double y2{-coordsToFace.at(1)};

    double faceAngle{atan2((y2-y),(x2-x))*(180/PI)};

    if(faceAngle<0)
    {
        faceAngle+=360;
    }
    faceAngle-=90;
    if(faceAngle<0)
    {
        faceAngle+=360;
    }
    faceAngle = 360-faceAngle;

    angle = faceAngle;

//    std::cout << "playerAngle2:" << angle << std::endl;

}

void Coords::updateCoord(std::vector<double> newCoords, double newAngle)
{
    x = newCoords.at(0);
    y = newCoords.at(1);
    angle = newAngle;
}

void Coords::addX(const double& deltaX)
{
    x+= deltaX;
}

void Coords::addY(const double& deltaY)
{
    y += deltaY;
}

double Coords::getX() const
{
    return x;
}

void Coords::setX(double newX)
{
    x = newX;
}

double Coords::getY() const
{
    return y;
}

void Coords::setY(double newY)
{
    y = newY;
}

double Coords::getAngle() const
{
    return angle;
}

void Coords::setAngle(double newAngle)
{
    angle = newAngle;
}

double Coords::generate_random_double()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(minRandomNumber, maxRandomNumber);
    return dis(gen);
}
