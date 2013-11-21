#include "..\headers\Game.hpp"
#include "..\..\engine\headers\StringHelpers.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// Define the time per frame to be 1/60th of a second, for an FPS of 60
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game()
: gameWindow(sf::VideoMode(640, 480), "Project 2", sf::Style::Close)
, gameFont()
, gameStatisticsText()
, gameStatisticsUpdateTime()
, gameStatisticsNumFrames(0)
{
        gameFont.loadFromFile("Media/LinLibertine.ttf");
        gameStatisticsText.setFont(gameFont);
        gameStatisticsText.setPosition(5.f, 5.f);
        gameStatisticsText.setCharacterSize(10);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(gameWindow.isOpen()){

        // elapsedTime is the time it takes for the loop to run once.
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        // if the loop has taken more than 1/60 of a second to run
        while(timeSinceLastUpdate > TimePerFrame){
            timeSinceLastUpdate -= TimePerFrame;

            processEvents();
            update(TimePerFrame);
        }

        updateStatistics(elapsedTime);
        draw();
    }
}

void Game::update(sf::Time elapsedTime)
{

}

void Game::draw()
{
    gameWindow.clear();
    gameWindow.draw(gameStatisticsText);
    gameWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
    gameStatisticsUpdateTime += elapsedTime;
    gameStatisticsNumFrames += 1;

    if(gameStatisticsUpdateTime >= sf::seconds(1.0f)){
        gameStatisticsText.setString(
                            "Frames / Second = " + toString(gameStatisticsNumFrames) + "\n" +
                            "Time / Update = " + toString(gameStatisticsUpdateTime.asMicroseconds() / gameStatisticsNumFrames) + "us");

        gameStatisticsUpdateTime -= sf::seconds(1.0f);
        gameStatisticsNumFrames = 0;
    }
}

void Game::processEvents()
{
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
                switch (event.type)
                {
                        case sf::Event::Closed:
                                gameWindow.close();
                                break;
                        default:
                            break;
                }
        }
}















