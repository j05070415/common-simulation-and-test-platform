#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QDebug>

#include "TreeModel.h"
#include "HwaHomePage.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

	qmlRegisterType<HwaTreeModel>("Hwa.TreeModel", 1, 0, "HwaTreeModel");
    QQmlApplicationEngine engine("main.qml");
    QList<QObject*> objects = engine.rootObjects();
    if (objects.size() > 0)
    {
        QObject* root  = objects[0];

        HwaHomePage* homePage = new HwaHomePage;
        homePage->setUI(root);
    }
	
    return app.exec();
}
