#include "../headers/World.hpp"
#include "../headers/SpaceCraft.hpp"
#include "../headers/Enemy.hpp"
#include "../headers/Player.hpp"
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
{
        loadTextures();
        buildScene();

        // Prepare the view
        mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
    mPlayer->setVelocity(0.f, 0.f);

    while (!mCommandQueue.isEmpty()){
                Command cmd = mCommandQueue.pop();
                cmd.action(cmd.node, dt);
    }
    mSceneGraph.update(dt);
    adaptPlayerPosition();
}

void World::draw()
{
        mWindow.setView(mWorldView);
        mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
        return mCommandQueue;
}

void World::loadTextures()
{
        mTextures.load(Textures::SpaceCraft, "Media/Player.png");
        mTextures.load(Textures::Enemy, "Media/Enemy.png");
        mTextures.load(Textures::Background, "Media/background.png");
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

        // Add Background
        SpriteNode* backgroundSprite(new SpriteNode(texture, backTextureRect));
        backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
        mSceneLayers[Background]->attachChild( backgroundSprite );

        // Add player
        SpaceCraft* player(new SpaceCraft(mTextures));
        mPlayer = player;
        mPlayer->setPosition(mSpawnPosition);
        mPlayer->setVelocity(0.f, 0.f);
        mSceneLayers[Air]->attachChild(player);

        //Test Enemy
        //spawnEnemy(mWorldView.getSize().x / 2, (mWorldView.getSize().y / 2) - 50, );
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

SceneNode* World::getPlayer()
{
    return mPlayer;
}

std::vector<Enemy*> World::getEnemies()
{
    return mEnemies;
}

void World::spawnEnemy(float x, float y, std::string type, IState state)
{
        Enemy* enemy(new Enemy(mTextures, type, state));
        enemy->setPosition(x, y);
        mEnemies.push_back( enemy );
        mSceneLayers[Air]->attachChild( enemy );
}

void World::isEnemiesEmpty()
{
    if (mEnemies.empty())
        std::cout << "mEnemies is still empty";
    else
        std::cout << "mEnemies has something in it";
}

bool World::hasLeader()
{
    return leaderExists;
}
