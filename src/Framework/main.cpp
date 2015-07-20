#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine("main.qml");
	QList<QObject*> objects = engine.rootObjects();
	if (objects.size() > 0)
	{
		QObject* root  = objects[0];
		root->findChild<QObject*>("TableView");
	}
	

    return app.exec();
}
