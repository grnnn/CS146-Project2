#ifndef ICONDITION_H
#define ICONDITION_H

#include "..\headers\World.hpp"

class ICondition
{
    public:
                                                ICondition();
        virtual                                 ~ICondition();
        virtual bool                            test(World world);
};

#endif // ICONDITION_H
