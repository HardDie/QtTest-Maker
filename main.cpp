#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "guiworker.h"

int main( int argc, char *argv[] ) {
	QCoreApplication::setAttribute( Qt::AA_EnableHighDpiScaling );

	QGuiApplication app( argc, argv );

	QQmlApplicationEngine engine;

	GUIWorker    guiWorker;
	QQmlContext *context = engine.rootContext();
	context->setContextProperty( "guiWorker", &guiWorker );

	engine.load( QUrl( QStringLiteral( "qrc:/main.qml" ) ) );
	if ( engine.rootObjects().isEmpty() )
		return -1;

	return app.exec();
}
