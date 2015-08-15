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
#include <QMutex>
#include <QSharedPointer>

#include "HwaDataSourceObserver.h"

class HwaProjectView;
class HwaDataSource;

/**
*	\class HwaViewBinder
*	\breif 视图绑定器，如与数据视图绑定、与统计视图绑定，
*			功能：通过遍历视图配置，将绑定信息显示到视图中；与特定数据源绑定，多个绑定器可以共享一个数据源.
*	Details
*/
class COMMONPROJECT_EXPORT HwaViewBinder : public HwaDataSourceObserver
{
	Q_OBJECT
public:
	HwaViewBinder();
	~HwaViewBinder();

	virtual QString name() const;
	HwaViewBinder(const HwaViewBinder& binder);
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
	void query(const QJsonObject& infor);
	
	/**
	*    \fn    processReportInfor
	*    \brief 处理服务端上报信息，将有效命令加入到查询队列中.
	*    \param const QString & infor
	*    \returns void
	*/
	virtual QVector<QJsonObject> processReportInfor(const QJsonObject& infor);

	virtual void notify(const QJsonObject& infor, uchar* data);

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

protected:
	QVector<HwaProjectView*> _views;
	//数据源
	QSharedPointer<HwaDataSource> _source;
	bool _stoped;

	static const int MAX_CACHE = 1000;
	// card/path/row/count
	QQueue<QPair<QJsonObject, QSharedPointer<uchar> > > _cache;

	QMutex _mutex;
};

#endif //__HWAVIEWBINDER_H__
