#include "../headers/LeaderEnemy.hpp"
#include "../../engine/headers/ResourceHolder.hpp"
#include "../../engine/headers/Utility.hpp"
#include <iostream>
#include "../headers/Seek.hpp"

LeaderEnemy::LeaderEnemy(const TextureHolder& textures)
:maxSpeed(500)
,maxForce(10)
{
    sf::Sprite spr(textures.get(Textures::LeaderEnemy));
    centerOrigin(spr);
    setSprite(spr);
    setID(2);
}

void LeaderEnemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(getSprite(), states);

}

float LeaderEnemy::getMaxSpeed(){
    return maxSpeed;
}

float LeaderEnemy::getMaxForce(){
    return maxForce;
}
