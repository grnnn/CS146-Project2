#ifndef LEADERGONEANDDISTFROMPLAYER_H
#define LEADERGONEANDDISTFROMPLAYER_H

#include <SFML/System.hpp>

#include "../headers/World.hpp"
#include "../headers/Enemy.hpp"

#include "../FSM/ICondition.hpp"


class LeaderGoneAndDistFromPlayer: public ICondition
{
    public:
        LeaderGoneAndDistFromPlayer(int m_dist);
        virtual ~LeaderGoneAndDistFromPlayer();
        bool test(World& world, Enemy& enemy);
    protected:
    private:
        int dist;
};

#endif // LEADERGONEANDDISTFROMPLAYER_H
