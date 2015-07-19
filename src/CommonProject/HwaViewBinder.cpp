
#include <QDebug>
#include <QSharedPointer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPair>

#include "HwaDataSource.h"
#include "HwaAnalyserManager.h"
#include "HwaProjectView.h"
#include "HwaViewBinder.h"

Q_DECLARE_METATYPE(SmartBitsets);
HwaViewBinder::HwaViewBinder()
	: QThread(NULL)
{
}

HwaViewBinder::HwaViewBinder(const HwaViewBinder& binder)
{
	_views = binder._views;
	_cache = binder._cache;
}

HwaViewBinder::~HwaViewBinder()
{
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
	//stop thread
	this->quit();

	QQueue<QPair<QString, uchar*> >::iterator iter = _cache.begin();
	for (; iter != _cache.end(); ++iter)
	{
		delete[] (*iter).second;
	}
	_cache.clear();
	_views.clear();
}

void HwaViewBinder::enqueue(const QString& infor, uchar* data)
{
	//�������
	if (_cache.count() > MAX_CACHE)
	{
		qDebug("HwaViewBinder queue full!");
		_cache.dequeue();
	}

	_cache.enqueue(QPair<QString, uchar*>(infor, data));
	//�����߳�
	if (!this->isRunning())
	{
		this->wakeOne();
	}
}

void HwaViewBinder::query(QString& command)
{
	//{view:"CanDataViewer", item:"label1", path:"ArincSimulation/CAN/port1", id="00000011111", row=0, count=1000}
	_source->enqueue(command);
}

void HwaViewBinder::run()
{
	//ȡ����
	while (true)
	{
		QPair<QString, uchar*> source = _cache.dequeue();

		//����ʵ����Ϣ��ѯ����
		QSharedPointer<uchar> data(source.second);

		//��������
		HwaAnalyserManager& mgr = HwaAnalyserManager::getManager();
		QJsonParseError jsonError;
		QJsonDocument json = QJsonDocument::fromJson(source.first.toLatin1(), &jsonError);
		if (jsonError.error != QJsonParseError::NoError)
		{
			qDebug("json error in binder thread!");
			continue;
		}
		QJsonObject jObj = json.object();
		HwaProjectView* view = this->findView(jObj.value("view").toString());
		QString itemName = jObj.value("item").toString();

		std::vector<SourceInfor>& sources = view->getItemInfor(itemName).sources;
		SmartBitsets bitsets;
		foreach (const SourceInfor& source, sources)
		{
			bitsets += mgr.analyse(data.data(), jObj.value("id").toString(), QVector<int>::fromStdVector(source.segments));
		}
		
		//������ͼ
		view->updateView(itemName, QVariant::fromValue(bitsets));
		//emit changeValue(itemName, QVariant::fromValue(bitsets));

		if (_cache.isEmpty())
		{
			this->abort();
		}
	}
}

QVector<QString> HwaViewBinder::processReportInfor(const QString& infor)
{
	QJsonDocument json = QJsonDocument::fromJson(infor.toLatin1());
	QJsonObject jObj = json.object();
	QString path = jObj.value("path").toString();
	QVector<QString> filteredInfors;
	//TODO������������˴����Ż���Ŀ�꣺������ֻ��һ��Path���ݲ�ѯ
	QHash<uint, char> filter;
	foreach (HwaProjectView* view, _views)
	{
		ItemsInfor& infors = view->getItemsInfor();
		foreach (const ItemInfor& item, infors)
		{
			foreach (const SourceInfor& source, item.sources)
			{
				uint h = qHash(infor);
				if (!filter.contains(h) && source.path == path.toStdString())
				{
					filteredInfors.push_back(infor);
					filter[h] = '\0';
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

void HwaViewBinder::abort()
{
	_mutex.lock();
	_condition.wait(&_mutex);
	_mutex.unlock();
}

void HwaViewBinder::wakeOne()
{
	_mutex.lock();
	_condition.wakeOne();
	_mutex.unlock();
}
