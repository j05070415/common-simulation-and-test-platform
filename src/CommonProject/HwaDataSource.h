/**
*   \file HwaDataSource.h
*   \brief N/A.
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��7��12��
*   ����    : Weijun Shi
*   �汾    : 1.0
*/
#ifndef __HWADATASOURCE_H__
#define __HWADATASOURCE_H__

#include <QThread>
#include <QString>

#include "commonproject_global.h"

/**
*	\class HwaDataSource
*	\breif ��������������Դ���籾���ļ������ݷ���ˡ������.
*	Details
*/
class COMMONPROJECT_EXPORT HwaDataSource: public QThread
{
public:
	//������ѯ������Ϣ�����
	virtual void enqueue(const QString& infor) = 0
	//ִ�в�ѯ����,ִ�лص��ϱ���Ч����
	virtual void query(const QString& infor) = 0;
	//Ԥ�����ϱ���Ϣ
	virtual void processReportInfor(const QString& infor) = 0;
};

#endif //__HWADATASOURCE_H__
