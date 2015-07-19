/**
*   \file HwaCommonFrameAnalyser.h
*   \brief N/A.
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年7月2日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __HWACOMMONFRAMEANALYSER_H__
#define __HWACOMMONFRAMEANALYSER_H__

#include "HwaFrameAnalyser.h"

/**
*	\class HwaCommonFrameAnalyser
*	\breif 通用帧解析器，提供对一般数据进行解析实现.
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
