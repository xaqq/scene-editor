#include "entityTable.hpp"
#include "entity.hpp"

EntityTable::EntityTable(QObject *parent) :
QAbstractTableModel(parent)
{
    dataMapper_.setModel(this);
}

int EntityTable::rowCount(const QModelIndex &parent) const
{
    return entities_.size();
}

int EntityTable::columnCount(const QModelIndex &parent) const
{
    return 10;
}

QVariant EntityTable::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        Entity *e = entities_.at(row);

        switch (col)
        {
            case 0: /* name */
                return e->name();
            case 1: /* x */
                return e->posX();
            case 2: /* y */
                return e->posY();
            case 3: /* z */
                return e->posZ();

            case 4: /* x */
                return e->rotX();
            case 5: /* y */
                return e->rotY();
            case 6: /* z */
                return e->rotZ();

            case 7: /* x */
                return e->scaleX();
            case 8: /* y */
                return e->scaleY();
            case 9: /* z */
                return e->scaleZ();
        }
    }
    return QVariant();
}

bool EntityTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::EditRole)
    {
        Entity *e = entities_.at(row);
        emit dataChanged(index, index.sibling(index.row(), columnCount()));
        switch (col)
        {
            case 0: /* name */
                e->name(value.toString());
                return true;


                /*** Positions ***/
            case 1: /* x */
                e->setPosition(value.toFloat(), e->posY(), e->posZ());
                return true;
            case 2: /* y */
                e->setPosition(e->posX(), value.toFloat(), e->posZ());
                return true;
            case 3: /* z */
                e->setPosition(e->posX(), e->posY(), value.toFloat());
                return true;


                /*** Rotation ***/
            case 4: /* x */
                e->setRotation(value.toFloat(), e->rotY(), e->rotZ());
                return true;
            case 5: /* y */
                e->setRotation(e->rotX(), value.toFloat(), e->rotZ());
                return true;
            case 6: /* z */
                e->setRotation(e->rotX(), e->rotY(), value.toFloat());
                return true;

                /*** Scale ***/
            case 7: /* x */
                e->setScale(value.toFloat(), e->scaleY(), e->scaleZ());
                return true;
            case 8: /* y */
                e->setScale(e->scaleX(), value.toFloat(), e->scaleZ());
                return true;
            case 9: /* z */
                e->setScale(e->scaleX(), e->scaleY(), value.toFloat());
                return true;
        }
    }
    return false;
}

QVariant EntityTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case 0:
                    return QString("Name");
                case 1:
                    return QString("pos x");
                case 2:
                    return QString("pos y");
                case 3:
                    return QString("pos z");
                case 4:
                    return QString("rot x");
                case 5:
                    return QString("rot y");
                case 6:
                    return QString("rot z");
                case 7:
                    return QString("scale x");
                case 8:
                    return QString("scale y");
                case 9:
                    return QString("scale z");
            }
        }
    }
    return QVariant();
}

void EntityTable::insert(Entity *e)
{
    entities_.push_back(e);
    emit reset();
}

Qt::ItemFlags EntityTable::flags(const QModelIndex & index) const
{
    return /*Qt::ItemIsEditable |*/ Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void EntityTable::refresh()
{
    emit reset();
}

Entity *EntityTable::getEntityAt(int n)
{
    if (n >= 0)
    return entities_.at(n);
    return nullptr;
}

int EntityTable::entityToIndex(Entity *e)
{
    int idx = 0;
    for (auto ptr : entities_)
    {
        if (ptr == e)
            return idx;
        idx++;
    }
    return -1;
}

