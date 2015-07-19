/**
*   \file HwaViewBinder.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��7��6��
*   ����    : Weijun Shi
*   �汾    : 1.0
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
*	\breif ��ͼ����������������ͼ�󶨡���ͳ����ͼ�󶨣�
*			���ܣ�ͨ��������ͼ���ã�������Ϣ��ʾ����ͼ��.
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
	*    \brief ��������������ͼ�ź�����.
	*    \returns void
	*/
	void reset();

	/**
	*    \fn    query
	*    \brief  �����ʽΪJSON�ַ���.
	*    \param QString & command
	*    \returns uchar*
	*/
	void query(QString& command);

	/**
	*    \fn    enqueue
	*    \brief �����ݲ�ѯ��Ϣ��ӵ�������.
	*    \param const QString & infors
	*    \returns void
	*/
	void enqueue(const QString& infor, uchar* data);
	
	/**
	*    \fn    processReportInfor
	*    \brief ���������ϱ���Ϣ������Ч������뵽��ѯ������.
	*    \param const QString & infor
	*    \returns void
	*/
	virtual QVector<QString> processReportInfor(const QString& infor);

protected:
	virtual void run();

private:
	/**
	*    \fn    findView
	*    \brief ������ͼ���Ʋ����ַ���.
	*    \param const QString & viewName
	*    \returns HwaProjectView*
	*/
	HwaProjectView* findView(const QString& viewName);

	void abort();
	void wakeOne();

protected:
	QVector<HwaProjectView*> _views;
	//TODO:��server���ݱ仯�ź���view ���ݱ仯�ź�����
	HwaDataSource* _source;

	static const int MAX_CACHE = 20;
	// card/path/row/count
	QQueue<QPair<QString, uchar*> > _cache;

	//�߳��жϣ��ָ�
	QMutex _mutex;
	QWaitCondition _condition;
};

#endif //__HWAVIEWBINDER_H__
