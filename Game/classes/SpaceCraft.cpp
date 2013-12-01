#include "../headers/SpaceCraft.hpp"
#include "../../engine/headers/ResourceHolder.hpp"
#include "../../engine/headers/Utility.hpp"
#include <iostream>

SpaceCraft::SpaceCraft(const TextureHolder& textures)
: mSprite(textures.get(Textures::SpaceCraft))
{
    centerOrigin(mSprite);
}

void SpaceCraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
