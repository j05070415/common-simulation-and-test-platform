
#include "HwaBitset.h"
#include <vector>

#include <QSharedPointer>
#include <QVector>

QVector<QSharedPointer<HwaBitset> > Overlay()
{
	QVector<QSharedPointer<HwaBitset> > qBits;
	for (int i=0; i<2; ++i)
	{
		qBits.push_back(QSharedPointer<HwaBitset>(new HwaBitset));
	}

	return qBits;
}
QVector<HwaBitset> Overlay1()
{
	QVector<HwaBitset> qBits;
	for (int i=0; i<2; ++i)
	{
		qBits.push_back(HwaBitset());
	}

	return qBits;
}
void TestBitSet()
{
	uchar* buff = new uchar[11];
	memset(buff, 0, 11);

	//HwaBitset bits(buff, 88);
	//HwaBitset bits1(new uchar[10], 80);
	//HwaBitset b2 = bits;
	//HwaBitset b3, b4;
	//b3 = bits;
	//b4 = b2;

	//bits1 = bits;

	//std::vector<HwaBitset> vBits;
	//for (int i=0; i<10; ++i)
	//{
	//	vBits.push_back(HwaBitset(new uchar[11+i], 88));
	//}
	//QVector<QSharedPointer<HwaBitset> > aa = Overlay();

	QVector<HwaBitset> aa1 = Overlay1();
	getchar();
}