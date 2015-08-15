
#include "HwaCommonProject.h"

HwaCommonProject::HwaCommonProject()
	: _root(NULL)
{

}

HwaCommonProject::~HwaCommonProject()
{

}

QString HwaCommonProject::name() const
{
	return "HwaCommonProject";
}

void HwaCommonProject::setRoot(QObject* root)
{
	_root = root;
}
