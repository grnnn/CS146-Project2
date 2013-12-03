#include "../headers/EnemyController.hpp"
#include "../headers/EnemyActions.hpp"

#include <iostream>

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

    for(auto currentEnemy = mWorld->getEnemies().begin(); currentEnemy != mWorld->getEnemies().end(); ++currentEnemy){

        FState statePointer = sortState((**currentEnemy).getState()); //gets the current State
        if((**currentEnemy).isLoner()){
            LonerFSM.update(*mWorld, statePointer); //Potentially switches states, otherwise returns action vector
        }
        if((**currentEnemy).isSwarmer()){
            SwarmerFSM.update(*mWorld, statePointer); //Potentially switches states, otherwise returns action vector
        }
        if((**currentEnemy).isFlocker()){
            FlockerFSM.update(*mWorld, statePointer); //Potentially switches states, otherwise returns action vector
        }
        if((**currentEnemy).isLeader()){
            LeaderFSM.update(*mWorld, statePointer); //Potentially switches states, otherwise returns action vector
        }
        (**currentEnemy).setState(sortString(&statePointer)); //sets the current state to the enemy

        Command cmd(**currentEnemy);   //creates a command and pushes it onto the command queue
        sf::Vector2f vec = statePointer.getAction()->doAction();
        cmd.action = derivedAction<Enemy>(EnemyMover(vec.x, vec.y));
        commands.push(cmd);
    }

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

void EnemyController::initializeStates()
{

}

FState EnemyController::sortState(int n)
{
    switch(n)
    {
        case 1:
            return LWander;
            break;
        case 2:
            return LRushPlayer;
            break;
        case 3:
            return SWander;
            break;
        case 4:
            return SSwarmPlayer;
            break;
        case 5:
            return SRushPlayer;
            break;
        case 6:
            return FWander;
            break;
        case 7:
            return FRushPlayer;
            break;
        case 8:
            return FFollowLeader;
            break;
        case 9:
            return LeadWander;
            break;
        case 10:
            return LeadRushPlayer;
            break;

        default:
            std::cout << "error:EnemyController::SortState int not between 1 and 10 \n";
            exit(1);
    }
}

std::string EnemyController::sortString(FState *state)
{
    int sCase = 0;
    if(state == &LWander) sCase = 1;
    if(state == &LRushPlayer) sCase = 2;
    if(state == &SWander) sCase = 3;
    if(state == &SSwarmPlayer) sCase = 4;
    if(state == &SRushPlayer) sCase = 5;
    if(state == &FRushPlayer) sCase = 6;
    if(state == &FWander) sCase = 7;
    if(state == &FFollowLeader) sCase = 8;
    if(state == &LeadWander) sCase = 9;
    if(state == &LeadRushPlayer) sCase = 10;

    switch(sCase)
    {
        case 1:
            return "LWander";
            break;
        case 2:
            return "LRushPlayer";
            break;
        case 3:
            return "SWander";
            break;
        case 4:
            return "SSwarmPlayer";
            break;
        case 5:
            return "SRushPlayer";
            break;
        case 6:
            return "FWander";
            break;
        case 7:
            return "FRushPlayer";
            break;
        case 8:
            return "FFollowLeader";
            break;
        case 9:
            return "LeadWander";
            break;
        case 10:
            return "LeadRushPlayer";
            break;

        default:
            std::cout << "error:EnemyController::SortString int not between 1 and 10 \n";
            exit(1);
    }
}
