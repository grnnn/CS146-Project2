#include "../headers/World.hpp"
#include "../headers/SpaceCraft.hpp"
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
                mSceneGraph.onCommand(mCommandQueue.pop(), dt);
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
        mTextures.load(Textures::SpaceCraft, "Media/SpaceCraft.png");
        mTextures.load(Textures::Background, "Media/background.png");
}

void World::buildScene()
{
        // Initialize the different layers
        for (std::size_t i = 0; i < LayerCount; ++i)
        {
                SceneNode::Ptr layer(new SceneNode());
                mSceneLayers[i] = layer.get();

                mSceneGraph.attachChild(std::move(layer));
        }

        //prepare background sprite
        sf::Texture& texture = mTextures.get(Textures::Background);
        sf::IntRect backTextureRect(mWorldBounds);

        // Add Background
        std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, backTextureRect));
        backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
        mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

        // Add player
        std::unique_ptr<SpaceCraft> player(new SpaceCraft(mTextures));
        mPlayer = player.get();
        mPlayer->setPosition(mSpawnPosition);
        mPlayer->setVelocity(0.f, 0.f);
        mSceneLayers[Air]->attachChild(std::move(player));
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
