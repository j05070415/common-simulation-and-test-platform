
#include <QVector>
#include <QAbstractItemModel>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>

#include "HwaPropertyResponser.h"

HwaPropertyResponser::HwaPropertyResponser()
	: _role(0)
{

}

HwaPropertyResponser::HwaPropertyResponser(const HwaPropertyResponser& c)
{
	_index = c._index;
	_role = c._role;
}

HwaPropertyResponser::~HwaPropertyResponser()
{

}

QString HwaPropertyResponser::properties() const
{	if (!_index.isValid()) return "";
	
	QJsonArray props = _index.model()->data(_index, _role).value<QJsonArray>();
	
	return QJsonDocument(props).toJson();
}

QString HwaPropertyResponser::changeValue(const QString& key, const QVariant& value)
{
	if (!_index.isValid()) return "";

	QAbstractItemModel* model = (QAbstractItemModel*)_index.model();
	Q_ASSERT(model != NULL);
	QJsonValue jValue = model->data(_index, _role).value<QJsonValue>();
	if (!jValue.isArray()) return "";

	QJsonArray props = jValue.toArray();
	QJsonArray::iterator iter = props.begin();
	for (; iter != props.end(); ++iter)
	{
		//¸ÄkeyÖµ
		if ((*iter).isObject() && (*iter).toObject().contains(key))
		{
			QJsonObject jObj = (*iter).toObject();
			jObj[key] = QJsonValue::fromVariant(value);
			*iter = jObj;

			model->setData(_index, props, _role);
			break;
		}
	}

	return "";
}

void HwaPropertyResponser::bindNode(const QModelIndex& index, int propertyRole)
{
	_index = index;
	_role = propertyRole;
}

