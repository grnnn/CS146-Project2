#ifndef WANDER_H
#define WANDER_H

#include <SFML/System.hpp>

#include "../headers/World.hpp"
#include "../headers/Enemy.hpp"

#include "../FSM/IAction.hpp"



class Wander: public IAction
{
    public:
        Wander();
        virtual ~Wander();
        sf::Vector2f doAction(World& world, Enemy& enemy);
};

#endif // WANDER_H
