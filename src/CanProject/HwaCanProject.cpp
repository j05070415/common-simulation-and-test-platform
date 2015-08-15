
#include <QMetaType>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

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

QString HwaCanProject::name() const
{
	return "HwaCanProject";
}

bool HwaCanProject::newProject()
{
	HwaViewConfigManager& mgr = HwaViewConfigManager::getManager();
	std::vector<ViewInfor> views = mgr.getViews(this->name().toStdString());
	foreach (ViewInfor infor, views)
	{
		HwaProjectView* view = (HwaProjectView*)QMetaType::create(QMetaType::type(infor.name.c_str()));
		HwaViewBinder* binder = (HwaViewBinder*)QMetaType::create(QMetaType::type(infor.binder.c_str()));
		if (view == NULL || binder == NULL)
		{
			delete view;
			delete binder;
			continue;
		}

		view->setProjectName(this->name());
		binder->start();
		QObject* viewItem = _root->findChild<QObject*>(view->name());
		if (viewItem != NULL)
		{
			connect(viewItem, SIGNAL(action(QString, QVariant)), 
				view, SLOT(onAction(QString, QVariant)));

			connect(view, SIGNAL(changeValue(QVariant, QVariant)), 
				viewItem, SLOT(onChangeValue(const QVariant&, const QVariant&)));
		}
		else
		{
			qDebug() << "Cannot find view, name is " << view->name() << "parent item:" << _root;
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
		disconnect(this, 0, 0, 0);

		delete view;
	}
	_views.clear();
}

void HwaCanProject::onAction(const QString& action, const QVariant& param)
{
	qDebug() << action;
	//响应工程界面动作

	//若对工程，工程处理
	//试图处理
	QJsonParseError error;
	QJsonDocument json = QJsonDocument::fromJson(action.toLatin1(), &error);
	if (error.error == QJsonParseError::NoError)
	{
		QJsonObject jObj = json.object();
		int type = jObj.value("type").toInt();
		//if (type == 2 && jObj.contains("viewName"))
		//{
		//	HwaProjectView* view = this->findView(jObj.value("viewName").toString());
		//	Q_ASSERT(view != NULL);
		//	view->onAction(jObj.value("viewName").toString(), param);
		//}
		switch (type)
		{
		default:
			break;
		}
		
	}
}

HwaProjectView* HwaCanProject::findView( const QString& name )
{
	HwaProjectView* viewHandle = NULL;
	foreach (HwaProjectView* view, _views)
	{
		if (view->name() == name)
		{
			viewHandle = view;
			break;
		}
	}

	return viewHandle;
}

HwaCanProject::HwaCanProject(const HwaCanProject& copy)
{
	_views = copy._views;
	_binders = copy._binders;
}
