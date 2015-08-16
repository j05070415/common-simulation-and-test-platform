
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>

#include "tinyxml.h"
#include "HwaPropertyInforsManager.h"

struct HwaPropertyInforsManagerPrivate
{
	QJsonObject _data;//proto-prop(key,name,value,desc,scope...etc)
};

HwaPropertyInforsManager::HwaPropertyInforsManager()
	: _d(new HwaPropertyInforsManagerPrivate)
{

}

HwaPropertyInforsManager::~HwaPropertyInforsManager()
{
	delete _d;
}

HwaPropertyInforsManager& HwaPropertyInforsManager::getManager()
{
	static HwaPropertyInforsManager mgr;

	return mgr;
}

QString HwaPropertyInforsManager::getNodeProperty(const QString& protoType, 
												  const QString& nodeType)
{
	QJsonValue protoNdoe = _d->_data.value(protoType);
	if (!protoNdoe.isObject()) return "";

	QJsonValue props = protoNdoe.toObject().value(nodeType);
	if (!props.isObject()) return "";

	return QJsonDocument(props.toObject()).toJson();
}

void HwaPropertyInforsManager::setFile(const QString& file)
{
	TiXmlDocument doc(file.toLocal8Bit().constData());
	if (doc.LoadFile())
	{
		TiXmlElement* element = doc.RootElement();
		while (element)
		{
			QString name = element->Attribute("name");
			QJsonObject nodes;

			TiXmlElement* nodeElement = element->FirstChildElement();
			while (nodeElement)
			{
				QString nodeType = nodeElement->Attribute("type");
				TiXmlElement* propElement = nodeElement->FirstChildElement();
				QJsonObject propMap;
				while (propElement)
				{
					QJsonObject propObj;
					QString key = propElement->Attribute("id");
					propObj["id"] = key;
					propObj["type"] = propElement->Attribute("type");//value type
					propObj["name"] = propElement->Attribute("name");
					propObj["value"] = propElement->Attribute("value");
					propObj["desc"] = propElement->Attribute("desc");
					propObj["scope"] = propElement->Attribute("scope");

					propMap[key] = propObj;
					propElement = propElement->NextSiblingElement();
				}
				nodes[nodeType] = propMap;

				nodeElement = nodeElement->NextSiblingElement();
			}

			_d->_data[name] = nodes;
			element = element->NextSiblingElement();
		}
	}
	else
		qDebug("file=%s,line=%d", __FILE__, __LINE__);
}
