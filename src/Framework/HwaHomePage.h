/**
*   \file HwaHomePage.h
*   \brief N/A.
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��7��6��
*   ����    : Weijun Shi
*   �汾    : 1.0
*/
#ifndef __HWAHOMEPAGE_H__
#define __HWAHOMEPAGE_H__

#include <QString>
#include <QObject>

class HwaCommonProject;

/**
*	\class HwaHomePage
*	\breif ��ҳ�棬������ҳ����UI����������������;
*			ͨ�Ÿ�ʽΪjson�ַ���.
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
