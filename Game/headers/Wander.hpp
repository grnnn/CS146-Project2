
#include "../FSM/IAction.hpp"
#include "World.hpp"

#include <SFML/System.hpp>


class Wander: public IAction
{
public:
                                           Wander();
    virtual                             ~Wander();
    sf::Vector2f                    doAction(Enemy& enemy);
};
