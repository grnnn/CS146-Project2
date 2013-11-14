#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Game
{
    public:
                                Game();
        void                    run();
    protected:
        void                    update(sf::Time elapsedTime);
        void                    updateStatistics(sf::Time elapsedTime);
        void                    draw();
        void                    processEvents();
    private:
        static const sf::Time   TimePerFrame;

        sf::RenderWindow        gameWindow;
        sf::Font                gameFont;
        sf::Text                gameStatisticsText;
        sf::Time                gameStatisticsUpdateTime;
        std::size_t             gameStatisticsNumFrames;

};

#endif // GAME_HPP_INCLUDED
