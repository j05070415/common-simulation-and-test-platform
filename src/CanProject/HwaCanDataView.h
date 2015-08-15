/**
*   \file HwaCanDataView.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��7��7��
*   ����    : Weijun Shi
*   �汾    : 1.0
*/
#ifndef __HWACANDATAVIEW_H__
#define __HWACANDATAVIEW_H__

#include "canproject_global.h"
#include "HwaProjectView.h"

/**
*	\class HwaCanDataView
*	\breif Can��������ͼ.
*	Details
*/
class CANPROJECT_EXPORT HwaCanDataView : public HwaProjectView
{

public:
	HwaCanDataView();
	~HwaCanDataView();
	HwaCanDataView(const HwaCanDataView&);

	virtual QString name() const;
	virtual void onAction(const QString& action, const QVariant& param);
};

#endif //__HWACANDATAVIEW_H__
