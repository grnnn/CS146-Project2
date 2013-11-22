#include "Transition.hpp"

Transition::Transition()
{
    //ctor
}
State Transition::getTargetState()
{
    return this->targetState;
}
void Transition::setTargetState(State targetState)
{

    this->targetState = targetState;
}
IAction Transition::getAction()
{
    return this->action
}
void Transition::setAction(IAction action)
{

    this->action = action;
}
void Transition::setCondition(ICondition condition)
{
    this->condition = condition;
}
bool Transition::isTriggered(World world)
{
    return this->condition.test(world);
}
Transition::~Transition()
{
    //dtor
}
