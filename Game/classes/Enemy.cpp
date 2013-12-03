#include "../headers/Enemy.hpp"
#include "../../engine/headers/ResourceHolder.hpp"
#include "../../engine/headers/Utility.hpp"
#include "../headers/VectorUtil.hpp"
#include <iostream>

Enemy::Enemy(const TextureHolder& textures)
: mSprite(textures.get(Textures::Enemy))
{
    centerOrigin(mSprite);
}

void Enemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);

}


void Enemy::setType(std::string i_type)
{
    int sCase = 0;
    if(i_type == "loner") sCase = 1;
    if(i_type == "swarmer") sCase = 2;
    if(i_type == "flocker") sCase = 3;
    if(i_type == "leader") sCase = 4;

    switch(sCase)
    {
        case 1:
            type = Loner;
            break;
        case 2:
            type = Swarmer;
            break;
        case 3:
            type = Flocker;
            break;
        case 4:
            type = Leader;
            break;

        default:
            std::cout << "Enemy->setType(string) error, no enum for that string \n";
            exit(1);
            break;
    }
}

void Enemy::setState(std::string i_state)
{

    int sCase = 0;
    if(i_state == "LWander") sCase = 1;
    if(i_state == "LRushLeader") sCase = 2;
    if(i_state == "SWander") sCase = 3;
    if(i_state == "SSwarmLeader") sCase = 4;
    if(i_state == "SRushPlayer") sCase = 5;
    if(i_state == "FRushPlayer") sCase = 6;
    if(i_state == "FWander") sCase = 7;
    if(i_state == "FFollowLeader") sCase = 8;
    if(i_state == "LeadWander") sCase = 9;
    if(i_state == "LeadRushPlayer") sCase = 10;


    switch(sCase){
        // Loners
        case 1:
            state = LWander;
            break;
        case 2:
            state = LRushPlayer;
            break;

        //Swarmers
        case 3:
            state = SWander;
            break;
        case 4:
            state = SSwarmPlayer;
            break;
        case 5:
            state = SRushPlayer;
            break;

        // Flockers
        case 6:
            state = FWander;
            break;
        case 7:
            state = FRushPlayer;
            break;
        case 8:
            state = FFollowLeader;
            break;

        //Leader
        case 9:
            state = LeadWander;
            break;
        case 10:
            state = LeadRushPlayer;
            break;

        default:
            std::cout << "Enemy->setState(string) error, no enum for that string \n";
            exit(1);
            break;
    }
}

bool Enemy::isLoner()
{
    if(type == Loner) return true;
    else return false;
}

bool Enemy::isSwarmer()
{
    if(type == Swarmer) return true;
    else return false;
}

bool Enemy::isFlocker()
{
    if(type == Flocker) return true;
    else return false;
}

bool Enemy::isLeader()
{
    if(type == Leader) return true;
    else return false;
}

int Enemy::getState()
{
    switch(state){
        // Loners
        case LWander:
            return 1;
            break;
        case LRushPlayer:
            return 2;
            break;

        //Swarmers
        case SWander:
            return 3;
            break;
        case SSwarmPlayer:
            return 4;
            break;
        case SRushPlayer:
            return 5;
            break;

        // Flockers
        case FWander:
            return 6;
            break;
        case FRushPlayer:
            return 7;
            break;
        case FFollowLeader:
            return 8;
            break;

        //Leader
        case LeadWander:
            return 9;
            break;
        case LeadRushPlayer:
            return 10;
            break;
    }
}
