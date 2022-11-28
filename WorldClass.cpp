#include "WorldClass.hpp"
#include <random>

WorldClass::WorldClass()
{
}

void WorldClass::update_world(const std::vector<double>& mouseCoords, const std::vector<bool>& keyPresses, std::vector<int>& windowCoords)
{
    player.adjustAngle(mouseCoords);

    playerGun.set1(player.getX(), player.getY());
    playerGun.setAngle(player.getAngle());
    playerGun.set2();

    update_lasers();
    update_lasers(windowCoords.at(0), windowCoords.at(1), windowCoords.at(2), windowCoords.at(3));
}

void WorldClass::update_lasers()
{
    for(int i = 0; i < lasers.size(); i++)
    {
        lasers.at(i).update_laser();
    }
}

void WorldClass::update_lasers(int windowMaxX, int windowMaxY, int windowMinX, int windowMinY)
{
    for(int i = 0; i < lasers.size(); i++)
    {
        if(laser_location_is_valid(lasers.at(i).getLaserCoords().at(0), lasers.at(i).getLaserCoords().at(1), lasers.at(i).getLaserCoords().at(2), lasers.at(i).getLaserCoords().at(3), windowMaxX, windowMaxY, windowMinX, windowMinY))
        {
            lasers.at(i).update_laser();
        }
        else
        {
            lasers.erase(lasers.begin() + i);
            i--;
        }
    }
}

void WorldClass::move_player(const std::vector<bool> &keysPressed)
{
    if(keysPressed.at(0))
    {
        player.addY(-deltaAmount);
    }
    if(keysPressed.at(1))
    {
        player.addX(-deltaAmount);
    }
    if(keysPressed.at(2))
    {
        player.addY(deltaAmount);
    }
    if(keysPressed.at(3))
    {
        player.addX(deltaAmount);
    }
}

void WorldClass::add_random_enemy()
{
    Coords newEnemy{generate_random_double(), generate_random_double(), 0};
}

bool WorldClass::laser_location_is_valid(int laserX1, int laserY1, int laserX2, int laserY2, int windowMaxX, int windowMaxY, int windowMinX, int windowMinY)
{
    bool laserIsValid{true};

    if(laserX1 > windowMaxX || laserX1 < windowMinX)
    {
        laserIsValid = false;
    }

    if(laserY1 > windowMaxY || laserY1 < windowMinY)
    {
        laserIsValid = false;
    }

    return laserIsValid;
}

Coords WorldClass::getPlayer() const
{
    return player;
}

void WorldClass::setPlayer(const Coords &newPlayer)
{
    player = newPlayer;
}

std::vector<Coords> WorldClass::getEnemies() const
{
    return enemies;
}

void WorldClass::setEnemies(const std::vector<Coords> &newEnemies)
{
    enemies = newEnemies;
}

Laser WorldClass::getPlayerGun() const
{
    return playerGun;
}

void WorldClass::setPlayerGun(const Laser &newPlayerGun)
{
    playerGun = newPlayerGun;
}

double WorldClass::generate_random_double()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(minRandomNumber, maxRandomNumber);
    return dis(gen);
}
