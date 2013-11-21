#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

class GameState : public State
{
        public:
                GameState(StateStack& stack, Context context);

                virtual void                draw();
                virtual bool                update(sf::Time dt);
                virtual bool                handleEvent(const sf::Event& event);


        private:
                sf::Sprite                  mBackgroundSprite;
};

#endif // GAMESTATE_H_INCLUDED
