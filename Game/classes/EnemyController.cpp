#include "../headers/EnemyController.hpp"
#include "../headers/Seek.hpp"
#include <math.h>

#include <iostream>

const float PI = 3.14159265;
const int MAX_NUM_ENEMIES = 50;
const float SPAWN_INTERVAL = .7f;

EnemyController::EnemyController(sf::RenderWindow& window, World& world)
: mWindow(window)
, mWorld(&world)
{
}

void EnemyController::spawnEnemy(float x, float y)
{
    mWorld->spawnEnemy(x, y);

}

void EnemyController::update(CommandQueue& commands)
{


    sf::Vector2f playerPosition= mWorld->getPlayerPosition();
    sf::Vector2f enemyVelocity;

    Seek* seekObj = new Seek();

    for(auto &  i : mWorld->getEnemies()){
        enemyVelocity = seekObj->doAction(*i, playerPosition);
        float sign;
        i->setVelocity(enemyVelocity);

        float dx = i->getPosition().x - playerPosition.x;
        float dy = i->getPosition().y - playerPosition.y;

        float rotation = (atan2(dx*-1,dy)) * 180 / PI;
        i->setRotation(rotation + 180);
    }
lastVelocity = enemyVelocity;


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


    // Iterate through the mWorld->mEnemies list of Enemy SceneNodes

    // Given their state, check their transitions

    // Eventually, pass a command to the mWorld->mEnemies[i] ( or (mWorld->mEnemies)[i], Im not sure )
    /* This is done by creating a command and pushing it to the queue
     * Command cmd(mWorld->mEnemies[i]);                       This passes the node to the command so it knows which node to execute the command on
     * cmd.action = derivedAction<Enemy>(EnemyMover(x, y));
     * OR
     * cmd.action = mWorld->mEnemies[i]->curState.action       This is where the action is bound to the command
     *    NOTE: Im not yet sure how you wanted to do the actual actions. if we had a WANDER action, we can do the logic to determine where the velocity is goind to get added inside that
     *          WANDER action, then inside of the wander action it would also call node.accelerate(x, y). Or we can do the WANDER logic outside the action and just have our actions be
     *          changeVelocity or something.
     *
     * Finally, call commands.push(cmd);
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
