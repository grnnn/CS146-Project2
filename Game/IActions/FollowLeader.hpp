#ifndef FOLLOWLEADER_H
#define FOLLOWLEADER_H

#include <SFML/System.hpp>

#include "../headers/World.hpp"
#include "../headers/Enemy.hpp"

#include "../FSM/IAction.hpp"


class FollowLeader: public IAction
{
    public:
        FollowLeader();
        virtual ~FollowLeader();
        sf::Vector2f doAction(World& world, Enemy& enemy);
    protected:
    private:
};

#endif // FOLLOWLEADER_H
