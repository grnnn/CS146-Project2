#include "SwarmersGreaterThan.hpp"

SwarmersGreaterThan::SwarmersGreaterThan(int num)
{
    mNum = num;
}

SwarmersGreaterThan::~SwarmersGreaterThan()
{
    //dtor
}

bool SwarmersGreaterThan::test(World& world, Enemy& enemy)
{
    int count = 0;
    for(auto currentEnemy = world.getEnemies().begin(); currentEnemy != world.getEnemies().end(); ++currentEnemy){
        if((*currentEnemy)->isSwarmer()) count++;
    }
    if(count >= mNum) return true;
    else return false;
}
