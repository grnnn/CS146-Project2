#include "../headers/SpaceCraft.hpp"
#include "../../engine/headers/ResourceHolder.hpp"
#include "../../engine/headers/Utility.hpp"
#include "../../engine/headers/Command.hpp"
#include "../headers/World.hpp"
#include <iostream>

SpaceCraft::SpaceCraft(const TextureHolder& textures, World& world)
: mSprite(textures.get(Textures::SpaceCraft))
, mWorld(&world)

{
    centerOrigin(mSprite);

}

void SpaceCraft::createBullets(SceneNode& node, const TextureHolder& textures) const
{

    createProjectile(node, 0.0f, 0.5f, textures);
}

void SpaceCraft::checkProjectileLaunch(CommandQueue& commands, const TextureHolder& textures)
{
    if (mIsFiring)
    {

        SceneNode* air = mWorld->getAirLayer();
        Command mFireCommand(*air);
        mFireCommand.action = [this, &textures](SceneNode& node, sf::Time)
        {
            createBullets (node, textures);
        };
        commands.push(mFireCommand);
        mIsFiring = false;
    }
}

void SpaceCraft::createProjectile(SceneNode& node, float xOffset, float yOffset, const TextureHolder&
                             textures)const
{

    Projectile* projectile(
        new Projectile(textures));
    sf::Vector2f offset(
        xOffset * mSprite.getGlobalBounds().width,
        yOffset * mSprite.getGlobalBounds().height);
    sf::Vector2f velocity(0, projectile->getMaxSpeed());
    float sign = -1.f;
    projectile->setPosition(getWorldPosition() + offset * sign);
    projectile->setVelocity(velocity * sign);
    node.attachChild(std::move(projectile));

}


void SpaceCraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(mSprite, states);
}


