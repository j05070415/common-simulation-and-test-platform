/**
*   \file HwaBitset.h
*   \brief N/A.
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��7��3��
*   ����    : Weijun Shi
*   �汾    : 1.0
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
*	\breif ���ฺ�����һ�ζ����ƣ������ṩת�����ַ�����
*			�޷������Ρ��޷��ų����κͶ��������ǵȻ������ܣ��ݲ��ṩд����.
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
