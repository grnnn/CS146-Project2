#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include "../../engine/headers/ResourceHolder.hpp"
#include "../../engine/headers/ResourceIdentifier.hpp"
#include "../../engine/headers/SceneNode.hpp"

#include "../../engine/headers/CommandQueue.hpp"
#include "Enemy.hpp"
#include "LeaderEnemy.hpp"
#include "FollowEnemy.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>

// Forward declaration
class SpaceCraft;
class Enemy;
namespace sf
{
class RenderWindow;
}

class World : private sf::NonCopyable
{
public:
    int invT;
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
    void                                      loadFonts();
    std::vector<Enemy*>                       getEnemies();
    std::vector<FollowEnemy*>                 getFollowEnemies();
    std::vector<LeaderEnemy*>                 getLeaderEnemies();

    void                                      spawnEnemy(float x, float y);
    void                                      spawnLeaderEnemy(float x, float y);
    void                                      spawnFollowEnemy(float x, float y);
    void                                      handleCollisions();
    void                                      destroyEntitiesOutsideView();
    void                                      removeFromList(Enemy& e);
    void                                      listUpdate(int ty);
    int                     getLives();
    int                     getScore();
    void                    setLives(int i);
    void                    setScore(int i);

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
    FontHolder                                mFonts;
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
    std::vector<FollowEnemy*>                 mFollowEnemies;
    std::vector<LeaderEnemy*>                 mLeaderEnemies;
    sf::Sprite                                mSprite;
    sf::Text                                  scoreText;
    sf::Text                                  livesText;
    int                                       score;
    int                                       lives;





};


#endif // WORLD_HPP_INCLUDED
