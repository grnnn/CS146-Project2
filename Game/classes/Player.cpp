#include "../headers/Player.hpp"
#include "../../engine/headers/CommandQueue.hpp"
#include "../headers/SpaceCraft.hpp"
#include "../../engine/headers/Command.hpp"
#include "../headers/SpaceCraftActions.hpp"


#include <map>
#include <string>
#include <algorithm>
#include <iostream>

Player::Player(sf::RenderWindow& window, World& world)
: mWindow(window)
, mWorld(&world)
{

        // Set initial key bindings
        mKeyBinding[sf::Keyboard::A] = MoveLeft;
        mKeyBinding[sf::Keyboard::D] = MoveRight;
        mKeyBinding[sf::Keyboard::W] = MoveUp;
        mKeyBinding[sf::Keyboard::S] = MoveDown;
        mKeyBinding[sf::Keyboard::Space] = Fire;

        // Set initial action bindings
        initializeActions();
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
        if (event.type == sf::Event::KeyPressed)
        {
                // Check if pressed key appears in key binding, trigger command if so
                auto found = mKeyBinding.find(event.key.code);


                if (found != mKeyBinding.end() && !isRealtimeAction(found->second)){
                        std::cout << "Push onto commands";
                        commands.push(mActionBinding.at(found->second));
                }
        }
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
        //SceneNode* craft = mWorld->getPlayer();

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

            sf::Vector2f velocity(dx, dy);
            mRotation = velocity;

            //Command Rcmd(*craft);
            mActionBinding.at(Rotate).action = derivedAction<SpaceCraft>(SpaceCraftRotater(rotation + 180));
            //mActionBinding.insert(std::make_pair(Rotate, std::move(Rcmd)));

            commands.push(mActionBinding.at(Rotate));
        }


        // Traverse all assigned keys and check if they are pressed
        for(auto pair = mKeyBinding.rbegin(); pair != mKeyBinding.rend(); ++pair)
        {
                // If key is pressed, lookup action and trigger corresponding command
                if (sf::Keyboard::isKeyPressed((*pair).first) && isRealtimeAction((*pair).second))
                        commands.push(mActionBinding.at((*pair).second) );
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

        SceneNode* craft = mWorld->getPlayer();
        SceneNode* air = mWorld->getAirLayer();

        Command MLcmd(*craft);
        MLcmd.action = derivedAction<SpaceCraft>(SpaceCraftMover(-playerSpeed, 0.f));
        mActionBinding.insert(std::make_pair(MoveLeft, std::move(MLcmd)));

        Command MRcmd(*craft);
        MRcmd.action = derivedAction<SpaceCraft>(SpaceCraftMover(+playerSpeed, 0.f));
        mActionBinding.insert(std::make_pair(MoveRight, std::move(MRcmd)));

        Command MUcmd(*craft);
        MUcmd.action = derivedAction<SpaceCraft>(SpaceCraftMover(0.f, -playerSpeed));
        mActionBinding.insert(std::make_pair(MoveUp, std::move(MUcmd)));

        Command MDcmd(*craft);
        MDcmd.action = derivedAction<SpaceCraft>(SpaceCraftMover(0.f, +playerSpeed));
        mActionBinding.insert(std::make_pair(MoveDown, std::move(MDcmd)));

        Command Rcmd(*craft);
        Rcmd.action = nullptr;
        mActionBinding.insert(std::make_pair(Rotate, std::move(Rcmd)));

        Command Firecmd(*air);
        Firecmd.action = [this](SceneNode& node, sf::Time time)
        {

            this->mWorld->getPlayer()->checkProjectileLaunch(mWorld->getCommandQueue(), mWorld->getTextures(), mRotation);

        };
        mActionBinding.insert(std::make_pair(Fire, std::move(Firecmd)));
}

bool Player::isRealtimeAction(Action action)
{
        switch (action)
        {
                case Fire:
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
sf::Vector2f Player::getmRotations()
{
    return mRotation;
}

