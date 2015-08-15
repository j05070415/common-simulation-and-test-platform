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

#include <QMutex>
#include <QQueue>
#include <QVector>

#include "commonproject_global.h"
#include "HwaDataSource.h"

class DataStorage;
class HwaViewBinder;

/**
*	\class HwaDataSource
*	\breif 负责出软件的数据源，如本地文件、数据服务端、网络等.
*	Details
*/
class COMMONPROJECT_EXPORT HwaDataStorage: public HwaDataSource
{
public:
	HwaDataStorage(DataStorage* source);
	~HwaDataStorage();

	/**
	*    \fn    enqueue
	*    \brief 检查信息有效性，并加入队列.
	*    \param const QString & infor
	*    \returns void
	*/
	virtual void enqueue(const QJsonObject& infor);
	
	/**
	*    \fn    query
	*    \brief 按照信息查询数据，将数据传给绑定器.
	*    \param const QString & infor
	*    \returns void
	*/
	virtual void query(const QJsonObject& infor);

	/**
	*    \fn    processReportInfor
	*    \brief 挑拣上报信息，回调负责处理实际挑拣处理.
	*    \param const QString & infor
	*    \returns void
	*/
	virtual void processReportInfor(const QJsonObject& infor);
	virtual void addObserver(HwaDataSourceObserver* observer);

protected:
	virtual void run();

private:
	bool checkInfor(const QJsonObject& infor);

private:
	QVector<HwaDataSourceObserver*> _observers;
	DataStorage* _source;
	bool _stoped;

	QQueue<QJsonObject> _queue;

	QMutex _mutex;
};

#endif //__HWADATASTORAGE_H__