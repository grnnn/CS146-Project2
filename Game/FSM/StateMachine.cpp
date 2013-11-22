#include "StateMachine.hpp"

StateMachine::StateMachine()
{
    //ctor
}

StateMachine::~StateMachine()
{
    //dtor
}

std::vector<IAction> StateMachine::update(World world){
    actionStack.clear();
	bool trigger = false;

	for(ITransition trans: currentState.getTransitions()){
		if(trans.isTriggered(world)){
			triggeredtrans = trans;
			trigger = true;
			break;
		}
	}
	if(trigger){
		if(currentState.getExitAction() != null)
			actionStack.push_back(currentState.getExitAction());
		if(triggeredtrans.getAction() != null)
			actionStack.push_back(triggeredtrans.getAction());
		if(triggeredtrans.getTargetState().getEntryAction() != null)
			actionStack.push_back(triggeredtrans.getTargetState().getEntryAction());

		currentState = triggeredtrans.getTargetState();

		return actionStack;
	}
	else{
		if(currentState.getAction() != null)
			actionStack.push_back(currentState.getAction());
		return actionStack;
	}

}

IState StateMachine::getCurrentState() {
    return currentState;
}


void StateMachine::setCurrentState(IState state) {
	currentState = state;

}
