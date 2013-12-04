#include "../headers/Enemy.hpp"
#include "../../engine/headers/ResourceHolder.hpp"
#include "../../engine/headers/Utility.hpp"
#include <iostream>
#include "../headers/Seek.hpp"

Enemy::Enemy(const TextureHolder& textures)
:maxSpeed(50)
,maxForce(1)
{
    sf::Sprite spr(textures.get(Textures::Enemy));
    centerOrigin(spr);
    setSprite(spr);
    setID(2);

}

void Enemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(getSprite(), states);

}

float Enemy::getMaxSpeed(){
    return maxSpeed;
}

float Enemy::getMaxForce(){
    return maxForce;
}
