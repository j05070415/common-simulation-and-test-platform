
#include <QMetaType>

#include "HwaViewConfigManager.h"
#include "HwaViewBinder.h"
#include "HwaCanDataView.h"

#include "HwaCanProject.h"

HwaCanProject::HwaCanProject()
	: HwaCommonProject()
{
	REGISTER_META_TYPE(HwaCanDataView);
	REGISTER_META_TYPE(HwaViewBinder);
}

HwaCanProject::~HwaCanProject()
{
	this->clear();
}

QString HwaCanProject::name()
{
	return "HwaCanProject";
}

bool HwaCanProject::newProject()
{
	HwaViewConfigManager& mgr = HwaViewConfigManager::getManager();
	std::vector<ViewInfor> views = mgr.getViews(this->name().toStdString());
	foreach (ViewInfor infor, views)
	{
		HwaProjectView* view = (HwaProjectView*)(QMetaType::type(QString(infor.name.c_str()).toLatin1()));
		HwaViewBinder* binder = (HwaViewBinder*)(QMetaType::type(QString(infor.binder.c_str()).toLatin1()));
		if (view == NULL || binder == NULL)
		{
			delete view;
			delete binder;
			continue;
		}
		
		if (_root != NULL)
		{
			QObject* viewItem = _root->findChild<QObject*>(view->name());
			if (viewItem != NULL)
			{
				//与view直接交换数据
				connect(view, SIGNAL(changeValue(const QString&, const QVariant&)), 
					viewItem, SLOT(onChangeValue(const QString&, const QVariant&)));
				connect(viewItem, SIGNAL(valueChanged(const QString&, const QVariant&)),
					view, SLOT(onItemChanged(const QString&, const QVariant&)));
			}
		}
		
		_views.push_back(view);
		_binders.push_back(binder);

		binder->bind(view);
	}

	return true;
}

bool HwaCanProject::open(const QString& path)
{
	return true;
}

bool HwaCanProject::save(const QString& path)
{
	return true;
}

bool HwaCanProject::close()
{
	this->clear();

	return true;
}

void HwaCanProject::clear()
{
	foreach (HwaViewBinder* binder, _binders)
	{
		binder->reset();

		delete binder;
	}
	_binders.clear();

	foreach (HwaProjectView* view, _views)
	{
		QObject* viewItem = _root->findChild<QObject*>(view->name());
		if (viewItem != NULL)
		{
			disconnect(view, SIGNAL(changeValue(const QString&, const QVariant&)), 
				viewItem, SLOT(onChangeValue(const QString&, const QVariant&)));
			disconnect(viewItem, SIGNAL(valueChanged(const QString&, const QVariant&)),
				view, SLOT(onItemChanged(const QString&, const QVariant&)));
		}

		delete view;
	}
	_views.clear();
}

void HwaCanProject::onAction(const QString& action)
{
	//响应工程界面动作
}
