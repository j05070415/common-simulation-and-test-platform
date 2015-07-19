
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaType>
#include <QString>
#include <QDebug>


#include "HwaCommonProject.h"
#include "HwaPlatformConfigManager.h"
#include "HwaCanProject.h"

#include "HwaHomePage.h"


HwaHomePage::HwaHomePage()
	: QObject()
	, _project(NULL)
	, _homeRoot(NULL)
{
	REGISTER_META_TYPE(HwaCanProject);

	HwaPlatformConfigManager& mgr = HwaPlatformConfigManager::getManager();
	mgr.setFile("../config/framework-config.xml");
}

HwaHomePage::~HwaHomePage()
{
	this->closeProject(_project);
}

void HwaHomePage::setUI(QObject* ui)
{
	if (ui == NULL)
	{
		qDebug("ui is NULL");
		return;
	}
	connect(ui, SIGNAL(action(const QString&, const QVariant&)), this, SLOT(onAction(const QString& command, const QVariant& param)));
	connect(this, SIGNAL(command(const QString&, const QVariant&)), ui, SLOT(onCommand(const QString& command, const QVariant& param)));
	qDebug("connect ui to home page");
	qDebug("connect home page to ui");
	_homeRoot = ui;
}

void HwaHomePage::onAction(const QString& command, const QVariant& param)
{
	QJsonParseError error;
	QJsonDocument json = QJsonDocument::fromJson(command.toLatin1(), &error);
	if (error.error == QJsonParseError::NoError)
	{
		QJsonObject jObj = json.object();
		int type = jObj.value("type").toInt();
		if (type == PLATFORM && jObj.contains("command") && jObj.contains("project"))
		{
			int comm = jObj.value("command").toInt();
			QString projectName = jObj.value("project").toString();
			switch (comm)
			{
			case NEW_PROJECT:
				{
					this->closeProject(_project);

					_project = this->createProject(projectName);

					if (_project && _homeRoot)
					{
						QObject* projectNode = _homeRoot->findChild<QObject*>(projectName);
						_project->setRoot(projectNode);
						connect(_project, SIGNAL(command(const QString&)), this, SIGNAL(command(const QString&)));
						qDebug("connect projet to home page");
						_project->newProject();
					}
				}
				break;
			case OPEN_PROJECT:
				{
					if (_project != NULL)
					{
						_project->open(jObj.value("path").toString());
					}
				}
				break;
			case SAVE_PROJECT:
				if (_project != NULL)
				{
					_project->open(jObj.value("path").toString());
				}
				break;
			case CLOSE_PROJECT:
				this->closeProject(_project);
				break;
			}
		}
		else if (_project != NULL)
		{
			_project->onAction(command, param);
		}
	}
}

HwaCommonProject* HwaHomePage::createProject(const QString& name)
{
	int projType = QMetaType::type(name.toLatin1());

	return (HwaCommonProject*)(QMetaType::create(projType));
}

void HwaHomePage::closeProject(HwaCommonProject* project)
{
	if (_project == NULL)
	{
		return;
	}

	disconnect(project, SIGNAL(command(const QString&)), this, 0);
	qDebug("disconnect projet to home page");

	_project->close();
	delete _project;
	_project = NULL;
}

void HomeUI::onChangeValue(const QString& infor, const QVariant& param)
{
	qDebug("view::updateView()");
	qDebug() << infor;
}

void HomeUI::onCommand(const QString& command, const QVariant& param)
{
	qDebug("UI HomePage command");
	qDebug() << command;
}
