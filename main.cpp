#include "MainWindow.h"

#include <iostream>
#include <ctime>

#include <QApplication>
#include <QDateTime>

#include "OGLExceptions.h"
#include "DebugApplication.h"

void qDebugMsgHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    (void) context;
    QString msgPrefix = "[" + QTime::currentTime().toString() + "] ";
    switch (type) {
        case QtDebugMsg		: msgPrefix += "Debug:    "; break;
        case QtWarningMsg	: msgPrefix += "Warning:  "; break;
        case QtCriticalMsg	: msgPrefix += "Critical: "; break;
        case QtFatalMsg		: msgPrefix += "Fatal:    "; break;
        case QtInfoMsg		: msgPrefix += "Info:     "; break;
    }
    QStringList lines = msg.split("\n");
    for (const QString & l : lines)
        std::cout << (msgPrefix + l).toStdString() << std::endl;
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(qDebugMsgHandler);

    QApplication a(argc, argv);

    //qsrand(time(nullptr));

    MainWindow w;
    w.show();

    return a.exec();
}
