
#ifndef __HWA_PROJECTCONFIGMANAGER_H__
#define __HWA_PROJECTCONFIGMANAGER_H__

#include <QString>
#include <QModelIndex>

#include "commonproject_global.h"

class QAbstractItemModel;
class TiXmlElement;

class COMMONPROJECT_EXPORT HwaProjectConfigManager
{
public:
	static HwaProjectConfigManager& getManager();

	QString readConfig(const QString& path);

	static QAbstractItemModel* fileToModel(const QString& path);
	static bool modelToFile(QAbstractItemModel* model, const QString& file);

private:
	HwaProjectConfigManager();
	~HwaProjectConfigManager();
	HwaProjectConfigManager(const HwaProjectConfigManager& c);
	HwaProjectConfigManager& operator=(const HwaProjectConfigManager& c);

	static void loadChild(QAbstractItemModel* model, const QModelIndex& index, TiXmlElement* parent);
	static void saveModel(QAbstractItemModel* model, const QModelIndex& index, TiXmlElement* parent);
};

#endif//__HWA_PROJECTCONFIGMANAGER_H__