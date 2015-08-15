/**
*   \file TreeItem.h
*   \brief 节点类型定义.
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年8月11日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __TREEITEM_H__
#define __TREEITEM_H__

#include <QIcon>
#include <QVector>
#include <QList>
#include <QVariant>
#include <QString>

class HwaItemData
{
public:
	inline HwaItemData() : role(-1) {}
	inline HwaItemData(int r, const QVariant& v) : role(r), value(v) {}
	int role;
	QVariant value;
	inline bool operator==(const HwaItemData &other) const { return role == other.role && value == other.value; }
};

class HwaTreeItem
{
public:
	enum NodeType
	{
		Type = 0,
		TypeCard = Qt::UserRole,    //板卡
		TypeVirtualTerminal,    //虚拟终端
		TypeVirtualLink,        //虚链路
		TypePort,               //端口 
		TypeMsg                 //工程值
	};

	HwaTreeItem();
	HwaTreeItem(const QString& text);
	HwaTreeItem(const QIcon& icon, const QString& text);
	virtual ~HwaTreeItem();

	//modify
	virtual QVariant data(int column, int role = Qt::DisplayRole) const;
	virtual bool setData(int column, const QVariant& value, int role = Qt::EditRole);
	virtual Qt::ItemFlags flags() const;

	inline void setFlags(Qt::ItemFlags flags) { _flags = flags; }
	inline HwaTreeItem* parent() const { return _parent; }
	void insertChild(int row, HwaTreeItem* child);
	//sarch
	int row() const;
	int indexOfChild(HwaTreeItem* child) const;
	HwaTreeItem* child(int index) const;

	//delete
	HwaTreeItem* takeChild(int index);

	inline int rowCount() const { return _children.size(); }
	inline int columnCount() const { return _values.size(); }
	inline void setColumnCount(int count) { _values.resize(count); }
	void setType(int type);
	virtual int type() const;

private:
	int _type;

	// One item has a vector of column entries. Each column has a vector of (role, value) pairs.
	QVector< QVector<HwaItemData> > _values;
	HwaTreeItem* _parent;
	QList<HwaTreeItem*> _children;
	Qt::ItemFlags _flags;
};

#endif //__TREEITEM_H__
