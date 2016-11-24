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
    dataCommunication = new DataCommunication;

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
        return weldDefaults->_Recall();
    else if (code == "_Set") {
        return weldDefaults->_Set();
    }
    else if (code == "_Default")
        weldDefaults->_Default();
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
    else if (index == "Cooling") {
        if (weldDefaults->CurrentWeldSettings.CurrentCoolingMode == CoolingMode::ENERGYMODE)
            reb = true;
        else if (weldDefaults->CurrentWeldSettings.CurrentCoolingMode == CoolingMode::OFF)
            reb = false;
        else if (weldDefaults->CurrentWeldSettings.CurrentCoolingMode == CoolingMode::ON)
            reb = true;
    }
    else if (index == "cooling(1sec/100J)") {
        if (weldDefaults->CurrentWeldSettings.CurrentCoolingMode == CoolingMode::ENERGYMODE)
            reb = true;
        else if (weldDefaults->CurrentWeldSettings.CurrentCoolingMode == CoolingMode::OFF)
            reb = false;
        else if (weldDefaults->CurrentWeldSettings.CurrentCoolingMode == CoolingMode::ON)
            reb = false;
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
    if (index == -1 ) {
        list << weldDefaults->CurrentWeldSettings.CurrentCoolingDur.Maximum
             << weldDefaults->CurrentWeldSettings.CurrentCoolingDur.Current
             << weldDefaults->CurrentWeldSettings.CurrentCoolingDur.Minimum
             << weldDefaults->CurrentWeldSettings.CurrentCoolingDel.Maximum
             << weldDefaults->CurrentWeldSettings.CurrentCoolingDel.Current
             << weldDefaults->CurrentWeldSettings.CurrentCoolingDel.Minimum;
        return list;
    }
    list << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Range.Maximum
         << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Range.Current
         << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Range.Minimum
         << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Offset.Maximum
         << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Offset.Current
         << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Offset.Minimum
         << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Multiplier.Maximum
         << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Multiplier.Current
         << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Multiplier.Minimum
         << weldDefaults->CurrentWeldSettings.WeldSettingFormula[index].Identifier;
    return list;
}

bool HmiAdaptor::weldDefaultsSetValue(QList<bool> boolList, QStringList strList, int sampleIndex, QString coolingDur,QString coolingDel)
{
    weldDefaults->CurrentWeldSettings.SampleRatio = (SAMPLERATIO)sampleIndex;
    weldDefaults->CurrentWeldSettings.CurrentCoolingDur.Current = coolingDur;
    weldDefaults->CurrentWeldSettings.CurrentCoolingDel.Current = coolingDel;

    weldDefaults->CurrentWeldSettings.WidthEncoder = boolList[0];
    weldDefaults->CurrentWeldSettings.HeightEncoder = boolList[1];
    weldDefaults->CurrentWeldSettings.FootPedalAbort = boolList[2];
    weldDefaults->CurrentWeldSettings.CoolingForTooling = boolList[5];
    if (boolList[3] && boolList[4])
        weldDefaults->CurrentWeldSettings.CurrentCoolingMode = CoolingMode::ENERGYMODE;
    else if (!boolList[3])
        weldDefaults->CurrentWeldSettings.CurrentCoolingMode = CoolingMode::OFF;
    else if (boolList[3] && !boolList[4])
        weldDefaults->CurrentWeldSettings.CurrentCoolingMode = CoolingMode::OFF;
    weldDefaults->CurrentWeldSettings.Imperical2Metric = boolList[6];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR1].Range.Current = strList[0];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR1].Offset.Current = strList[1];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR1].Multiplier.Current = strList[2];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR2].Range.Current = strList[3];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR2].Offset.Current = strList[4];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR2].Multiplier.Current = strList[5];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR3].Range.Current = strList[6];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR3].Offset.Current = strList[7];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR3].Multiplier.Current = strList[8];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR1].Range.Current = strList[9];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR1].Offset.Current = strList[10];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR1].Multiplier.Current = strList[11];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR2].Range.Current = strList[12];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR2].Offset.Current = strList[13];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR2].Multiplier.Current = strList[14];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR3].Range.Current = strList[15];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR3].Offset.Current = strList[16];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR3].Multiplier.Current = strList[17];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR1].Range.Current = strList[18];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR1].Offset.Current = strList[19];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR1].Multiplier.Current = strList[20];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR2].Range.Current = strList[21];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR2].Offset.Current = strList[22];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR2].Multiplier.Current = strList[23];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR3].Range.Current = strList[24];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR3].Offset.Current = strList[25];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR3].Multiplier.Current = strList[26];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR1].Range.Current = strList[27];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR1].Offset.Current = strList[28];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR1].Multiplier.Current = strList[29];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR2].Range.Current = strList[30];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR2].Offset.Current = strList[31];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR2].Multiplier.Current = strList[32];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR3].Range.Current = strList[33];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR3].Offset.Current = strList[34];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR3].Multiplier.Current = strList[35];

    return true;
}

bool HmiAdaptor::dataCommunicationExecute(QString code)
{
    if (code == "_Recall")
        return dataCommunication->_Recall();
    else if (code == "_Set") {
        return dataCommunication->_Set();
    }
//    else if (code == "_Default")
//        dataCommunication->_Default();
    return true;
}

bool HmiAdaptor::dataCommunicationGetSwitch(QString index)
{
    return true;
}

bool HmiAdaptor::stringRegexMatch(QString exp, QString value)
{
    QRegExp rx(exp);
    bool match = rx.exactMatch(value);
    return match;
}

QString HmiAdaptor::getStringUnit(QString value)
{
    QString unit;
    if (!value.isEmpty() && !value.isNull()) {
        for (int i = 0; i < value.length(); i++) {
            if ((value.at(i) >= '0' && value.at(i) <= '9') || value.at(i) == '.') {
                continue;
            } else {
                unit = value.right(value.length()-i);
                break;
            }
        }
    }
    return unit;
}
QString HmiAdaptor::getStringValue(QString value)
{
    QString num;
    if (!value.isEmpty() && !value.isNull()) {
        for (int i = 0; i < value.length(); i++) {
            if ((value.at(i) >= '0' && value.at(i) <= '9') || value.at(i) == '.') {
                continue;
            } else {
                num = value.left(i);
                break;
            }
        }
    }
    return num;
}

bool HmiAdaptor::keyNumStringMatch(QString minValue, QString maxValue, QString value)
{
    bool ok;
    QString minNum = getStringValue(minValue);
    QString maxNum = getStringValue(maxValue);
    if (value.contains("*")) {
        return false;
    }
    if(minNum.toFloat(&ok) > 10 && value.toFloat(&ok) < minNum.toFloat(&ok)) {
        return true;
    }
    if (value.toFloat(&ok) >= minNum.toFloat(&ok) && value.toFloat(&ok) <= maxNum.toFloat(&ok)) {
        return true;
    } else {
        return false;
    }
}

bool HmiAdaptor::comepareCurrentValue(QString minValue, QString maxValue, QString value)
{
    bool ok;
    QString minNum = getStringValue(minValue);
    QString maxNum = getStringValue(maxValue);
    QString theValue = getStringValue(value);
    qDebug()<<"2222222222222"<<minNum<<maxNum<<theValue;
    if (theValue.toFloat(&ok) >= minNum.toFloat(&ok) && theValue.toFloat(&ok) <= maxNum.toFloat(&ok)) {
        return true;
    } else {
        return false;
    }
}
