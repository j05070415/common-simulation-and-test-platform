/**
*   \file HwaCommonFrameAnalyser.h
*   \brief N/A.
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��7��2��
*   ����    : Weijun Shi
*   �汾    : 1.0
*/
#ifndef __HWACOMMONFRAMEANALYSER_H__
#define __HWACOMMONFRAMEANALYSER_H__

#include "HwaFrameAnalyser.h"

/**
*	\class HwaCommonFrameAnalyser
*	\breif ͨ��֡���������ṩ��һ�����ݽ��н���ʵ��.
*	Details
*/
class HwaCommonFrameAnalyser : public HwaFrameAnalyser
{
public:
	HwaCommonFrameAnalyser();
	~HwaCommonFrameAnalyser();

	virtual SmartBitsets analyse(uchar* data, const QVector<int>& segments);
	
protected:
	virtual void calculateOffset(FrameInfor& frameInfor, const uchar* data);
	inline SegmentInfor findSegment(const HwaSegments& segments, int id);
	inline uchar* readValue(const uchar* data, int offset, int& size);
};

#endif //__HWACOMMONFRAMEANALYSER_H__
