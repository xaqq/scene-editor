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
    return 4;
}

QVariant EntityTable::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole)
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

      switch (col)
      {
      case 0: /* name */
           e->name(value.toString());
          return true;
      case 1: /* x */
          e->setPosition(value.toFloat(), e->posY(), e->posZ());
          return true;
      case 2: /* y */

          e->setPosition(e->posX(), value.toFloat(), e->posZ());
          return true;
      case 3: /* z */
          e->setPosition(e->posX(), e->posY(), value.toFloat());
          return true;
      }
      }return false;
  }

QVariant EntityTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Name");
            case 1:
                return QString("x");
            case 2:
                return QString("y");
            case 3:
                return QString("z");
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
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
