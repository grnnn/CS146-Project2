#include "../headers/World.hpp"
#include "../headers/Player.hpp"
#include "../../engine/headers/SceneNode.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

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
        mSceneGraph.update(dt);
}

void World::draw()
{
        mWindow.setView(mWorldView);
        mWindow.draw(mSceneGraph);
}

void World::loadTextures()
{
        mTextures.load(Textures::Player, "Media/Player.pdf");
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

        // Add player
        std::unique_ptr<Player> player(new Player(mTextures));
        mPlayer = player.get();
        mPlayer->setPosition(mSpawnPosition);
        mPlayer->setVelocity(0.f, 0.f);

        // Currently the new problem 11/21/2013 2:41 AM
        // For some reason, the tutorial allows a unique_ptr<Aircraft> (unique_ptr<Player for us>)
        // To be attached to the scene layer with this call to std::move. However, attachChild only
        // Takes SceneNode Ptr's. Somehow the player class is checked as a Scene Node and allowed to
        // attach. I don't know how - Ethan
        mSceneLayers[Air]->attachChild(std::move(player));

        // Add the background sprite to the scene
        /*std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
        backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
        mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

        // Add player's aircraft
        std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
        mPlayerAircraft = leader.get();
        mPlayerAircraft->setPosition(mSpawnPosition);
        mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
        mSceneLayers[Air]->attachChild(std::move(leader));

        // Add two escorting aircrafts, placed relatively to the main plane
        std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures));
        leftEscort->setPosition(-80.f, 50.f);
        mPlayerAircraft->attachChild(std::move(leftEscort));

        std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, mTextures));
        rightEscort->setPosition(80.f, 50.f);
        mPlayerAircraft->attachChild(std::move(rightEscort));*/
}