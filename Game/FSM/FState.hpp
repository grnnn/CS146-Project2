#ifndef FSTATE_H
#define FSTATE_H

#include "IAction.hpp"
#include "Transition.hpp"

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
        std::vector<Transition>             getTransitions();
        void                                setTransitions(std::vector<Transition> transitions);
        virtual                             ~FState();
    protected:
    private:
        IAction                             action;
        IAction                             EAction;
        IAction                             EXAction;
        std::vector<Transition>             transitions;


};

#endif // FSTATE_H
