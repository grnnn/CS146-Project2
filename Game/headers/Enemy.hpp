#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include "../../engine/headers/Entity.hpp"
#include "../../engine/headers/ResourceIdentifier.hpp"


class Enemy : public Entity
{
    public:
        Enemy(const TextureHolder& textures);

        void                        processEvents();
        void                        update(sf::Time dt);

        float                       getMaxSpeed();

    private:
        float maxSpeed;

        virtual void                drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // ENEMY_HPP_INCLUDED
