#include "LeaderAppears.hpp"

LeaderAppears::LeaderAppears()
{
    //ctor
}

LeaderAppears::~LeaderAppears()
{
    //dtor
}

bool LeaderAppears::test(World& world, Enemy& enemy){
    return world.hasLeader();
}
