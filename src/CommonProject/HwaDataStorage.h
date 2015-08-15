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
#include <QQueue>
#include <QVector>

#include "commonproject_global.h"
#include "HwaDataSource.h"

class DataStorage;
class HwaViewBinder;

/**
*	\class HwaDataSource
*	\breif ��������������Դ���籾���ļ������ݷ���ˡ������.
*	Details
*/
class COMMONPROJECT_EXPORT HwaDataStorage: public HwaDataSource
{
public:
	HwaDataStorage(DataStorage* source);
	~HwaDataStorage();

	/**
	*    \fn    enqueue
	*    \brief �����Ϣ��Ч�ԣ����������.
	*    \param const QString & infor
	*    \returns void
	*/
	virtual void enqueue(const QJsonObject& infor);
	
	/**
	*    \fn    query
	*    \brief ������Ϣ��ѯ���ݣ������ݴ�������.
	*    \param const QString & infor
	*    \returns void
	*/
	virtual void query(const QJsonObject& infor);

	/**
	*    \fn    processReportInfor
	*    \brief �����ϱ���Ϣ���ص�������ʵ��������.
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