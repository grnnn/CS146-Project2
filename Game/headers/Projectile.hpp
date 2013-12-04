#ifndef PROJECTILE_HPP_INCLUDED
#define PROJECTILE_HPP_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include "../../engine/headers/Entity.hpp"
#include "../../engine/headers/ResourceIdentifier.hpp"
#include "../../engine/headers/Command.hpp"
#include "World.hpp"
#include "../../engine/headers/CommandQueue.hpp"
#include <iostream>
class Projectile : public Entity
{
    public:
        enum Type
        {
            AlliedBullet,
            EnemyBullet,
            Missile,
            TypeCount
        };
    public:
        Projectile(const TextureHolder& textures);
        void guideTowards(sf::Vector2f position);
        bool isGuided() const;
        void checkOutOfBounds();

        virtual ~Projectile();
        float getMaxSpeed() const;
        int getDamage() const;

    private:
        void updateCurrent(sf::Time dt);
        virtual void drawCurrent(sf::RenderTarget& target,
        sf::RenderStates states) const;
    private:
        Type mType;
        sf::Vector2f mTargetDirection;
};
#endif // PROJECTILE_HPP
