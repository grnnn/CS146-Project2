#include "../headers/SpaceCraft.hpp"
#include "../../engine/headers/ResourceHolder.hpp"
#include "../../engine/headers/Utility.hpp"
#include "../../engine/headers/Command.hpp"
#include "../headers/World.hpp"

#include <iostream>
#include <math.h>

SpaceCraft::SpaceCraft(const TextureHolder& textures, World& world)
: mWorld(&world)
, mTimer(0)

{
    sf::Sprite spr(textures.get(Textures::SpaceCraft));
    centerOrigin(spr);
    setSprite(spr);
    setID(100);
}

void SpaceCraft::createBullets(SceneNode& node, const TextureHolder& textures, sf::Vector2f mRotations) const
{

    createProjectile(node, 0.0f, 0.5f, textures, mRotations);
}

void SpaceCraft::checkProjectileLaunch(CommandQueue& commands, const TextureHolder& textures, sf::Vector2f mRotations)
{
    if (mTimer > 10)
    {
        mTimer = 0;
        SceneNode* air = mWorld->getAirLayer();
        Command mFireCommand(*air);
        mFireCommand.action = [this, &textures, mRotations](SceneNode& node, sf::Time)
        {
            createBullets (node, textures, mRotations);
        };
        commands.push(mFireCommand);
        mIsFiring = false;
    }
}

void SpaceCraft::createProjectile(SceneNode& node, float xOffset, float yOffset, const TextureHolder&
                             textures, sf::Vector2f mRotations)const
{

    Projectile* projectile(
        new Projectile(textures));
    sf::Vector2f offset(
        xOffset * getSprite().getGlobalBounds().width,
        yOffset * getSprite().getGlobalBounds().height);

    //sf::Vector2f velocity(mRotations, projectile->getMaxSpeed());
    float sign = -300.f;

    float len = sqrt((mRotations.x * mRotations.x) +(mRotations.y * mRotations.y));
    mRotations.x = mRotations.x / len;
    mRotations.y = mRotations.y / len;
    projectile->setPosition(getWorldPosition());
    projectile->setVelocity(mRotations * sign);
    node.attachChild(std::move(projectile));

}
void SpaceCraft::updateCurrent(sf::Time dt)
{
    mTimer++;
    move(getVelocity() * dt.asSeconds());
}


void SpaceCraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(getSprite(), states);
}




