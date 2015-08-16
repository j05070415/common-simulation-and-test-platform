
#ifndef __HWA_PROPERTYINFORSMANAGER_H__
#define __HWA_PROPERTYINFORSMANAGER_H__

#include <QString>

#include "commonproject_global.h"

class HwaPropertyInforsManagerPrivate;

class COMMONPROJECT_EXPORT HwaPropertyInforsManager
{
public:
	static HwaPropertyInforsManager& getManager();

	void setFile(const QString& file);
	QString getNodeProperty(const QString& protoType, const QString& nodeType);
private:
	HwaPropertyInforsManager();
	~HwaPropertyInforsManager();
	HwaPropertyInforsManager(const HwaPropertyInforsManager& c);
	HwaPropertyInforsManager& operator=(const HwaPropertyInforsManager& c);

private:
	HwaPropertyInforsManagerPrivate* _d;
};

#endif//__HWA_PROPERTYINFORSMANAGER_H__