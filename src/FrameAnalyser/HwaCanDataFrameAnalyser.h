/**
*   \file HwaCanDataFrameAnalyser.h
*   \brief .
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��7��14��
*   ����    : Weijun Shi
*   �汾    : 1.0
*/
#ifndef __HWACANDATAFRAMEANALYSER_H__
#define __HWACANDATAFRAMEANALYSER_H__

#include "HwaCommonFrameAnalyser.h"

/**
*	\class HwaCanDataFrameAnalyser
*	\breif Can������֡����������Ҫ����DLC���ݶ�.
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
