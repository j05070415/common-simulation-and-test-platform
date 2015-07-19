/**
*   \file HwaViewBinder.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年7月6日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __HWAVIEWBINDER_H__
#define __HWAVIEWBINDER_H__

#include <QHash>
#include <QString>
#include <QThread>
#include <QVector>
#include <QVariant>
#include <QQueue>
#include <QWaitCondition>
#include <QMutex>

#include "commonproject_global.h"

class HwaProjectView;
class HwaDataSource;

/**
*	\class HwaViewBinder
*	\breif 视图绑定器，如与数据视图绑定、与统计视图绑定，
*			功能：通过遍历视图配置，将绑定信息显示到视图中.
*	Details
*/
class COMMONPROJECT_EXPORT HwaViewBinder : public QThread
{
	Q_OBJECT
public:
	HwaViewBinder();
	~HwaViewBinder();
	HwaViewBinder(const HwaViewBinder& binder);

	virtual QString name() const;
	void bind(HwaProjectView* view);
	
	/**
	*    \fn    reset
	*    \brief 解绑绑定器与已有视图信号连接.
	*    \returns void
	*/
	void reset();

	/**
	*    \fn    query
	*    \brief  命令格式为JSON字符串.
	*    \param QString & command
	*    \returns uchar*
	*/
	void query(QString& command);

	/**
	*    \fn    enqueue
	*    \brief 将数据查询信息添加到队列中.
	*    \param const QString & infors
	*    \returns void
	*/
	void enqueue(const QString& infor, uchar* data);
	
	/**
	*    \fn    processReportInfor
	*    \brief 处理服务端上报信息，将有效命令加入到查询队列中.
	*    \param const QString & infor
	*    \returns void
	*/
	virtual QVector<QString> processReportInfor(const QString& infor);

protected:
	virtual void run();

private:
	/**
	*    \fn    findView
	*    \brief 按照视图名称查找字符串.
	*    \param const QString & viewName
	*    \returns HwaProjectView*
	*/
	HwaProjectView* findView(const QString& viewName);

	void abort();
	void wakeOne();

protected:
	QVector<HwaProjectView*> _views;
	//TODO:将server数据变化信号与view 数据变化信号相连
	HwaDataSource* _source;

	static const int MAX_CACHE = 20;
	// card/path/row/count
	QQueue<QPair<QString, uchar*> > _cache;

	//线程中断，恢复
	QMutex _mutex;
	QWaitCondition _condition;
};

#endif //__HWAVIEWBINDER_H__
