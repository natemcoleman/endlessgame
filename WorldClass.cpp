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

    check_lasers_and_zombies();

    update_enemies();
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

void WorldClass::update_enemies()
{
    std::vector<double> playerCoords{player.getX(), -player.getY()};
    for(int i = 0; i < enemies.size(); i++)
    {
        enemies.at(i).adjustAngle(playerCoords);
        enemies.at(i).setAngle(enemies.at(i).getAngle()+generate_random_angle());
        enemies.at(i).moveCoordAlongAngle();
    }
}

void WorldClass::check_lasers_and_zombies()
{
    for(int i = 0; i < enemies.size(); i++)
    {
        for(int j = 0; j < lasers.size(); j++)
        {
            if(maxKillDistance > get_distance_between_two_points(enemies.at(i).getX(), enemies.at(i).getY(), lasers.at(j).getLaserCoords().at(0), lasers.at(j).getLaserCoords().at(1)))
            {
                numEnemiesDefeated++;
                enemies.erase(enemies.begin()+i);
                lasers.erase(lasers.begin()+j);
                break;
            }
        }
    }
}

void WorldClass::add_random_enemy()
{
    Coords newEnemy{generate_random_double(), generate_random_double(), 0};
    enemies.push_back(newEnemy);
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
    std::uniform_real_distribution<> dis(minRandomDistance, maxRandomDistance);

    return dis(gen);
}

double WorldClass::generate_random_angle()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-enemyIntelligence, enemyIntelligence);

    return dis(gen);
}

void WorldClass::set_enemy_speed(int newSpeed)
{
    for(int i = 0; i < enemies.size(); i++)
    {
        enemies.at(i).setZombieUpdateMoveAmount(newSpeed);
    }
}

int WorldClass::getEnemyIntelligence() const
{
    return enemyIntelligence;
}

void WorldClass::setEnemyIntelligence(int newEnemyIntelligence)
{
    enemyIntelligence = newEnemyIntelligence;
}

int WorldClass::getNumEnemiesDefeated() const
{
    return numEnemiesDefeated;
}

void WorldClass::setNumEnemiesDefeated(int newNumEnemiesDefeated)
{
    numEnemiesDefeated = newNumEnemiesDefeated;
}

double WorldClass::get_distance_between_two_points(const double& firstX, const double& firstY, const double& secondX, const double& secondY)
{
    return (sqrt(((secondX-firstX)*(secondX-firstX))+((secondY-firstY)*(secondY-firstY))));
}
