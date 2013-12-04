#include "IAction.hpp"

IAction::IAction()
{
    //ctor
}

IAction::~IAction()
{
    //dtor
}

sf::Vector2f IAction::doAction(World& world, Enemy& enemy){
    //empty by default, filled in by polymorphic classes
}
