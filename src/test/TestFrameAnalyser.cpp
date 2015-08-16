
#include "HwaFrameAnalyser.h"
#include "HwaAnalyserManager.h"
#include "HwaPlatformConfigManager.h"
#include "HwaFrameConfigManager.h"

struct CanTestData
{
	uint a: 1;
	uint b: 11;
	uint c: 2;
	uint d: 4;
	uint e: 7;
	uint f: 8;
	char g[4];
	int h;
};

void TestAnalyser()
{
	CanTestData* c = new CanTestData;
	memset(c, 0, sizeof(CanTestData));
	c->a = 1;
	c->b = 100;//1100 100 0x64
	c->c = 2;//10 0x02
	c->d = 11;//1011 0x0B
	c->e = 127;//111 1111 0x7F
	c->f = 121;//111 1001 0x79
	c->h = 1;
	memcpy(c->g, "Helo", 4);
	printf("value=%u\n", c->a);
	printf("value=%u\n", c->b);
	printf("value=%u\n", c->c);
	printf("value=%u\n", c->d);
	printf("value=%u\n", c->e);
	printf("value=%u\n", c->f);
	printf("value=%s\n", c->g);
	printf("value=%d\n", c->h);
	HwaPlatformConfigManager& mgr = HwaPlatformConfigManager::getManager();
	mgr.setFile("../config/framework-config.xml");
	HwaFrameConfigManager& frameMgr = HwaFrameConfigManager::getManager();
	FrameInfor frameInfor = frameMgr.getFrameInfor("00000011111");
	QVector<int> segments;
	segments.push_back(1);
	segments.push_back(2);
	segments.push_back(3);
	segments.push_back(4);
	segments.push_back(5);
	segments.push_back(6);
	segments.push_back(7);
	segments.push_back(8);
	uchar* data = (uchar*)(c);
	HwaAnalyserManager& analyseMgr = HwaAnalyserManager::getManager();
	SmartBitsets bitsets = analyseMgr.analyse(data, frameInfor.id.c_str(), segments);
	foreach (SmartBitset bitset, bitsets)
	{
		printf("value=%u\n", bitset->toULong());
	}
	printf("g=%s\n", bitsets[6]->toString().c_str());

}