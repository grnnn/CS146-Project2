#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "SceneNode.hpp"
//include "CommandQueue.hpp"

class Entity: public SceneNode
{
    public:
        void            setVelocity(sf::Vector2f v);
        void            setVelocity(float vx, float vy);
        void            accelerate(sf::Vector2f velocity);
        void            accelerate(float vx, float vy);
        sf::Vector2f    getVelocity() const;
    private:
        virtual void    updateCurrent(sf::Time dt);
        sf::Vector2f    mVelocity;
        sf::Vector2f    mPosition;
        //sf::Vector3f    mOrientation;
};

#endif // ENTITY_HPP_INCLUDED
