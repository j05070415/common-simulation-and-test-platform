/**
*   \file HwaPlatformConfigManager.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��6��30��
*   ����    : Weijun Shi
*   �汾    : 1.0
*/
#ifndef __HwaPLATFORMCONFIGMANAGER_H__
#define __HwaPLATFORMCONFIGMANAGER_H__

#include "resourcemanager_global.h"
#include "typedefs.h"

struct HwaPlatformConfigManagerPrivate;

/**
*	\class HwaPlatformConfigManager
*	\breif ƽ̨�����ļ�����.
*	Details
*/
class RESOURCEMANAGERSHARED_EXPORT HwaPlatformConfigManager
{
public:
	static HwaPlatformConfigManager& getManager();

	
	/**
	*    \fn    getViewConfigPath
	*    \brief ��ȡ��ͼ�����ļ�·��.
	
	*    \returns HwaString
	*/
	HwaString getViewConfigPath() const;
	
	/**
	*    \fn    getProtocalConfigPath
	*    \brief ��ȡЭ�������ļ�·��.
	
	*    \returns HwaString
	*/
	HwaString getProtocalConfigPath() const;

	HwaString getHomePageDescription() const;
	
	/**
	*    \fn    getProjectsInfor
	*    \brief ��ȡ����������Ϣ.
	
	*    \returns std::vector<ProjectInfor>
	*/
	std::vector<ProjectInfor> getProjectsInfor() const;
	
	/**
	*    \fn    getProjectCardInfors
	*    \brief ��ȡ�������������а忨��Ϣ
	*			nameΪ��������.
	*    \param const HwaString & name
	*    \returns std::vector<ProjectCardInfor>
	*/
	std::vector<ProjectCardInfor> getProjectCardInfors(const HwaString& name) const;
	
	/**
	*    \fn    getFile
	*    \brief ��ȡ��������ļ�·��.
	
	*    \returns HwaString
	*/
	HwaString getFile() const;
	
	/**
	*    \fn    setFile
	*    \brief ���ÿ�������ļ�·��.
	
	*    \param const HwaString & file
	*    \returns void
	*/
	void setFile(const HwaString& file);

private:
	HwaPlatformConfigManager();
	~HwaPlatformConfigManager();
	HwaPlatformConfigManager(const HwaPlatformConfigManager& c);
	HwaPlatformConfigManager& operator=(const HwaPlatformConfigManager& c);

private:
	HwaPlatformConfigManagerPrivate* _p;
};

#endif //__HwaPLATFORMCONFIGMANAGER_H__
