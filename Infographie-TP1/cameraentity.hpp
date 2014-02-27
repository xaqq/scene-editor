#ifndef CAMERAENTITY_HPP
#define CAMERAENTITY_HPP


#include <QString>
#include "entity.hpp"

class QIrrlichtWidget;

class CameraEntity : public Entity
{
public:
    CameraEntity(QIrrlichtWidget *w, const QString &name = "Camera");

    virtual bool buildNode() override;

private:
};

#endif // CAMERAENTITY_HPP
