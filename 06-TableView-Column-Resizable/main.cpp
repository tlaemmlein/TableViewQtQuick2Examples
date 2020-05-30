#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QAbstractTableModel>
#include <QQmlContext>

#include "ProcessModel.h"
#include "SortFilterTableModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ProcessModel>("ProcessModel", 0, 1, "ProcessModel");
    qmlRegisterType<SortFilterTableModel>("SortFilterTableModel", 0, 1, "SortFilterTableModel");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}

