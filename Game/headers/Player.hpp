#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "../../engine/headers/Command.hpp"
#include "World.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/System/NonCopyable.hpp>



#include <map>

// Forward declarations
class CommandQueue;
namespace sf
{
        class RenderWindow;
}

class Player : private sf::NonCopyable
{
        public:
                enum Action
                {
                        MoveLeft,
                        MoveRight,
                        MoveUp,
                        MoveDown,
                        Rotate,
                        ActionCount
                };
        public:
                explicit                                     Player(sf::RenderWindow& window, World& world);
                void                                         handleEvent(const sf::Event& event, CommandQueue& commands);
                void                                         handleRealtimeInput(CommandQueue& commands);

                void                                         assignKey(Action action, sf::Keyboard::Key key);
                sf::Keyboard::Key                            getAssignedKey(Action action) const;
        private:
                void                                         initializeActions();
                static bool                                  isRealtimeAction(Action action);
        private:
                sf::RenderWindow&                            mWindow;
                std::map<sf::Keyboard::Key, Action>          mKeyBinding;
                std::map<Action, Command>                    mActionBinding;

                sf::Vector2i                                 deltaMouse;
                sf::Vector2i                                 lastMousePosition;
                sf::Vector2f                                 lastPlayerPosition;

                World*                                       mWorld;
};

#endif // PLAYER_HPP_INCLUDED
