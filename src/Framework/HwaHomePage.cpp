
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

	QObject* homePage = ui->findChild<QObject*>("homepage");
	connect(homePage, SIGNAL(action(const QString&, const QVariant&)), this, SLOT(onAction(const QString&, const QVariant&)));
	connect(this, SIGNAL(command(QVariant, QVariant)), homePage, SLOT(onCommand(QVariant, QVariant)));
	qDebug("connect ui to home page");
	qDebug("connect home page to ui");
	_homeRoot = ui;
}

void HwaHomePage::onAction(const QString& action, const QVariant& param)
{
	qDebug("HwaHomePage::onAction");
	QJsonParseError error;
	QJsonDocument json = QJsonDocument::fromJson(action.toLatin1(), &error);
	if (error.error == QJsonParseError::NoError)
	{
		QJsonObject jObj = json.object();
		if (jObj.contains("action"))
		{
			int action = jObj.value("action").toInt();
			HwaPlatformConfigManager& mgr = HwaPlatformConfigManager::getManager();
			switch (action)
			{
			case NEW_PROJECT:
				{
					this->closeProject(_project);

					QString projectName = jObj.value("projectName").toString();
					_project = this->createProject(projectName);

					if (_project && _homeRoot)
					{
						//大小为2不正常
						qDebug() << "-->size=" << _homeRoot->findChildren<QObject*>(projectName).size();
						QObject* qmlProject = _homeRoot->findChild<QObject*>(projectName);
						_project->setRoot(qmlProject);
						_project->newProject();
					}
				}
				break;
			case CLICK_NEW_PROJECT:
				std::vector<ProjectInfor> projIfnors = mgr.getProjectsInfor();
				foreach (const ProjectInfor& infor, projIfnors)
				{
					//action New clicked
					emit command(QString("{\"projectName\":\"%1\",\"objectName\":\"%2\",\"picture\":\"%3\",\"text\":\"%4\",\"action\":\"%5\"}")
						.arg(infor.className.c_str(), jObj.value("objectName").toString()
						, infor.icon.c_str(), infor.description.c_str(), QString::number(CLICK_NEW_PROJECT)), "");
				}
			}
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

	//安全考虑重命名
	QObject* qmlProject = _homeRoot->findChild<QObject*>(_project->name());
	qmlProject->setObjectName("__TEMP_TO_DESTROIED__");

	emit command("{\"action\":3}", "");

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
