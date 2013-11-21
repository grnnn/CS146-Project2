#include "../headers/GameState.hpp"


GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window)
{
}

void GameState::draw()
{
        mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
        mWorld.update(dt);

        return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
        // Escape pressed, trigger the pause screen
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                requestStackPush(States::Pause);

        return true;
}
