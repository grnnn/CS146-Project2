#ifndef SPACECRAFTACTIONS_HPP_INCLUDED
#define SPACECRAFTACTIONS_HPP_INCLUDED

#include "../headers/SpaceCraft.hpp"

#include <iostream>

struct SpaceCraftMover
{
        SpaceCraftMover(float vx, float vy)
        : velocity(vx, vy)
        {
        }

        void operator() (SpaceCraft& spacecraft, sf::Time) const
        {
                spacecraft.accelerate(velocity);
        }

        sf::Vector2f velocity;
};

struct SpaceCraftRotater
{
        SpaceCraftRotater(float degree)
        : angle(degree)
        {
        }

        void operator() (SpaceCraft& spacecraft, sf::Time) const
        {
                spacecraft.setRotation(angle);
        }

        float angle;
};

#endif // SPACECRAFTACTIONS_HPP_INCLUDED
