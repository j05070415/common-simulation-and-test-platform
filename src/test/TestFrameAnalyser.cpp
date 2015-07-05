
#include "HwaFrameAnalyser.h"
#include "HwaCommonFrameAnalyser.h"
#include "HwaPlatformConfigManager.h"
#include "HwaFrameConfigManager.h"

struct CanTestData
{
	uint a: 1;
	uint b: 11;
	uint c: 2;
	uint d: 4;
	uint e: 7;
	uint f: 7;
	int g;
};

void TestAnalyser()
{
	CanTestData* c = new CanTestData;
	memset(c, 0, sizeof(CanTestData));
	c->a = 1;
	c->b = 100;//110 0100
	c->c = 2;//10
	c->d = 11;//1011
	c->e = 127;//111 1111
	c->f = 129;//1000 0000
	c->g = -1;
	HwaPlatformConfigManager& mgr = HwaPlatformConfigManager::getManager();
	mgr.setFile("../config/framework-config.xml");
	HwaFrameConfigManager& frameMgr = HwaFrameConfigManager::getManager();
	FrameInfor frameInfor = frameMgr.getFrameInfor("00000011110");
	QVector<int> segments;
	segments.push_back(1);
	segments.push_back(2);
	segments.push_back(3);
	segments.push_back(4);
	segments.push_back(5);
	segments.push_back(6);
	segments.push_back(7);
	uchar* data = (uchar*)(c);
	HwaCommonFrameAnalyser analyser;
	analyser.setData(data);
	analyser.setFrameInfor(frameInfor);
	SmartBitsets bitsets = analyser.analyse(segments);
	foreach (SmartBitset bitset, bitsets)
	{
		printf("value=%lf\n", bitset->toDouble());
	}

}