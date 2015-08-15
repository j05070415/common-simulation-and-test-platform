
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMutexLocker>
#include <QDebug>

#include "HwaViewBinder.h"

#include "HwaDataStorage.h"

HwaDataStorage::HwaDataStorage(DataStorage* source)
	: _source(source)
	, _stoped(true)
{
}

HwaDataStorage::~HwaDataStorage()
{
	_stoped = true;

	WAIT_THREAD_FINISHED
}

void HwaDataStorage::enqueue(const QJsonObject& infor)
{
	if (this->checkInfor(infor))
	{
		QMutexLocker locker(&_mutex);
		_queue.enqueue(infor);
	}
}

void HwaDataStorage::query(const QJsonObject& infor)
{
	//_source查询数据
	//给_binder发送
	//测试数据
	struct CanData
	{
		quint64 start : 1;
		quint64 id : 11;
		quint64 rtr : 1;
		quint64 idr : 1;
		quint64 r0 : 1;
		quint64 DLC : 4;
		quint64 data : 16;//据实际数据实时运算
		quint64 crc_queue : 15;
		quint64 crc_define : 1;
		quint64 ack_slot : 1;
		quint64 ack_define : 1;
		quint64 eof : 7;
	};

	CanData* c = new CanData;
	memset(c, 0, sizeof(CanData));
	c->start = 1;
	c->id = 0x1E;
	c->rtr = 1;
	c->idr = 0;
	c->r0 = 1;
	c->DLC = 2;
	c->data = 0xFFFF;
	c->crc_queue = 0xE0;//224
	c->crc_define = 1;
	c->ack_slot = 1;
	c->ack_define = 1;
	c->eof = 66;
	uchar* data = (uchar*)c;

	QJsonObject jobj = infor;
	jobj["length"] = QJsonValue((int)sizeof(CanData));

#ifndef NDEBUG
	for (int i=0; i<1000; ++i)
	{
		c->id = i;
		foreach (HwaDataSourceObserver* binder, _observers)
		{
			binder->notify(jobj, data);
		}
		msleep(10);
	}
#else
	foreach (HwaDataSourceObserver* binder, _observers)
	{
		binder->notify(jobj, data);
	}
#endif

	delete c;
}

void HwaDataStorage::processReportInfor(const QJsonObject& infor)
{
	foreach (HwaDataSourceObserver* observer, _observers)
	{
		QVector<QJsonObject>& infors = observer->processReportInfor(infor);
		foreach (const QJsonObject& rawInfor, infors)
		{
			this->enqueue(rawInfor);
		}
	}
}

void HwaDataStorage::run()
{
	qDebug("storage started!");
	_stoped = false;
	//遍历队列
	while (!_stoped)
	{
		if (!_queue.isEmpty())
		{
			QMutexLocker locker(&_mutex);
			QJsonObject& infor = _queue.dequeue();
			locker.unlock();

			//查询数据,将查询数据给绑定器解析处理,
			this->query(infor);
		}
		else
		{
			msleep(1);
		}
	}

	qDebug("storage exited!");
}

bool HwaDataStorage::checkInfor(const QJsonObject& jobj)
{
	return jobj.contains("view") && jobj.contains("item") 
		&& jobj.contains("path") && jobj.contains("id")
		&& jobj.contains("row") && jobj.contains("count");
}

void HwaDataStorage::addObserver(HwaDataSourceObserver* observer)
{
	if (observer != NULL)
	{
		_observers.push_back(observer);
	}
}
