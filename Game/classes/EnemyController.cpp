#include "../headers/EnemyController.hpp"
#include "../headers/EnemyActions.hpp"

#include "../IActions/FollowLeader.hpp"
#include "../IActions/SeekPlayer.hpp"
#include "../IActions/Wander.hpp"

#include "../IConditions/DistFromPlayer.hpp"
#include "../IConditions/LeaderAppears.hpp"
#include "../IConditions/LeaderGoneAndDistFromPlayer.hpp"
#include "../IConditions/LeaderGoneAndNotDistFromPlayer.hpp"
#include "../IConditions/notDistFromPlayer.hpp"
#include "../IConditions/SwarmersGreaterThan.hpp"

#include <iostream>

const int MAX_NUM_ENEMIES = 50;
const float SPAWN_INTERVAL = .7f;

EnemyController::EnemyController(sf::RenderWindow& window, World& world)
: mWindow(window)
, mWorld(&world)
{
}

void EnemyController::spawnEnemy(float x, float y, std::string type, IState state)
{
    mWorld->spawnEnemy(x, y, type, state);
}

void EnemyController::update(CommandQueue& commands)
{

    // Spawn enemies randomly at SPAWN_INTERVAL second intervals
    if (mSpawnTimer.getElapsedTime().asSeconds() >= SPAWN_INTERVAL){
        float winX = mWindow.getDefaultView().getSize().x;
        float winY = mWindow.getDefaultView().getSize().y;
        float x = rand() % (int)winX;
        float y = rand() % (int)winY;
        spawnEnemy(x, y, "loner", ILWander);

        mSpawnTimer.restart();
    }


    // Iterate through the mWorld->mEnemies list of Enemy SceneNodes

    for(auto currentEnemy = mWorld->getEnemies().begin(); currentEnemy != mWorld->getEnemies().end(); ++currentEnemy){

        FState* statePointer = sortState((**currentEnemy).getState()); //gets the current State

         std::cout <<  "okay3\n";

        //FSM.update(*mWorld, **currentEnemy, *statePointer); //Potentially switches states, otherwise returns action vector

         std::cout <<  "okay4\n";
        /*
        (*currentEnemy)->setState(sortFIStates(statePointer)); //sets the current state to the enemy
        */
        //std::cout <<  sortString(statePointer) + "\n";

        Command cmd(**currentEnemy);   //creates a command and pushes it onto the command queue
        sf::Vector2f vec = statePointer->getAction()->doAction(*mWorld, **currentEnemy);
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

void EnemyController::initializeStates()
{
/*
* Loner Finite State Machine initialization
*/
//LWander
IAction* LWanderAction = new Wander();
LWander.setAction(*LWanderAction);

std::vector<ICondition>* LWandVec = new std::vector<ICondition>;
std::vector<FState>* LWandVec2 = new std::vector<FState>;

ICondition* LWanderCond1 = new DistFromPlayer(30);
LWandVec->push_back(*LWanderCond1);
LWandVec2->push_back(LRushPlayer);

LWander.setConditions(*LWandVec);
LWander.setTransitionStates(*LWandVec2);


//LRushPlayer
IAction* LRushPlayerAction = new SeekPlayer();
LRushPlayer.setAction(*LRushPlayerAction);

std::vector<ICondition>* LRushPlayerVec = new std::vector<ICondition>;
std::vector<FState>* LRushPlayerVec2 = new std::vector<FState>;

ICondition* LRushPlayerCond1 = new NotDistFromPlayer(50);
LRushPlayerVec->push_back(*LRushPlayerCond1);
LRushPlayerVec2->push_back(LWander);

LRushPlayer.setConditions(*LRushPlayerVec);
LRushPlayer.setTransitionStates(*LRushPlayerVec2);

/*
* Leader Finite State Machine initialization
*/
//LeadWander
IAction* LeadWanderAction = new Wander();
LeadWander.setAction(*LeadWanderAction);

std::vector<ICondition>* LeadWandVec = new std::vector<ICondition>;
std::vector<FState>* LeadWandVec2 = new std::vector<FState>;

ICondition* LeadWanderCond1 = new DistFromPlayer(50);
LeadWandVec->push_back(*LeadWanderCond1);
LeadWandVec2->push_back(LeadRushPlayer);

LeadWander.setConditions(*LeadWandVec);
LeadWander.setTransitionStates(*LeadWandVec2);


//LeadRushPlayer
IAction* LeadRushPlayerAction = new SeekPlayer();
LeadRushPlayer.setAction(*LeadRushPlayerAction);

std::vector<ICondition>* LeadRushPlayerVec = new std::vector<ICondition>;
std::vector<FState>* LeadRushPlayerVec2 = new std::vector<FState>;

ICondition* LeadRushPlayerCond1 = new NotDistFromPlayer(100);
LeadRushPlayerVec->push_back(*LeadRushPlayerCond1);
LeadRushPlayerVec2->push_back(LWander);

LeadRushPlayer.setConditions(*LeadRushPlayerVec);
LeadRushPlayer.setTransitionStates(*LeadRushPlayerVec2);


/*
* Swarmer Finite State Machine initialization
*/
//SWander
IAction* SWanderAction = new Wander();
SWander.setAction(*SWanderAction);

std::vector<ICondition>* SWanderVec = new std::vector<ICondition>;
std::vector<FState>* SWanderVec2 = new std::vector<FState>;

ICondition* SWanderCond1 = new DistFromPlayer(10);
SWanderVec->push_back(*SWanderCond1);
SWanderVec2->push_back(SRushPlayer);
ICondition* SWanderCond2 = new SwarmersGreaterThan(10);
SWanderVec->push_back(*SWanderCond2);
SWanderVec2->push_back(SSwarmPlayer);

SWander.setConditions(*SWanderVec);
SWander.setTransitionStates(*SWanderVec2);


//SRushPlayer
IAction* SRushPlayerAction = new SeekPlayer();
SRushPlayer.setAction(*SRushPlayerAction);

std::vector<ICondition>* SRushPlayerVec = new std::vector<ICondition>;
std::vector<FState>* SRushPlayerVec2 = new std::vector<FState>;

ICondition* SRushPlayerCond1 = new NotDistFromPlayer(15);
SRushPlayerVec->push_back(*SRushPlayerCond1);
SRushPlayerVec2->push_back(SWander);
ICondition* SRushPlayerCond2 = new SwarmersGreaterThan(10);
SRushPlayerVec->push_back(*SRushPlayerCond2);
SRushPlayerVec2->push_back(SSwarmPlayer);

SRushPlayer.setConditions(*SRushPlayerVec);
SRushPlayer.setTransitionStates(*SRushPlayerVec2);


//SSwarmPlayer
IAction* SSwarmPlayerAction = new SeekPlayer();
SSwarmPlayer.setAction(*SSwarmPlayerAction);

/*
* Flocker Finite State Machine initialization
*/
//FWander
IAction* FWanderAction = new Wander();
FWander.setAction(*FWanderAction);

std::vector<ICondition>* FWanderVec = new std::vector<ICondition>;
std::vector<FState>* FWanderVec2 = new std::vector<FState>;

ICondition* FWanderCond1 = new DistFromPlayer(15);
FWanderVec->push_back(*FWanderCond1);
FWanderVec2->push_back(FRushPlayer);
ICondition* FWanderCond2 = new LeaderAppears();
FWanderVec->push_back(*FWanderCond2);
FWanderVec2->push_back(FFollowLeader);

FWander.setConditions(*FWanderVec);
FWander.setTransitionStates(*FWanderVec2);

//FRushPlayer
IAction* FRushPlayerAction = new SeekPlayer();
FRushPlayer.setAction(*FRushPlayerAction);

std::vector<ICondition>* FRushPlayerVec = new std::vector<ICondition>;
std::vector<FState>* FRushPlayerVec2 = new std::vector<FState>;

ICondition* FRushPlayerCond1 = new NotDistFromPlayer(20);
FRushPlayerVec->push_back(*FRushPlayerCond1);
FRushPlayerVec2->push_back(FWander);
ICondition* FRushPlayerCond2 = new LeaderAppears();
FRushPlayerVec->push_back(*FRushPlayerCond2);
FRushPlayerVec2->push_back(FFollowLeader);

FRushPlayer.setConditions(*FRushPlayerVec);
FRushPlayer.setTransitionStates(*FRushPlayerVec2);


//FFollowLeader
IAction* FFollowLeaderAction = new FollowLeader();
FFollowLeader.setAction(*FFollowLeaderAction);

std::vector<ICondition>* FFollowLeaderVec = new std::vector<ICondition>;
std::vector<FState>* FFollowLeaderVec2 = new std::vector<FState>;

ICondition* FFollowLeaderCond1 = new LeaderGoneAndDistFromPlayer(20);
FFollowLeaderVec->push_back(*FFollowLeaderCond1);
FFollowLeaderVec2->push_back(FWander);
ICondition* FFollowLeaderCond2 = new LeaderGoneAndDistFromPlayer(15);
FFollowLeaderVec->push_back(*FFollowLeaderCond2);
FFollowLeaderVec2->push_back(FRushPlayer);

FFollowLeader.setConditions(*FFollowLeaderVec);
FFollowLeader.setTransitionStates(*FFollowLeaderVec2);

}

FState* EnemyController::sortState(int n)
{
    switch(n)
    {
        case 1:
            return &LWander;
            break;
        case 2:
            return &LRushPlayer;
            break;
        case 3:
            return &SWander;
            break;
        case 4:
            return &SSwarmPlayer;
            break;
        case 5:
            return &SRushPlayer;
            break;
        case 6:
            return &FWander;
            break;
        case 7:
            return &FRushPlayer;
            break;
        case 8:
            return &FFollowLeader;
            break;
        case 9:
            return &LeadWander;
            break;
        case 10:
            return &LeadRushPlayer;
            break;

        default:
            std::cout << "error:EnemyController::SortState int not between 1 and 10 \n";
            exit(1);
    }
}

IState EnemyController::sortFIStates(FState* state)
{
    std::cout <<  "okay1\n";

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

    std::cout <<  "okay2\n";

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
            //std::cout << "";
            std::cout << "error:EnemyController::SortString state not valid \n";
            exit(1);
    }
}
