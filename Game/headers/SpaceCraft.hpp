#ifndef SPACECRAFT_HPP_INCLUDED
#define SPACECRAFT_HPP_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include "../../engine/headers/Entity.hpp"
#include "../../engine/headers/ResourceIdentifier.hpp"


class SpaceCraft : public Entity
{
    public:
        SpaceCraft(const TextureHolder& textures);
        void processEvents();
        void update(sf::Time dt);
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        sf::Sprite              mSprite;
};

#endif // SPACECRAFT_HPP_INCLUDED
