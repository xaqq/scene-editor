#ifndef ENTITYTABLE_HPP
#define ENTITYTABLE_HPP

#include <QAbstractItemModel>
#include <QDataWidgetMapper>
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
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex & index) const;

    void insert(Entity *e);

    QDataWidgetMapper &dataMapper()
    {
        return dataMapper_;
    }

private:
    QList<Entity *> entities_;
    // configuration is done by mainwidget;
    QDataWidgetMapper dataMapper_;
};

#endif // ENTITYTABLE_HPP
