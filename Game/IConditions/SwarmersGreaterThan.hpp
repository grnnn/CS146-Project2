#ifndef SWARMERSGREATERTHAN_H
#define SWARMERSGREATERTHAN_H


#include <SFML/System.hpp>

#include "../headers/World.hpp"
#include "../headers/Enemy.hpp"

#include "../FSM/ICondition.hpp"

class SwarmersGreaterThan: public ICondition
{
    public:
        SwarmersGreaterThan(int num);
        virtual ~SwarmersGreaterThan();
        bool test(World& world, Enemy& enemy);
    protected:
    private:
        int mNum;
};

#endif // SWARMERSGREATERTHAN_H
