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

#include <QThread>
#include <QString>

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

	virtual void enqueue(const QString& infor);
	virtual void query(const QString& infor);

	//�����ϱ���Ϣ���ص�������ʵ��������
	virtual void processReportInfor(const QString& infor);

protected:
	virtual void run();

private:
	HwaViewBinder* _binder;
	DataStorage* _source;

	QList<QString> _queue;
};

#endif //__HWADATASTORAGE_H__