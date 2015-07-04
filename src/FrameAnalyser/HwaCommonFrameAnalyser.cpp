
#include "HwaCommonFrameAnalyser.h"

SegmentInfor findSegment(const HwaSegments& segments, int id)
{
	HwaSegments::const_iterator iter = segments.begin();
	for (; iter != segments.end(); ++iter)
	{
		if (id == (*iter).id)
		{
			return *iter;
		}
	}

	return SegmentInfor();
}

HwaCommonFrameAnalyser::HwaCommonFrameAnalyser()
	: HwaFrameAnalyser()
{

}

HwaCommonFrameAnalyser::~HwaCommonFrameAnalyser()
{

}

SmartBitsets HwaCommonFrameAnalyser::analyse(const QVector<int>& segments)
{
	FrameInfor frameInfor = this->getFrameInfor();
	QSharedPointer<uchar> data = getData();
	if (_calculated && frameInfor.type == "rtti")
	{
		this->calculateOffset(frameInfor, data);
		_calculated = true;
	}

	SmartBitsets bitsets;
	foreach (int id, segments)
	{
		SegmentInfor& segmentInfor = findSegment(frameInfor.segments, id);
		Q_ASSERT(segmentInfor.size > 0 && segmentInfor.offset >= 0);
		int bytes = (segmentInfor.size + 7)/8;
		uchar* buffer = new uchar[bytes];
		memset(buffer, 0, bytes);
		memcpy(buffer, data.data() + segmentInfor.offset, bytes);
		uchar* cursor = buffer + bytes - 1;
		(*cursor) &= (0xFF >> (8 - segmentInfor.size%8));

		HwaBitset* bitset = new HwaBitset(buffer, segmentInfor.size);
		SmartBitset smartBitset(bitset);
		bitsets.push_back(smartBitset);
	}

	return bitsets;
}

void HwaCommonFrameAnalyser::calculateOffset(FrameInfor& frameInfor, const QSharedPointer<uchar>& data)
{
	HwaSegments::iterator iter = frameInfor.segments.begin();
	for (; iter != frameInfor.segments.end(); ++iter)
	{
		SegmentInfor& segment = *iter;
		if (segment.reference > 0 && !segment.previous)
		{

		}
	}
}
