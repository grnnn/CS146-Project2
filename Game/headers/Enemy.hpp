#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include "../../engine/headers/Entity.hpp"
#include "../../engine/headers/ResourceIdentifier.hpp"
#include "World.hpp"

class World;
class Enemy : public Entity
{
    public:
        Enemy(const TextureHolder& textures, World& world);

        void                        processEvents();
        void                        update(sf::Time dt);

        float                       getMaxSpeed();
        float                       getMaxForce();

    public:
        bool listRemoval;

    private:
        float maxForce;
        float maxSpeed;
        World* mWorld;
        virtual void updateCurrent(sf::Time dt);

        virtual void                drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // ENEMY_HPP_INCLUDED
