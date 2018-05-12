#ifndef TOWERDEFENSE_BULLETLVLTWO_H
#define TOWERDEFENSE_BULLETLVLTWO_H


#include "Bullet.h"

class BulletLvlTwo: public Bullet {
public:
    BulletLvlTwo(const sf::Vector2f& position, float angle, Warrior& target);

    static const int kDamage_ = 150;
    constexpr static const float kVelocity_ = 500;
};


#endif //TOWERDEFENSE_BULLETLVLTWO_H
