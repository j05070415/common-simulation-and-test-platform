/**
*   \file HwaCommonProject.h
*   \brief N/A.
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年7月6日
*   作者    : Weijun Shi
*   版本    : 1.0
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
*	\breif 基本工程类，其他工程的父类.
*	Details
*/
class COMMONPROJECT_EXPORT HwaCommonProject : public QObject
{
	Q_OBJECT
public:
	enum ProjcetAction
	{
		UiCompleted = 0
	};
public:
	HwaCommonProject();
	~HwaCommonProject();

	virtual QString name() const;
	virtual bool newProject() = 0;
	virtual bool open(const QString& path) = 0;
	virtual bool save(const QString& path) = 0;
	virtual bool close() = 0;

	void setRoot(QObject* root);

	/**
	*    \fn    onAction
	*    \brief 响应界面动作，通信内容格式为json.
	*    \param const QString & action
	*    \returns void
	*/
	virtual void onAction(const QString& action, const QVariant& param) = 0;

signals:
	/**
	*    \fn    command
	*    \brief 对界面发送命令，命令格式为json.
	*    \param const QString & command
	*    \param const QVariant& param
	*    \returns void
	*/
	void command(QString, QVariant);

protected:
	QObject* _root;
};

#endif //__HWACOMMONPROJECT_H__
