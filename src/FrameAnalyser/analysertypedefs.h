/**
*   \file typedefs.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��7��8��
*   ����    : Weijun Shi
*   �汾    : 1.0
*/
#ifndef __ANALYSERTYPEDEFS_H__
#define __ANALYSERTYPEDEFS_H__

#include <QSharedPointer>
#include <QList>

#include "typedefs.h"
#include "HwaBitset.h"

typedef QSharedPointer<HwaBitset> SmartBitset;
typedef QVector<SmartBitset > SmartBitsets;

#endif //__ANALYSERTYPEDEFS_H__
