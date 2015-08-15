
#include <QJsonDocument>
#include <QJsonObject>

#include "HwaViewBinder.h"
#include "HwaViewConfigManager.h"

#include "HwaProjectView.h"

HwaProjectView::HwaProjectView()
	: _binder(NULL)
{
}

HwaProjectView::HwaProjectView(const HwaProjectView& view)
{
	_binder = view._binder;
	_projectName = view._projectName;
	_items = view._items;
}

HwaProjectView::~HwaProjectView()
{

}

QString HwaProjectView::name() const
{
	return "HwaProjectView";
}

ItemsInfor HwaProjectView::getItemsInfor() const
{
	return _items;
}

bool HwaProjectView::hasItem(const QString& objName) const
{
	foreach (const ItemInfor& item, _items)
	{
		if (item.objName == objName.toStdString())
		{
			return true;
		}
	}

	return false;
}

void HwaProjectView::setBinder(HwaViewBinder* binder)
{
	_binder = binder;
}

void HwaProjectView::setProjectName(const QString& name)
{
	_projectName = name;
	HwaViewConfigManager& mgr = HwaViewConfigManager::getManager();
	_items = ItemsInfor::fromStdVector(mgr.getBindObjects(_projectName.toStdString(), this->name().toStdString()));
}

void HwaProjectView::updateView(const QString& objName, const QVariant& value)
{
	emit changeValue(objName, value);
}

ItemInfor HwaProjectView::getItemInfor(const QString& objName) const
{
	foreach (const ItemInfor& item, _items)
	{
		if (item.objName == objName.toStdString())
		{
			return item;
		}
	}

	return ItemInfor();
}

void HwaProjectView::onAction( const QString& action, const QVariant& param )
{
	// ¥¶¿Ì ”Õº√¸¡Ó
	qDebug("HwaProjectView::onAction");
}
