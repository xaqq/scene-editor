#ifndef ANIMATEDENTITY_H
#define ANIMATEDENTITY_H

#include "entity.hpp"

class AnimatedEntity : public Entity
{
public:
    AnimatedEntity(QIrrlichtWidget *w, const QString & name = "Unnamed");

    virtual bool loadTexture(QString path);
    virtual bool buildNode();
};

#endif // ANIMATEDENTITY_H
