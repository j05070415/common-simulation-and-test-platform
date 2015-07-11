/**
*   \file HwaViewConfigManager.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��6��30��
*   ����    : Weijun Shi
*   �汾    : 1.0
*/
#ifndef __HwaVIEWCONFIGMANAGER_H__
#define __HwaVIEWCONFIGMANAGER_H__

#include "resourcemanager_global.h"
#include "typedefs.h"

class TiXmlElement;

/**
*	\class HwaViewConfigManager
*	\breif ��ͼ�����ļ������ṩ��ͼ�󶨿ؼ���Ϣ.
*/
class RESOURCEMANAGERSHARED_EXPORT HwaViewConfigManager
{
public:
	static HwaViewConfigManager& getManager();

	/**
	*    \fn    getBindObjects
	*    \brief ��ȡ��ͼ���а󶨿ؼ���Ϣ.
	
	*    \param const HwaString & projectName
	*    \param const HwaString & viewName
	*    \returns std::vector<ItemInfor>
	*/
	std::vector<ItemInfor> getBindObjects(const HwaString& projectName, 
									   const HwaString& viewName) const;
	
	/**
	*    \fn    getBindObject
	*    \brief ��ȡ��ͼĳһ�ؼ�����Ϣ.
	
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
	*    \brief ���ղ��ҵ��ĸ��ڵ㣬�������µĹ��̽ڵ�.
	
	*    \param TiXmlElement * root
	*    \param const HwaString & project
	*    \returns TiXmlElement*
	*/
	TiXmlElement* findProject(TiXmlElement* root, const HwaString& project) const;
	
	/**
	*    \fn    findView
	*    \brief ���ղ��ҵ��Ĺ��̽ڵ㣬�������µ���ͼ�ڵ�.
	
	*    \param TiXmlElement * project
	*    \param const HwaString & viewName
	*    \returns TiXmlElement*
	*/
	TiXmlElement* findView(TiXmlElement* project, const HwaString& viewName) const;
	
	/**
	*    \fn    findAll
	*    \brief ������ͼ�µ����а󶨿ؼ�.
	
	*    \param TiXmlElement * view
	*    \returns std::vector<ItemInfor>
	*/
	std::vector<ItemInfor> findAll(TiXmlElement* view) const;
	
	/**
	*    \fn    findItem
	*    \brief ���ն������ƣ�������ͼ�¿ؼ�.
	
	*    \param TiXmlElement * view
	*    \param const HwaString & objName
	*    \returns ItemInfor
	*/
	ItemInfor findItem(TiXmlElement* view, const HwaString& objName) const;
};

#endif //__HwaVIEWCONFIGMANAGER_H__
