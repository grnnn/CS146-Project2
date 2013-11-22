#ifndef TRANSITION_H
#define TRANSITION_H

#include "FState.hpp"
#include "IAction.hpp"
#include "ICondition.hpp"

class Transition
{
    public:
                                    Transition();
        FState                      getTargetState();
        void                        setTargetState(FState targetState);
        IAction                     getAction();
        void                        setAction(IAction action);
        void                        setCondition(ICondition condition);
        bool                        isTriggered(World world);
        virtual                     ~Transition();
    protected:
    private:
        FState                      targetState;
        IAction                     action;
        ICondition                  condition;
};

#endif // TRANSITION_H
