#ifndef DISTFROMPLAYER_H
#define DISTFROMPLAYER_H

#include <SFML/System.hpp>

#include "../headers/World.hpp"
#include "../headers/Enemy.hpp"

#include "../FSM/ICondition.hpp"



class DistFromPlayer: public ICondition
{
    public:
        DistFromPlayer(int dist);
        virtual ~DistFromPlayer();
        bool test(World& world, Enemy& enemy);
    private:
        int m_dist;
};

#endif // DISTFROMPLAYER_H
