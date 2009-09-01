#ifndef TITLECARRIERLISTMODEL_HPP
#define TITLECARRIERLISTMODEL_HPP

#include <QAbstractListModel>


class I_TitleCarrier;

class TitleCarrierListModel : public QAbstractListModel
{
public:
    TitleCarrierListModel(QObject* parent = NULL);

    template <class ATC>
        TitleCarrierListModel(const QList<ATC*>& list, QObject* parent = NULL )
        : TitleCarrierListModel(parent) { copyList(list); }

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    /*
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
    */
    template <class ATC>
    void setList(const QList<ATC*>& list)
    {
        copyList(list);
        reset();
    }

    const QList<I_TitleCarrier*>& list();

private:
    template <class ATC>
    void copyList(const QList<ATC*>& list)
    {
        m_list.clear();
        for (int i = 0; i < list.size(); ++i)
        {
            m_list.append(list[i]);
        }
    }


    QList<I_TitleCarrier*> m_list;

};

#endif
