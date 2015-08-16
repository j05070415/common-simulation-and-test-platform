/****************************************************************************
** Last Modified: 2012-11-15-001
**
** File Name: TreeModel.cpp
** Created Time: 2012-11-15 9:33:08
** Created By: WeiJun Shi
**
****************************************************************************/
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

#include "TreeItem.h"
#include "TreeModel.h"

HwaTreeModel::HwaTreeModel(QObject *parent)
: QAbstractItemModel(parent)
, _head(new HwaTreeItem)
{
    _head->setColumnCount(2);
    _head->setData(0, "A");
    _head->setData(1, "B");

//    insertRows(0, 10);
//    for (int i=0; i<10; ++i)
//    {
//        setData(index(i, 0), "file:///F:/VS/QmlTreeView/1.ico", Qt::DecorationRole);
//        setData(index(i, 0), "A");
//        setData(index(i, 1), 'E'+i);
//    }

//    QModelIndex itemIndex = index(0, 0);
//    insertRows(0, 1, itemIndex);
//    setData(index(0, 0, itemIndex), "DD");
    qDebug("Model constructed!");
}

HwaTreeModel::~HwaTreeModel()
{
}

int HwaTreeModel::columnCount(const QModelIndex& parent) const
{
    return _head->columnCount();
}

int HwaTreeModel::rowCount(const QModelIndex& parent) const
{
	HwaTreeItem* parentItem = NULL;
	if (!parent.isValid())
		parentItem = _head;
	else
		parentItem = static_cast<HwaTreeItem*>(parent.internalPointer());

	return parentItem->rowCount();
}

QVariant HwaTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
    {
        qDebug("invalid data");
        return QVariant();
    }

	HwaTreeItem* item = (HwaTreeItem*)(index.internalPointer());
	//处理系统role和属性role
	if (role < Qt::UserRole || role >= 2000)
	{
		return item->data(index.column(), role);
	}

	//处理QML界面列数据
    QJsonObject jobj;
    switch (role) {
    case Qt::UserRole+1://column1
        jobj["icon"] = item->data(0, Qt::DecorationRole).toString();
        jobj["text"] = item->data(0, Qt::DisplayRole).toString();
        break;
    case Qt::UserRole+2://column2
        jobj["text"] = item->data(1, Qt::DisplayRole).toString();
        break;
    case Qt::UserRole+3://column3
        jobj["text"] = item->data(2, Qt::DisplayRole).toString();
        break;
    default:
        jobj["text"] = item->data(index.column(), Qt::DisplayRole).toString();
        break;
    }

    return QJsonDocument(jobj).toJson();
}

bool HwaTreeModel::setData(const QModelIndex & index, 
	const QVariant & value, int role)
{
	HwaTreeItem* item = (HwaTreeItem*)(index.internalPointer());

	if (item != NULL)
    {
        item->setData(index.column(), value, role);
        QVector<int> roles;
        roles.push_back(Qt::UserRole+1+index.column());
        emit dataChanged(index, index, roles);
		return true;
	}

	return false;
}

QModelIndex HwaTreeModel::index(int row, int column,
							 const QModelIndex & parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	HwaTreeItem* parentItem = static_cast<HwaTreeItem*>(parent.internalPointer());
	if (parentItem == NULL) parentItem = _head;

	HwaTreeItem* childItem = parentItem->child(row);

	return childItem != NULL ? createIndex(row, column, childItem) : QModelIndex();
}

QModelIndex HwaTreeModel::parent(const QModelIndex& index) const
{
	if (!index.isValid())
	{
		return QModelIndex();
	}

	HwaTreeItem* childItem = (HwaTreeItem*)(index.internalPointer());
	HwaTreeItem* parentItem = childItem->parent();

    return parentItem == _head ? QModelIndex() : createIndex(parentItem->row(), index.column(), parentItem);
}

Qt::ItemFlags HwaTreeModel::flags(const QModelIndex & index) const
{
	HwaTreeItem* item = (HwaTreeItem*)(index.internalPointer());

	return item != NULL ? item->flags() : 0;
}

bool HwaTreeModel::insertRows(int row, int count, const QModelIndex& parent)
{
	HwaTreeItem* parentItem = NULL;
	if (!parent.isValid())
    {
        parentItem = _head;
    }
	else
		parentItem = (HwaTreeItem*)(parent.internalPointer());

	Q_ASSERT(parentItem != NULL);

	beginInsertRows(parent, row, row+count-1);
	for (int i=0; i<count; ++i)
    {
        parentItem->insertChild(row+i, new HwaTreeItem());
	}
	endInsertRows();

	return true;
}

bool HwaTreeModel::removeRows(int row, int count, const QModelIndex& parent)
{
	if (!parent.isValid())
		return false;

	HwaTreeItem* item = (HwaTreeItem*)(parent.internalPointer());
	Q_ASSERT(item != NULL);
	beginRemoveRows(parent, row, row+count-1);
	for (int i=0; i<count; ++i)
	{
		delete item->takeChild(row+i);
	}
	endRemoveRows();

	return true;
}

QVariant HwaTreeModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
		return _head->data(section, role);
	}

	return QVariant();
}

QHash<int,QByteArray> HwaTreeModel::roleNames() const
{
    QHash<int,QByteArray> roles = QAbstractItemModel::roleNames();

    roles.insert(Qt::UserRole+1, "column1");
    roles.insert(Qt::UserRole+2, "column2");
    roles.insert(Qt::UserRole+3, "column3");

    return roles;
}

void HwaTreeModel::setColumnsHeader(const QStringList& columns)
{
	if (columns.size() == 0) return;
	_head->setColumnCount(columns.size());
	for (int i=0; i<columns.size(); ++i)
	{
		_head->setData(i, columns[i]);
	}
}
