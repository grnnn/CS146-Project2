#include "..\headers\Projectile.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include "../../engine/headers/Entity.hpp"
#include "../../engine/headers/ResourceIdentifier.hpp"
#include "../../engine/headers/Command.hpp"
#include "../../engine/headers/Utility.hpp"
#include "../../engine/headers/CommandQueue.hpp"
#include <iostream>



Projectile::Projectile(const TextureHolder& textures)
: mType(AlliedBullet)
, mSprite(textures.get(Textures::Enemy))
{
    centerOrigin(mSprite);
}
Projectile::~Projectile()
{
    //dtor
}
void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}


void Projectile::updateCurrent(sf::Time dt,
        CommandQueue& commands){}
sf::FloatRect Projectile::getBoundingRect() const
{
    return getWorldTransform()
    .transformRect(mSprite.getGlobalBounds());
}

float Projectile::getMaxSpeed() const{return 100;}
