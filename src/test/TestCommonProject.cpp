
#include <QDebug>
#include "HwaPropertyInforsManager.h"
#include "HwaProjectConfigManager.h"

void TestPropertyInfors()
{
	HwaPropertyInforsManager& propsMgr = HwaPropertyInforsManager::getManager();
	propsMgr.setFile("D:/Git-repository/common-simulation-and-test-platform/src/config/node-attributes.xml");

	//qDebug() << propsMgr.getNodeProperty("AFDX", "USER");
	//qDebug() << propsMgr.getNodeProperty("AFDX", "VL");
	//qDebug() << propsMgr.getNodeProperty("AFDX", "PORT");
	//qDebug() << propsMgr.getNodeProperty("CAN", "USER");
	qDebug() << propsMgr.getNodeProperty("CAN", "ROOT");
}