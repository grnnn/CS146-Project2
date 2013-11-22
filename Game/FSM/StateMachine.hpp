#ifndef STATEMACHINE_H
#define STATEMACHINE_H


class StateMachine
{
    public:
                                                StateMachine();
        virtual                                 ~StateMachine();
        std::vector<IAction>                    update(World world);
        FState                                  getCurrentState();
        void                                    setCurrentState(FState state);

    private:
        FState                                  currentState;
        ITransition                             triggeredtrans;
        std::vector<IAction>                    actionStack
};

#endif // STATEMACHINE_H
