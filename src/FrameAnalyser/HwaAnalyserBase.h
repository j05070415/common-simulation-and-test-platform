/**
*   \file HwaAnalyserBase.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��7��2��
*   ����    : Weijun Shi
*   �汾    : 1.0
*/
#ifndef __HWAANALYSERBASE_H__
#define __HWAANALYSERBASE_H__

#include <QVector>
#include <QSharedPointer>

#include "HwaBitset.h"
#include "typedefs.h"
#include "frameanalyser_global.h"

typedef QSharedPointer<HwaBitset> SmartBitset;
typedef QVector<SmartBitset > SmartBitsets;

class FRAMEANALYSERSHARED_EXPORT HwaAnalyserBase
{
public:
	virtual SmartBitsets analyse(const QVector<int>& segments) = 0;
};

#endif //__HWAANALYSERBASE_H__
