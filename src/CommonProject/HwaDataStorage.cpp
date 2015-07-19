
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include "HwaViewBinder.h"

#include "HwaDataStorage.h"

HwaBinderDataSource::HwaBinderDataSource(HwaViewBinder* binder, DataStorage* source)
	: _binder(binder)
	, _source(source)
{

}

HwaBinderDataSource::~HwaBinderDataSource()
{

}

void HwaBinderDataSource::enqueue(const QString& infor)
{
	if (this->checkInfor(infor))
	{
		_queue.enqueue(infor);

		this->wakeOne();
	}

	if (!this->isRunning())
	{
		this->wakeOne();
	}
}

void HwaBinderDataSource::query(const QString& infor)
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

	_binder->enqueue(infor, data);
}

void HwaBinderDataSource::processReportInfor(const QString& infor)
{
	QVector<QString>& infors = _binder->processReportInfor(infor);
	foreach (const QString& rawInfor, infors)
	{
		this->enqueue(rawInfor);
	}
}

void HwaBinderDataSource::run()
{
	//遍历队列
	while (true)
	{
		QString infor = _queue.dequeue();

		//查询数据,将查询数据给绑定器解析处理,
		this->query(infor);

		if (_queue.isEmpty())
		{
			this->abort();
		}
	}
}

bool HwaBinderDataSource::checkInfor(const QString& infor)
{
	QJsonParseError error;
	QJsonDocument jDoc = QJsonDocument::fromJson(infor.toLatin1(), &error);
	if (error.error == QJsonParseError::NoError)
	{
		QJsonObject jobj = jDoc.object();
		
		return jobj.contains("view") && jobj.contains("item") 
			&& jobj.contains("path") && jobj.contains("id")
			&& jobj.contains("row") && jobj.contains("count");
	}

	return false;
}

void HwaBinderDataSource::abort()
{
	_mutex.lock();
	_condition.wait(&_mutex);
	_mutex.unlock();
}

void HwaBinderDataSource::wakeOne()
{
	_mutex.lock();
	_condition.wakeOne();
	_mutex.unlock();
}
