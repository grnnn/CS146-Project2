#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "SceneNode.hpp"

class Entity: public SceneNode
{
    public:
        void            setVelocity(sf::Vector2f v);
        void            setVelocity(float vx, float vy);
        void            setPosition(float px, float py);
        void            setPosition(sf::Vector2f p);
        sf::Vector2f    getVelocity() const;
        sf::Vector2f    getPosition() const;
    private:
        sf::Vector2f    velocity;
        sf::Vector2f    position;
};

#endif // ENTITY_HPP_INCLUDED
