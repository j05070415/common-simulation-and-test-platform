
#include "HwaCommonFrameAnalyser.h"

SegmentInfor HwaCommonFrameAnalyser::findSegment(const HwaSegments& segments, int id)
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

SmartBitsets HwaCommonFrameAnalyser::analyse(uchar* data, const QVector<int>& segments)
{
	FrameInfor frameInfor = this->getFrameInfor();

	if (frameInfor.type == "rtti")
	{
		//必须全部重新计算，反之，就不会计算中间中变长字段的大小和偏移
		this->calculateOffset(frameInfor, data);
	}

	SmartBitsets bitsets;
	foreach (int id, segments)
	{
		SegmentInfor& segmentInfor = findSegment(frameInfor.segments, id);
		Q_ASSERT(segmentInfor.size > 0 && segmentInfor.offset >= 0);

		int size = segmentInfor.size;
		uchar* buffer = this->readValue(data, segmentInfor.offset, size);
		HwaBitset* bitset = new HwaBitset(buffer, segmentInfor.size);
		SmartBitset smartBitset(bitset);
		bitsets.push_back(smartBitset);
	}

	return bitsets;
}

void HwaCommonFrameAnalyser::calculateOffset(FrameInfor& frameInfor, const uchar* data)
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
			SegmentInfor& refSegment = findSegment(frameInfor.segments, segment.reference);
			buffer = 0;
			int size = refSegment.size;
			uchar* res = this->readValue(data, refSegment.offset, size);
			memcpy(&buffer, res, size);

			segment.offset = refSegment.offset + refSegment.size + buffer;
		}
	}
}

uchar* HwaCommonFrameAnalyser::readValue(const uchar* data, int offset, int& size)
{
	uchar* buffer = NULL;
	int length = 0;
	//低位对齐
	if (offset % 8 == 0)
	{
		length = (size + 7)/8;
		buffer = new uchar[length];
		memcpy(buffer, data + offset/8, length);

		if (size % 8 != 0)
		{
			uchar* p = buffer + length - 1;
			*p &= (0xFF >> (8 - size%8));
		}
	}
	else
	{
		int leftOffset = offset%8;
		int left = 8 - leftOffset;
		int right = size - left;
		length = (left + 7) / 8 + (right + 7) / 8;

		buffer = new uchar[length];
		memcpy(buffer, data + offset/8, length);
		//高位截断,防止移位时杂项数据干扰
		if ((offset + size) % 8 != 0)
			*(buffer + length - 1) &= (0xFF >> (8 - (offset+size)%8));

		//按字节移位
		uchar* p = buffer;
		uchar* next = p;
		for (int i=0; i<length-1; ++i)
		{
			*p >>= leftOffset;

			++next;
			*p |= ((*next) << (8 - leftOffset));

			//下一字节
			++p;
		}

		//最后一字节数据操作
		*next >>= leftOffset;
	}

	size = length;
	return buffer;
}
