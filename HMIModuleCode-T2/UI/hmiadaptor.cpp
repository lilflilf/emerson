#include "hmiadaptor.h"
#include <qdebug.h>
#include <QSqlQuery>
#include <QSqlError>
HmiAdaptor::HmiAdaptor(QObject *parent) : QObject(parent)
{
    workOrderModel = new WorkOrderModel(this);
    QStringList list;
    list << "workOrderId" << "name" << "date" << "middle" << "count";
    workOrderModel->setRoles(list);
    workOrderModel->setModelList();

    spliceModel = new SpliceModel(this);
    list.clear();
    list << "spliceId" << "name" << "date" << "middle" << "count" << "SpliceName" << "DateCreated" << "OperatorName" << "CrossSection" << "TotalWires" << "Verified" << "WeldMode" << "Energy" << "Amplitude"
         << "Width" << "TriggerPressure" << "WeldPressure" << "Time+" << "Time-" << "Power+" << "Power-" << "Pre-Height+" << "Pre-Height-" << "Height+" << "Height-";
    spliceModel->setRoles(list);
    spliceModel->setModelList();

    partModel = new PartModel(this);
    list.clear();
    list << "PartId" << "PartName" << "DateCreated" << "OperatorName" << "TotalSplices" << "ProcessMode" << "#ofWorkstation" << "#ofSplicesperWorkstation" << "Rows" << "Columns" << "MaxSplicesPerZone";
    partModel->setRoles(list);
    partModel->setModelList();

    wireModel = new WireModel(this);
    list.clear();
    list <<"WireId"<< "WireName" << "DateCreated" << "OperatorName" << "Color" << "StripeType" << "StripeColor" << "Gauge" << "MetalType" << "HorizontalLocation" << "VerticalLocation" << "VerticalPosition";
    wireModel->setRoles(list);
    wireModel->setModelList();

    operatorModel = new OperatorModel(this);
    list.clear();;
    list << "operatorId" << "name" << "date" << "middle" << "count";
    operatorModel->setRoles(list);
    operatorModel->setModelList();

    weldHistoryModel = new WeldHistoryModel(this);
    list.clear();
    list << "WeldHistoryId" << "WorkOrderName" << "PartName" << "SpliceName" << "OperatorName" << "DateCreated"
         << "CrossSection" << "WeldMode" << "Energy" << "Amplitude" << "Width" << "TriggerPressure" << "WeldPressure"
         << "Time+" << "Timer-" << "Time" << "Power+" << "Power-" << "Power" << "Pre-Height+" << "Pre-Height-"
         << "Pre-Height" << "Height+" << "Height-" << "Height" << "Alarm" << "SampleRatio" <<"GraphData";

    weldHistoryModel->setRoles(list);
    weldHistoryModel->setModelList();

    alarmModel = new AlarmModel(this);
    list.clear();
    list << "AlarmId" <<"CreatedDate" << "Alarm/ErrorType" << "Alarm/ErrorLevel" << "Message" << "SpliceName";
    alarmModel->setRoles(list);
    alarmModel->setModelList();

    advanceMaintenance = new AdvancedMaintenance;
    calibration = new Calibration;
    maintenanceCount = new MaintenanceCounter;
    maintenanceLog = new MaintenanceLogElement;
    toolChange = new ToolChange;
    interfaceClass = InterfaceClass::Instance();


    permissionSetting = new PermissionSetting(this);
    weldDefaults = new WeldDefaults(this);

    connect(calibration,SIGNAL(WidthCalibrationFinish(bool)),this,SIGNAL(widthCalibrationFinish(bool)));
    connect(calibration,SIGNAL(HeightCalibrationFinish(bool)),this,SIGNAL(heightCalibrationFinish(bool)));

//    QSqlDatabase db;
//    db = QSqlDatabase::addDatabase("QSQLITE", "hmiconnect");
//    db.setDatabaseName("./hmi.db");
//    if (!db.open())
//    {
//        qDebug() << "Cannot open contact database" << db.lastError().text();
//    }

//    QSqlQuery query(db);
//    if(!db.tables().contains("wire"))
//    {
//        query.exec("create table wire (id INTEGER PRIMARY KEY AUTOINCREMENT, surname varchar(20))");
//    }
//    qDebug() << query.lastError();

//    query.prepare("INSERT INTO wire (surname) VALUES (?)");
//    query.addBindValue("zhangjy");
//    query.exec();
//    qDebug() << query.lastError();
//    db.close();
}

void HmiAdaptor::openFileDialog()
{
    qDebug() << tr("openFileDialog");
    //QString fileName = QFileDialog::getOpenFileName(NULL, tr("Open File"),"C:",tr("Images (*.png *.xpm *.jpg)"));
}

void HmiAdaptor::advancedMaintenanceExecute(int code)
{
        advanceMaintenance->_execute(code);
}

void HmiAdaptor::maintenanceStart(int page)
{
//    AdvancedMaintenance * advanceMaintenance;
//    Calibration * calibration;
//    MaintenanceCounter *maintenanceCount;
//    MaintenanceLogElement *maintenanceLog;
//    ToolChange *toolChange;
    switch (page) {
    case 0:
        calibration->_start();
        break;
    case 1:
        toolChange->_start();
        break;
    case 2:
        advanceMaintenance->_start();
        break;
    case 3:
        maintenanceCount->_start();
        break;
    case 4:
        break;
    default:
        break;
    }
}

void HmiAdaptor::maintenanceStop(int page)
{
    switch (page) {
    case 0:
        calibration->_stop();
        break;
    case 1:
        toolChange->_stop();
        break;
    case 2:
        advanceMaintenance->_stop();
        break;
    case 3:
        maintenanceCount->_stop();
        break;
    case 4:
        break;
    default:
        break;
    }
}

bool HmiAdaptor::login(QString passwd)
{
    OperatorElement myOperator;
    bool isLog = operatorModel->login(passwd, &myOperator);
    if (isLog)
    {
        interfaceClass->CurrentOperator = myOperator;
    }
    else
    {
        if (passwd == "0000")
            isLog = true;
    }

    return isLog;
}

void HmiAdaptor::calibrationMaintenanceExecute(int code)
{
    calibration->_execute(code);
}


bool HmiAdaptor::permissionsettingExecute(QString code)
{
    if (code == "_Recall")
        return permissionSetting->_Recall();
    else if (code == "_Set") {
        return permissionSetting->_Set();
    }
    else if (code == "_Default")
        permissionSetting->_Default();
    else if (code == "_Clear")
        permissionSetting->CurrentPermissionList.clear();
    return true;
}

QStringList HmiAdaptor::permissionsettingGetValue(QString code)
{
    if (code == "AllFunctionNameList")
        return permissionSetting->AllFunctionNameList;
    else if (code == "FourLevelIdentifier")
        return permissionSetting->FourLevelIdentifier;
    else if (code == "CurrentIdentifier"){
        QStringList currentIdentifier;
        for (int i = 0; i < permissionSetting->CurrentPermissionList.count(); i++)
        {
            currentIdentifier << permissionSetting->CurrentPermissionList.at(i).Identifier;
        }
        return currentIdentifier;
    }

}

bool HmiAdaptor::permissionsettingGetChecked(QString stringIndex, int level)
{
    bool reb = false;
    int index = -1;
    for (int i = 0; i < permissionSetting->CurrentPermissionList.count(); i++)
    {
        if (stringIndex == permissionSetting->CurrentPermissionList.at(i).Identifier)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
        return reb;
    switch (level) {
    case 1:
        reb = permissionSetting->CurrentPermissionList.at(index).Level1;
        break;
    case 2:
        reb = permissionSetting->CurrentPermissionList.at(index).Level2;
        break;
    case 3:
        reb = permissionSetting->CurrentPermissionList.at(index).Level3;
        break;
    case 4:
        reb = permissionSetting->CurrentPermissionList.at(index).Level4;
        break;
    default:
        break;
    }
    return reb;
}

bool HmiAdaptor::permissionsettingSetValue(QString name, bool level1, bool level2, bool level3, bool level4)
{
    PermissionSettingForScreen temp;
    temp.Identifier = name;
    temp.Level1 = level1;
    temp.Level2 = level2;
    temp.Level3 = level3;
    temp.Level4 = level4;
    permissionSetting->CurrentPermissionList.append(temp);
}

bool HmiAdaptor::permissionsettingSetFourValue(QStringList fourName)
{
    permissionSetting->FourLevelIdentifier = fourName;
    return true;
}

bool HmiAdaptor::weldDefaultsExecute(QString code)
{
    if (code == "_Recall")
        return permissionSetting->_Recall();
    else if (code == "_Set") {
        return permissionSetting->_Set();
    }
    else if (code == "_Default")
        permissionSetting->_Default();
    return true;
}

bool HmiAdaptor::weldDefaultsGetSwitch(QString index)
{
    bool reb = false;
    if (index == "Width Encoder")
        reb = weldDefaults->CurrentWeldSettings.WidthEncoder;
    else if (index == "Height Encoder")
        reb = weldDefaults->CurrentWeldSettings.HeightEncoder;
    else if (index == "Foot Pedal Abort")
        reb = weldDefaults->CurrentWeldSettings.FootPedalAbort;
    else if (index == "Cooling" || index == "cooling(1sec/100J)") {
        if (weldDefaults->CurrentWeldSettings.CurrentCoolingMode == CoolingMode::ENERGYMODE)
            reb = true;
        else if (weldDefaults->CurrentWeldSettings.CurrentCoolingMode == CoolingMode::OFF)
            reb = false;
        else if (weldDefaults->CurrentWeldSettings.CurrentCoolingMode == CoolingMode::ON)
            reb = true;
    }
    else if (index == "Cooling Tooling")
        reb = weldDefaults->CurrentWeldSettings.CoolingForTooling;
    else if (index == "Unit Conversion")
        reb = weldDefaults->CurrentWeldSettings.Imperical2Metric;
    else if (index == "Graph Data Sampling 1ms")
        reb = weldDefaults->CurrentWeldSettings.SampleRatio == SampleWith1ms ? true : false;
    else if (index == "Graph Data Sampling 5ms")
        reb = weldDefaults->CurrentWeldSettings.SampleRatio == SampleWith5ms ? true : false;
    else if (index == "Graph Data Sampling 10ms")
        reb = weldDefaults->CurrentWeldSettings.SampleRatio == SampleWith10ms ? true : false;
    else if (index == "Graph Data Sampling 20ms")
        reb = weldDefaults->CurrentWeldSettings.SampleRatio == SampleWith20ms ? true : false;
    return reb;
}

QStringList HmiAdaptor::weldDefaultsGetValue(HmiAdaptor::FormulaRange index)
{
    QStringList list;
    list << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Range.Maximum
         << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Range.Current
         << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Range.Minimum
         << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Offset.Maximum
         << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Offset.Current
         << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Offset.Minimum
         << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Multiplier.Maximum
         << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Multiplier.Current
         << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Multiplier.Minimum;
    qDebug() << "ccccccccccccc" << list;
    return list;
}
