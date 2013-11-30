#ifndef COMMAND_HPP_INCLUDED
#define COMMAND_HPP_INCLUDED

#include "../../Game/headers/Category.hpp"

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>


class SceneNode;

struct Command
{
        Command(SceneNode& n);

        std::function<void(SceneNode&, sf::Time)>        action;
        unsigned int                                     category;
        SceneNode&                                       node;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
        return [=] (SceneNode& node, sf::Time dt)
        {
                // Check if cast is safe
                assert(dynamic_cast<GameObject*>(&node) != nullptr);

                // Downcast node and invoke function on it
                fn(static_cast<GameObject&>(node), dt);
        };
}


#endif // COMMAND_HPP_INCLUDED
