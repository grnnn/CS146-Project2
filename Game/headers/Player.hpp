#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include "../../engine/headers/Entity.hpp"
#include "../../engine/headers/ResourceIdentifier.hpp"

class Player : public Entity
{
    public:
        Player(const TextureHolder& textures);
        void processEvents();
        void update(sf::Time dt);
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        sf::Sprite              mSprite;
};

#endif // PLAYER_HPP_INCLUDED
