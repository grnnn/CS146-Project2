#include "../headers/Enemy.hpp"
#include "../../engine/headers/ResourceHolder.hpp"
#include "../../engine/headers/Utility.hpp"
#include <iostream>

Enemy::Enemy(const TextureHolder& textures, Category::Type type)
: mSprite(textures.get(Textures::Enemy))
, mType()
{
    mType = type;
    centerOrigin(mSprite);
}

void Enemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

unsigned int Enemy::getCategory() const
{
    return mType;
}
