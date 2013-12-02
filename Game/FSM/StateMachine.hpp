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
        std::vector<IAction>                    update(World& world);
        FState                                  getCurrentState();
        void                                    setCurrentState(FState state);

    private:
        FState                                  currentState;
        std::vector<IAction>                    actionStack;
};

#endif // STATEMACHINE_H
