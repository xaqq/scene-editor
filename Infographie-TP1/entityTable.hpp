#ifndef ENTITYTABLE_HPP
#define ENTITYTABLE_HPP

#include <QAbstractItemModel>
#include <QList>

class Entity;

class EntityTable :  public QAbstractTableModel
{
    Q_OBJECT
public:
    EntityTable(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;


    void insert(Entity *e);

private:
    QList<Entity *> entities_;
};

#endif // ENTITYTABLE_HPP
