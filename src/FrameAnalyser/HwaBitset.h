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
*	\breif ���ฺ�����һ�ζ����ƣ������ṩת�����ַ�����
*			�޷������Ρ��޷��ų����κͶ��������ǵȻ������ܣ��ݲ��ṩд����.
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
