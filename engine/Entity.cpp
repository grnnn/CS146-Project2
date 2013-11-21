#include "headers\Entity.hpp"

void Entity::setVelocity(sf::Vector2f v)
{
    velocity = v;
}

void Entity::setVelocity(float vx, float vy)
{
    velocity.x = vx;
    velocity.y = vy;
}

void Entity::setPosition(sf::Vector2f p)
{
    position = p;
}

void Entity::setPosition(float px, float py)
{
    position.x = px;
    position.y = py;
}

sf::Vector2f Entity::getVelocity() const
{
    return velocity;
}

sf::Vector2f Entity::getPosition() const
{
    return position;
}
