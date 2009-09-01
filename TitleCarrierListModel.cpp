#include "I_TitleCarrier.h"

#include "TitleCarrierListModel.hpp"


TitleCarrierListModel::TitleCarrierListModel(QObject* parent)
:   QAbstractListModel(parent)
{
}

int TitleCarrierListModel::rowCount(const QModelIndex &parent) const
{
    return m_list.count();
}

QVariant TitleCarrierListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_list.count())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return m_list.at(index.row())->Title();
    else if (role == Qt::UserRole)
        return qVariantFromValue(m_list.at(index.row()));
    else
        return QVariant();
}

QVariant TitleCarrierListModel::headerData(int section, Qt::Orientation orientation,
                    int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

const QList<I_TitleCarrier*>& TitleCarrierListModel::list()
{
    return m_list;
}
