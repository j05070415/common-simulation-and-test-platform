/**
*   \file HwaHomePage.h
*   \brief N/A.
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年7月6日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __HWAHOMEPAGE_H__
#define __HWAHOMEPAGE_H__

#include <QString>
#include <QObject>

class HwaCommonProject;

/**
*	\class HwaHomePage
*	\breif 主页面，负责主页面与UI交互、创建管理工程;
*			通信格式为json字符串.
*	Details
*/
class HwaHomePage : public QObject
{
	Q_OBJECT
public:
	enum CommandType
	{
		PLATFORM = 1,
		PROJECT = 2,
		VIEW = 4,
		ITEM = 8
	};

	enum Command
	{
		NEW_PROJECT,
		OPEN_PROJECT,
		CLOSE_PROJECT,
		SAVE_PROJECT
	};

public:
	HwaHomePage();
	~HwaHomePage();

	void setUI(QObject* ui);

public slots:
	void onUICommand(const QString& command);

signals:
	void command(const QString&);

private:
	HwaCommonProject* createProject(const QString& name);
	void closeProject(HwaCommonProject* project);

private:
	HwaCommonProject* _project;
};

#endif //__HWAHOMEPAGE_H__
