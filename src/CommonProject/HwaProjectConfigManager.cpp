
#include <QAbstractItemModel>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QMetaType>

#include "tinyxml.h"
#include "TreeModel.h"
#include "HwaPropertyResponser.h"
#include "HwaProjectConfigManager.h"

HwaProjectConfigManager::HwaProjectConfigManager()
{

}

HwaProjectConfigManager::~HwaProjectConfigManager()
{

}

HwaProjectConfigManager& HwaProjectConfigManager::getManager()
{
	static HwaProjectConfigManager mgr;

	return mgr;
}

QString HwaProjectConfigManager::readConfig(const QString& path)
{
	return "";
}

QAbstractItemModel* HwaProjectConfigManager::fileToModel(const QString& path)
{
	TiXmlDocument doc(path.toLocal8Bit().constData());
	if (!doc.LoadFile()) return NULL;

	HwaTreeModel* model = new HwaTreeModel;
	TiXmlElement* root = doc.RootElement();
	while (root)
	{
		QString columns = root->Attribute("columns");
		model->setColumnsHeader(columns.split(";"));
		HwaProjectConfigManager::loadChild(model, model->index(0, 0), root);
	}
	
	return model;
}

bool HwaProjectConfigManager::modelToFile(QAbstractItemModel* model, 
	const QString& file)
{
	if (model == NULL) return false;

	TiXmlDocument doc(file.toLocal8Bit().constData());
	if (!doc.SaveFile()) return false;

	TiXmlElement* rootElement = doc.RootElement();
	QStringList columns;
	for (int i=0; i<model->columnCount(); ++i)
	{
		columns.push_back(model->headerData(i, Qt::Horizontal).toString());
	}
	rootElement->SetAttribute("columns", columns.join(";").toLatin1().constData());

	HwaProjectConfigManager::saveModel(model, QModelIndex(), rootElement);
	return true;
}

void HwaProjectConfigManager::loadChild(QAbstractItemModel* model, 
	const QModelIndex& index, 
	TiXmlElement* parent)
{
	TiXmlElement* nodeElement = parent->FirstChildElement("node");
	int row = 0;
	while (nodeElement)
	{
		TiXmlElement* propElement = nodeElement->FirstChildElement("property");
		QString nodeType = propElement->Attribute("type");
		QString strResponser = propElement->Attribute("responser");
		int type = QMetaType::type(strResponser.toLatin1());
		HwaPropertyResponser* responser = (HwaPropertyResponser*)QMetaType::create(type);
		if (responser == NULL)
		{
			nodeElement = nodeElement->NextSiblingElement("node");
			continue;
		}

		QString nodeName = propElement->Attribute("name");
		QJsonArray props;
		while (propElement)
		{
			QJsonObject propObj;
			propObj["id"] = propElement->Attribute("id");
			propObj["type"] = propElement->Attribute("type");
			propObj["name"] = propElement->Attribute("name");
			propObj["value"] = propElement->Attribute("value");
			propObj["desc"] = propElement->Attribute("desc");
			propObj["scope"] = propElement->Attribute("scope");
			props.append(propObj);

			propElement = propElement->NextSiblingElement("property");
		}

		model->insertRows(row, 1, index);
		QModelIndex childIndex = model->index(row, 0, index);
		model->setData(childIndex, props, Qt::UserRole + 1000);
		model->setData(childIndex, nodeName);
		//TODO:删除节点时删除此对象
		model->setData(childIndex, QVariant::fromValue<HwaPropertyResponser*>(responser), Qt::UserRole + 1001);
		model->setData(childIndex, nodeType, Qt::UserRole + 1002);
		HwaProjectConfigManager::loadChild(model, childIndex, nodeElement);

		nodeElement = nodeElement->NextSiblingElement("node");
	}
}

void HwaProjectConfigManager::saveModel(QAbstractItemModel* model, 
	const QModelIndex& index, 
	TiXmlElement* parent)
{
	for (int i=0; i<model->rowCount(index); ++i)
	{
		QModelIndex childIndex = model->index(i, 0, index);
		QJsonArray data = model->data(childIndex, Qt::UserRole + 1000).toJsonArray();

		//TiXmlElement* childElement = new TiXmlElement;
		//childElement->SetAttribute()
		//parent->inser
	}
}
