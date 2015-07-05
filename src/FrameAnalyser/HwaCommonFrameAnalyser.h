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

#include "frameanalyser_global.h"
#include "HwaFrameAnalyser.h"

/**
*	\class HwaCommonFrameAnalyser
*	\breif 通用帧解析器，提供对一般数据进行解析实现.
*	Details
*/
class FRAMEANALYSERSHARED_EXPORT HwaCommonFrameAnalyser : public HwaFrameAnalyser
{
public:
	HwaCommonFrameAnalyser();
	~HwaCommonFrameAnalyser();

	virtual SmartBitsets analyse(const QVector<int>& segments);
	
private:
	Q_DISABLE_COPY(HwaCommonFrameAnalyser);

	void calculateOffset(FrameInfor& frameInfor, const uchar* data);
	inline uchar* readValue(const uchar* data, int offset, int& size);

private:
	bool _calculated;
};

#endif //__HWACOMMONFRAMEANALYSER_H__
