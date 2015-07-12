/**
*   \file HwaDataSource.h
*   \brief N/A.
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年7月12日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __HWADATASOURCE_H__
#define __HWADATASOURCE_H__

#include <QThread>
#include <QString>

#include "commonproject_global.h"

/**
*	\class HwaDataSource
*	\breif 负责出软件的数据源，如本地文件、数据服务端、网络等.
*	Details
*/
class COMMONPROJECT_EXPORT HwaDataSource: public QThread
{
public:
	//主动查询，将信息入队列
	virtual void enqueue(const QString& infor) = 0
	//执行查询命令,执行回调上报有效数据
	virtual void query(const QString& infor) = 0;
	//预处理上报信息
	virtual void processReportInfor(const QString& infor) = 0;
};

#endif //__HWADATASOURCE_H__
