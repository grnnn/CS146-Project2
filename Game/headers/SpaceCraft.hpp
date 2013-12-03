#ifndef SPACECRAFT_HPP_INCLUDED
#define SPACECRAFT_HPP_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include "../../engine/headers/Entity.hpp"
#include "Projectile.hpp"
#include "../../engine/headers/ResourceIdentifier.hpp"
#include "../../engine/headers/Command.hpp"
#include "Player.hpp"

#include <iostream>
class World;
class CommandQueue;

class SpaceCraft : public Entity
{
    public:
        SpaceCraft(const TextureHolder& textures, World& world);
        void processEvents();

        void fire();
        void createBullets(SceneNode& node, const
                           TextureHolder& texture, sf::Vector2f mRotations) const;
        void createProjectile(SceneNode& node, float xOffset, float yOffset, const TextureHolder& textures, sf::Vector2f mRotations) const;
        void checkProjectileLaunch(CommandQueue& commands, const TextureHolder& textures, sf::Vector2f mRotations);

    public:
        bool                                         mIsFiring;
        int mTimer;


    private:
        //virtual void updateCurrent(sf::Time dt);
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void updateCurrent(sf::Time dt);

        World*                                       mWorld;



};

#endif // SPACECRAFT_HPP_INCLUDED
