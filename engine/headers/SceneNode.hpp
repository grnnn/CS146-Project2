#ifndef SCENENODE_HPP_INCLUDED
#define SCENENODE_HPP_INCLUDED

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <iostream>
#include <vector>
#include <memory>
#include <set>

struct Command;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    typedef std::pair<SceneNode*, SceneNode*> Pair;
    SceneNode();
    void                                attachChild(SceneNode* child);
    SceneNode*                          detachChild(const SceneNode& node);
    void                                update(sf::Time dt);
    sf::Vector2f                        getWorldPosition() const;
    sf::Transform                       getWorldTransform() const;
    void                                checkNodeCollision(SceneNode& node, std::set<Pair>&
            collisionPairs);
    void                                checkSceneCollision(SceneNode& sceneGraph,
            std::set<Pair>& collisionPairs);
    sf::FloatRect                       getBoundingRect() const;
    bool                                isDestroyed();
    bool                                isMarkedForRemoval();
    int                                 getID();
    sf::Sprite                          getSprite() const;
    void                                setSprite(sf::Sprite spr);
    void                                setID(int i);
    void                                markForRemoval();
    void                                removeWrecks();
    void                                destroyOutsideWorld();
    void                                removeFromList();
    void                                enemyDestroy();
    bool                                getEnemyRemoval();

public:
    int lives;
    int                                 getLives();
    void                                damage();
    bool                                mIsDestroyed;
    bool                                mMarkedForRemoval;
    bool                                enemyRemoval;

private:
    sf::Sprite                          mSprite;
    std::vector<SceneNode*>             mChildren;
    SceneNode*                          mParent;

    int                                 mID;

private:
    virtual void                        draw(sf::RenderTarget& target,sf::RenderStates states) const;
    virtual void                        drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;
    void                                drawChildren(sf::RenderTarget& target,sf::RenderStates states) const;
    virtual void                        updateCurrent(sf::Time dt);
    void                                updateChildren(sf::Time dt);

};


#endif // SCENENODE_HPP_INCLUDED
