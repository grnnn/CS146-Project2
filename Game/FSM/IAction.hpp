#ifndef IACTION_H
#define IACTION_H

#include <SFML/System.hpp>

#include "../headers/World.hpp"
#include "../headers/Enemy.hpp"

class IAction
{
    public:
                                                IAction();
        virtual                                 ~IAction();
        virtual sf::Vector2f                    doAction(World& world, Enemy& enemy);
};

#endif // IACTION_H
