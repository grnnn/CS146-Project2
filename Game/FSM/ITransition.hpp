#ifndef ITRANSITION_H
#define ITRANSITION_H

#include "..\headers\World.hpp"
#include "ICondition.hpp"
#include "IAction.hpp"

class ITransition
{
    public:
                                        ITransition();
        virtual                         ~ITransition();
        bool                            isTriggered(World world);
        IAction                         getAction();
    protected:
    private:
        IAction                         action;
        ICondition                      condition;
};

#endif // ITRANSITION_H
