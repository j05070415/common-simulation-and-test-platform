/****************************************************************************
** Last Modified: 2012-11-15-001
**
** File Name: TreeModel.h
** Created Time: 2012-11-15 9:32:59
** Created By: WeiJun Shi
**
****************************************************************************/
#ifndef __TreeModel_h__
#define __TreeModel_h__

#include <QAbstractItemModel>

class HwaTreeItem;

class HwaTreeModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	HwaTreeModel(QObject *parent = 0);
	virtual ~HwaTreeModel();

    int columnCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column,
                            const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex & index,
                            const QVariant & value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex& index) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex & index) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    Q_INVOKABLE bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) Q_DECL_OVERRIDE;
    Q_INVOKABLE bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) Q_DECL_OVERRIDE;

    QHash<int,QByteArray> roleNames() const Q_DECL_OVERRIDE;

private:
	HwaTreeItem* _head;
};

#endif //__TreeModel_h__
