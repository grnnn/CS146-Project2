#ifndef ENEMYCONTROLLER_HPP_INCLUDED
#define ENEMYCONTROLLER_HPP_INCLUDED

#include "../../engine/headers/Command.hpp"
#include "World.hpp"
#include "Enemy.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <map>

// Forward declarations
class CommandQueue;
namespace sf
{
        class RenderWindow;
}

class EnemyController : private sf::NonCopyable
{
        public:
                enum Action
                {
                    Wander,
                    FlockToLeader,
                    FollowLeader,
                    Attack,
                    ActionCount
                };
        public:
                explicit                                     EnemyController(sf::RenderWindow& window, World& world);
                void                                         handleEvent(const sf::Event& event, CommandQueue& commands);
                void                                         update(CommandQueue& commands);
                void                                         spawnEnemy(float x, float y);
                //void                                         initializeStates();
        private:
                static bool                                  isAction(Action action);
        private:
            // @TAYLOR: YOU WILL NEED TO ADD ALL THE STATES HERE AS MEMBERS AS WE DISCUSSED
            //          ADDITIONALLY, YOU MIGHT WANT AN initializeStates() FUNCTION TO SET ALL THEIR TRANSITIONS AND ACTIONS (see above)
                sf::RenderWindow&                            mWindow;
                std::map<sf::Keyboard::Key, Action>          mKeyBinding;
                World*                                       mWorld;
                sf::Clock                                    mSpawnTimer;
};

#endif // ENEMYCONTROLLER_HPP_INCLUDED
