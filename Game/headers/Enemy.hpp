#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include "../../engine/headers/Entity.hpp"
#include "../../engine/headers/ResourceIdentifier.hpp"
#include "IState.hpp"


class Enemy : public Entity
{
    public:

        enum Type
        {
            Loner,
            Swarmer,
            Flocker,
            Leader
        };



        Enemy(const TextureHolder& textures, std::string m_type, IState m_state);

        void                        processEvents();
        void                        update(sf::Time dt);

        void                        setType(std::string i_type);
        void                        setState(std::string i_state);

        bool                        isLoner();
        bool                        isSwarmer();
        bool                        isFlocker();
        bool                        isLeader();

        int                         getState();

        void                        setState(IState i_state);

    private:
        virtual void                drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Sprite                  mSprite;
        Type                        type;
        IState                      state;
};

#endif // ENEMY_HPP_INCLUDED
