/**
*   \file CanProject.h
*   \brief N/A.
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年7月6日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __CANPROJECT_H__
#define __CANPROJECT_H__

#include "HwaCommonProject.h"
#include "canproject_global.h"

#include <QVector>

class HwaViewBinder;
class HwaProjectView;

/**
*	\class CanProject
*	\breif Can工程类,负责工程的新建、打开、保存、关闭，提供工程名接口;
*			管理视图、绑定器.
*	Details
*/
class CANPROJECT_EXPORT HwaCanProject : public HwaCommonProject
{
	Q_OBJECT
public:
	HwaCanProject();
	~HwaCanProject();
	HwaCanProject(const HwaCanProject& copy);

	virtual QString name();
	virtual bool newProject();
	virtual bool open(const QString& path);
	virtual bool save(const QString& path);
	virtual bool close();
	virtual void onAction(const QString& action, const QVariant& param);

	HwaProjectView* findView(const QString& name);

private:
	void clear();

private:
	QVector<HwaProjectView*> _views;
	QVector<HwaViewBinder*> _binders;
};

#endif //__CANPROJECT_H__
