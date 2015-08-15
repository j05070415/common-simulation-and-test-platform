/**
*   \file HwaProjectView.h
*   \brief N/A.
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��7��6��
*   ����    : Weijun Shi
*   �汾    : 1.0
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
*	\breif ��ͼ�࣬�ṩ����������ӿں���ͼ���潻���ӿ�.
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
	*    \brief ��������.
	*    \returns QT_NAMESPACE::QString
	*/
	virtual QString name() const;

	/**
	*    \fn    updateView
	*    \brief ��Ҫ������ͼʱ������ֱ�ӷ���changeValue�źŸ��½��棻
	*			�������߼��Ƚϸ���ʱ�����Իص��˽ӿڣ����ڲ�����.
	*    \returns void
	*/
	virtual void updateView(const QString& item, const QVariant& value);
	
	/**
	*    \fn    getItemsInfor
	*    \brief ��ȡ��ͼ�пؼ���Ϣ.
	*    \returns ItemsInfor
	*/
	ItemsInfor getItemsInfor() const;

	/**
	*    \fn    getItemInfor
	*    \brief ��ȡ��ͼ��ĳ���ؼ���Ϣ.
	*    \returns ItemInfor
	*/
	ItemInfor getItemInfor(const QString& objName) const;

	/**
	*    \fn    hasItem
	*    \brief һ������Ľӿڣ��ṩ�ؼ���ѯ.
	*    \returns bool
	*/
	bool hasItem(const QString& objName) const;

	void setBinder(HwaViewBinder* binder);
	
	/**
	*    \fn    setProjectName
	*    \brief ������ͼ�������̵����ƣ�ע�⣺Ӧ�������ù�����һ��;������ͼ�ؼ���Ϣ.
	*    \param const QString & name
	*    \returns void
	*/
	void setProjectName(const QString& name);



public slots:
	/**
	*    \fn    onAction
	*    \brief ��Ӧ���̴��¶���.
	*    \param const QString & action
	*    \param const QVariant & param
	*    \returns void
	*/
	virtual void onAction(const QString& action, const QVariant& param);

signals:
	/**
	*    \fn    command
	*    \brief �����̷��ͳ�����������������ʽΪjson.
	*    \param const QString & command
	*    \param const QVariant& param
	*    \returns void
	*/
	void command(QString, QVariant);
	
	/**
	*    \fn    changeValue
	*    \brief �����ؼ��������ݣ�����һΪjson����project��view��item.
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
