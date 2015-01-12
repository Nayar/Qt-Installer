#include "functions.h"

bool isJavaInstalled(){
    {
        QProcess *java = new QProcess();
        java->start("java -version");

        if(!java->waitForFinished()){
            return false;
        }

        QString result = java->readAllStandardError();
        if(result.contains("java version")){
            return true;
        }
        return false;
    }
}
