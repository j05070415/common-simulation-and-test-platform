/**
*   \file HwaDataSource.h
*   \brief N/A.
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年7月12日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __HWABINDERDATASOURCE_H__
#define __HWABINDERDATASOURCE_H__

#include <QThread>
#include <QString>

#include "commonproject_global.h"
#include "HwaDataSource.h"

class DataStorage;
class HwaViewBinder;

/**
*	\class HwaDataSource
*	\breif 负责出软件的数据源，如本地文件、数据服务端、网络等.
*	Details
*/
class COMMONPROJECT_EXPORT HwaBinderDataSource: public HwaDataSource
{
public:
	HwaBinderDataSource(HwaViewBinder* binder, DataStorage* source);
	~HwaBinderDataSource();

	virtual void enqueue(const QString& infor);
	virtual void query(const QString& infor);

	//挑拣上报信息，回调负责处理实际挑拣处理
	virtual void processReportInfor(const QString& infor);

protected:
	virtual void run();

private:
	HwaViewBinder* _binder;
	DataStorage* _source;

	QList<QString> _queue;
};

#endif //__HWADATASTORAGE_H__