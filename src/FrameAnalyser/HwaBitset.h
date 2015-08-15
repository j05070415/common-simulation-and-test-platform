/**
*   \file HwaBitset.h
*   \brief N/A.
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年7月3日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __HWABITSET_H__
#define __HWABITSET_H__

#if defined(USE_QT)
#include <QObject>
#include <QString>
#else
#include <string>
#endif

#include "frameanalyser_global.h"

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;
typedef unsigned long long ullong;

/**
*	\class HwaBitset
*	\breif 此类负责管理一段二进制，对外提供转换成字符串、
*			无符号整形、无符号长整形和对数据与或非等基本功能，暂不提供写功能.
*	Details
*/
#if defined(USE_QT)
class FRAMEANALYSERSHARED_EXPORT HwaBitset : public QObject
#else
class FRAMEANALYSERSHARED_EXPORT HwaBitset
#endif
{
public:
	HwaBitset();
	HwaBitset(uchar* data, int size);
	~HwaBitset();

	HwaBitset(const HwaBitset& bit);
	HwaBitset& operator=(const HwaBitset& bit);

	void setData(uchar* data);

	uchar* cloneData() const;
	int size() const;

#if defined(USE_QT)
	Q_INVOKABLE QString toString() const;

	Q_INVOKABLE ulong toULong() const;
	Q_INVOKABLE ullong toULLong() const;
	Q_INVOKABLE double toDouble() const;
#else
	std::string toString() const;

	ulong toULong() const;
	ullong toULLong() const;
	double toDouble() const;
#endif

private:
	uchar* _data;
	int _size;//bit size
};

#endif //__HWABITSET_H__
