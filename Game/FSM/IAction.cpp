#include "IAction.hpp"

IAction::IAction()
{
    //ctor
}

IAction::~IAction()
{
    //dtor
}

sf::Vector2f IAction::doAction(){
    //empty by default, filled in by polymorphic classes
}
