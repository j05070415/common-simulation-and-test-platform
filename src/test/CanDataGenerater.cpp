
#include "HwaFrameAnalyser.h"
#include "HwaAnalyserManager.h"
#include "HwaPlatformConfigManager.h"
#include "HwaFrameConfigManager.h"

struct CanData
{
	ullong start : 1;
	ullong id : 11;
	ullong rtr : 1;
	ullong idr : 1;
	ullong r0 : 1;
	ullong DLC : 4;
	ullong data : 16;//据实际数据实时运算
	ullong crc_queue : 15;
	ullong crc_define : 1;
	ullong ack_slot : 1;
	ullong ack_define : 1;
	ullong eof : 7;
};

void GenerateData()
{
	CanData* c = new CanData;
	memset(c, 0, sizeof(CanData));
	c->start = 1;
	c->id = 0x1E;
	c->rtr = 1;
	c->idr = 0;
	c->r0 = 1;
	c->DLC = 2;
	c->data = 0xFFFF;
	c->crc_queue = 0xE0;//224
	c->crc_define = 1;
	c->ack_slot = 1;
	c->ack_define = 1;
	c->eof = 66;
	
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
	segments.push_back(8);
	segments.push_back(9);
	segments.push_back(10);
	segments.push_back(11);
	segments.push_back(12);
	uchar* data = (uchar*)(c);
	HwaAnalyserManager& analyseMgr = HwaAnalyserManager::getManager();
	SmartBitsets bitsets = analyseMgr.analyse(data, frameInfor.id.c_str(), segments);
	foreach (SmartBitset bitset, bitsets)
	{
		printf("value=%u\n", bitset->toULong());
	}
}