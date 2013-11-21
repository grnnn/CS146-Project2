#ifndef SCENENODE_HPP_INCLUDED
#define SCENENODE_HPP_INCLUDED

class SceneNode
{
    public:
        typedef std::unique_ptr<SceneNode>  Ptr;

    public:
                                            SceneNode();
        void                                attachChild(Ptr child);
        Ptr                                 detachChild(const SceneNode& node);
    private:
        std::vector<Ptr>                    mChildren;
        SceneNode*                          mParent;
    private:
        virtual void                        draw(sf::RenderTarget& target,sf::RenderStates states) const;
        virtual void                        drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;
};


#endif // SCENENODE_HPP_INCLUDED
