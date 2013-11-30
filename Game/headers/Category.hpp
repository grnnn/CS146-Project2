#ifndef CATEGORY_HPP_INCLUDED
#define CATEGORY_HPP_INCLUDED


// Entity/scene node category, used to dispatch commands
namespace Category
{
        enum Type
        {
                None                 = 0,
                Scene                = 1 << 0,
                PlayerSpaceCraft     = 1 << 1,
                Freezer              = 1 << 2,
                MoveRight            = 1 << 3,
        };
}

#endif // CATEGORY_HPP_INCLUDED
