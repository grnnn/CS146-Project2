#ifndef ENEMYACTIONS_HPP_INCLUDED
#define ENEMYACTIONS_HPP_INCLUDED

#include "../headers/Enemy.hpp"

#include <iostream> // For testing

/** This is where the Enemy Actions will be implememnted.
 * There are two ways to do this, I leave the decision up to Taylor and Tyler
 * 1. Implement these structs to be our "large" actions, like Wander and FollowLeader
 *      With this implementation, our code might look like this
 *
 *      struct Wander
 *      {
 *          Wander()
 *          {
 *          }
 *
 *          void operator() (Enemy& enemy, sf::Time) const
 *          {
 *                 -- IMPLEMENT WANDER LOGIC HERE --
 *
 *                 enemy.accelerate(FINAL_VELOCITY_VECTOR_AS_DETERMINED_BY_WANDER_LOGIC);
 *          }
 *      };
 *
 * 2. Alternatively, we can do all of the wander logic outside of these structs, then just pass in the final movement vector. This will look
 *    more like the code you see in SpaceCraftActions
 */
       struct EnemyMover
       {
           EnemyMover(float vx, float vy)
           : velocity(vx, vy)
           {
           }

           void operator() (Enemy& enemy, sf::Time) const
           {
                   enemy.accelerate(velocity);
           }

           sf::Vector2f velocity;
       };


#endif // ENEMYACTIONS_HPP_INCLUDED
