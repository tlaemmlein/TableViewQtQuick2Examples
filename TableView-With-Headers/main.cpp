#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QAbstractTableModel>
#include <QQmlContext>

#include "TableModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<TableModel>("TableModel", 0, 1, "TableModel");
    TableModel tm;


    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("_TableModel", &tm);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}

