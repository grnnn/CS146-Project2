#include "../headers/Command.hpp"

Command::Command(SceneNode& n)
: action()
, category(Category::None)
, node(n)
{
}
