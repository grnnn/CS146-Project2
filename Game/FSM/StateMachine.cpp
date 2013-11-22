#include "StateMachine.hpp"

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

	for(auto trans = currentState.getTransitions().begin(); trans != currentState.getTransitions().end(); ++trans){
		if((*trans).isTriggered(world)){
			triggeredtrans = (*trans);
			trigger = true;
			break;
		}
	}
	if(trigger){
		if(currentState.getExitAction() != NULL)
			actionStack.push_back(currentState.getExitAction());
		if(triggeredtrans.getAction() != NULL)
			actionStack.push_back(triggeredtrans.getAction());
		if(triggeredtrans.getTargetState().getEntryAction() != NULL)
			actionStack.push_back(triggeredtrans.getTargetState().getEntryAction());

		currentState = triggeredtrans.getTargetState();

		return actionStack;
	}
	else{
		if(currentState.getAction() != NULL)
			actionStack.push_back(currentState.getAction());
		return actionStack;
	}

}

FState StateMachine::getCurrentState() {
    return currentState;
}


void StateMachine::setCurrentState(FState state) {
	currentState = state;

}
