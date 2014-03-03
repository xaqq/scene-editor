#ifndef ENTITY_HPP
#define ENTITY_HPP


#include <irrlicht/irrlicht.h>
#include <QString>

class QIrrlichtWidget;

class Entity
{
public:
    Entity(QIrrlichtWidget *w, const QString & name = "Unnamed");

    virtual ~Entity()
    {
    }

    const QString &name() const
    {
        return name_;
    }

    float posX() const
    {
        if (node_)
            return node_->getPosition().X;
        return -1;
    }

    float posY() const
    {
        if (node_)
            return node_->getPosition().Y;
        return -1;
    }

    float posZ() const
    {
        if (node_)
            return node_->getPosition().Z;
        return -1;
    }

    int rotX() const
    {
        if (node_)
            return node_->getRotation().X;
        return -1;
    }

    int rotY() const
    {
        if (node_)
            return node_->getRotation().Y;
        return -1;
    }

    int rotZ() const
    {
        if (node_)
            return node_->getRotation().Z;
        return -1;
    }

    int scaleX() const
    {
        if (node_)
            return node_->getScale().X * 100;
        return -1;
    }

    int scaleY() const
    {
        if (node_)
            return node_->getScale().Y * 100;
        return -1;
    }

    int scaleZ() const
    {
        if (node_)
            return node_->getScale().Z * 100;
        return -1;
    }

    irr::scene::ISceneNode *node()
    {
        return node_;
    }

    void name(const QString &name)
    {
        name_ = name;
        if (node_)
        {
            node_->setName(name.toStdString().c_str());
        }
    }

    /**
     * @brief loadMesh
     * Load texture based on based on path. Irrlicht is nice and do caching.
     * @param path
     * @return
     */
    virtual bool loadMesh(QString path);
    virtual bool loadTexture(QString path);

    virtual bool buildNode();

    void setPosition(float x, float y, float z);
    void setRotation(float x, float y, float z);
    void setScale(float x, float y, float z);

    void setNode(irr::scene::ISceneNode *node)
    {
        node_ = node;
    }

    void setMesh(irr::scene::IMesh *mesh)
    {
        mesh_ = mesh;
    }

    // wrapper to irrlicht
    void addChild(Entity *child)
    {
        if (node_)
            node_->addChild(child->node());
    }

    void remove();

protected:

    QString name_;

    QIrrlichtWidget *widget_;
    /* Irrlicht stuff */
    irr::scene::ISceneNode *node_;
    irr::scene::IMesh *mesh_;
};

#endif // ENTITY_HPP
