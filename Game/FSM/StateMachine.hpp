#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <vector>

#include "IAction.hpp"
#include "ICondition.hpp"
#include "FState.hpp"
#include "..\headers\World.hpp"

class StateMachine
{
    public:
                                                StateMachine();
        virtual                                 ~StateMachine();
        std::vector<IAction>                    update(World& world, FState currentState);

    private:
        std::vector<IAction>                    actionStack;
};

#endif // STATEMACHINE_H
