
#include <stdio.h>

#include "tinyxml.h"
#include "HwaPlatformConfigManager.h"

struct HwaPlatformConfigManagerPrivate
{
	HwaString _file;
};

HwaPlatformConfigManager& HwaPlatformConfigManager::getManager()
{
	static HwaPlatformConfigManager mgr;

	return mgr;
}

HwaString HwaPlatformConfigManager::getViewConfigPath() const
{
	HwaString path;
	TiXmlDocument doc(_p->_file.c_str());
	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		if (root != NULL)
		{
			TiXmlElement* child = root->FirstChildElement();
			if (child != NULL)
			{
				do
				{
					std::string tag = child->Value();
					if (tag == "path" && HwaString(child->Attribute("name")) == "view")
					{
						path = child->Attribute("path");
						break;
					}

				} while (child = child->NextSiblingElement());
			}
		}
	}	

	return path;
}

HwaString HwaPlatformConfigManager::getProtocalConfigPath() const
{
	HwaString path;
	TiXmlDocument doc(_p->_file.c_str());
	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		if (root != NULL)
		{
			TiXmlElement* child = root->FirstChildElement();
			if (child != NULL)
			{
				do
				{
					std::string tag = child->Value();
					if (tag == "path" && HwaString(child->Attribute("name")) == "protocal")
					{
						path = child->Attribute("path");
						break;
					}

				} while (child = child->NextSiblingElement());
			}
		}
	}

	return path;
}

std::vector<ProjectInfor> HwaPlatformConfigManager::getProjectsInfor() const
{
	std::vector<ProjectInfor> projects;

	TiXmlDocument doc(_p->_file.c_str());
	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		if (root != NULL)
		{
			TiXmlElement* child = root->FirstChildElement();
			if (child != NULL)
			{
				ProjectInfor infor;
				do
				{
					std::string tag = child->Value();
					if (tag == "project")
					{
						infor.name = child->Attribute("name");
						infor.className = child->Attribute("class");
						infor.icon = child->Attribute("icon");
						infor.description = child->Attribute("desc");
						projects.push_back(infor);
					}

				} while (child = child->NextSiblingElement());
			}
		}
	}

	return projects;
}

std::vector<ProjectCardInfor> HwaPlatformConfigManager::getProjectCardInfors(const HwaString& name) const
{
	std::vector<ProjectCardInfor> cards;

	TiXmlDocument doc(_p->_file.c_str());
	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		if (root != NULL)
		{
			TiXmlElement* child = root->FirstChildElement();
			if (child != NULL)
			{
				ProjectInfor infor;
				do
				{
					std::string tag = child->Value();
					if (tag == "project" && HwaString(child->Attribute("class")) == name)
					{
						TiXmlElement* cardChild = child->FirstChildElement();
						if (cardChild != NULL)
						{
							ProjectCardInfor cardInfor;
							do 
							{
								cardInfor.name = cardChild->Attribute("name");
								cardInfor.frameId = cardChild->Attribute("ID");
								//printf("name=%s,id=%s\n", cardInfor.name.c_str(), cardInfor.frameId.c_str());
							} while (cardChild = cardChild->NextSiblingElement());
						}
					}

				} while (child = child->NextSiblingElement());
			}
		}
	}

	return cards;
}

HwaPlatformConfigManager::HwaPlatformConfigManager()
	: _p(new HwaPlatformConfigManagerPrivate)
{

}

HwaPlatformConfigManager::~HwaPlatformConfigManager()
{
	delete _p;
}

void HwaPlatformConfigManager::setFile( const HwaString& file )
{
	 _p->_file = file;
}

HwaString HwaPlatformConfigManager::getFile() const
{
	return _p->_file;
}

HwaString HwaPlatformConfigManager::getHomePageDescription() const
{
	TiXmlDocument doc(_p->_file.c_str());
	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		if (root != NULL)
		{
			return root->Attribute("information");
		}
	}

	return "";
}
