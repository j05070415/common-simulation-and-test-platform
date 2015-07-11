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

#include <string>

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
class FRAMEANALYSERSHARED_EXPORT HwaBitset
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

	std::string toStdString() const;
	ulong toULong() const;
	ullong toULLong() const;
	double toDouble() const;

private:
	uchar* _data;
	int _size;//bit size
};

#endif //__HWABITSET_H__
