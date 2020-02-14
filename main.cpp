#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "guiworker.h"
#include "debug_page.h"

int main( int argc, char *argv[] ) {
	QCoreApplication::setAttribute( Qt::AA_EnableHighDpiScaling );

	QGuiApplication app( argc, argv );
	app.setOrganizationName( "HardDie" );
	app.setOrganizationDomain( "HardDie" );

	QQmlApplicationEngine engine;

	GUIWorker    guiWorker;
	QQmlContext *context = engine.rootContext();
	context->setContextProperty( "guiWorker", &guiWorker );
	context->setContextProperty( "debugPage", &pDebug );

	engine.load( QUrl( QStringLiteral( "qrc:/Qml_Main.qml" ) ) );
	if ( engine.rootObjects().isEmpty() )
		return -1;

	return app.exec();
}
