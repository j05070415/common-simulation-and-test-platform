/**
*   \file HwaDataSource.h
*   \brief N/A.
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��7��12��
*   ����    : Weijun Shi
*   �汾    : 1.0
*/
#ifndef __HWABINDERDATASOURCE_H__
#define __HWABINDERDATASOURCE_H__

#include <QMutex>
#include <QWaitCondition>
#include <QQueue>

#include "commonproject_global.h"
#include "HwaDataSource.h"

class DataStorage;
class HwaViewBinder;

/**
*	\class HwaDataSource
*	\breif ��������������Դ���籾���ļ������ݷ���ˡ������.
*	Details
*/
class COMMONPROJECT_EXPORT HwaBinderDataSource: public HwaDataSource
{
public:
	HwaBinderDataSource(HwaViewBinder* binder, DataStorage* source);
	~HwaBinderDataSource();

	/**
	*    \fn    enqueue
	*    \brief �����Ϣ��Ч�ԣ����������.
	*    \param const QString & infor
	*    \returns void
	*/
	virtual void enqueue(const QString& infor);
	
	/**
	*    \fn    query
	*    \brief ������Ϣ��ѯ���ݣ������ݴ�������.
	*    \param const QString & infor
	*    \returns void
	*/
	virtual void query(const QString& infor);

	/**
	*    \fn    processReportInfor
	*    \brief �����ϱ���Ϣ���ص�������ʵ��������.
	*    \param const QString & infor
	*    \returns void
	*/
	virtual void processReportInfor(const QString& infor);

	void abort();
	void wakeOne();
protected:
	virtual void run();

private:
	bool checkInfor(const QString& infor);

private:
	HwaViewBinder* _binder;
	DataStorage* _source;

	QQueue<QString> _queue;

	//�߳��жϣ��ָ�
	QMutex _mutex;
	QWaitCondition _condition;
};

#endif //__HWADATASTORAGE_H__