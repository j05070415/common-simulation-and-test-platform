
#include "HwaBitset.h"


HwaBitset::HwaBitset()
	: _data(NULL)
	, _size(0)
{
	printf("HwaBitset()\n");
}

//bit size
HwaBitset::HwaBitset(uchar* data, int size)
	: _data(data)
	, _size(size)
{
	printf("HwaBitset(uchar*, int)\n");
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
	printf("HwaBitset(copy)\n");
}

HwaBitset::~HwaBitset()
{
	delete _data;
	printf("~HwaBitset()\n");
}

HwaBitset& HwaBitset::operator=(const HwaBitset& bit)
{
	printf("oprator=\n");
	if (this != &bit)
	{
		delete _data;

		_data = bit.cloneData();
		_size = bit._size;
	}

	return *this;
}

std::string HwaBitset::toStdString() const
{
	return "";
}

ulong HwaBitset::toULong() const
{
	return 0;
}

ullong HwaBitset::toULLong() const
{
	return 0;
}

double HwaBitset::toDouble() const
{
	return 0.0;
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
	printf("size=%d\n", _size);

	return buff;
}

int HwaBitset::size() const
{
	return _size;
}
