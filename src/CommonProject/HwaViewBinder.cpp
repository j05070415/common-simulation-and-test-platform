
#include <QDebug>
#include <QSharedPointer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPair>
#include <QMutexLocker>

#include "HwaAnalyserManager.h"
#include "HwaProjectView.h"
#include "HwaDataStorage.h"
#include "HwaViewBinder.h"

HwaViewBinder::HwaViewBinder()
	: _stoped(true)
{
	//TODO: 暂时模拟数据源
	_source.reset(new HwaDataStorage(NULL));
	_source->addObserver(this);
	_source->start();
}

HwaViewBinder::HwaViewBinder(const HwaViewBinder& binder)
{
	_views = binder._views;
	_source.reset(new HwaDataStorage(NULL));
	_source->addObserver(this);
	_source->start();
}

HwaViewBinder::~HwaViewBinder()
{
	_source.reset();
	this->_stoped = true;
	WAIT_THREAD_FINISHED

	this->reset();
}

QString HwaViewBinder::name() const
{
	return "HwaViewBinder";
}

void HwaViewBinder::bind(HwaProjectView* view)
{
	if (view == NULL)
	{
		return;
	}

	_views.push_back(view);
	view->setBinder(this);
}

void HwaViewBinder::reset()
{
	_cache.clear();
	_views.clear();
}

void HwaViewBinder::query(const QJsonObject& infor)
{
	//{view:"CanDataViewer", objectName:"label1", path:"ArincSimulation/CAN/port1", id="00000011111", row=0, count=1000}
	_source->enqueue(infor);
}

void HwaViewBinder::run()
{
	qDebug("binder started!");
	_stoped = false;
	//取队列
	while (!_stoped)
	{
		if (!_cache.isEmpty())
		{
			QMutexLocker locker(&_mutex);
			QPair<QJsonObject, QSharedPointer<uchar> > source = _cache.dequeue();
			locker.unlock();

			//按照实际信息查询数据
			QSharedPointer<uchar> data = source.second;

			//解析数据
			HwaAnalyserManager& mgr = HwaAnalyserManager::getManager();
			QJsonObject jObj = source.first;
			HwaProjectView* view = this->findView(jObj.value("view").toString());
			if (view == NULL) continue;

			QString itemName = jObj.value("item").toString();

			std::vector<SourceInfor>& sources = view->getItemInfor(itemName).sources;
			SmartBitsets bitsets;
			foreach (const SourceInfor& source, sources)
			{
				bitsets += mgr.analyse(data.data(), jObj.value("id").toString(), QVector<int>::fromStdVector(source.segments));
			}

			//更新视图
			if (bitsets.size() > 0)
			{
				QList<QString> resData;
				foreach (SmartBitset bitset, bitsets)
				{
					resData.push_back(QString::number(bitset->toULong()));
				}
				view->updateView(itemName, QVariant::fromValue(resData));
			}
		}
		else
		{
			msleep(1);
		}
	}

	qDebug("binder exited!");
}

QVector<QJsonObject> HwaViewBinder::processReportInfor(const QJsonObject& jObj)
{
	QString path = jObj.value("path").toString();
	QVector<QJsonObject> filteredInfors;
	foreach (HwaProjectView* view, _views)
	{
		ItemsInfor& infors = view->getItemsInfor();
		foreach (const ItemInfor& item, infors)
		{
			foreach (const SourceInfor& source, item.sources)
			{
				//相同通道数据
				if (source.path == path.toStdString())
				{
					QJsonObject infor = jObj;
					infor["item"] = item.objName.c_str();
					infor["view"] = view->name();
					infor["id"] = source.id.c_str();
					filteredInfors.push_back(infor);
				}
			}
		}
	}

	return filteredInfors;
}

HwaProjectView* HwaViewBinder::findView(const QString& viewName)
{
	HwaProjectView* res = NULL;
	foreach (HwaProjectView* view, _views)
	{
		if (view->name() == viewName)
		{
			res = view;
			break;
		}
	}

	return res;
}

void HwaViewBinder::notify(const QJsonObject& infor, uchar* data)
{
	if (!infor.contains("length"))
	{
		return;
	}

	int length = infor["length"].toInt();
	uchar* buffer = new uchar[length];
	memcpy(buffer, data, length);
	//插入队列
	QMutexLocker locker(&_mutex);
	if (_cache.count() > MAX_CACHE)
	{
		qDebug("HwaViewBinder queue full!");
		_cache.dequeue();
	}

	_cache.enqueue(QPair<QJsonObject, QSharedPointer<uchar> >(infor, QSharedPointer<uchar>(buffer)));
}
