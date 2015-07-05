// test.cpp : 定义控制台应用程序的入口点。
//
#include <stdio.h>
#include <string>
void TestResourceManager();
void TestAnalyser();

class Data
{
public:
	int i;
	~Data()
	{
		printf("~Data\n");
	}
};

struct GOO
{
	Data p;
};

typedef unsigned char uchar;
typedef unsigned int uint;

struct BitSt 
{
	uchar a : 1;
	uchar b : 1;
	uchar c : 1;
	uchar d : 1;
	uchar e : 1;
	uchar f : 1;
	uchar g : 1;
	uchar h : 1;
};

struct Can
{
	uint a: 1;
	uint b: 11;
	uint c: 2;
	uint d: 4;
	uint e: 7;
	uint f: 7;
};

void TestBitSet();

int main(int argc, char* argv[])
{
	//TestResourceManager();
	/*GOO g1;
	g1.p.i = 1;
	GOO g2;
	g2.p.i = 2;

	g1.p = g2.p;
	getchar();*/

	//TestBitSet();
	//printf("size of uchar =%d\n", sizeof(uchar));
	//uchar c = 0x2;
	//uchar c2 = 0;
	//BitSt* p = (BitSt*)(&c);
	//p->a = p->b;

	//printf("%d ", p->a);
	//printf("%d ", p->b);
	//printf("%d ", p->c);
	//printf("%d ", p->d);
	//printf("%d ", p->e);
	//printf("%d ", p->f);
	//printf("%d ", p->g);
	//printf("%d ", p->h);

	//printf("can sizeof=%d\n", sizeof(Can));
	////10 - 000 0110 0100 - 1
	//Can c;
	//memset(&c, 0, sizeof c);
	//c.a = 1;
	//c.b = 100;
	//c.c = 2;

	//uchar* p = (uchar*)(&c);
	//uchar buff[2] = {0};
	//memcpy(buff, p, sizeof buff);
	////uchar v1 = *p;
	//int aSize = 1;
	//int bSize = 11;
	//int unitSize = sizeof(uchar);
	//(*buff) >>= aSize;
	//p++;
	//(*buff) |= (*p) << (unitSize - aSize);
	////buff[0] = v1;

	//*(buff+1) = *p;
	//*(buff+1) &= (*p >> aSize) & (0xFF >> (unitSize - (bSize - unitSize)));
	////buff[1] = v1;

	//uint res = 0;
	//memcpy(&res, buff, sizeof buff);

	//printf("res=%u\n", res);


	TestAnalyser();
	return 0;
}

