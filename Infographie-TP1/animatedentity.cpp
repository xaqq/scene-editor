#include "animatedentity.h"
#include "qirrlichtwidget.hpp"


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;

AnimatedEntity::AnimatedEntity(QIrrlichtWidget *w, const QString & name) :
Entity(w, name)
{
}

bool AnimatedEntity::buildNode()
{
    node_ = widget_->getSceneManager()->addAnimatedMeshSceneNode(static_cast<scene::IAnimatedMesh *> (mesh_));
    name(name()); // dispatch the name to the node;
    if (node_)
        return true;
    return false;
}

bool AnimatedEntity::loadTexture(QString path)
{
    if (node_)
    {
        node_->setMaterialFlag(EMF_LIGHTING, false);
        if (auto ptr = dynamic_cast<IAnimatedMeshSceneNode *> (node_))
        {
            ptr->setMD2Animation(EMAT_STAND);
        }
        ITexture *texture = widget_->getVideoDriver()->getTexture(path.toStdString().c_str());
        if (!texture)
            return false;
        node_->setMaterialTexture(0, widget_->getVideoDriver()->getTexture(path.toStdString().c_str()));
        return true;
    }
    else
    {
        qDebug("Error !! Tried to load texture, but no node.");
    }
    return false;
}
