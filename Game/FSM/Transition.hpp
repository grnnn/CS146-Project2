#ifndef TRANSITION_H
#define TRANSITION_H

#include "FState.hpp"
#include "IAction.hpp"
#include "ICondition.hpp"

class Transition: public ITransition
{
    public:
                                    Transition();
        FState                      getTargetState();
        void                        setTargetState(FState targetState);
        void                        setAction(IAction action);
        void                        setCondition(ICondition condition);
        virtual                     ~Transition();
    protected:
    private:
        FState                      targetState;
};

#endif // TRANSITION_H
