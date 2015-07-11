
#include <QString>

#include "HwaPlatformConfigManager.h"
#include "HwaFrameConfigManager.h"
#include "HwaViewConfigManager.h"
#include "StringHelper.h"


void printFrame(const FrameInfor& frame)
{
	printf("name=%s,id=%s,type=%s,analyser=%s\n", QString::fromUtf8(frame.name.c_str()).toLocal8Bit().constData(), frame.id.c_str(), frame.type.c_str(), frame.analyser.c_str());
	for (size_t i=0; i < frame.segments.size(); ++i)
	{
		SegmentInfor segment = frame.segments[i];
		printf("name=%s,id=%d,size=%d,offset=%d,ref=%d,pre=%d,des=%s\n", QString::fromUtf8(segment.name.c_str()).toLocal8Bit().constData(), segment.id
			,segment.size, segment.offset, segment.reference, segment.previous, segment.description.c_str());
	}
}

void TestPlatformConfigManager()
{
	HwaPlatformConfigManager& mgr = HwaPlatformConfigManager::getManager();
	mgr.setFile("../config/framework-config.xml");
	printf("view path=%s\n", mgr.getViewConfigPath().c_str());
	printf("protocal path=%s\n", mgr.getProtocalConfigPath().c_str());
	mgr.getProjectsInfor();
	mgr.getProjectCardInfors("simulation");
	mgr.getProjectCardInfors("test");

	HwaFrameConfigManager& frameMgr = HwaFrameConfigManager::getManager();
	FrameInfor frameInfor = frameMgr.getFrameInfor("00000011111");
	printFrame(frameInfor);

	HwaString information = mgr.getHomePageDescription();
	printf("page infor=%s\n", information.c_str());
}

void TestStringHelper()
{
	std::vector<std::string> result = StringHelper::Split("1 ;  2;3 ;4 ", ' ');
	for (size_t i=0; i<result.size(); ++i)
	{
		printf("v=%s,size=%d\n", result[i].c_str(), result[i].size());
	}

	std::string ss("		a	sdf ");
	printf("ssize=%d,sub=%s,size=%d\n", ss.size(), StringHelper::Trim(ss).c_str(), StringHelper::Trim(ss).size());
}

void PrintItemInfor(ItemInfor& item)
{
	printf("obj name=%s\n", QString::fromUtf8(item.objName.c_str()).toLocal8Bit().constData());
	std::vector<SourceInfor>::iterator iter = item.sources.begin();
	while (iter != item.sources.end())
	{
		printf("id=%s,path=%s ", (*iter).id.c_str(), (*iter).path.c_str());
		foreach (int id, (*iter).segments)
		{
			printf(" seg id=%d", id);
		}

		printf("\n");
		++iter;
	}
}

void TestViewManager()
{
	HwaPlatformConfigManager& platMgr = HwaPlatformConfigManager::getManager();
	platMgr.setFile("../config/framework-config.xml");
	HwaViewConfigManager& mgr = HwaViewConfigManager::getManager();
	std::vector<ItemInfor> items = mgr.getBindObjects("ArincSimulation", "CanDataViewer");
	foreach (ItemInfor item, items)
	{
		PrintItemInfor(item);
	}

	PrintItemInfor(mgr.getBindObject("ArincSimulation", "CanDataViewer", "label1"));
	PrintItemInfor(mgr.getBindObject("ArincSimulation", "CanDataViewer", "table1"));
}

void TestResourceManager()
{
	TestPlatformConfigManager();
	TestStringHelper();
	TestViewManager();
}