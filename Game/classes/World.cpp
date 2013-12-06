#include "../headers/World.hpp"
#include "../headers/SpaceCraft.hpp"
#include "../headers/Enemy.hpp"
#include "../headers/Player.hpp"
#include "../headers/GameState.hpp"

#include "../../engine/headers/SpriteNode.hpp"
#include "../../engine/headers/SceneNode.hpp"
#include "../../engine/headers/CommandQueue.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

World::World(sf::RenderWindow& window)
    : mWindow(window)
    , mWorldView(window.getDefaultView())
    , mTextures()
    , mSceneGraph()
    , mSceneLayers()
    , mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
    , mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldView.getSize().y / 2.f)
    , mPlayer(nullptr)
    , livesText()
    , scoreText()
    , score()
    , lives()
    , mFonts()

{
    loadFonts();
    loadTextures();
    buildScene();
    score = 0;
    lives = 3;

    scoreText.setFont(mFonts.get(Fonts::Main));
    livesText.setFont(mFonts.get(Fonts::Main));

    // Prepare the view
    mWorldView.setCenter(mSpawnPosition);
}


void World::update(sf::Time dt)
{
    mPlayer->setVelocity(0.1f, 0.1f);

    while (!mCommandQueue.isEmpty())
    {
        Command cmd = mCommandQueue.pop();
        cmd.action(cmd.node, dt);
    }
    mSceneGraph.update(dt);
    handleCollisions();
    mSceneGraph.removeWrecks();
    //destroyEntitiesOutsideView();
    adaptPlayerPosition();


    //Text
    char buffer [33];
    sprintf (buffer, "Lives: %d", lives);
    livesText.setString(buffer);
    sprintf(buffer, "Score: %d", score);
    scoreText.setString(buffer);
    livesText.setPosition(mWindow.getView().getSize().x -180.f, 5.f);
    scoreText.setPosition(mWindow.getView().getSize().x -180.f, 35.f);
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
    mWindow.draw(livesText);
    mWindow.draw(scoreText);
}

CommandQueue& World::getCommandQueue()

{
    return mCommandQueue;
}
TextureHolder& World::getTextures()
{
    return mTextures;
}

SceneNode* World::getAirLayer()
{
    return mSceneLayers[Air];
}

void World::loadTextures()
{
    mTextures.load(Textures::SpaceCraft, "Media/Player.png");
    mTextures.load(Textures::Enemy, "Media/Enemy.png");
    mTextures.load(Textures::Background, "Media/background.png");
    mTextures.load(Textures::Projectile, "Media/Projectile.png");
    mTextures.load(Textures::LeaderEnemy, "Media/LeaderEnemy.png");
    mTextures.load(Textures::FollowEnemy, "Media/FollowEnemy.png");
}
void World::loadFonts()
{
    mFonts.load(Fonts::Main, "Media/LinLibertine.ttf");
}

void World::buildScene()
{
    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode* layer(new SceneNode());
        mSceneLayers[i] = layer;
        mSceneGraph.attachChild( layer );
    }

    //prepare background sprite
    sf::Texture& texture = mTextures.get(Textures::Background);

    sf::IntRect backTextureRect(mWorldBounds);
    sf::Sprite spr(mTextures.get(Textures::Background));
    mSprite = spr;
    // Add Background
    SpriteNode* backgroundSprite(new SpriteNode(texture, backTextureRect));
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->attachChild( backgroundSprite );

    // Add player
    SpaceCraft* player(new SpaceCraft(mTextures, (*this)));
    mPlayer = player;
    mPlayer->setPosition(mSpawnPosition);
    mPlayer->setVelocity(0.f, 0.f);
    mSceneLayers[Air]->attachChild(player);

}

void World::adaptPlayerPosition()
{
    // Keep player's position inside the screen bounds, at least borderDistance units from the border
    sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
    const float borderDistance = 40.f;

    sf::Vector2f position = mPlayer->getPosition();
    position.x = std::max(position.x, viewBounds.left + borderDistance);
    position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
    position.y = std::max(position.y, viewBounds.top + borderDistance);
    position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
    mPlayer->setPosition(position);
}

void World::adaptPlayerVelocity()
{
    sf::Vector2f velocity = mPlayer->getVelocity();

    // If moving diagonally, reduce velocity (to have always same velocity)
    if (velocity.x != 0.f && velocity.y != 0.f)
        mPlayer->setVelocity(velocity / std::sqrt(2.f));
}

sf::Vector2f World::getPlayerPosition()
{
    return mPlayer->getPosition();
}

SpaceCraft* World::getPlayer()
{
    return mPlayer;
}

void World::spawnEnemy(float x, float y)
{
    Enemy* enemy(new Enemy(mTextures, (*this)));
    enemy->setPosition(x, y);
    enemy->setVelocity(0.f, 100.f);
    mEnemies.push_back( enemy );
    mSceneLayers[Air]->attachChild( enemy );
}

void World::spawnLeaderEnemy(float x, float y)
{
    LeaderEnemy* enemy(new LeaderEnemy(mTextures));
    enemy->setPosition(x, y);
    enemy->setVelocity(0.f, 100.f);
    mLeaderEnemies.push_back( enemy );
    mSceneLayers[Air]->attachChild( enemy );
}
void World::spawnFollowEnemy(float x, float y)
{
    FollowEnemy* enemy(new FollowEnemy(mTextures));
    enemy->setPosition(x, y);
    enemy->setVelocity(0.f, 100.f);
    mFollowEnemies.push_back( enemy );
    mSceneLayers[Air]->attachChild( enemy );
}


void World::isEnemiesEmpty()
{
    if (mEnemies.empty())
        std::cout << "mEnemies is still empty";
    else
        std::cout << "mEnemies has something in it";
}
bool matchesCategories(SceneNode::Pair& colliders,
                       int type1, int type2)
{
    int category1 = colliders.first->getID();
    int category2 = colliders.second->getID();
    if (type1 & category1 && type2 & category2)
    {
        return true;
    }
    else if (type1 & category2 && type2 & category1)
    {
        std::swap(colliders.first, colliders.second);
        return true;
    }
    else
    {
        return false;
    }
}
void World::handleCollisions()
{
    std::set<SceneNode::Pair> collisionPairs;
    mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);
    for(auto & i : collisionPairs)
    {
        SceneNode::Pair thing = i;
        if (matchesCategories(thing, 1, 2))
        {
            if(!thing.second->getEnemyRemoval())
            {
                thing.first->markForRemoval();
                thing.second->enemyDestroy();
                listUpdate();
                score += 10;

                //thing.second->markForRemoval();
            }





        }
        else if(matchesCategories(thing, 2, 100))
        {
            lives--;

            //    thing.first->markForRemoval();
            //  thing.second->markForRemoval();

            thing.first->enemyDestroy();
            listUpdate();
            //thing.second->markForRemoval();

            // std::cout<<"DEMO VERSION, ship would take damage \n";
        }
    }
}


std::vector<Enemy*>  World::getEnemies()
{
    return mEnemies;
}

std::vector<LeaderEnemy*>  World::getLeaderEnemies()
{
    return mLeaderEnemies;
}
std::vector<FollowEnemy*>  World::getFollowEnemies()
{
    return mFollowEnemies;
}
void World::listUpdate()
{
    int h = 0;
    for(auto & i : mEnemies)
    {

        if((*i).listRemoval && !mEnemies.empty())
        {
            auto k = mEnemies.begin();
            mSceneLayers[Air]->detachChild(**(k+h));
            mEnemies.erase(k + h);

        }
        h++;
    }

}


