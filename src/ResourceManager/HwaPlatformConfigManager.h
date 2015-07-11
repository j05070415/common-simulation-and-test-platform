/**
*   \file HwaPlatformConfigManager.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年6月30日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __HwaPLATFORMCONFIGMANAGER_H__
#define __HwaPLATFORMCONFIGMANAGER_H__

#include "resourcemanager_global.h"
#include "typedefs.h"

struct HwaPlatformConfigManagerPrivate;

/**
*	\class HwaPlatformConfigManager
*	\breif 平台配置文件管理.
*	Details
*/
class RESOURCEMANAGERSHARED_EXPORT HwaPlatformConfigManager
{
public:
	static HwaPlatformConfigManager& getManager();

	
	/**
	*    \fn    getViewConfigPath
	*    \brief 获取视图配置文件路径.
	
	*    \returns HwaString
	*/
	HwaString getViewConfigPath() const;
	
	/**
	*    \fn    getProtocalConfigPath
	*    \brief 获取协议配置文件路径.
	
	*    \returns HwaString
	*/
	HwaString getProtocalConfigPath() const;

	HwaString getHomePageDescription() const;
	
	/**
	*    \fn    getProjectsInfor
	*    \brief 获取索引工程信息.
	
	*    \returns std::vector<ProjectInfor>
	*/
	std::vector<ProjectInfor> getProjectsInfor() const;
	
	/**
	*    \fn    getProjectCardInfors
	*    \brief 获取工程下配置所有板卡信息
	*			name为工程类名.
	*    \param const HwaString & name
	*    \returns std::vector<ProjectCardInfor>
	*/
	std::vector<ProjectCardInfor> getProjectCardInfors(const HwaString& name) const;
	
	/**
	*    \fn    getFile
	*    \brief 获取框架配置文件路径.
	
	*    \returns HwaString
	*/
	HwaString getFile() const;
	
	/**
	*    \fn    setFile
	*    \brief 设置框架配置文件路径.
	
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
