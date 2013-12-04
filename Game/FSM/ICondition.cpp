#include "ICondition.hpp"

ICondition::ICondition()
{
    //ctor
}

ICondition::~ICondition()
{
}

void ICondition::setTransitionAction(IAction iAction){
    this->action = iAction;
}

IAction* ICondition::getTransitionAction(){
    return &action;
}

bool ICondition::test(World& world, Enemy& enemy){
    return false;
    //returns false by default, filled in later by polymorphic classes
}
