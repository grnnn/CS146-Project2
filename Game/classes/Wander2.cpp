
#include "../headers/VectorUtil.hpp"
#include "../headers/Enemy.hpp"

#include "../headers/Wander2.hpp"
#include <SFML/System/Vector2.hpp>


Wander2::~Wander2() {}

Wander2::Wander2()
{
}
sf::Vector2f Wander2::doAction(Enemy& enemy)
{
    VectorUtil* util = new VectorUtil();

  float CIRCLE_DISTANCE = 100;
    float CIRCLE_RADIUS = 90;
    float ANGLE_CHANGE = 50;
    float wanderAngle = 0;

    //Set values
    sf::Vector2f velocity = enemy.getVelocity();

    float max_speed = 180;
    float max_force = 10;



/*
    float CIRCLE_DISTANCE = 20;
    float CIRCLE_RADIUS = 10;
    float ANGLE_CHANGE = 20;
    float wanderAngle = 0;

    //Set values
     sf::Vector2f velocity = enemy.getVelocity();

    float max_speed = 120;
    float max_force = 20;
*/

   sf::Vector2f circleCenter = velocity;
   circleCenter = util->normalize(circleCenter);
   circleCenter *= CIRCLE_DISTANCE;

    sf::Vector2f displacement(0, -1);
    displacement*= (CIRCLE_RADIUS);

   float len = util->length(&displacement);
   wanderAngle +=rand() * ANGLE_CHANGE - (ANGLE_CHANGE * 0.5) ;

   displacement.x =cos(wanderAngle) * len;
   displacement.y = sin(wanderAngle) * len;
//std::cout<<"Displacement.x: "<<displacement.x<< ",Displacement.y: "<<displacement.y<<"\n";
   // Wander force
   sf::Vector2f wanderForce = circleCenter + (displacement);

   //TAKE VELOCITY PASSED IN AND MOVE IT BY WANDER FORCE
   sf::Vector2f steering = wanderForce;
   steering = util->truncate(steering, max_force);
   velocity = util->truncate (velocity + steering, max_speed);


   return velocity;

}
