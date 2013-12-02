#include "StateMachine.hpp"
#include "ICondition.hpp"
#include "FState.hpp"
#include "..\headers\World.hpp"

StateMachine::StateMachine()
{
    //ctor
}

StateMachine::~StateMachine()
{
    //dtor
}

std::vector<IAction> StateMachine::update(World& world){
    actionStack.clear();
	bool trigger = false;
	ICondition triggeredtrans;
    FState triggeredState;

    auto tState = currentState.getTransitionStates().begin();
	for(auto trans = currentState.getConditions().begin(); trans != currentState.getConditions().end(); ++trans){
		if((*trans).test(world)){
			triggeredtrans = (*trans);
			triggeredState = (*tState);
			trigger = true;
			break;
		}
		++tState;
	}
	if(trigger){
		if(currentState.getExitAction() != nullptr)
			actionStack.push_back(*currentState.getExitAction());
		if(triggeredtrans.getTransitionAction() != nullptr)
			actionStack.push_back(*triggeredtrans.getTransitionAction());
		if(triggeredState.getEntryAction() != nullptr)
			actionStack.push_back(*triggeredState.getEntryAction());

		currentState = triggeredState;

		return actionStack;
	}
	else{
		if(currentState.getAction() != nullptr)
			actionStack.push_back(*currentState.getAction());
		return actionStack;
	}

}

FState StateMachine::getCurrentState() {
    return currentState;
}


void StateMachine::setCurrentState(FState state) {
	currentState = state;

}
