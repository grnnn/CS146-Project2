#include "../headers/GameState.hpp"
#include "../headers/World.hpp"
#include "../../engine/headers/Command.hpp"
#include "../../engine/headers/CommandQueue.hpp"


GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window)
, mPlayer(*context.window, mWorld)
, mEnemyController(*context.window, mWorld)


{


}

void GameState::draw()
{
        mWorld.draw();

}

bool GameState::update(sf::Time dt)
{
        mWorld.update(dt);

//        if(mWorld->getLives() == 0)stack

        CommandQueue& commands = mWorld.getCommandQueue();
        mPlayer.handleRealtimeInput(commands);
        mEnemyController.update(commands);

        return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
        // Game input handling
        CommandQueue& commands = mWorld.getCommandQueue();
        mPlayer.handleEvent(event, commands);

        // Escape pressed, trigger the pause screen
        //if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        //        requestStackPush(States::Pause);

        return true;
}

