
#include "HwaPropertyResponser.h"
#include "HwaCommonProject.h"

HwaCommonProject::HwaCommonProject()
	: _root(NULL)
{
	qRegisterMetaType<HwaPropertyResponser>("HwaPropertyResponser");
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
