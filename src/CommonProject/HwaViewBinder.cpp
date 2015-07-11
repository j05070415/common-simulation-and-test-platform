
#include <QDebug>
#include <QSharedPointer>
#include <QJsonDocument>
#include <QJsonObject>

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
	_cache.clear();

	_views.clear();
}

void HwaViewBinder::enqueue(const QString& infors)
{
	//�������
	if (_cache.count() > MAX_CACHE)
	{
		_cache.dequeue();
	}

	_cache.enqueue(infors);
	//�����߳�
	if (!this->isRunning())
	{
		this->start();
	}
}

uchar* HwaViewBinder::query(QString& command)
{
	//{view:"CanDataViewer", item:"label1", path:"ArincSimulation/CAN/port1", id="00000011111", row=0, count=1000}
	return NULL;
}

void HwaViewBinder::run()
{
	//ȡ����
	while (true)
	{
		QString command = _cache.dequeue();
		this->query(command);

		//����ʵ����Ϣ��ѯ����
		QSharedPointer<uchar> data(this->query(command));

		//��������
		HwaAnalyserManager& mgr = HwaAnalyserManager::getManager();
		QJsonParseError jsonError;
		QJsonDocument json = QJsonDocument::fromJson(command.toLatin1(), &jsonError);
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
		
		//�����ź�
		view->updateView(itemName, QVariant::fromValue(bitsets));
		//emit changeValue(itemName, QVariant::fromValue(bitsets));

		if (_cache.size() == 0)
		{
			this->sleep(ULONG_MAX);
		}
	}
}

void HwaViewBinder::processReportInfor(const QString& infor)
{
	QJsonDocument json = QJsonDocument::fromJson(infor.toLatin1());
	QJsonObject jObj = json.object();
	QString path = jObj.value("path").toString();
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
					_cache.enqueue(infor);
					filter[h] = '\0';
				}
			}
		}
	}
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
