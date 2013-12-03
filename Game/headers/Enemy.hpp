#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include "../../engine/headers/Entity.hpp"
#include "../../engine/headers/ResourceIdentifier.hpp"


class Enemy : public Entity
{
    public:
        Enemy(const TextureHolder& textures);

        enum Type
        {
            Loner,
            Swarmer,
            Flocker,
            Leader
        };

        enum IState
        {
            // Loners
            LWander,
            LRushPlayer,

            //Swarmers
            SWander,
            SSwarmPlayer,
            SRushPlayer,

            // Flockers
            FWander,
            FRushPlayer,
            FFollowLeader,

            //Leader
            LeadWander,
            LeadRushPlayer
        };

        void                        processEvents();
        void                        update(sf::Time dt);

        void                        setType(std::string i_type);
        void                        setState(std::string i_state);

        bool                        isLoner();
        bool                        isSwarmer();
        bool                        isFlocker();
        bool                        isLeader();

        int                         getState();

    private:
        virtual void                drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Sprite                  mSprite;
        Type                        type;
        IState                      state;
};

#endif // ENEMY_HPP_INCLUDED
