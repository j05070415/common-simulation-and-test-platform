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

	virtual SmartBitsets analyse(const QVector<int>& segments);
	
private:
	Q_DISABLE_COPY(HwaCommonFrameAnalyser);

	void calculateOffset(FrameInfor& frameInfor, const QSharedPointer<uchar>& data);

private:
	bool _calculated;
};

#endif //__HWACOMMONFRAMEANALYSER_H__
