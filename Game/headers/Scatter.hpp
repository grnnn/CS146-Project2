
#include "../FSM/IAction.hpp"
#include "World.hpp"

#include <SFML/System.hpp>


class Scatter: public IAction
{
public:
                                           Scatter();
    virtual                             ~Scatter();
    sf::Vector2f                    doAction(FollowEnemy& enemy);
};
