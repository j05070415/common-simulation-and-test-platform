// test.cpp : 定义控制台应用程序的入口点。
//
#include <stdio.h>
void TestResourceManager();

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

	TestBitSet();

	return 0;
}

