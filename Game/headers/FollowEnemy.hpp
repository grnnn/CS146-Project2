#ifndef FollowEnemy_HPP_INCLUDED
#define FollowEnemy_HPP_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include "../../engine/headers/Entity.hpp"
#include "../../engine/headers/ResourceIdentifier.hpp"
#include "LeaderEnemy.hpp"


class FollowEnemy : public Entity
{
    public:
        FollowEnemy(const TextureHolder& textures);

        void                        processEvents();
        void                        update(sf::Time dt);

        float                       getMaxSpeed();
        float                       getMaxForce();
        void                        setLeader(LeaderEnemy& l);
        LeaderEnemy*                getLeader();

    private:
        float maxForce;
        float maxSpeed;
        LeaderEnemy* leader;

        virtual void                drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // FollowEnemy_HPP_INCLUDED
