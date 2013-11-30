#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include "../../engine/headers/Entity.hpp"
#include "../../engine/headers/ResourceIdentifier.hpp"


class Enemy : public Entity
{
    public:
        Enemy(const TextureHolder& textures, Category::Type type);

        void                        processEvents();
        void                        update(sf::Time dt);
        virtual unsigned int        getCategory() const;
    private:
        virtual void                drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Sprite                  mSprite;
        Category::Type              mType;
};

#endif // ENEMY_HPP_INCLUDED
