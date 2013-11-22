#ifndef IACTION_H
#define IACTION_H


class IAction
{
    public:
                                                IAction();
        virtual                                 ~IAction();
        virtual void                            doAction();
};

#endif // IACTION_H
