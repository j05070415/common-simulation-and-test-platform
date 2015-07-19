
#include "HwaCanDataFrameAnalyser.h"


HwaCanDataFrameAnalyser::HwaCanDataFrameAnalyser()
	: HwaCommonFrameAnalyser()
{

}

HwaCanDataFrameAnalyser::~HwaCanDataFrameAnalyser()
{

}

void HwaCanDataFrameAnalyser::calculateOffset(FrameInfor& frameInfor, const uchar* data)
{
	uint buffer = 0;
	HwaSegments::iterator iter = frameInfor.segments.begin();
	for (; iter != frameInfor.segments.end(); ++iter)
	{
		SegmentInfor& segment = *iter;
		if (segment.previous)
		{
			SegmentInfor& preSegment = *(iter - 1);
			segment.offset = preSegment.offset + preSegment.size;
		}
		else if (segment.reference > 0)
		{
			SegmentInfor& refSegment = this->findSegment(frameInfor.segments, segment.reference);
			buffer = 0;
			int size = refSegment.size;
			uchar* res = this->readValue(data, refSegment.offset, size);
			//size = qMin<int>(size, sizeof buffer);
			memcpy(&buffer, res, size);
			//delete[] res;
			//res = NULL;

			segment.offset = refSegment.offset + refSegment.size;
			segment.size = buffer * 8;
		}
	}
}
