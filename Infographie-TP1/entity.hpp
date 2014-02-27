#ifndef ENTITY_HPP
#define ENTITY_HPP


#include <irrlicht/irrlicht.h>
#include <QString>

class QIrrlichtWidget;

class Entity
{
public:
    Entity(QIrrlichtWidget *w, const QString & name = "Unnamed");
    const QString &name() const
    {
        return name_;
    }

    int posX() const
    {
        if (node_)
            return node_->getPosition().X;
        return -1;
    }

    int posY() const
    {
        if (node_)
          return  node_->getPosition().Y;
        return -1;
    }

    int posZ() const
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
          return  node_->getRotation().Y;
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
            return node_->getScale().X;
        return -1;
    }

    int scaleY() const
    {
        if (node_)
            return node_->getScale().Y;
        return -1;
    }


    int scaleZ() const
    {
        if (node_)
            return node_->getScale().Z;
        return -1;
    }


    void name(const QString &name)
    {
        name_ = name;
    }

    virtual bool loadMesh(QString path);
    virtual bool loadTexture(QString path);

    virtual bool buildNode();

    void setPosition(float x, float y, float z);
    void setRotation(float x, float y, float z);
    void setScale(float x, float y, float z);
    protected:

    QString name_;

    QIrrlichtWidget *widget_;
    /* Irrlicht stuff */
    irr::scene::ISceneNode *node_;
    irr::scene::IMesh *mesh_;
};

#endif // ENTITY_HPP
