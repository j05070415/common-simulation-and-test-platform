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
*	\breif ���������������Դ���籾���ļ������ݷ���ˡ������.
*	Details
*/
class COMMONPROJECT_EXPORT HwaDataSource: public QThread
{
public:
	/**
	*    \fn    enqueue
	*    \brief ������ѯ������Ϣ�����.
	*    \param const QString & infor
	*    \returns void
	*/
	virtual void enqueue(const QString& infor) = 0;
	
	/**
	*    \fn    query
	*    \brief ִ�в�ѯ����,����ѯ���ݸ�����.
	*    \param const QString & infor
	*    \returns void
	*/
	virtual void query(const QString& infor) = 0;
	
	/**
	*    \fn    processReportInfor
	*    \brief Ԥ�����ϱ���Ϣ.
	*    \param const QString & infor
	*    \returns void
	*/
	virtual void processReportInfor(const QString& infor) = 0;
};

#endif //__HWADATASOURCE_H__