
#include "../headers/VectorUtil.hpp"
#include "../headers/Enemy.hpp"

#include "../headers/Seek.hpp"
#include <SFML/System/Vector2.hpp>




Seek::~Seek(){}

Seek::Seek(){
}
sf::Vector2f Seek::doAction(Enemy& enemy, sf::Vector2f target){
VectorUtil* util = new VectorUtil();

float maxSpeed = enemy.getMaxSpeed();
sf::Vector2f velocity = enemy.getVelocity();
sf::Vector2f position = enemy.getPosition();

sf::Vector2f desired_velocity = util->normalize(position - target) * maxSpeed;
sf::Vector2f steering = desired_velocity - velocity; // Set the steering
velocity = util->truncate (velocity + steering , maxSpeed);
return velocity;
}
