#ifndef IACTION_H
#define IACTION_H

#include <SFML/System.hpp>

class IAction
{
    public:
                                                IAction();
        virtual                                 ~IAction();
        virtual sf::Vector2f                    doAction();
};

#endif // IACTION_H
