
#include "HwaFrameAnalyser.h"

struct HwaFrameAnalyserPrivate
{
	QSharedPointer<uchar> _data;
	FrameInfor _frameInfor;
};

HwaFrameAnalyser::HwaFrameAnalyser()
	: _p(new HwaFrameAnalyserPrivate)
{

}

HwaFrameAnalyser::~HwaFrameAnalyser()
{
	delete _p;
}

void HwaFrameAnalyser::setData(uchar* data)
{
	H_D(HwaFrameAnalyser);

	d->_data.reset(data);
}

void HwaFrameAnalyser::setFrameInfor(const FrameInfor& frame)
{
	H_D(HwaFrameAnalyser);

	d->_frameInfor = frame;
}

QSharedPointer<uchar> HwaFrameAnalyser::getData() const
{
	return _p->_data;
}

FrameInfor HwaFrameAnalyser::getFrameInfor() const
{
	return _p->_frameInfor;
}
