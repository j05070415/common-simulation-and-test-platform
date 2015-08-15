/**
*   \file HwaDataSourceObserver.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年8月6日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __HWADATASOURCEOBSERVER_H__
#define __HWADATASOURCEOBSERVER_H__

#include <QThread>
#include <QJsonObject>
#include "commonproject_global.h"

class COMMONPROJECT_EXPORT HwaDataSourceObserver : public QThread
{
public:
	//处理数据源上报信息，过滤有效信息并返回
	virtual QVector<QJsonObject> processReportInfor(const QJsonObject& infor) = 0;
	virtual void notify(const QJsonObject& infor, uchar* data) = 0;
};

#endif //__HWADATASOURCEOBSERVER_H__
