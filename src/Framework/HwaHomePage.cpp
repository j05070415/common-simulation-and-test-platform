
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaType>
#include <QString>

#include "HwaCommonProject.h"

#include "HwaHomePage.h"


HwaHomePage::HwaHomePage()
	: QObject()
	, _project(NULL)
{

}

HwaHomePage::~HwaHomePage()
{
	this->closeProject(_project);
}

void HwaHomePage::setUI(QObject* ui)
{
	connect(ui, SIGNAL(action(const QString&)), this, SLOT(onUICommand(const QString&)));
	connect(this, SIGNAL(command(const QString&)), ui, SLOT(onCommand(const QString&)));
}

void HwaHomePage::onUICommand(const QString& command)
{
	QJsonParseError error;
	QJsonDocument json = QJsonDocument::fromJson(command.toLatin1(), &error);
	if (error.error == QJsonParseError::NoError)
	{
		QJsonObject jObj = json.object();
		int type = jObj.value("type").toInt();
		if (type == PLATFORM && jObj.contains("command") && jObj.contains("projectName"))
		{
			int comm = jObj.value("command").toInt();
			QString projectName = jObj.value("projectNmae").toString();
			switch (comm)
			{
			case NEW_PROJECT:
				{
					this->closeProject(_project);

					_project = this->createProject(projectName);
					connect(_project, SIGNAL(command(const QString&)), this, SIGNAL(command(const QString&)));
					_project->newProject();
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
			_project->onAction(command);
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

	_project->close();
	delete _project;
	_project = NULL;
}
