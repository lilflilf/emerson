#include "ModRunSetup.h"
#include "M102IA.h"
#include "M2010.h"
#include "M10INI.h"
#include "typedef.h"
#include <QCoreApplication>
#include <QDateTime>
#include <QString>
#include "MDefine.h"
#include "SaveReplace.h"
#include <QDir>
#include <QDataStream>

ModRunSetup* ModRunSetup::_instance = 0;
ModRunSetup* ModRunSetup::Instance()
{
    if(_instance == 0){
        _instance = new ModRunSetup();
    }
    return _instance;
}
ModRunSetup::ModRunSetup()
{
    OfflineModeEnabled = false;
    GlobalOfflineModeEnabled = false;
}

void ModRunSetup::DeleteStatTempFiles()
{
    QString sFileName;

}




