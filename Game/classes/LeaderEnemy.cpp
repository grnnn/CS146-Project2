#include "../headers/LeaderEnemy.hpp"
#include "../../engine/headers/ResourceHolder.hpp"
#include "../../engine/headers/Utility.hpp"
#include <iostream>
#include "../headers/Seek.hpp"

LeaderEnemy::LeaderEnemy(const TextureHolder& textures)
    :maxSpeed(500)
    ,maxForce(10)
    ,health(6)
    ,listRemoval(false)
{
    sf::Sprite spr(textures.get(Textures::LeaderEnemy));
    centerOrigin(spr);
    setSprite(spr);
    setID(500);
}

void LeaderEnemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(!listRemoval)
        target.draw(getSprite(), states);

}

float LeaderEnemy::getMaxSpeed()
{
    return maxSpeed;
}

float LeaderEnemy::getMaxForce()
{
    return maxForce;
}

int LeaderEnemy::getHealth()
{
    return health;
}

void LeaderEnemy::damage()
{
    health--;
}




void LeaderEnemy::updateCurrent(sf::Time dt)
{
    if(getEnemyRemoval())
    {
        listRemoval = true;
    }
    move(getVelocity() * dt.asSeconds());
}
