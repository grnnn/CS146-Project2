#include "FState.hpp"


FState::FState()
{
    //ctor
}
IAction* FState::getAction()
{
    return &action;
}
void FState::setAction(IAction action)
{
    this->action = action;
}
IAction* FState::getEntryAction()
{
    return &EAction;
}
void FState::setEntryAction(IAction action)
{
    this->EAction = action;
}
IAction* FState::getExitAction()
{
    return &EXAction;
}
void FState::setExitAction(IAction action)
{
    this->EXAction = action;
}
std::vector<ICondition> FState::getConditions()
{
    return conditions;
}
void FState::setConditions(std::vector<ICondition> iConditions)
{
    this->conditions = iConditions;
}
std::vector<FState> FState::getTransitionStates()
{
    return states;
}
void FState::setTransitionStates(std::vector<FState> fStates)
{
    this->states = fStates;
}

FState::~FState()
{
    //dtor
}
