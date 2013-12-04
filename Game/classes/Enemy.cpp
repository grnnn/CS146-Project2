#include "../headers/Enemy.hpp"
#include "../../engine/headers/ResourceHolder.hpp"
#include "../../engine/headers/Utility.hpp"
#include "../headers/VectorUtil.hpp"



#include <iostream>

Enemy::Enemy(const TextureHolder& textures, std::string m_type, IState m_state)
: mSprite(textures.get(Textures::Enemy))
{
    centerOrigin(mSprite);
    setType(m_type);
    setState(m_state);

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
     std::cout <<  "okay6\n";

      std::cout <<  i_state + "huehue\n";

    int sCase = 0;
    if(i_state == "LWander") sCase = 1;
    else if(i_state == "LRushLeader") sCase = 2;
    else if(i_state == "SWander") sCase = 3;
    else if(i_state == "SSwarmLeader") sCase = 4;
    else if(i_state == "SRushPlayer") sCase = 5;
    else if(i_state == "FRushPlayer") sCase = 6;
    else if(i_state == "FWander") sCase = 7;
    else if(i_state == "FFollowLeader") sCase = 8;
    else if(i_state == "LeadWander") sCase = 9;
    else if(i_state == "LeadRushPlayer") sCase = 10;

    switch(sCase){
        // Loners
        case 1:
             std::cout <<  "okay7\n";
            setState(ILWander);
             std::cout <<  "okay8\n";
            break;
        case 2:
            state = ILRushPlayer;
            break;

        //Swarmers
        case 3:
            state = ISWander;
            break;
        case 4:
            state = ISSwarmPlayer;
            break;
        case 5:
            state = ISRushPlayer;
            break;

        // Flockers
        case 6:
            state = IFWander;
            break;
        case 7:
            state = IFRushPlayer;
            break;
        case 8:
            state = IFFollowLeader;
            break;

        //Leader
        case 9:
            state = ILeadWander;
            break;
        case 10:
            state = ILeadRushPlayer;
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
        case ILWander:
            return 1;
            break;
        case ILRushPlayer:
            return 2;
            break;

        //Swarmers
        case ISWander:
            return 3;
            break;
        case ISSwarmPlayer:
            return 4;
            break;
        case ISRushPlayer:
            return 5;
            break;

        // Flockers
        case IFWander:
            return 6;
            break;
        case IFRushPlayer:
            return 7;
            break;
        case IFFollowLeader:
            return 8;
            break;

        //Leader
        case ILeadWander:
            return 9;
            break;
        case ILeadRushPlayer:
            return 10;
            break;
    }
}

void Enemy::setState(IState i_state){
    state = i_state;
}
