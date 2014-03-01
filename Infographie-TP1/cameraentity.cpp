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
    ICameraSceneNode *camera;
    node_ = widget_->getSceneManager ()->addCameraSceneNodeFPS();
      name(name()); // dispatch the name to the node;
     if (node_)
         return true;
     return false;
}
