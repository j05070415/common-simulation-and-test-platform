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
#include <QVariant>
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
	enum Command
	{
		NEW_PROJECT = 1,
		OPEN_PROJECT = 2,
		CLOSE_PROJECT = 3,
		SAVE_PROJECT = 4,
		CLICK_NEW_PROJECT = 5,
		CLICK_OPEN_PROJECT = 6,
		CLICK_SAVE_PROJECT = 7,
		CLICK_CLOSE_PROJECT = 8
	};

public:
	HwaHomePage();
	~HwaHomePage();

	void setUI(QObject* ui);

public slots:
	void onAction(const QString& command, const QVariant& param);

signals:
	void command(QVariant, QVariant);

private:
	HwaCommonProject* createProject(const QString& name);
	void closeProject(HwaCommonProject* project);

private:
	HwaCommonProject* _project;
	QObject* _homeRoot;
};

class HomeUI : public QObject
{
	Q_OBJECT
signals:
	/**
	*    \fn    query
	*    \brief 与View通信.
	*    \param const QString &
	*    \param const QVariant &
	*    \returns void
	*/
	void query(const QString&, const QVariant&);
	
	/**
	*    \fn    action
	*    \brief 连接对象HomePage.
	*    \param const QString &
	*    \param const QVariant &
	*    \returns void
	*/
	void action(const QString&, const QVariant&);

public slots:
	/**
	*    \fn    onChangeValue
	*    \brief 响应View数据更新.
	*    \param const QString & infor
	*    \param const QVariant & param
	*    \returns void
	*/
	void onChangeValue(const QString& infor, const QVariant& param);
	
	/**
	*    \fn    onCommand
	*    \brief 响应HomePage命令.
	*    \param const QString & command
	*    \param const QVariant & param
	*    \returns void
	*/
	void onCommand(const QString& command, const QVariant& param);
};

#endif //__HWAHOMEPAGE_H__
