#include "NotDistFromPlayer.hpp"

NotDistFromPlayer::NotDistFromPlayer(int dist)
{
    m_dist = dist;
}

NotDistFromPlayer::~NotDistFromPlayer()
{
    //dtor
}

bool NotDistFromPlayer::test(World& world, Enemy& enemy)
{
    sf::Vector2f playerPos = world.getPlayer()->getPosition();
    sf::Vector2f enemyPos = enemy.getPosition();

    if(sqrt((playerPos.x - enemyPos.x)*(playerPos.x - enemyPos.x)
            + (playerPos.y - enemyPos.y)*(playerPos.y - enemyPos.y)) > m_dist)
    {
        return true;
    }
    return false;
}
