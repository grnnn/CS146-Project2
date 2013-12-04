#ifndef ENEMYCONTROLLER_HPP_INCLUDED
#define ENEMYCONTROLLER_HPP_INCLUDED

#include "../../engine/headers/Command.hpp"
#include "World.hpp"
#include "Enemy.hpp"

#include "../FSM/StateMachine.hpp"

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
        public:
                explicit                                     EnemyController(sf::RenderWindow& window, World& world);
                void                                         handleEvent(const sf::Event& event, CommandQueue& commands);
                void                                         update(CommandQueue& commands);
                void                                         spawnEnemy(float x, float y, std::string type, IState state);
                void                                         initializeStates();

                FState*                                      sortState(int n);
                IState                                       sortFIStates(FState *state);
        private:

        private:
            // @TAYLOR: YOU WILL NEED TO ADD ALL THE STATES HERE AS MEMBERS AS WE DISCUSSED
            //          ADDITIONALLY, YOU MIGHT WANT AN initializeStates() FUNCTION TO SET ALL THEIR TRANSITIONS AND ACTIONS (see above)
                sf::RenderWindow&                            mWindow;
                World*                                       mWorld;
                sf::Clock                                    mSpawnTimer;

                StateMachine                                 FSM;

                //Loner State machine components
                FState                                       LWander;
                FState                                       LRushPlayer;

                //Swarmer State Machine Components
                FState                                       SWander;
                FState                                       SRushPlayer;
                FState                                       SSwarmPlayer;

                //Flocker State Machine Components
                FState                                       FWander;
                FState                                       FFollowLeader;
                FState                                       FRushPlayer;

                //Leader State Machine Components
                FState                                       LeadWander;
                FState                                       LeadRushPlayer;

};

#endif // ENEMYCONTROLLER_HPP_INCLUDED
