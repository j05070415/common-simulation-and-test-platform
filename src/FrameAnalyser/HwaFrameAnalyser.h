/**
*   \file HwaFrameAnalyser.h
*   \brief N/A.
*   Copyright (C), 2015-2016, All rights reserved.
*   ��������: 2015��6��30��
*   ����    : Weijun Shi
*   �汾    : 1.0
*/
#ifndef __HWAFRAMEANALYSER_H__
#define __HWAFRAMEANALYSER_H__

#include "typedefs.h"

#include "HwaAnalyserBase.h"

/**
*	\class HwaFrameAnalyser
*	\breif �ӿ�ʵ�֣�analyseΪ��ʵ�֣������м̳�ʵ��.
*	Details
*/
class HwaFrameAnalyser : public HwaAnalyserBase
{
public:
	HwaFrameAnalyser();
	virtual ~HwaFrameAnalyser();

	void setFrameInfor(const FrameInfor& frame);

protected:
	FrameInfor getFrameInfor() const;

private:
	FrameInfor _frameInfor;
};

#endif //__FRAMEANALYSER_H__
