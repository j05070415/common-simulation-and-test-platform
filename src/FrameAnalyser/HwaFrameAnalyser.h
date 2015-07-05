/**
*   \file HwaFrameAnalyser.h
*   \brief N/A.
*   Copyright (C), 2015-2016, All rights reserved.
*   创建日期: 2015年6月30日
*   作者    : Weijun Shi
*   版本    : 1.0
*/
#ifndef __HWAFRAMEANALYSER_H__
#define __HWAFRAMEANALYSER_H__

#include "frameanalyser_global.h"
#include "HwaAnalyserBase.h"

struct HwaFrameAnalyserPrivate;

/**
*	\class HwaFrameAnalyser
*	\breif 接口实现，analyse为空实现，需自行继承实现.
*	Details
*/
class FRAMEANALYSERSHARED_EXPORT HwaFrameAnalyser : public HwaAnalyserBase
{
public:
	HwaFrameAnalyser();
	virtual ~HwaFrameAnalyser();

	void setData(uchar* data);
	void setFrameInfor(const FrameInfor& frame);

protected:
	uchar* getData() const;
	FrameInfor getFrameInfor() const;

private:
	H_DECLARE_PRIVATE(HwaFrameAnalyser);
	Q_DISABLE_COPY(HwaFrameAnalyser);

private:
	HwaFrameAnalyserPrivate* _p;	
};

#endif //__FRAMEANALYSER_H__
