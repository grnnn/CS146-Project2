#include "..\headers\TitleState.hpp"
#include "..\..\engine\headers\Utility.hpp"
#include "..\..\engine\headers\ResourceHolder.hpp"
#include <iostream>


#include <SFML/Graphics/RenderWindow.hpp>


TitleState::TitleState(StateStack& stack, Context context)
: State(stack, context)
, mText()
, mShowText(true)
{
        mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

        mText.setFont(context.fonts->get(Fonts::Main));
        mTitle.setFont(context.fonts->get(Fonts::Main));
        mText.setString("Press any key to start");
        mTitle.setString("Title Screen");
        centerOrigin(mText);
        centerOrigin(mTitle);
        sf::Vector2<float> pos = (context.window->getView().getSize() / 2.f);
        //Debug
            std::cout << "Position = (" << pos.x << ", " << pos.y << ")";
        mText.setPosition(context.window->getView().getSize() / 2.f);
        mTitle.setPosition(context.window->getView().getSize().x / 2.f, context.window->getView().getSize().y / 4.f);
}

void TitleState::draw()
{
        sf::RenderWindow& window = *getContext().window;

        window.draw(mBackgroundSprite);
        window.draw(mTitle);
        if (mShowText)
                window.draw(mText);
}

bool TitleState::update(sf::Time dt)
{
        mTextEffectTime += dt;

        if (mTextEffectTime >= sf::seconds(0.5f))
        {
                mShowText = !mShowText;
                mTextEffectTime = sf::Time::Zero;
        }

        return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
        // If any key is pressed, trigger the next screen
        /*if (event.type == sf::Event::KeyPressed)
        {
                requestStackPop();
                requestStackPush(States::Game);
        }*/

        return true;
}
