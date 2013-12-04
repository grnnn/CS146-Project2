
#include "../headers/VectorUtil.hpp"
#include "../headers/Enemy.hpp"

#include "../headers/Seek.hpp"
#include <SFML/System/Vector2.hpp>




Seek::~Seek() {}

Seek::Seek()
{
}
sf::Vector2f Seek::doAction(Enemy& enemy, sf::Vector2f target)
{
    VectorUtil* util = new VectorUtil();

    float max_speed = enemy.getMaxSpeed();
    float max_force = enemy.getMaxForce();
    sf::Vector2f currentVelocity = enemy.getVelocity();



    sf::Vector2f position = enemy.getPosition();
/*

    sf::Vector2f desired_velocity = util->normalize(target-position)*max_speed;
    sf::Vector2f steering = desired_velocity - currentVelocity;
    steering = util->truncate(steering, max_force);
    sf::Vector2f finalVelocity = util->truncate(currentVelocity + steering, max_speed);
*/
		sf::Vector2f source = position;

		sf::Vector2f des_vel = target - (source);

		float distance = util->length(&des_vel);

		des_vel.x = des_vel.x * (max_speed / distance);
		des_vel.y = des_vel.y * (max_speed /distance);

		des_vel.x = des_vel.x - currentVelocity.x;
		des_vel.y = des_vel.y - currentVelocity.y;

		des_vel.x = des_vel.x * max_force;
		des_vel.y = des_vel.y * max_force;

		return des_vel;


    /*

    sf::Vector2f desired_velocity = util->normalize(target - position) * max_speed;
    sf::Vector2f steering = desired_velocity - currentVelocity;
    steering = steering/ 20.f;
    steering = util->truncate (steering, max_force);

    sf::Vector2f velocity = util->truncate(velocity + steering, max_speed);
*/

   /*
    sf::Vector2f desired_velocity = util->normalize(position - target) * maxSpeed;

    std::cout<<"Max Speed"<<maxSpeed<<"\n";

    sf::Vector2f steering = desired_velocity - velocity; // Set the steering
    steering = util->truncate (velocity + steering , maxSpeed);
*/

    return des_vel;
}
