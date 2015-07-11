
#include "HwaCommonProject.h"

HwaCommonProject::HwaCommonProject()
	: _root(NULL)
{

}

HwaCommonProject::~HwaCommonProject()
{

}

QString HwaCommonProject::name()
{
	return "HwaCommonProject";
}

void HwaCommonProject::setRoot(QObject* root)
{
	_root = root;
}
