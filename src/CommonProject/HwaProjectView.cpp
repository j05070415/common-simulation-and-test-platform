
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

void HwaProjectView::onItemChanged(const QString& objName, const QVariant& param)
{
	if (_binder != NULL)
	{
		QVector<QString> infors;
		ItemInfor& item = this->getItemInfor(objName);
		//{view:"CanDataViewer", item:"label1", path:"ArincSimulation/CAN/port1", id="00000011111", row=0, count=1000}
		//TODO:默认为一个控件绑定一个path下数据，如有不同绑定子类化自行处理
		if (item.sources.size() > 0)
		{
			QJsonDocument json = QJsonDocument::fromJson(param.toString().toLatin1());
			QJsonObject jObj = json.object();
			SourceInfor& source = item.sources[0];
			QString command = QString("\"view\":\"%1\",\"item\":\"%2\",\"path\":\"%3\",\"id\"=\"%4\",\"row\"=%5,\"count\"=%6")
				.arg(this->name())
				.arg(objName)
				.arg(source.path.c_str())
				.arg(source.id.c_str())
				.arg(jObj.value("row").toInt())
				.arg(jObj.value("count").toInt());
			_binder->enqueue(command);
		}
	}
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
