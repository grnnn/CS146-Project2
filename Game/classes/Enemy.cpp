#include "../headers/Enemy.hpp"
#include "../../engine/headers/ResourceHolder.hpp"
#include "../../engine/headers/Utility.hpp"
#include <iostream>
#include <vector>
#include "../headers/Seek.hpp"

Enemy::Enemy(const TextureHolder& textures, World& world)
:maxSpeed(500)
,maxForce(10)
,mWorld(&world)
,listRemoval(false)
{
    sf::Sprite spr(textures.get(Textures::Enemy));
    centerOrigin(spr);
    setSprite(spr);
    setID(2);

}

void Enemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(!listRemoval)
    target.draw(getSprite(), states);

}
void Enemy::updateCurrent(sf::Time dt){
    int h;

    if(getEnemyRemoval()){



                        listRemoval = true;
                }





    move(getVelocity() * dt.asSeconds());
}

float Enemy::getMaxSpeed(){
    return maxSpeed;
}

float Enemy::getMaxForce(){
    return maxForce;
}
