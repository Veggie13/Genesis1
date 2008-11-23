#ifndef QSTRINGMAPREFMODEL_HPP
#define QSTRINGMAPREFMODEL_HPP

#include <QAbstractItemView>
#include <QMap>


template <typename T>
class QStringMapRefModel : public QAbstractListModel
{
    typedef QMap<QString, T> MapType;
    typedef typename MapType::iterator MapIterator;

public:
    QStringMapRefModel(MapType* map = 0, QObject* parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    /*
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
    */
    void setStringMap(MapType* map);

private:
    MapType* m_stringMap;

};

template <typename T>
QStringMapRefModel<T>::QStringMapRefModel(MapType* map, QObject* parent)
:   QAbstractListModel(parent)
{
    setStringMap(map);
}

template <typename T>
int QStringMapRefModel<T>::rowCount(const QModelIndex &parent) const
{
    if (!m_stringMap)
        return -1;

    return m_stringMap->count();
}

template <typename T>
QVariant QStringMapRefModel<T>::data(const QModelIndex &index, int role) const
{
    if (!m_stringMap)
        return QVariant();

    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_stringMap->size())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        MapIterator it;
        int n;
        for ( n = 0, it = m_stringMap->begin();
              n < index.row();
              it++, ++n );
        return it.key();
    }
    else
        return QVariant();
}

template <typename T>
QVariant QStringMapRefModel<T>::headerData(int section, Qt::Orientation orientation,
                    int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

template <typename T>
void QStringMapRefModel<T>::setStringMap(MapType* map)
{
    m_stringMap = map;
    reset();
}

#endif
