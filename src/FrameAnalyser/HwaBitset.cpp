
#include "HwaBitset.h"


HwaBitset::HwaBitset()
	: _data(NULL)
	, _size(0)
{
}

//bit size
HwaBitset::HwaBitset(uchar* data, int size)
	: _data(data)
	, _size(size)
{
}

HwaBitset::HwaBitset(const HwaBitset& bit)
	: _size(0)
	, _data(0)
{
	if (bit._size > 0)
	{
		_size = bit._size;
		_data = new uchar[(_size + 7)/8];
	}
}

HwaBitset::~HwaBitset()
{
	delete _data;
}

HwaBitset& HwaBitset::operator=(const HwaBitset& bit)
{
	if (this != &bit)
	{
		delete _data;

		_data = bit.cloneData();
		_size = bit._size;
	}

	return *this;
}

#if defined(USE_QT)
QString HwaBitset::toString() const
#else
std::string HwaBitset::toString() const
#endif
{
	int size = (_size + 7)/8;
	if (size == 0)
	{
		return "";
	}
	
#if defined(USE_QT)
	return QString::fromLatin1((char*)_data, size);
#else
	return std::string((char*)_data, size);
#endif
}

ulong HwaBitset::toULong() const
{
	if ((_size + 7)/8 > 4)
	{
		return 0;
	}

	ulong temp = 0;
	memcpy(&temp, _data, (_size + 7)/8);

	return temp;
}

ullong HwaBitset::toULLong() const
{
	if ((_size + 7)/8 > 8)
	{
		return 0;
	}

	ullong temp = 0;
	memcpy(&temp, _data, (_size + 7)/8);

	return temp;
}

double HwaBitset::toDouble() const
{
	int length = (_size + 7)/8;
	if (length > 8)
	{
		return 0;
	}
	
	ullong temp = 0;
	Q_ASSERT(sizeof temp == 8);
	memcpy(&temp, _data, length);

	//²¹Âë
	int flag = 1;
	if (temp >> (_size - 1) == 1)
	{
		temp = ~temp;
		temp &= (0xFFFFFFFFFFFFFFFF >> (64 - _size));

		++temp;
		flag = -1;
	}

	return 1.0 * flag * temp;
}

uchar* HwaBitset::cloneData() const
{
	int size = (_size + 7)/8;
	if (size <= 0)
	{
		return NULL;
	}

	uchar* buff = new uchar[size];
	memset(buff, 0, size);
	memcpy(buff, _data, size);

	return buff;
}

int HwaBitset::size() const
{
	return _size;
}

void HwaBitset::setData(uchar* data)
{
	_data = data;
}
