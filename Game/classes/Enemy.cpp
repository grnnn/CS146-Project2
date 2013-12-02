#include "../headers/Enemy.hpp"
#include "../../engine/headers/ResourceHolder.hpp"
#include "../../engine/headers/Utility.hpp"
#include <iostream>

Enemy::Enemy(const TextureHolder& textures)
: mSprite(textures.get(Textures::Enemy))
{
    centerOrigin(mSprite);
}

void Enemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
sf::FloatRect Enemy::getBoundingRect() const
{
    return getWorldTransform()
    .transformRect(mSprite.getGlobalBounds());
}
