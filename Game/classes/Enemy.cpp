#include "../headers/Enemy.hpp"
#include "../../engine/headers/ResourceHolder.hpp"
#include "../../engine/headers/Utility.hpp"
#include <iostream>

Enemy::Enemy(const TextureHolder& textures)

{
    sf::Sprite spr(textures.get(Textures::Enemy));
    centerOrigin(spr);
    setSprite(spr);
    setID(2);
}

void Enemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(getSprite(), states);
}


