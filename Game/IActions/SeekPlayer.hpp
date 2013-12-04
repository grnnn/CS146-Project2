#ifndef SEEKPLAYER_H
#define SEEKPLAYER_H

#include <SFML/System.hpp>

#include "../headers/World.hpp"
#include "../headers/Enemy.hpp"

#include "../FSM/IAction.hpp"



class SeekPlayer: public IAction
{
    public:
        SeekPlayer();
        virtual ~SeekPlayer();
        sf::Vector2f doAction(World& world, Enemy& enemy);
    protected:
    private:
};

#endif // SEEKPLAYER_H
