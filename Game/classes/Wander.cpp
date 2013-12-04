
#include "../headers/VectorUtil.hpp"
#include "../headers/Enemy.hpp"
#include "../headers/Wander.hpp"

#include <SFML/System/Vector2.hpp>
#include <math.h>

Wander::~Wander() {}

Wander::Wander()
{
}
sf::Vector2f Wander::doAction(Enemy& enemy)
{
 VectorUtil* util = new VectorUtil();

    float CIRCLE_DISTANCE = 10;
    float CIRCLE_RADIUS = 20;
    float ANGLE_CHANGE = 20;
    float wanderAngle = 0;

    //Set values
    float max_speed = enemy.getMaxSpeed();
    float max_force = enemy.getMaxForce();
    sf::Vector2f velocity = enemy.getVelocity();

   // Calculate the circle center
   sf::Vector2f circleCenter = velocity;
   util->normalize(circleCenter);
   circleCenter *= CIRCLE_DISTANCE;

   // Calculate the displacement force
 sf::Vector2f displacement(0, -1);
   displacement*= (CIRCLE_RADIUS);

   // Randomly change the vector direction
   // by making it change its current angle


   float len = util->length(&displacement);
   displacement.x =cos(wanderAngle) * len;
   displacement.y = sin(wanderAngle) * len;

   // Change wanderAngle just a bit, so it
   // won't have the same value in the
   // next game frame.
   wanderAngle +=rand() * ANGLE_CHANGE - ANGLE_CHANGE * .5;

   // Finally calculate and return the wander force

   sf::Vector2f wanderForce = circleCenter + (displacement);
   return wanderForce;


}
