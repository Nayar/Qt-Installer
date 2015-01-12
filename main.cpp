#include "mainwindow.h"
#include <QApplication>
#include "functions.h"
#include "licensewizard.h"
#include "QDebug"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LicenseWizard lw;
    lw.show();
    if(isJavaInstalled()){
        qDebug() << "Wawa ena";
    }

    return a.exec();
}
