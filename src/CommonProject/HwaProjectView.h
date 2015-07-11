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
	*    \fn    onItemChanged
	*    \brief 响应控件变化，可添加自己的处理然后通知绑定器;
	*			param既可以是视图中控件命令，也可是下传数据.
	*    \param const QString & objName
	*    \param const QVariant & param
	*    \returns void
	*/
	virtual void onItemChanged(const QString& objName, const QVariant& param);

signals:
	void changeValue(const QString&, const QVariant&);

protected:
	HwaViewBinder* _binder;

	QString _projectName;

private:
	ItemsInfor _items;
};

#endif //__HWAVIEW_H__
