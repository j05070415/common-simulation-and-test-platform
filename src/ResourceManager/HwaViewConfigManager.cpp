
#include "tinyxml.h"
#include "StringHelper.h"
#include "HwaPlatformConfigManager.h"

#include "HwaViewConfigManager.h"


HwaViewConfigManager& HwaViewConfigManager::getManager()
{
	static HwaViewConfigManager mgr;

	return mgr;
}

std::vector<ItemInfor> HwaViewConfigManager::getBindObjects(const HwaString& projectName, const HwaString& viewName) const
{
	HwaPlatformConfigManager& platformMgr = HwaPlatformConfigManager::getManager();
	HwaString viewConfigPath = platformMgr.getViewConfigPath();
	TiXmlDocument doc(viewConfigPath.c_str());
	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* projectNode = this->findProject(root, projectName);
		TiXmlElement* viewNode = this->findView(projectNode, viewName);

		return this->findAll(viewNode);
	}

	printf("error=%s\n", doc.ErrorDesc());
	return std::vector<ItemInfor>();
}

ItemInfor HwaViewConfigManager::getBindObject(const HwaString& projectName, const HwaString& viewName, const HwaString& objName) const
{
	ItemInfor infor;

	HwaPlatformConfigManager& platformMgr = HwaPlatformConfigManager::getManager();
	HwaString viewConfigPath = platformMgr.getViewConfigPath();
	TiXmlDocument doc(viewConfigPath.c_str());
	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* projectNode = this->findProject(root, projectName);
		TiXmlElement* viewNode = this->findView(projectNode, viewName);

		infor = this->findItem(viewNode, objName);
	}

	return infor;
}

HwaViewConfigManager::HwaViewConfigManager()
{

}

HwaViewConfigManager::~HwaViewConfigManager()
{

}

TiXmlElement* HwaViewConfigManager::findProject(TiXmlElement* root, const HwaString& project) const
{
	TiXmlElement* tempRoot = root;
	while (tempRoot != NULL)
	{
		std::string projName = tempRoot->Attribute("class");
		if (projName == project)
		{
			break;
		}

		tempRoot = tempRoot->NextSiblingElement();
	}

	return tempRoot;
}

TiXmlElement* HwaViewConfigManager::findView(TiXmlElement* project, const HwaString& viewName) const
{
	if (project == NULL)
	{
		return NULL;
	}

	TiXmlElement* projectChild = project->FirstChildElement();
	while (projectChild != NULL)
	{
		std::string parsedName = projectChild->Attribute("class");
		if (parsedName == viewName)
		{
			break;
		}

		projectChild = projectChild->NextSiblingElement();
	}

	return projectChild;
}

std::vector<ItemInfor> HwaViewConfigManager::findAll(TiXmlElement* view) const
{
	std::vector<ItemInfor> items;
	if (view == NULL)
	{
		return items;
	}

	TiXmlElement* viewChild = view->FirstChildElement();
	while (viewChild != NULL)
	{
		ItemInfor item;
		item.objName = viewChild->Attribute("objectName");

		TiXmlElement* itemChild = viewChild->FirstChildElement();
		while (itemChild != NULL)
		{
			SourceInfor source;
			source.id = itemChild->Attribute("ID");
			source.path = itemChild->Attribute("path");

			HwaString value = itemChild->GetText();
			source.segments = StringHelper::SplitInt(value, ';');
			item.sources.push_back(source);

			itemChild = itemChild->NextSiblingElement();
		}
		viewChild = viewChild->NextSiblingElement();

		items.push_back(item);
	}

	return items;
}

ItemInfor HwaViewConfigManager::findItem(TiXmlElement* view, const HwaString& objName) const
{
	ItemInfor item;
	if (view == NULL)
	{
		return item;
	}

	TiXmlElement* viewChild = view->FirstChildElement();
	while (viewChild != NULL)
	{
		std::string parsedObjName = viewChild->Attribute("objectName");
		if (objName != parsedObjName)
		{
			viewChild = viewChild->NextSiblingElement();
			continue;
		}

		item.objName = parsedObjName;
		TiXmlElement* itemChild = viewChild->FirstChildElement();
		while (itemChild != NULL)
		{
			SourceInfor source;
			source.id = itemChild->Attribute("ID");
			source.path = itemChild->Attribute("path");

			HwaString value = itemChild->GetText();
			source.segments = StringHelper::SplitInt(value, ';');
			item.sources.push_back(source);

			itemChild = itemChild->NextSiblingElement();
		}

		break;
	}

	return item;
}

std::vector<ViewInfor> HwaViewConfigManager::getViews(const HwaString& projectName) const
{
	std::vector<ViewInfor> views;
	HwaPlatformConfigManager& platformMgr = HwaPlatformConfigManager::getManager();
	HwaString viewConfigPath = platformMgr.getViewConfigPath();
	TiXmlDocument doc(viewConfigPath.c_str());
	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* projectNode = this->findProject(root, projectName);

		TiXmlElement* projectChild = projectNode->FirstChildElement();
		while (projectChild != NULL)
		{
			ViewInfor infor;
			infor.name = projectChild->Attribute("class");
			infor.binder = projectChild->Attribute("binder");

			views.push_back(infor);
		}
	}

	return views;
}
