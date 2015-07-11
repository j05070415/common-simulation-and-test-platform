
#include "HwaFrameAnalyser.h"

HwaFrameAnalyser::HwaFrameAnalyser()
{

}

HwaFrameAnalyser::~HwaFrameAnalyser()
{
}

void HwaFrameAnalyser::setFrameInfor(const FrameInfor& frame)
{
	_frameInfor = frame;
}

FrameInfor HwaFrameAnalyser::getFrameInfor() const
{
	return _frameInfor;
}
