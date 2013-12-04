#include "LeaderGoneAndNotDistFromPlayer.hpp"

LeaderGoneAndNotDistFromPlayer::LeaderGoneAndNotDistFromPlayer(int m_dist)
{
    dist = m_dist;
}

LeaderGoneAndNotDistFromPlayer::~LeaderGoneAndNotDistFromPlayer()
{
    //dtor
}

bool LeaderGoneAndNotDistFromPlayer::test(World& world, Enemy& enemy)
{
    if(world.hasLeader())
    {
        return false;
    }

    sf::Vector2f playerPos = world.getPlayer()->getPosition();
    sf::Vector2f enemyPos = enemy.getPosition();

    if(sqrt((playerPos.x - enemyPos.x)*(playerPos.x - enemyPos.x)
            + (playerPos.y - enemyPos.y)*(playerPos.y - enemyPos.y)) > dist)
    {
        return true;
    }
    return false;
}
