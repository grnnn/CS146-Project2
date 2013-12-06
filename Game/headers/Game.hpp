#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "..\..\engine\headers\ResourceHolder.hpp"
#include "..\..\engine\headers\ResourceIdentifier.hpp"
#include "..\..\engine\headers\StateStack.hpp"
#include "Player.hpp"
#include "SpaceCraft.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

class Game : private sf::NonCopyable
{
    public:
                                Game();
        void                    run();
    protected:
        void                    update(sf::Time elapsedTime);
        void                    updateStatistics(sf::Time elapsedTime);
        void                    draw();
        void                    processEvents();
        void                    registerStates();
        int                     getLives();
        int                     getScore();
        void                    setLives(int i);
        void                    setScore(int i);
    private:
        static const sf::Time   TimePerFrame;


        sf::RenderWindow        gameWindow;
        TextureHolder           gameTextures;
        FontHolder              gameFont;
        //Player                  gamePlayer;
        StateStack              gameStateStack;
        sf::Text                gameStatisticsText;
        sf::Time                gameStatisticsUpdateTime;
        std::size_t             gameStatisticsNumFrames;

};

#endif // GAME_HPP_INCLUDED
