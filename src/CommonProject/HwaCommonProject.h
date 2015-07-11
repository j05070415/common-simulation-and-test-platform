/**
*   \file HwaCommonProject.h
*   \brief N/A.
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��7��6��
*   ����    : Weijun Shi
*   �汾    : 1.0
*/
#ifndef __HWACOMMONPROJECT_H__
#define __HWACOMMONPROJECT_H__

#include <QObject>
#include <QString>
#include <QVector>

#include "HwaViewBinder.h"
#include "commonproject_global.h"

/**
*	\class HwaCommonProject
*	\breif ���������࣬�������̵ĸ���.
*	Details
*/
class COMMONPROJECT_EXPORT HwaCommonProject : public QObject
{
	Q_OBJECT
public:
	HwaCommonProject();
	~HwaCommonProject();

	virtual QString name();
	virtual bool newProject() = 0;
	virtual bool open(const QString& path) = 0;
	virtual bool save(const QString& path) = 0;
	virtual bool close() = 0;

	void setRoot(QObject* root);

	/**
	*    \fn    onAction
	*    \brief ��Ӧ���涯����ͨ�����ݸ�ʽΪjson.
	*    \param const QString & action
	*    \returns void
	*/
	virtual void onAction(const QString& action) = 0;

signals:
	/**
	*    \fn    command
	*    \brief �Խ��淢����������ʽΪjson.
	*    \param const QString & command
	*    \returns void
	*/
	void command(const QString&);

protected:
	QObject* _root;
};

#endif //__HWACOMMONPROJECT_H__
