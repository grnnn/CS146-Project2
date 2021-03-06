#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED

#include "StateIdentifiers.hpp"
#include "ResourceIdentifier.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace sf
{
        class RenderWindow;
}

class StateStack;
class Player;

class State
{
        public:
                typedef std::unique_ptr<State> Ptr;

                struct Context
                {
                        Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts);

                        sf::RenderWindow*    window;
                        TextureHolder*       textures;
                        FontHolder*          fonts;
                };


        public:
                                                        State(StateStack& stack, Context context);
                virtual                                ~State();

                virtual void                draw() = 0;
                virtual bool                update(sf::Time dt) = 0;
                virtual bool                handleEvent(const sf::Event& event) = 0;


        protected:
                void                                requestStackPush(States::ID stateID);
                void                                requestStackPop();
                void                                requestStateClear();

                Context                             getContext() const;


        private:
                StateStack*                        mStack;
                Context                            mContext;
};

#endif // STATE_HPP_INCLUDED
