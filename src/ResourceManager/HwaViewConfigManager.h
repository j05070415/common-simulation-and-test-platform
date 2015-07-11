/**
*   \file HwaViewConfigManager.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年6月30日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __HwaVIEWCONFIGMANAGER_H__
#define __HwaVIEWCONFIGMANAGER_H__

#include "resourcemanager_global.h"
#include "typedefs.h"

class TiXmlElement;

/**
*	\class HwaViewConfigManager
*	\breif 视图配置文件管理，提供视图绑定控件信息.
*/
class RESOURCEMANAGERSHARED_EXPORT HwaViewConfigManager
{
public:
	static HwaViewConfigManager& getManager();

	/**
	*    \fn    getBindObjects
	*    \brief 获取视图所有绑定控件信息.
	
	*    \param const HwaString & projectName
	*    \param const HwaString & viewName
	*    \returns std::vector<ItemInfor>
	*/
	std::vector<ItemInfor> getBindObjects(const HwaString& projectName, 
									   const HwaString& viewName) const;
	
	/**
	*    \fn    getBindObject
	*    \brief 获取视图某一控件绑定信息.
	
	*    \param const HwaString & projectName
	*    \param const HwaString & viewName
	*    \param const HwaString & objName
	*    \returns ItemInfor
	*/
	ItemInfor getBindObject(const HwaString& projectName, 
						   const HwaString& viewName, 
						   const HwaString& objName) const;

	std::vector<ViewInfor> getViews(const HwaString& projectName) const;

private:
	HwaViewConfigManager();
	~HwaViewConfigManager();
	HwaViewConfigManager(const HwaViewConfigManager& c);
	HwaViewConfigManager& operator=(const HwaViewConfigManager& c);

	
	/**
	*    \fn    findProject
	*    \brief 按照查找到的根节点，索引其下的工程节点.
	
	*    \param TiXmlElement * root
	*    \param const HwaString & project
	*    \returns TiXmlElement*
	*/
	TiXmlElement* findProject(TiXmlElement* root, const HwaString& project) const;
	
	/**
	*    \fn    findView
	*    \brief 按照查找到的工程节点，索引其下的视图节点.
	
	*    \param TiXmlElement * project
	*    \param const HwaString & viewName
	*    \returns TiXmlElement*
	*/
	TiXmlElement* findView(TiXmlElement* project, const HwaString& viewName) const;
	
	/**
	*    \fn    findAll
	*    \brief 查找视图下的所有绑定控件.
	
	*    \param TiXmlElement * view
	*    \returns std::vector<ItemInfor>
	*/
	std::vector<ItemInfor> findAll(TiXmlElement* view) const;
	
	/**
	*    \fn    findItem
	*    \brief 按照对象名称，查找视图下控件.
	
	*    \param TiXmlElement * view
	*    \param const HwaString & objName
	*    \returns ItemInfor
	*/
	ItemInfor findItem(TiXmlElement* view, const HwaString& objName) const;
};

#endif //__HwaVIEWCONFIGMANAGER_H__
