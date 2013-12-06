#include "../headers/FollowEnemy.hpp"
#include "../../engine/headers/ResourceHolder.hpp"
#include "../../engine/headers/Utility.hpp"
#include <iostream>
#include "../headers/Seek.hpp"

FollowEnemy::FollowEnemy(const TextureHolder& textures)
:maxSpeed(500)
,maxForce(10)
{
    sf::Sprite spr(textures.get(Textures::FollowEnemy));
    centerOrigin(spr);
    setSprite(spr);
    setID(2);

}

void FollowEnemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(getSprite(), states);

}

float FollowEnemy::getMaxSpeed(){
    return maxSpeed;
}

float FollowEnemy::getMaxForce(){
    return maxForce;
}

void FollowEnemy::setLeader(LeaderEnemy& l){
    leader = &l;

}

LeaderEnemy* FollowEnemy::getLeader(){
    return leader;
}
