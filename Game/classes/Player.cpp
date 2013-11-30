#include "../headers/Player.hpp"
#include "../../engine/headers/CommandQueue.hpp"
#include "../headers/SpaceCraft.hpp"
#include "../../engine/headers/Command.hpp"
#include "../headers/SpaceCraftActions.hpp"

#include <map>
#include <string>
#include <algorithm>
#include <iostream>

Player::Player(sf::RenderWindow& window)
: mWindow(window)
{
        //lastMousePosition = sf::Mouse::getPosition(mWindow);

        // Set initial key bindings
        mKeyBinding[sf::Keyboard::Left] = MoveLeft;
        mKeyBinding[sf::Keyboard::Right] = MoveRight;
        mKeyBinding[sf::Keyboard::Up] = MoveUp;
        mKeyBinding[sf::Keyboard::Down] = MoveDown;

        // Set initial action bindings
        initializeActions();

        // Assign all categories to player's aircraft
        for(auto& pair : mActionBinding)
                pair.second.category = Category::PlayerSpaceCraft;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
        if (event.type == sf::Event::KeyPressed)
        {
                // Check if pressed key appears in key binding, trigger command if so
                auto found = mKeyBinding.find(event.key.code);
                /*if (!(found != mKeyBinding.end()))
                    std::cout << "found != mKeyBinding.end() returned false";
                if (!(!isRealtimeAction(found->second)))
                    std::cout << "!isRealtimeAction(found->second) returned false";*/
                if (found != mKeyBinding.end() && !isRealtimeAction(found->second)){
                    //std::cout << "Also got here.\n";
                        commands.push(mActionBinding[found->second]);
                }
        }
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
        // Update delta mouse
        sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
        deltaMouse = lastMousePosition - mousePosition;
        sf::Vector2f spritePos = mWorld->getPlayerPosition();

        // If the mouse has moved, we must update the sprites rotation
        if ((deltaMouse.x != 0 && deltaMouse.y != 0) || (lastPlayerPosition != spritePos)){

            const float PI = 3.14159265;

            float dx = spritePos.x - mousePosition.x;
            float dy = spritePos.y - mousePosition.y;

            float rotation = (atan2(dy, dx)) * 180 / PI;

            mActionBinding[Rotate].action = derivedAction<SpaceCraft>(SpaceCraftRotater(rotation + 180));

            commands.push(mActionBinding[Rotate]);
        }


        // Traverse all assigned keys and check if they are pressed
        for(auto pair = mKeyBinding.rbegin(); pair != mKeyBinding.rend(); ++pair)
        {
                // If key is pressed, lookup action and trigger corresponding command
                if (sf::Keyboard::isKeyPressed((*pair).first) && isRealtimeAction((*pair).second))
                        commands.push(mActionBinding[(*pair).second]);
        }

        lastMousePosition = mousePosition;
        lastPlayerPosition = spritePos;
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
        // Remove all keys that already map to action
        for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
        {
                if (itr->second == action)
                        mKeyBinding.erase(itr++);
                else
                        ++itr;
        }

        // Insert new binding
        mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
        for(auto pair = mKeyBinding.rbegin(); pair != mKeyBinding.rend(); ++pair)
        {
                if ((*pair).second == action)
                        return (*pair).first;
        }

        return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
        const float playerSpeed = 250.f;

        mActionBinding[MoveLeft].action = derivedAction<SpaceCraft>(SpaceCraftMover(-playerSpeed, 0.f));
        mActionBinding[MoveRight].action = derivedAction<SpaceCraft>(SpaceCraftMover(+playerSpeed, 0.f));
        mActionBinding[MoveUp].action = derivedAction<SpaceCraft>(SpaceCraftMover(0.f, -playerSpeed));
        mActionBinding[MoveDown].action = derivedAction<SpaceCraft>(SpaceCraftMover(0.f, +playerSpeed));
        mActionBinding[Rotate].action = nullptr;
}

bool Player::isRealtimeAction(Action action)
{
        switch (action)
        {
                case MoveLeft:
                case MoveRight:
                case MoveDown:
                case MoveUp:
                case Rotate:
                        return true;
                default:
                        return false;
        }
}

void Player::setWorld(World& world)
{
    mWorld = &world;
}
