#ifndef FSTATE_H
#define FSTATE_H

#include <vector>

#include "IAction.hpp"
#include "ITransition.hpp"

class FState
{
    public:
                                            FState();
        IAction                             getAction();
        void                                setAction(IAction action);
        IAction                             getEntryAction();
        void                                setEntryAction(IAction action);
        IAction                             getExitAction();
        void                                setExitAction(IAction action);
        std::vector<ITransition>            getTransitions();
        void                                setTransitions(std::vector<ITransition> transitions);
        virtual                             ~FState();
    protected:
    private:
        IAction                             action;
        IAction                             EAction;
        IAction                             EXAction;
        std::vector<ITransition>            transitions;


};

#endif // FSTATE_H
