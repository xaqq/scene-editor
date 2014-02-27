#include "cameraentity.hpp"
#include "qirrlichtwidget.hpp"

#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;

CameraEntity::CameraEntity(QIrrlichtWidget *w, const QString &name):
    Entity(w, name)
{
}

bool CameraEntity::buildNode()
{
     node_ = widget_->getSceneManager ()->addCameraSceneNode (0, vector3df (3,3,20), vector3df (3,3,3));
     if (node_)
         return true;
     return false;
}
