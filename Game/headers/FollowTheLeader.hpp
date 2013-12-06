#include "../FSM/IAction.hpp"
#include "World.hpp"

#include <SFML/System.hpp>
class SpaceCraft;

class FollowTheLeader: public IAction
{
public:
                                           FollowTheLeader();
    virtual                             ~FollowTheLeader();
    sf::Vector2f                    doAction(FollowEnemy& enemy, LeaderEnemy& leader, World& world);
};
