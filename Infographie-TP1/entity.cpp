#include "entity.hpp"
#include "qirrlichtwidget.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;


Entity::Entity(QIrrlichtWidget *w, const QString &name) :
    name_(name),
    widget_(w)
{
}


bool Entity::loadMesh(QString path)
{
    mesh_ = (widget_->getSceneManager()->getMesh(path.toStdString().c_str()));
    if (mesh_)
        return true;
    return false;
}

bool Entity::buildNode()
{
     node_ = widget_->getSceneManager()->addAnimatedMeshSceneNode( static_cast<scene::IAnimatedMesh *>(mesh_) );
     if (node_)
         return true;
     return false;
}

bool Entity::loadTexture(QString path)
{
    if (node_)
    {
        node_->setMaterialFlag(EMF_LIGHTING, false);
        if (auto ptr = dynamic_cast<IAnimatedMeshSceneNode *>(node_))
        {
            ptr->setMD2Animation(EMAT_STAND);
        }
        ITexture *texture = widget_->getVideoDriver()->getTexture(path.toStdString().c_str());
        if (!texture)
            return false;
        node_->setMaterialTexture( 0, widget_->getVideoDriver()->getTexture(path.toStdString().c_str()) );
        return true;
    }
    else
    {
        qDebug("Error !! Tried to load texture, but no node.");
    }
    return false;
}

void Entity::setPosition(float x, float y, float z)
{
    if (node_)
        node_->setPosition(vector3df(x, y, z));
}

void Entity::setRotation(float x, float y, float z)
{
    if (node_)
        node_->setRotation(vector3df(x, y, z));
}

void Entity::setScale(float x, float y, float z)
{
    if (node_)
        node_->setScale(vector3df(x, y, z));
}
