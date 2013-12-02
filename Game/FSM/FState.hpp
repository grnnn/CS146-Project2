#ifndef FSTATE_H
#define FSTATE_H

#include <vector>

#include "IAction.hpp"
#include "ICondition.hpp"

class FState
{
    public:
                                            FState();
        IAction*                            getAction();
        void                                setAction(IAction action);
        IAction*                            getEntryAction();
        void                                setEntryAction(IAction action);
        IAction*                            getExitAction();
        void                                setExitAction(IAction action);
        std::vector<ICondition>             getConditions();
        void                                setConditions(std::vector<ICondition> iConditions);
        std::vector<FState>                 getTransitionStates();
        void                                setTransitionStates(std::vector<FState> fStates);
        virtual                             ~FState();
    protected:
    private:
        IAction                             action;
        IAction                             EAction;
        IAction                             EXAction;
        std::vector<ICondition>             conditions;
        std::vector<FState>                 states;


};

#endif // FSTATE_H
