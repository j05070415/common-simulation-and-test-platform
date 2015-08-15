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
#include <QJsonObject>

#include "commonproject_global.h"

class HwaDataSourceObserver;
/**
*	\class HwaDataSource
*	\breif 负责接软件的数据源，如本地文件、数据服务端、网络等.
*	Details
*/
class COMMONPROJECT_EXPORT HwaDataSource: public QThread
{
public:
	/**
	*    \fn    enqueue
	*    \brief 主动查询，将信息入队列.
	*    \param const QString & infor
	*    \returns void
	*/
	virtual void enqueue(const QJsonObject& infor) = 0;
	
	/**
	*    \fn    query
	*    \brief 执行查询命令,将查询数据给绑定器.
	*    \param const QString & infor
	*    \returns void
	*/
	virtual void query(const QJsonObject& infor) = 0;
	
	/**
	*    \fn    processReportInfor
	*    \brief 预处理上报信息.
	*    \param const QString & infor
	*    \returns void
	*/
	virtual void processReportInfor(const QJsonObject& infor) = 0;

	virtual void addObserver(HwaDataSourceObserver* observer) = 0;
};

#endif //__HWADATASOURCE_H__
