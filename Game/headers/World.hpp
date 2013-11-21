#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include "../../engine/headers/ResourceHolder.hpp"
#include "../../engine/headers/ResourceIdentifier.hpp"
#include "../../engine/headers/SceneNode.hpp"
#include "../headers/Player.hpp"
//#include <SpriteNode.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>

// Forward declaration
namespace sf
{
        class RenderWindow;
}

class World : private sf::NonCopyable
{
        public:
                explicit                                  World(sf::RenderWindow& window);
                void                                      update(sf::Time dt);
                void                                      draw();


        private:
                void                                       loadTextures();
                void                                       buildScene();


        private:
                enum Layer
                {
                        Background,
                        Air,
                        LayerCount
                };


        private:
                sf::RenderWindow&                         mWindow;
                sf::View                                  mWorldView;
                TextureHolder                             mTextures;

                SceneNode                                 mSceneGraph;
                std::array<SceneNode*, LayerCount>        mSceneLayers;
                sf::FloatRect                             mWorldBounds;
                sf::Vector2f                              mSpawnPosition;
                Player*                                    mPlayer;

};


#endif // WORLD_HPP_INCLUDED
