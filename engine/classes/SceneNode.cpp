#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include "../headers/SceneNode.hpp"
#include "../headers/Command.hpp"
#include <iterator>
#include <algorithm>
#include <cassert>
#include <iostream>


SceneNode::SceneNode()
: mChildren()
, mParent(nullptr)
, mIsDestroyed(false)
, mMarkedForRemoval(false)
, enemyRemoval(false)
{
}

void SceneNode::attachChild(SceneNode* child)
{
        child->mParent = this;
        mChildren.push_back(child);
}

SceneNode* SceneNode::detachChild(const SceneNode& node)
{
        auto found = std::find_if(mChildren.begin(), mChildren.end(), [&] (SceneNode* p) { return p == &node; });
        assert(found != mChildren.end());

        SceneNode* result = std::move(*found);
        result->mParent = nullptr;
        mChildren.erase(found);
        return result;
}

void SceneNode::update(sf::Time dt)
{
        updateCurrent(dt);
        updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time dt)
{
        // Do nothing by default
}

void SceneNode::updateChildren(sf::Time dt)
{
        for (std::vector<SceneNode*>::iterator child = mChildren.begin(); child != mChildren.end(); ++child)
        //FOREACH(Ptr& child, mChildren)
                (*child)->update(dt);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
        // Apply transform of current node
        states.transform *= getTransform();

        // Draw node and children with changed transform
        drawCurrent(target, states);
        drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
        // Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
        for (std::vector<SceneNode*>::const_iterator child = mChildren.begin(); child != mChildren.end(); ++child)
                (*child)->draw(target, states);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
        return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
        sf::Transform transform = sf::Transform::Identity;

        for (const SceneNode* node = this; node != nullptr; node = node->mParent)
                transform = node->getTransform() * transform;

        return transform;
}
bool collision(const SceneNode& lhs, const SceneNode& rhs)
{

    return lhs.getBoundingRect()
    .intersects(rhs.getBoundingRect());
}
void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>&
                                   collisionPairs)
{
    if (this != &node && collision(*this, node)
    && !isDestroyed() && !node.isDestroyed()){
        collisionPairs.insert(std::minmax(this, &node));

        }
    for(auto & child : mChildren)
        child->checkNodeCollision(node, collisionPairs);
}

void SceneNode::checkSceneCollision(SceneNode& sceneGraph,
std::set<Pair>& collisionPairs)
{

    checkNodeCollision(sceneGraph, collisionPairs);
    for(auto & child : sceneGraph.mChildren)
    checkSceneCollision(*child, collisionPairs);
}
sf::FloatRect SceneNode::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}
bool SceneNode::isDestroyed()
{
    return mIsDestroyed;
}
int SceneNode::getID()
{
    return mID;
}
sf::Sprite SceneNode::getSprite() const
{
    return mSprite;
}
void SceneNode::setSprite(sf::Sprite spr)
{
    mSprite = spr;
}
void SceneNode::setID(int i)
{
    mID = i;
}
void SceneNode::markForRemoval()
{
    mIsDestroyed = true;
    mMarkedForRemoval = true;
}
bool SceneNode::isMarkedForRemoval()
{

    return mMarkedForRemoval;

}
void SceneNode::removeWrecks()
{

    auto wreckfieldBegin = std::remove_if(mChildren.begin(),
    mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
    mChildren.erase(wreckfieldBegin, mChildren.end());

    std::for_each(mChildren.begin(), mChildren.end(),
    std::mem_fn(&SceneNode::removeWrecks));
}
void SceneNode::enemyDestroy()
{
    enemyRemoval = true;
}
bool SceneNode::getEnemyRemoval()
{
    return enemyRemoval;
}
