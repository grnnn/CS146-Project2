#ifndef LEADERAPPEARS_H
#define LEADERAPPEARS_H

#include <SFML/System.hpp>

#include "../headers/World.hpp"
#include "../headers/Enemy.hpp"

#include "../FSM/ICondition.hpp"

class LeaderAppears: public ICondition
{
    public:
        LeaderAppears();
        virtual ~LeaderAppears();
        bool test(World& world, Enemy& enemy);
    protected:
    private:
};

#endif // LEADERAPPEARS_H
