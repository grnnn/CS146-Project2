#ifndef LeaderEnemy_HPP_INCLUDED
#define LeaderEnemy_HPP_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include "../../engine/headers/Entity.hpp"
#include "../../engine/headers/ResourceIdentifier.hpp"


class LeaderEnemy : public Entity
{
    public:
        LeaderEnemy(const TextureHolder& textures);

        void                        processEvents();
        void                        update(sf::Time dt);

        float                       getMaxSpeed();
        float                       getMaxForce();

    private:
        float maxForce;
        float maxSpeed;

        virtual void                drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // LeaderEnemy_HPP_INCLUDED
