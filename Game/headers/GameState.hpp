#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "../../engine/headers/State.hpp"
#include "World.hpp"
#include "Player.hpp"
#include "EnemyController.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameState : public State
{
        public:
                                            GameState(StateStack& stack, Context context);

                virtual void                draw();
                virtual bool                update(sf::Time dt);
                virtual bool                handleEvent(const sf::Event& event);


        private:
                World                       mWorld;
                Player                      mPlayer;
};

#endif // GAMESTATE_HPP_INCLUDED
