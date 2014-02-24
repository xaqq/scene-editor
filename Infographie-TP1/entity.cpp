#include "entity.hpp"
#include "qirrlichtwidget.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;


Entity::Entity(QIrrlichtWidget *w, const QString &name) :
    name_(name),
    posX_(0),
    posY_(0),
    posZ_(0),
    widget_(w)
{
}


void Entity::loadMesh(QString path)
{
    mesh_ = (widget_->getSceneManager()->getMesh(path.toStdString().c_str()));
}

void Entity::buildNode()
{
     node_ = widget_->getSceneManager()->addAnimatedMeshSceneNode( static_cast<scene::IAnimatedMesh *>(mesh_) );
}

void Entity::loadTexture(QString path)
{
    if (node_)
    {
        node_->setMaterialFlag(EMF_LIGHTING, false);
        if (auto ptr = dynamic_cast<IAnimatedMeshSceneNode *>(node_))
        {
            ptr->setMD2Animation(EMAT_STAND);
        }
        node_->setMaterialTexture( 0, widget_->getVideoDriver()->getTexture(path.toStdString().c_str()) );
    }
    else
    {
        qDebug("Error !! Tried to load texture, but no node.");
    }
}

void Entity::setPosition(float x, float y, float z)
{
    if (node_)
        node_->setPosition(vector3df(x, y, z));
}
