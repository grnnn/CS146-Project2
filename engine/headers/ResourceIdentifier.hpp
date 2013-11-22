#ifndef RESOURCEIDENTIFIER_HPP_INCLUDED
#define RESOURCEIDENTIFIER_HPP_INCLUDED

// Forward declaration of SFML classes
namespace sf
{
        class Texture;
        class Font;
}

namespace Textures
{
    enum ID
    {
        TitleScreen,
        SpaceCraft,
        Background,
    };
}

namespace Fonts
{
    enum ID
    {
        Main,
    };
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>     TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>           FontHolder;

#endif // RESOURCEIDENTIFIER_HPP_INCLUDED
