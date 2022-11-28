#ifndef WORLDCLASS_HPP
#define WORLDCLASS_HPP

#include "Coords.hpp"
#include "Laser.hpp"
#include <iostream>
#include <vector>

class WorldClass
{
public:
    WorldClass(){};

    void update_world(const std::vector<double>& mouseCoords, const std::vector<bool>& keyPresses, std::vector<int>& windowCoords);
    void update_lasers();
    void update_lasers(int windowMaxX, int windowMaxY, int windowMinX, int windowMinY);
    void move_player(const std::vector<bool>& keysPressed);
    void update_enemies();

    void check_lasers_and_zombies();
    void check_lasers_and_player();
    void check_zombies_and_player();

    void add_random_enemy();

    double get_distance_between_two_points(const double& firstX, const double& firstY, const double& secondX, const double& secondY);

    bool laser_location_is_valid(int laserX1, int laserY1, int laserX2, int laserY2, int windowMaxX, int windowMaxY, int windowMinX, int windowMinY);

    Coords getPlayer() const;
    void setPlayer(const Coords &newPlayer);

    std::vector<Coords> getEnemies() const;
    void setEnemies(const std::vector<Coords> &newEnemies);

    Laser getPlayerGun() const;
    void setPlayerGun(const Laser &newPlayerGun);

    std::vector<Laser> lasers{};

    double generate_random_double();
    double generate_random_angle();

    void set_enemy_speed(int newSpeed);

    int getEnemyIntelligence() const;
    void setEnemyIntelligence(int newEnemyIntelligence);

    int getNumEnemiesDefeated() const;
    void setNumEnemiesDefeated(int newNumEnemiesDefeated);

    void setPlayerHealth(int newPlayerHealth);

    int getPlayerHealth() const;

protected:
    int playerHealth{100};

    int numEnemiesDefeated{0};
    int enemyIntelligence{0};

    double maxRandomDistance{400};
    double minRandomDistance{-maxRandomDistance};

    double maxKillDistance{15};
    double maxKillDistanceBetweenPlayersAndZombies{10};

    double deltaAmount{5};
    Coords player{};
    std::vector<Coords> enemies{};
    Laser playerGun{player.getX(), player.getY(), player.getAngle()};
};

#endif // WORLDCLASS_HPP
