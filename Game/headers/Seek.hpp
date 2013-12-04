
#include "../FSM/IAction.hpp"
#include "World.hpp"

#include <SFML/System.hpp>


class Seek: public IAction
{
public:
                                           Seek();
    virtual                             ~Seek();
    sf::Vector2f                    doAction(Enemy& enemy, sf::Vector2f target);
};
