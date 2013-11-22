#include "FState.hpp"


FState::FState()
{
    //ctor
}
IAction FState::getAction()
{
    return action;
}
void FState::setAction(IAction action)
{
    this->action = action;
}
IAction FState::getEntryAction()
{
    return EAction;
}
void FState::setEntryAction(IAction action)
{
    this->EAction = action;
}
IAction FState::getExitAction()
{
    return EXAction;
}
void FState::setExitAction(IAction action)
{
    this->EXAction = action;
}
std::vector<ITransition> FState::getTransitions()
{
    return transitions;
}
void FState::setTransitions(std::vector<ITransition> transitions)
{
    this->transitions = transitions;
}

FState::~FState()
{
    //dtor
}
