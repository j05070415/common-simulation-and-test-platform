/**
*   \file HwaCanDataFrameAnalyser.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年7月14日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __HWACANDATAFRAMEANALYSER_H__
#define __HWACANDATAFRAMEANALYSER_H__

#include "HwaCommonFrameAnalyser.h"

/**
*	\class HwaCanDataFrameAnalyser
*	\breif Can的数据帧解析器，主要处理DLC数据段.
*	Details
*/
class HwaCanDataFrameAnalyser : public HwaCommonFrameAnalyser
{
public:
	HwaCanDataFrameAnalyser();
	virtual ~HwaCanDataFrameAnalyser();

protected:
	virtual void calculateOffset(FrameInfor& frameInfor, const uchar* data);
};

#endif //__HWACANDATAFRAMEANALYSER_H__
