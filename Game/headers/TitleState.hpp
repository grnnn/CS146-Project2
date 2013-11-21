#ifndef TITLESTATE_HPP_INCLUDED
#define TITLESTATE_HPP_INCLUDED

#include "..\..\engine\headers\State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class TitleState : public State
{
        public:
                TitleState(StateStack& stack, Context context);

                virtual void                draw();
                virtual bool                update(sf::Time dt);
                virtual bool                handleEvent(const sf::Event& event);


        private:
                sf::Sprite                  mBackgroundSprite;
                sf::Text                    mText;
                sf::Text                    mTitle;
                sf::Time                    mTextEffectTime;
                bool                        mShowText;
};



#endif // TITLESTATE_HPP_INCLUDED
