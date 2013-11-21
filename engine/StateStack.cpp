#include "headers\StateStack.hpp"
#include "headers\FOREACH.hpp"

#include <cassert>
#include <iostream>

StateStack::StateStack(State::Context context)
: mStack()
, mPendingList()
, mContext(context)
, mFactories()
{
}

void StateStack::update(sf::Time dt)
{
        // Iterate from top to bottom, stop as soon as update() returns false
        for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
        {
                if (!(*itr)->update(dt))
                        break;
        }

        applyPendingChanges();
}

void StateStack::draw()
{
    //DEBUG
    std::cout << "StateStack.draw()\n";

        // Draw all active states from bottom to top
        for (auto itr = mStack.rend(); itr != mStack.rbegin(); --itr)
        {
            //DEBUG
            std::cout << "Inside Loop";
                (*itr)->draw();
        }
}

void StateStack::handleEvent(const sf::Event& event)
{
        // Iterate from top to bottom, stop as soon as handleEvent() returns false
        for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
        {
                if (!(*itr)->handleEvent(event))
                        break;
        }

        applyPendingChanges();
}

void StateStack::pushState(States::ID stateID)
{
        mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
        mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
        mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const
{
        return mStack.empty();
}

State::Ptr StateStack::createState(States::ID stateID)
{
        auto found = mFactories.find(stateID);
        assert(found != mFactories.end());

        return found->second();
}

void StateStack::applyPendingChanges()
{
        //FOREACH(PendingChange change, mPendingList)
        /*
         * We're hung up on finding a way to iterate through this pending list of states
         * without running into any weird errors
         */

        for (auto change = mPendingList.begin(); change != mPendingList.end(); ++change)
        {
                switch (change.action)
                {
                        case Push:
                                mStack.push_back(createState(change.stateID));
                                break;

                        case Pop:
                                mStack.pop_back();
                                break;

                        case Clear:
                                mStack.clear();
                                break;
                }
        }

        mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
: action(action)
, stateID(stateID)
{
}
