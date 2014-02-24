#ifndef ENTITY_HPP
#define ENTITY_HPP


#include <QString>


class Entity
{
public:
    Entity(const QString & name = "Unnamed");
    const QString &name() const
    {
        return name_;
    }
    int posX() const
    {
        return posX_;
    }
    int posY() const
    {
        return posY_;
    }

    int posZ() const
    {
        return posZ_;
    }

private:
    QString name_;
    int posX_;
    int posY_;
    int posZ_;
};

#endif // ENTITY_HPP
