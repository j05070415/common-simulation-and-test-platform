
#ifndef __HWA_PROPERTY_RESPONSER_H__
#define __HWA_PROPERTY_RESPONSER_H__

#include <QString>
#include <QVariant>
#include <QModelIndex>

struct HwaNodeProperty
{
	QString type;
	QString key;
	QString name;
	QVariant value;
	QString desc;
	QString jsonscope;
};

class HwaPropertyResponser : public QObject
{
public:
	HwaPropertyResponser();
	HwaPropertyResponser(const HwaPropertyResponser& c);
	~HwaPropertyResponser();

	void bindNode(const QModelIndex& index, int propertyRole);
	virtual QString properties() const;
	virtual QString changeValue(const QString& key, const QVariant& value);
protected:
	QModelIndex _index;
	int _role;
};

#endif