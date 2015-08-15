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
#include <QMutex>
#include <QSharedPointer>

#include "HwaDataSourceObserver.h"

class HwaProjectView;
class HwaDataSource;

/**
*	\class HwaViewBinder
*	\breif ��ͼ����������������ͼ�󶨡���ͳ����ͼ�󶨣�
*			���ܣ�ͨ��������ͼ���ã�������Ϣ��ʾ����ͼ�У����ض�����Դ�󶨣�����������Թ���һ������Դ.
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
	void query(const QJsonObject& infor);
	
	/**
	*    \fn    processReportInfor
	*    \brief ���������ϱ���Ϣ������Ч������뵽��ѯ������.
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
	*    \brief ������ͼ���Ʋ����ַ���.
	*    \param const QString & viewName
	*    \returns HwaProjectView*
	*/
	HwaProjectView* findView(const QString& viewName);

protected:
	QVector<HwaProjectView*> _views;
	//����Դ
	QSharedPointer<HwaDataSource> _source;
	bool _stoped;

	static const int MAX_CACHE = 1000;
	// card/path/row/count
	QQueue<QPair<QJsonObject, QSharedPointer<uchar> > > _cache;

	QMutex _mutex;
};

#endif //__HWAVIEWBINDER_H__
