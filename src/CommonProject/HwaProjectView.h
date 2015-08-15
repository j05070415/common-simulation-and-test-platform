/**
*   \file HwaProjectView.h
*   \brief N/A.
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年7月6日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __HWAVIEW_H__
#define __HWAVIEW_H__

#include <QString>
#include <QVariant>

#include "typedefs.h"
#include "commonproject_global.h"

class HwaViewBinder;

/**
*	\class HwaProjectView
*	\breif 视图类，提供与绑定器交互接口和视图界面交互接口.
*	Details
*/
class COMMONPROJECT_EXPORT HwaProjectView : public QObject
{
	Q_OBJECT
public:
	enum ViewAction
	{
		NewItemData = 0,
		UiCompleted = 1
	};

public:
	HwaProjectView();
	~HwaProjectView();
	HwaProjectView(const HwaProjectView& view);
	
	/**
	*    \fn    name
	*    \brief 界面名称.
	*    \returns QT_NAMESPACE::QString
	*/
	virtual QString name() const;

	/**
	*    \fn    updateView
	*    \brief 当要更新视图时，可以直接发送changeValue信号更新界面；
	*			当界面逻辑比较复杂时，可以回调此接口，做内部处理.
	*    \returns void
	*/
	virtual void updateView(const QString& item, const QVariant& value);
	
	/**
	*    \fn    getItemsInfor
	*    \brief 获取视图中控件信息.
	*    \returns ItemsInfor
	*/
	ItemsInfor getItemsInfor() const;

	/**
	*    \fn    getItemInfor
	*    \brief 获取视图中某个控件信息.
	*    \returns ItemInfor
	*/
	ItemInfor getItemInfor(const QString& objName) const;

	/**
	*    \fn    hasItem
	*    \brief 一个方便的接口，提供控件查询.
	*    \returns bool
	*/
	bool hasItem(const QString& objName) const;

	void setBinder(HwaViewBinder* binder);
	
	/**
	*    \fn    setProjectName
	*    \brief 设置视图所属工程的名称，注意：应该与配置工程名一致;更新视图控件信息.
	*    \param const QString & name
	*    \returns void
	*/
	void setProjectName(const QString& name);



public slots:
	/**
	*    \fn    onAction
	*    \brief 响应工程传下动作.
	*    \param const QString & action
	*    \param const QVariant & param
	*    \returns void
	*/
	virtual void onAction(const QString& action, const QVariant& param);

signals:
	/**
	*    \fn    command
	*    \brief 给工程发送除数据其他命令，命令格式为json.
	*    \param const QString & command
	*    \param const QVariant& param
	*    \returns void
	*/
	void command(QString, QVariant);
	
	/**
	*    \fn    changeValue
	*    \brief 向界面控件发送数据，参数一为json，有project、view、item.
	*    \param const QVariant &
	*    \param const QVariant &
	*    \returns void
	*/
	void changeValue(QVariant, QVariant);

protected:
	HwaViewBinder* _binder;

	QString _projectName;

private:
	ItemsInfor _items;
};

#endif //__HWAVIEW_H__
