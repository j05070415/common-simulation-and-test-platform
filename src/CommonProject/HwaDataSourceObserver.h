/**
*   \file HwaDataSourceObserver.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��8��6��
*   ����    : Weijun Shi
*   �汾    : 1.0
*/
#ifndef __HWADATASOURCEOBSERVER_H__
#define __HWADATASOURCEOBSERVER_H__

#include <QThread>
#include <QJsonObject>
#include "commonproject_global.h"

class COMMONPROJECT_EXPORT HwaDataSourceObserver : public QThread
{
public:
	//��������Դ�ϱ���Ϣ��������Ч��Ϣ������
	virtual QVector<QJsonObject> processReportInfor(const QJsonObject& infor) = 0;
	virtual void notify(const QJsonObject& infor, uchar* data) = 0;
};

#endif //__HWADATASOURCEOBSERVER_H__
