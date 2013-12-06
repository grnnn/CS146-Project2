#include "../FSM/IAction.hpp"
#include "World.hpp"

#include <SFML/System.hpp>
class SpaceCraft;

class Snake: public IAction
{
public:
                                           Snake();
    virtual                             ~Snake();
    sf::Vector2f                    doAction(Enemy& enemy, Enemy& leader, World& world);
};
