#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include "../../engine/headers/ResourceHolder.hpp"
#include "../../engine/headers/ResourceIdentifier.hpp"
#include "../../engine/headers/SceneNode.hpp"

#include "../../engine/headers/CommandQueue.hpp"
#include "Enemy.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>

// Forward declaration
class SpaceCraft;
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
                CommandQueue&                             getCommandQueue();
                sf::Vector2f                              getPlayerPosition();
                SpaceCraft*                               getPlayer();
                SceneNode*                                getAirLayer();
                TextureHolder&                            getTextures();
                void                                      isEnemiesEmpty();
                void                                      loadTextures();
                std::vector<Enemy*>                       getEnemies();

                void                                      spawnEnemy(float x, float y);
                void                                      handleCollisions();
                void                                      destroyEntitiesOutsideView();
        private:
                enum Layer
                {
                        Background,
                        Air,
                        LayerCount
                };

        private:

                void                                       buildScene();
                void                                       adaptPlayerVelocity();
                void                                       adaptPlayerPosition();
                sf::FloatRect                              getBattlefieldBounds();


        private:
                sf::RenderWindow&                         mWindow;
                sf::View                                  mWorldView;
                TextureHolder                             mTextures;
                CommandQueue                              mCommandQueue;
                SceneNode                                 mSceneGraph;
                std::array<SceneNode*, LayerCount>        mSceneLayers;
                sf::FloatRect                             mWorldBounds;
                sf::Vector2f                              mSpawnPosition;
                SpaceCraft*                               mPlayer;
                std::vector<Enemy*>                       mEnemies;
                sf::Sprite                                mSprite;


};


#endif // WORLD_HPP_INCLUDED
