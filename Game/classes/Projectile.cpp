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
{
    sf::Sprite spr(textures.get(Textures::Projectile));
    centerOrigin(spr);
    setSprite(spr);
    setID(1);
}
Projectile::~Projectile()
{
    //dtor
}
void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(getSprite(), states);
}


void Projectile::updateCurrent(sf::Time dt){
    move(getVelocity() * dt.asSeconds());
    checkOutOfBounds();

}

void Projectile::checkOutOfBounds()
{
    if(getPosition().x < -10 || getPosition().x > 680 || getPosition().y < -10 || getPosition().y > 500){
        markForRemoval();
    }
}


float Projectile::getMaxSpeed() const{return 100;}
