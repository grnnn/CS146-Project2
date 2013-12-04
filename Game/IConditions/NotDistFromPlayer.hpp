#ifndef NOTDISTFROMPLAYER_H
#define NOTDISTFROMPLAYER_H

#include <SFML/System.hpp>

#include "../headers/World.hpp"
#include "../headers/Enemy.hpp"

#include "../FSM/ICondition.hpp"

class NotDistFromPlayer: public ICondition
{
    public:
        NotDistFromPlayer(int dist);
        virtual ~NotDistFromPlayer();
        bool test(World& world, Enemy& enemy);
    protected:
    private:
        int m_dist;
};

#endif // NOTDISTFROMPLAYER_H
