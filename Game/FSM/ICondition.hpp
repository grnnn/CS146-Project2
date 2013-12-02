#ifndef ICONDITION_H
#define ICONDITION_H

#include "..\headers\World.hpp"
#include "IAction.hpp"

class ICondition
{
    public:
                                                ICondition();
        virtual                                 ~ICondition();
        virtual bool                            test(World& world);


        void                                    setTransitionAction(IAction action);
        IAction*                                getTransitionAction();

    private:

        IAction                                 action;

};

#endif // ICONDITION_H
