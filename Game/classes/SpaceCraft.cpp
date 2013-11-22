#include "../headers/SpaceCraft.hpp"
#include "../../engine/headers/ResourceHolder.hpp"

SpaceCraft::SpaceCraft(const TextureHolder& textures)
: mSprite(textures.get(Textures::SpaceCraft))
{
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void SpaceCraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
