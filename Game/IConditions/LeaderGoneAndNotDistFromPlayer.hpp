#ifndef LEADERGONEANDNOTDISTFROMPLAYER_H
#define LEADERGONEANDNOTDISTFROMPLAYER_H

#include <SFML/System.hpp>

#include "../headers/World.hpp"
#include "../headers/Enemy.hpp"

#include "../FSM/ICondition.hpp"


class LeaderGoneAndNotDistFromPlayer: public ICondition
{
    public:
        LeaderGoneAndNotDistFromPlayer(int m_dist);
        virtual ~LeaderGoneAndNotDistFromPlayer();
        bool test(World& world, Enemy& enemy);
    protected:
    private:
        int dist;
};

#endif // LEADERGONEANDNOTDISTFROMPLAYER_H
