
#include "../FSM/IAction.hpp"
#include "World.hpp"

#include <SFML/System.hpp>


class Wander2: public IAction
{
public:
                                           Wander2();
    virtual                             ~Wander2();
    sf::Vector2f                    doAction(LeaderEnemy& enemy);
};
