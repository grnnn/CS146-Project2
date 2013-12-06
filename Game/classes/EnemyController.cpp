#include "../headers/EnemyController.hpp"
#include "../headers/Seek.hpp"
#include "../headers/FollowTheLeader.hpp"
#include "../headers/Wander2.hpp"
#include "../headers/Snake.hpp"
#include <math.h>

#include <iostream>

const float PI = 3.14159265;
const int MAX_NUM_ENEMIES = 50;
const float SPAWN_INTERVAL = 1.0f;

EnemyController::EnemyController(sf::RenderWindow& window, World& world)
    : mWindow(window)
    , mWorld(&world)
{
    spawnGroup (500,100);
}

void EnemyController::spawnEnemy(float x, float y)
{
    mWorld->spawnEnemy(x, y);

}

void EnemyController::spawnGroup(float x, float y)
{
    mWorld->spawnLeaderEnemy(x, y);
    for(int i=5; i>0; i--)
    {
        float winX = mWindow.getDefaultView().getSize().x;
        float winY = mWindow.getDefaultView().getSize().y;
        float x2 = rand() % (int)winX/7;
        float y2 = rand() % (int)winY/7;
        mWorld->spawnFollowEnemy(x+x2,y+y2);
        mWorld->getFollowEnemies().back()->setLeader(*mWorld->getLeaderEnemies().back());
    }

}


void EnemyController::update(CommandQueue& commands)
{

    sf::Vector2f playerPosition= mWorld->getPlayerPosition();
    sf::Vector2f enemyVelocity;

    Seek* seekObj = new Seek();
    FollowTheLeader* fObj = new FollowTheLeader();
    Wander2* wObj = new Wander2();
    Snake* snakeObj = new Snake();

    int h = 0;
    Enemy* lastEnemy;


    // LEADERS -- WANDER
    for(auto &  i : mWorld->getLeaderEnemies())
    {
        enemyVelocity = wObj->doAction(*i);
        i->setVelocity(enemyVelocity);
        float dx = enemyVelocity.x;
        float dy = enemyVelocity.y;
        float rotation = (atan2(dx*-1,dy)) * 180 / PI;
        i->setRotation(rotation);
    }

    // FOLLOWERS -- FOLLOWTHELEADER
    for(auto &  i : mWorld->getFollowEnemies())
    {
        enemyVelocity = fObj->doAction(*i,*i->getLeader(),*mWorld );
        i->setVelocity(-enemyVelocity);

        float dx = enemyVelocity.x;
        float dy = enemyVelocity.y;
        float rotation = (atan2(dx*-1,dy)) * 180 / PI;
        i->setRotation(rotation+180);
    }


    /*
    for(auto &  i : mWorld->getEnemies())
    {
        if(h==0)
        {
            enemyVelocity = seekObj->doAction(*i, playerPosition);
            h++;
            lastEnemy = i;
            i->setVelocity(enemyVelocity);
            float dx = enemyVelocity.x;
            float dy = enemyVelocity.y;
            float rotation = (atan2(dx*-1,dy)) * 180 / PI;
            i->setRotation(rotation);
        }
        else
        {

            enemyVelocity = snakeObj->doAction(*i, *lastEnemy);
            i->setVelocity(-enemyVelocity);
            float dx = enemyVelocity.x;
            float dy = enemyVelocity.y;
            float rotation = (atan2(dx*-1,dy)) * 180 / PI;
            i->setRotation(rotation + 180);
            lastEnemy = i;
        }
    }

    */


    /*
        // Spawn enemies randomly at SPAWN_INTERVAL second intervals
        if (mSpawnTimer.getElapsedTime().asSeconds() >= SPAWN_INTERVAL){
            float winX = mWindow.getDefaultView().getSize().x;
            float winY = mWindow.getDefaultView().getSize().y;
            float x = rand() % (int)winX;
            float y = rand() % (int)winY;
            spawnEnemy(x, y);
            mSpawnTimer.restart();
        }
    */

}

void EnemyController::handleEvent(const sf::Event& event, CommandQueue& commands)
{
    // This is here incase we want Enemies to do something on a button press (debugging purposes only, probably)
}


bool EnemyController::isAction(Action action)
{
    switch (action)
    {
    case Wander:
    case FlockToLeader:
    case FollowLeader:
    case Attack:
        return true;
    default:
        return false;
    }
}
