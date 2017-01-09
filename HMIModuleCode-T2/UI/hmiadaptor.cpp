#include "hmiadaptor.h"
#include <qdebug.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QAxObject>
#include <QAxWidget>
#include <QQuickView>
#include <windows.h>
#include <QDesktopWidget>
#include <QTimer>
HmiAdaptor::HmiAdaptor(QObject *parent) : QObject(parent)
{

    interfaceClass = InterfaceClass::Instance();
    operateProcess = MakeWeldProcess::Instance();
    workOrderModel = new WorkOrderModel(this);
    QStringList list;
    list << "WorkOrderId" << "WorkOrderName" << "DateCreated" << "PART" << "QUANTITY";
    workOrderModel->setRoles(list);
    workOrderModel->setModelList();

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
    alarmModel->setModelList(false);

    maintenanceLogModel = new MaintenanceLogModel(this);
    list.clear();
    list << "MaintenanceLogId" << "CreatedDate" << "OperatorName" << "Type" << "Message";
    maintenanceLogModel->setRoles(list);
    maintenanceLogModel->setModelList();

    spliceModel = new SplicesModel(this);
    QStringList listSplice;
    listSplice << "SpliceId" << "SpliceName" << "DateCreated" << "OperatorName" << "CrossSection" << "TotalWires" << "Verified" << "WeldMode" << "Energy" << "Amplitude"
         << "Width" << "TriggerPressure" << "WeldPressure" << "Time+" << "Time-" << "Power+" << "Power-" << "Pre-Height+" << "Pre-Height-" << "Height+" << "Height-" << "count";
    spliceModel->setRoles(listSplice);
    spliceModel->setModelList();


    advanceMaintenance = new AdvancedMaintenance;
    calibration = new Calibration;
    maintenanceCount = new MaintenanceCounter;
    maintenanceLog = new MaintenanceLogElement;
    toolChange = new ToolChange;
    statisticalTrend = new StatisticalTrend;
    interfaceClass = InterfaceClass::Instance();
    m_variantToString = VariantToString::Instance();
    m_stringToVariant = StringToVariant::Instance();
    connect(advanceMaintenance, SIGNAL(IOstatusFeedback(ulong)),this,SLOT(slotButtonState(ulong)));
    connect(interfaceClass, SIGNAL(EnableErrorMessageSignal(BransonMessageBox&)), this, SLOT(slotEnableDialog(BransonMessageBox&)));
    connect(interfaceClass, SIGNAL(DisableErrorMessageSignal(BransonMessageBox&)), this, SLOT(slotDisableDialog(BransonMessageBox&)));

    permissionSetting = new PermissionSetting(this);
    weldDefaults = new WeldDefaults(this);
    dataCommunication = new DataCommunication;

    connect(calibration,SIGNAL(WidthCalibrationFinish(bool)),this,SIGNAL(widthCalibrationFinish(bool)));
    connect(calibration,SIGNAL(HeightCalibrationFinish(bool)),this,SIGNAL(heightCalibrationFinish(bool)));
    connect(interfaceClass,SIGNAL(ThereAreAlarmItemsSignal()),this,SLOT(slotGetAlarmFlag()));

    connect(operateProcess,SIGNAL(WeldCycleCompleted(bool)),this,SLOT(slotWeldCycleCompleted(bool)));
    m_spliceAdaptor = DBPresetTable::Instance();
    testSpliceId = -1;
}

HmiAdaptor::~HmiAdaptor()
{

}

void HmiAdaptor::setTestSpliceId(int spliceId)
{
    testSpliceId = spliceId;
}

int HmiAdaptor::getTestSpliceId()
{
    qDebug() << "getTestSpliceId";
    int id;
    id = testSpliceId;
    testSpliceId = -1;
    return id;
}

void HmiAdaptor::quit()
{
//    int cx = GetSystemMetrics( SM_CXFULLSCREEN );
//    int cy = GetSystemMetrics( SM_CYFULLSCREEN );
    int cx=GetSystemMetrics(SM_CXSCREEN);
    int cy=GetSystemMetrics(SM_CYSCREEN);
    RECT rc = {0,0,cx,cy-taskBarHeight};
    SystemParametersInfo(SPI_SETWORKAREA,
                         0,
                         &rc,
                         0);
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

void HmiAdaptor::maintenanceCountExecute(QString code)
{
    if (code == "_Recall")
        maintenanceCount->_recall();
}

QString HmiAdaptor::maintenanceCountGetValue(int code, int index)
{
    QString value;
    bool bResult;
    if (code == 0)
    {
        switch (index) {
        case 2:
            value = maintenanceCount->CurrentMaintenanceCounter.HornCounterLimit.Current;
            break;
        case 3:
            value = maintenanceCount->CurrentMaintenanceCounter.HornCurrentCount;
            break;
        case 4:
            value = maintenanceCount->CurrentMaintenanceCounter.HornDateStarted;
            break;
        case 5:
            value = maintenanceCount->CurrentMaintenanceCounter.HornCounterLimit.Maximum;
            break;
        case 6:
            value = maintenanceCount->CurrentMaintenanceCounter.HornCounterLimit.Minimum;
            break;
        case 7:
            bResult = maintenanceCount->CurrentMaintenanceCounter.Horn80PercentAlarm;
            if(bResult == true)
                value = "left";
            else
                value = "right";
        default:
            break;
        }
    }
    else if (code == 1)
    {
        switch (index) {
        case 2:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilTipCounterLimit.Current;
            break;
        case 3:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilTipCurrentCount;
            break;
        case 4:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilTipDateStarted;
            break;
        case 5:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilTipCounterLimit.Maximum;
            break;
        case 6:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilTipCounterLimit.Minimum;
            break;
        case 7:
            bResult = maintenanceCount->CurrentMaintenanceCounter.Anvil80PercentAlarm;
            if(bResult == true)
                value = "left";
            else
                value = "right";
        default:
            break;
        }
    }
    else if (code == 2)
    {
        switch (index) {
        case 2:
            value = maintenanceCount->CurrentMaintenanceCounter.GatherCounterLimit.Current;
            break;
        case 3:
            value = maintenanceCount->CurrentMaintenanceCounter.GatherCurrentCount;
            break;
        case 4:
            value = maintenanceCount->CurrentMaintenanceCounter.GatherDateStarted;
            break;
        case 5:
            value = maintenanceCount->CurrentMaintenanceCounter.GatherCounterLimit.Maximum;
            break;
        case 6:
            value = maintenanceCount->CurrentMaintenanceCounter.GatherCounterLimit.Minimum;
            break;
        case 7:
            bResult = maintenanceCount->CurrentMaintenanceCounter.Gather80PercentAlarm;
            if(bResult == true)
                value = "left";
            else
                value = "right";
            break;
        default:
            break;
        }
    }
    else if (code == 3)
    {
        switch (index) {
        case 2:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilGuideCounterLimit.Current;
            break;
        case 3:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilGuideCurrentCount;
            break;
        case 4:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilGuideDateStarted;
            break;
        case 5:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilGuideCounterLimit.Maximum;
            break;
        case 6:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilGuideCounterLimit.Minimum;
            break;
        case 7:
            bResult = maintenanceCount->CurrentMaintenanceCounter.AnvilGuide80PercentAlarm;
            if(bResult == true)
                value = "left";
            else
                value = "right";
        default:
            break;
        }
    }
    else if (code == 4)
    {
        switch (index) {
        case 2:
            value = maintenanceCount->CurrentMaintenanceCounter.ConverterCounterLimit.Current;
            break;
        case 3:
            value = maintenanceCount->CurrentMaintenanceCounter.ConverterCurrentCount;
            break;
        case 4:
            value = maintenanceCount->CurrentMaintenanceCounter.ConverterDateStarted;
            break;
        case 5:
            value = maintenanceCount->CurrentMaintenanceCounter.ConverterCounterLimit.Maximum;
            break;
        case 6:
            value = maintenanceCount->CurrentMaintenanceCounter.ConverterCounterLimit.Minimum;
            break;
        case 7:
            bResult = maintenanceCount->CurrentMaintenanceCounter.Converter80PercentAlarm;
            if(bResult == true)
                value = "left";
            else
                value = "right";
        default:
            break;
        }
    }
    else if (code == 5)
    {
        switch (index) {
        case 2:
            value = "-";
            break;
        case 3:
            value = maintenanceCount->CurrentMaintenanceCounter.ActuatorCurrentCount;
            break;
        case 4:
            value = maintenanceCount->CurrentMaintenanceCounter.ActuatorDateStarted;
            break;
        case 5:
            value = "-";
            break;
        case 6:
            value = "-";
            break;
        default:
            break;
        }
    }
    return value;
}

QString HmiAdaptor::maintenanceCountGetImage(int index)
{
    QString source = "";
    switch (index) {
    case 0:
        source = "qrc:/images/images/Horn.JPG";
        break;
    case 1:
        source = "qrc:/images/images/Anvil_Tip.JPG";
        break;
    case 2:
        source = "qrc:/images/images/Gather_Tip.JPG";
        break;
    case 3:
        source = "qrc:/images/images/Booster.JPG";
        break;
    case 4:
        source = "qrc:/images/images/Converter.JPG";
        break;
    default:
        break;
    }
    return source;
}

QString HmiAdaptor::getMaintenanceVerson(int index)
{
    QString value = "";
    switch (index) {
    case 0:
        value = maintenanceCount->CurrentMaintenanceCounter.ActuatorPartNumber;
        break;
    case 1:
        value = maintenanceCount->CurrentMaintenanceCounter.ActuatorSoftwareVersion;
        break;
    case 2:
        value = maintenanceCount->CurrentMaintenanceCounter.ActuatorSerialNumber;
        break;
    case 3:
        value = maintenanceCount->CurrentMaintenanceCounter.ActuatorModuleNumber;
        break;
    default:
        break;
    }
    return value;
}

QString HmiAdaptor::getSoftVerson(int index)
{
    QString value = "";
    InterfaceClass* _Interface = InterfaceClass::Instance();
    switch (index) {
    case 0:
        value = _Interface->StatusData.ActuatorPartNumber;
        break;
    case 1:
        value = _Interface->StatusData.ActuatorSerialNumber;
        break;
    case 2:
    case 3:
        break;
    case 4:
        value = _Interface->CurrentVersions.ControllerVersion;
        break;
    case 5:
        value = _Interface->CurrentVersions.SoftwareVersion;
        break;
    case 6:
        value = _Interface->CurrentVersions.ActuatorVersion;
        break;
    default:
        break;
    }
    return value;
}

//listModel.append({mytitle:"Horn"})
//listModel.append({mytitle:"AnvilTip"})
//listModel.append({mytitle:"Gather"})
//listModel.append({mytitle:"AnvilGuide"})
//listModel.append({mytitle:"Converter"})
//listModel.append({mytitle:"Actuator"})
void HmiAdaptor::maintenanceCountReset(QString code)
{
    if (code == "Horn")
        maintenanceCount->_execute(TOOLINGCOUNT::HORNRESET);
    else if (code == "AnvilTip")
        maintenanceCount->_execute(TOOLINGCOUNT::ANVILTIPRESET);
    else if (code == "Gather")
        maintenanceCount->_execute(TOOLINGCOUNT::GATHERRESET);
    else if (code == "AnvilGuide")
        maintenanceCount->_execute(TOOLINGCOUNT::ANVILGUIDERESET);
    else if (code == "Converter")
        maintenanceCount->_execute(TOOLINGCOUNT::CONVERTERRESET);
}

void HmiAdaptor::maintenanceCountSetLimit(QString code, QString value)
{
    if (code == "Horn"){
        maintenanceCount->CurrentMaintenanceCounter.HornCounterLimit.Current = value;
        maintenanceCount->_execute(TOOLINGCOUNT::HORNCHANGE);
    }
    else if (code == "AnvilTip") {
        maintenanceCount->CurrentMaintenanceCounter.AnvilTipCounterLimit.Current = value;
        maintenanceCount->_execute(TOOLINGCOUNT::ANVILTIPCHANGE);
    }
    else if (code == "Gather"){
        maintenanceCount->CurrentMaintenanceCounter.GatherCounterLimit.Current = value;
        maintenanceCount->_execute(TOOLINGCOUNT::GATHERCHANGE);
    }
    else if (code == "AnvilGuide"){
        maintenanceCount->CurrentMaintenanceCounter.AnvilGuideCounterLimit.Current = value;
        maintenanceCount->_execute(TOOLINGCOUNT::ANVILGUIDECHANGE);
    }
    else if (code == "Converter"){
        maintenanceCount->CurrentMaintenanceCounter.ConverterCounterLimit.Current = value;
        maintenanceCount->_execute(TOOLINGCOUNT::CONVERTERCHANGE);
    }
}

void HmiAdaptor::maintenanceCount80PercentAlarm(QString code, QString value)
{
//    qDebug()<<"80%alarm code"<<code<<"value"<<value;
    if (code == "Horn")
        maintenanceCount->_execute(TOOLINGCOUNT::HORN80PERCENTALARM);
    else if (code == "AnvilTip") {
        maintenanceCount->_execute(TOOLINGCOUNT::ANVILTIP80PERCENTALARM);
    }
    else if (code == "Gather"){
        maintenanceCount->_execute(TOOLINGCOUNT::GATHER80PERCENTALARM);
    }
    else if (code == "AnvilGuide"){
        maintenanceCount->_execute(TOOLINGCOUNT::ANVILGUID80PERCENTALARM);
    }
    else if (code == "Converter"){
        maintenanceCount->_execute(TOOLINGCOUNT::CONVERTER80PERCENTALARM);
    }
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
    mutex.lock();
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
    mutex.unlock();
}

void HmiAdaptor::maintenanceReset()
{
    advanceMaintenance->Reset();
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

bool HmiAdaptor::borrowLogin(QString passwd, QString pageName)
{
    if (passwd == "0000")
        return true;
    OperatorElement myOperator;
    bool isLog = operatorModel->login(passwd, &myOperator);
    if (isLog)
    {
        permissionsettingExecute("_Recall");
        int i;
        int funcIndex = -1;
        int levelIndex = -1;
        bool reb = false;
        QList<struct PermissionSettingForScreen> funcNameList;
        funcNameList = permissionSetting->CurrentPermissionList;
        for (i = 0; i < funcNameList.length();i++)
        {
            if (pageName == funcNameList[i].Identifier) {
                funcIndex = i;
                break;
            }
        }
        if (funcIndex == -1)
            return false;
        levelIndex = (int)myOperator.PermissionLevel;
        if (levelIndex == 1)
            reb = permissionSetting->CurrentPermissionList.at(funcIndex).Level1;
        else if (levelIndex == 2)
            reb = permissionSetting->CurrentPermissionList.at(funcIndex).Level2;
        else if (levelIndex == 3)
            reb = permissionSetting->CurrentPermissionList.at(funcIndex).Level3;
        else if (levelIndex == 4)
            reb = permissionSetting->CurrentPermissionList.at(funcIndex).Level4;

        return reb;
    }
    else
        return false;
}

int HmiAdaptor::getCurrentOperatorId()
{
    return interfaceClass->CurrentOperator.OperatorID;
}

QString HmiAdaptor::getCurrentOperatorName()
{
    return interfaceClass->CurrentOperator.OperatorName;
}

QStringList HmiAdaptor::getCarTempLate()
{
    QStringList carList;
    int count = interfaceClass->StatusData.carTemplate.count();
    for (int i = 0; i < count; i++) {
        QString name = interfaceClass->StatusData.carTemplate.value(interfaceClass->StatusData.carTemplate.keys().at(i));
        carList.append(name);
    }
    return carList;
}

void HmiAdaptor::addCarTempLate(QString name)
{
    interfaceClass->StatusData.carTemplate.insert(interfaceClass->StatusData.carTemplate.count(),name);
}

void HmiAdaptor::removeCarTemplate(QString name)
{
    interfaceClass->StatusData.carTemplate.remove(interfaceClass->StatusData.carTemplate.key(name));
}

void HmiAdaptor::calibrationMaintenanceExecute(int code)
{
    calibration->_execute(code);
}

void HmiAdaptor::hornCalibrationComplete(int temp)
{
    calibration->HornCalibrationComplete(temp);
}

int HmiAdaptor::randPoint()
{
    return qrand() % 40;
}

QString HmiAdaptor::copyFileToPath(QString source)
{
    bool reb;
    if (source.contains("file:///"))
        source = source.mid(8);
    QString toPath = TOPATH + QDateTime::currentDateTime().toString("yyMMddhhmmss") + ".png";
    reb = QFile::copy(source,toPath);
    if (reb)
        return toPath;
    return "";
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
    else if (code == "_Init")
        permissionSetting->InitializeFRAM();
    return true;
}

bool HmiAdaptor::needPassWord(QString pageName)
{
    permissionsettingExecute("_Recall");

    int i;
    int funcIndex = -1;
    int levelIndex = -1;
    bool reb = true;
    QList<struct PermissionSettingForScreen> funcNameList;
    funcNameList = permissionSetting->CurrentPermissionList;
    for (i = 0; i < funcNameList.length();i++)
    {
        if (pageName == funcNameList[i].Identifier) {
            funcIndex = i;
            break;
        }
    }
    if (funcIndex == -1)
        return reb;
    levelIndex = (int)interfaceClass->CurrentOperator.PermissionLevel;
    qDebug() << "needPassWord" << pageName << funcIndex << levelIndex;

    if (levelIndex == 1)
        reb = permissionSetting->CurrentPermissionList.at(funcIndex).Level1;
    else if (levelIndex == 2)
        reb = permissionSetting->CurrentPermissionList.at(funcIndex).Level2;
    else if (levelIndex == 3)
        reb = permissionSetting->CurrentPermissionList.at(funcIndex).Level3;
    else if (levelIndex == 4)
        reb = permissionSetting->CurrentPermissionList.at(funcIndex).Level4;

    return !reb;
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
    return true;
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

QString HmiAdaptor::weldDefaultsGetNum(QString index)
{
    bool ok;
    QString temp;
    if (getStringValue(index).toFloat(&ok) < 0.01)
        return index;
    else
        return QString("%1%2").arg(getStringValue(index).toFloat(&ok) - 0.01).arg(getStringUnit(index));
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
    else if (code == "_Default")
        dataCommunication->_Default();
    return true;
}

bool HmiAdaptor::dataCommunicationGetSwitch(QString index)
{
    bool reb = false;
    if (index == "Network(Ethernet)")
        reb = dataCommunication->CurrentDataCommunication.EthernetMode;
    else if (index == "Remote Data Logging")
        reb = dataCommunication->CurrentDataCommunication.RemoteDataLogging;
    else if (index == "Graph Data")
        reb = dataCommunication->CurrentDataCommunication.RemoteGraphData;
    else if (index == "Modular Producation Mode")
        reb = dataCommunication->CurrentDataCommunication.ModularProduction;
    return reb;
}

QStringList HmiAdaptor::dataCommunicationGetValue(QString index)
{
    QStringList list;
    if (index == "IpPort")
    {
        list << dataCommunication->CurrentDataCommunication.IPConfiguration
             << dataCommunication->CurrentDataCommunication.ServerPort.Maximum
             << dataCommunication->CurrentDataCommunication.ServerPort.Current
             << dataCommunication->CurrentDataCommunication.ServerPort.Minimum;
    }
    else if (index == "shrinkData")
    {
        for (int i = 0; i < dataCommunication->CurrentDataCommunication.ShrinkTubeDefault.size();i++)
        {
            list << dataCommunication->CurrentDataCommunication.ShrinkTubeDefault.at(i).Name
                 << dataCommunication->CurrentDataCommunication.ShrinkTubeDefault.at(i).Temp
                 << dataCommunication->CurrentDataCommunication.ShrinkTubeDefault.at(i).Time;
        }
    }
    else if (index == "shrinkLimit")
    {
        list << dataCommunication->CurrentDataCommunication.MaxmmTemp
             << dataCommunication->CurrentDataCommunication.MinmmTemp
             << dataCommunication->CurrentDataCommunication.MaxmmTime
             << dataCommunication->CurrentDataCommunication.MinmmTime;
    }
    return list;
}

bool HmiAdaptor::dataCommunicationSetValue(QList<bool> boolList, QStringList strList, QString ip, QString port)
{
    dataCommunication->CurrentDataCommunication.EthernetMode = boolList[0];
    dataCommunication->CurrentDataCommunication.RemoteDataLogging = boolList[1];
    dataCommunication->CurrentDataCommunication.RemoteGraphData = boolList[2];
    dataCommunication->CurrentDataCommunication.ModularProduction = boolList[3];
//    dataCommunication->CurrentDataCommunication.IPConfiguration = ip;
    dataCommunication->CurrentDataCommunication.ServerPort.Current = port;
//    for (int i = 0;i < strList.count() / 3; i++)
//    {
//        dataCommunication->CurrentDataCommunication.ShrinkTubeDefault[i].Name = strList[i*3];
//        dataCommunication->CurrentDataCommunication.ShrinkTubeDefault[i].Temp = strList[i*3+1];
//        dataCommunication->CurrentDataCommunication.ShrinkTubeDefault[i].Time = strList[i*3+2];
//    }
    return true;
}

void HmiAdaptor::slotWeldCycleCompleted(bool result)
{
    if (result) {
        alarmModel->weldResultElement = operateProcess->CurrentWeldResult;
        emit signalWeldCycleCompleted(result);

        //        maintenanceCountExecute("_Recall");
//        int count = maintenanceCountGetValue(0,3).toInt();
        emit signalMantenaneceCount(interfaceClass->StatusData.CurrentMaintenanceLimits[0]);
    }
}

void HmiAdaptor::slotGetAlarmFlag()
{
    emit alarmModel->signalShowFlag(true);
}

void HmiAdaptor::slotEnableDialog(BransonMessageBox &MsgBox)
{
    bransonMessageBox = MsgBox;
    this->func_ptr = bransonMessageBox.func_ptr;
    qDebug() << "slotEnableDialog" << bransonMessageBox._Object << (MsgBox.TipsMode & OFF_ON_LINE);
    bool okVisable = true;
    bool cancelVisable = false;
    QString okText = "OK";;
    QString cancelText;
    QString typeIco;
    bool isQuit = false;
    if (MsgBox.TipsMode & OKOnly)
    {
        cancelVisable = false;
        okText = "OK";
    }
    else if (MsgBox.TipsMode & OKCancel)
    {
        cancelVisable = true;
        okText = "OK";
        cancelText = "CANCEL";
    }
    else if (MsgBox.TipsMode & RESETCancel)
    {
        cancelVisable = true;
        okText = "RESET";
        cancelText = "CANCEL";
    }
    else if (MsgBox.TipsMode & ACCEPTReject)
    {
        cancelVisable = true;
        okText = "Accept";
        cancelText = "Reject";
    }

    if (MsgBox.TipsMode & Critical)
    {
        typeIco = "qrc:/images/images/error1.png";
    }
    else if (MsgBox.TipsMode & Exclamation)
    {
        typeIco = "qrc:/images/images/alarm1.png";
    }
    else if (MsgBox.TipsMode & Information)
    {
        typeIco = "qrc:/images/images/information1.png";
    }
    else if (MsgBox.TipsMode & Alarm)
    {
        typeIco = "qrc:/images/images/alarm1.png";
    }

    if (MsgBox.TipsMode & OFF_ON_LINE)
        isQuit = true;
    emit signalEnableDialog(okVisable, cancelVisable, okText, "CANCEL", typeIco, MsgBox.MsgTitle, MsgBox.MsgPrompt,isQuit);
}

void HmiAdaptor::slotDisableDialog(BransonMessageBox &MsgBox)
{
    emit signalDisableDialog();
}

void HmiAdaptor::slotButtonState(const unsigned long status)
{
    if ((status & HORN_ON) == HORN_ON)
        emit signalButtonStateChanged("AnvilArm", true);
    else
        emit signalButtonStateChanged("AnvilArm", false);
    if ((status & GATHER_ON) == GATHER_ON)
        emit signalButtonStateChanged("Gather", true);
    else
        emit signalButtonStateChanged("Gather", false);
    if ((status & COVER_OPEN) == COVER_OPEN)
        emit signalButtonStateChanged("Safety", false);
    else
        emit signalButtonStateChanged("Safety", true);
    if ((status & CUTTER_ON) == CUTTER_ON)
        emit signalButtonStateChanged("Cutter", true);
    else
        emit signalButtonStateChanged("Cutter", false);
    if ((status & TOOLINGCOOL_ON) == TOOLINGCOOL_ON)
        emit signalButtonStateChanged("Cooling Tooling", true);
    else
        emit signalButtonStateChanged("Cooling Tooling", false);
    if ((status & CONVERTERCOOL_ON) == CONVERTERCOOL_ON)
        emit signalButtonStateChanged("Cooling Converter", true);
    else
        emit signalButtonStateChanged("Cooling Converter", false);
    if ((status & CRASH_ON) == CRASH_ON)
        emit signalButtonStateChanged("Crash", true);
    else
        emit signalButtonStateChanged("Crash", false);
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
                num += value.at(i);
                continue;
            } else {
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
    if (value.length() == 1 && value == ".") {
        return false;
    }
    if (minNum.toFloat(&ok) < 1 && minNum.toFloat(&ok) != 0) {
        if (value.length() >=3 && minNum.length() >= 3) {
            if (value.toFloat(&ok) < minNum.toFloat(&ok)) {
                return false;
            }
        } else {
            if (value.toFloat(&ok) >= 1) {
                if (value.toFloat(&ok) >= minNum.toFloat(&ok) && value.toFloat(&ok) <= maxNum.toFloat(&ok)) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return true;
            }
        }
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
    if (theValue.toFloat(&ok) >= minNum.toFloat(&ok) && theValue.toFloat(&ok) <= maxNum.toFloat(&ok)) {
        return true;
    } else {
        return false;
    }
}

int HmiAdaptor::timeChangeToInt(QString time)
{
    QDateTime temptime = QDateTime::fromString(time, "yyyy-MM-dd hh:mm:ss");
    return temptime.toTime_t();
}

void HmiAdaptor::setOperateProcess(int spliceId, bool isText)
{
    m_spliceAdaptor->QueryOneRecordFromTable(spliceId,&operateProcess->CurrentSplice);
    operateProcess->CurrentNecessaryInfo.IsTestProcess = isText;
    operateProcess->CurrentNecessaryInfo.CurrentWorkOrder.WorkOrderID = workOrderModel->getStructValue("WorkOrderId").toInt();
    operateProcess->CurrentNecessaryInfo.CurrentWorkOrder.WorkOrderName = workOrderModel->getStructValue("WorkOrderName").toString();
    operateProcess->CurrentNecessaryInfo.CurrentPart.PartID = partModel->getStruceValue("PartId").toInt();
    operateProcess->CurrentNecessaryInfo.CurrentPart.PartName = partModel->getStruceValue("PartName").toString();

}

void HmiAdaptor::operateProcessExec(QString type)
{
    qDebug() << "operateProcessExec" << type;
    if (type == "Start")
        operateProcess->_start();
    else if (type == "Stop")
        operateProcess->_stop();
    else if (type == "Execute")
        operateProcess->_execute();
}

int HmiAdaptor::controlLimitProcess(QString type, QList<int> list, int redMax, int redMin)
{
    int upper;
    int lower;
    if (type == "Time+") {
        operateProcess->ControlLimitProcess(QUALITYTIME,list,redMax,redMin,&upper,&lower);
        return upper;
    }
    else if (type == "Time-") {
        operateProcess->ControlLimitProcess(QUALITYTIME,list,redMax,redMin,&upper,&lower);
        return lower;
    }
    else if (type == "Power+") {
        operateProcess->ControlLimitProcess(QUALITYPOWER,list,redMax,redMin,&upper,&lower);
        qDebug() << "controlLimitProcess" << list << redMax << redMin << upper<< lower;
        return upper;
    }
    else if (type == "Power-") {
        operateProcess->ControlLimitProcess(QUALITYPOWER,list,redMax,redMin,&upper,&lower);
        return lower;
    }
    else if (type == "Pre-Height+") {
        operateProcess->ControlLimitProcess(QUALITYPREHEIGHT,list,redMax,redMin,&upper,&lower);
        return upper;
    }
    else if (type == "Pre-Height-") {
        operateProcess->ControlLimitProcess(QUALITYPREHEIGHT,list,redMax,redMin,&upper,&lower);
        return lower;
    }
    else if (type == "Post-Height+") {
        operateProcess->ControlLimitProcess(QUALITYPOSTHEIGHT,list,redMax,redMin,&upper,&lower);
        return upper;
    }
    else if (type == "Post-Height-") {
        operateProcess->ControlLimitProcess(QUALITYPOSTHEIGHT,list,redMax,redMin,&upper,&lower);
        return lower;
    }
}

void HmiAdaptor::teachModeProcess()
{
    operateProcess->TeachModeProcess();
}

void HmiAdaptor::stopTeachMode()
{
    operateProcess->StopTeachMode();
}

void HmiAdaptor::statisticalTrendApply(int SpliceID, QString SpliceName, unsigned int time_from, unsigned int time_to)
{
    statisticalTrend->_apply(SpliceID,SpliceName,time_from,time_to);
}

QList<int> HmiAdaptor::getStatisticalTrendDataList(int index)
{
    return statisticalTrend->RawQualityWindowList[index];
}

QStringList HmiAdaptor::getWeldActualParameterDataList(int index)
{
    QStringList list;
    if (statisticalTrend->CurrentWeldParameterList.count() == 0) {
        return list;
    }
    list.append(statisticalTrend->CurrentWeldParameterList[index].CrossSection);
    list.append(statisticalTrend->CurrentWeldParameterList[index].Time);
    list.append(statisticalTrend->CurrentWeldParameterList[index].Energy);
    list.append(statisticalTrend->CurrentWeldParameterList[index].PeakPower);
    list.append(statisticalTrend->CurrentWeldParameterList[index].WeldPressure);
    list.append(statisticalTrend->CurrentWeldParameterList[index].PreHeight);
    list.append(statisticalTrend->CurrentWeldParameterList[index].TriggerPressure);
    list.append(statisticalTrend->CurrentWeldParameterList[index].PostHeight);
    list.append(statisticalTrend->CurrentWeldParameterList[index].Amplitude);
    list.append(statisticalTrend->CurrentWeldParameterList[index].PartName);
    list.append(statisticalTrend->CurrentWeldParameterList[index].Width);
    list.append(statisticalTrend->CurrentWeldParameterList[index].DateCreated);
    list.append(statisticalTrend->CurrentWeldParameterList[index].WorkOrderName);
    return list;
}

QStringList HmiAdaptor::getCurrentStatisticsParameterList(int index)
{
    QStringList list;
    list.append(statisticalTrend->CurrentStatisticsParameter[index].SampleSize);
    list.append(statisticalTrend->CurrentStatisticsParameter[index].Mean);
    list.append(statisticalTrend->CurrentStatisticsParameter[index].Median);
    list.append(statisticalTrend->CurrentStatisticsParameter[index].Sigma);
    list.append(statisticalTrend->CurrentStatisticsParameter[index].Cpk);
    return list;
}

void HmiAdaptor::msgBoxClick(bool clickOK)
{
    if (clickOK && this->func_ptr != NULL && bransonMessageBox._Object != NULL) {
        qDebug() << "msgBoxClick" << this->func_ptr << bransonMessageBox._Object;
        this->func_ptr(bransonMessageBox._Object);
    }
}

QString HmiAdaptor::getAmplitudeToString(int value, bool bIsMax)
{
    if (bIsMax) {
        return m_variantToString->AmplitudeToString(value).Maximum;
    } else {
        return m_variantToString->AmplitudeToString(value).Minimum;
    }
}

QString HmiAdaptor::getTestQuantity(int value, bool bIsMax)
{
    if (bIsMax) {
        return m_variantToString->TestQuantity(value).Maximum;
    } else {
        return m_variantToString->TestQuantity(value).Minimum;
    }
}

QString HmiAdaptor::getShrinkTemperatureToString(int value, bool bIsMax)
{
    if (bIsMax) {
        return m_variantToString->ShrinkTemperatureToString(value).Maximum;
    } else {
        return m_variantToString->ShrinkTemperatureToString(value).Minimum;
    }
}

QString HmiAdaptor::getShrinkTimeToString(int value, bool bIsMax)
{
    if (bIsMax) {
        return m_variantToString->ShrinkTimeToString(value).Maximum;
    } else {
        return m_variantToString->ShrinkTimeToString(value).Minimum;
    }
}

void HmiAdaptor::teachModeSaveSplice()
{
    spliceModel->updateSplice(operateProcess->CurrentSplice);
}

void HmiAdaptor::importData(QString fileUrl)
{
    QString fileSource;
    fileSource = fileUrl;
    if (fileSource.contains("file:///"))
        fileSource = fileSource.mid(8);
    QFile csvFile(fileSource);
    QStringList CSVList;
    CSVList.clear();


    if (csvFile.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&csvFile);
        while (!stream.atEnd())
        {
            CSVList.push_back(stream.readLine());
        }
        csvFile.close();
    }
    if (CSVList.size() > 1) {
        if (CSVList.at(0) == "WireData")
            wireModel->importData(CSVList[1]);
        else if (CSVList.at(0) == "SpliceData") {
            importSplice(CSVList[1]);
        }
        else if (CSVList.at(0) == "PartData") {
            importPart(CSVList[1]);
        }
        else if (CSVList.at(0) == "ShrinkData") {
            QStringList shrinkList = QString(CSVList.at(1)).split(",");
            if (shrinkList.count() >= 2)
                addInsulation(shrinkList[0],shrinkList[1],shrinkList[2]);
        }
        else if (CSVList.at(0) == "WorkOrderData") {
            importWorkOrder(CSVList[1]);
        }
    }
}

int HmiAdaptor::importSplice(QString spliceStr)
{
    QStringList tempList;
    QStringList wireList;
    QList<int> wireIdList;
    QString temp;
    QString spliceString;
    QMap<int,QString> tempMap;
    int i;
    tempList = spliceStr.split(",");

    temp = tempList.at(tempList.count() - 2);
    temp.replace(".",",");
    wireList = temp.split(";");
    for (i = 0;i < wireList.count();i++)
    {
        if (wireList[i] != "")
            wireIdList.push_back(wireModel->importData(wireList[i]));
    }

    for (i = 0; i < wireIdList.count();i++)
    {
        if (wireIdList[i] != -1)
            tempMap.insert(wireIdList[i],wireModel->getWireName(wireIdList[i]));
    }

    for (int j = 0;j < tempList.count(); j++)
    {
        spliceString.append(tempList[j] + ",");
    }
    int spliceId = spliceModel->importData(spliceString,tempMap);
    if (spliceId != -1)
        wireModel->updateSpliceIdToWire(wireIdList,spliceId);
    return spliceId;
}

int HmiAdaptor::importPart(QString partStr)
{
    qDebug() << "importPartppppppp" << partStr;
    QStringList tempList;
    QStringList spliceList;
    QList<int> spliceIdList;
    QString temp;
    QString partString;
    QMap<int,QString> tempMap;
    int i;
    tempList = partStr.split(",");
    if (tempList.count() > 2)
        temp = tempList.at(tempList.count() - 2);
    else
        return -1;
    temp.replace("*",",");
    spliceList = temp.split("|");
    for (i = 0;i < spliceList.count();i++)
    {
        if (spliceList[i] != "")
            spliceIdList.push_back(importSplice(spliceList[i]));
    }
    for (i = 0; i < spliceIdList.count();i++)
    {
        if (spliceIdList[i] != -1)
            tempMap.insert(spliceIdList[i],spliceModel->getSpliceName(spliceIdList[i]));
    }

    for (int j = 0;j < tempList.count(); j++)
    {
        partString.append(tempList[j] + ",");
    }
    int partId = partModel->importData(partString,tempMap);
    return partId;
}

int HmiAdaptor::importWorkOrder(QString workOrderStr)
{
    QStringList tempList;
    QStringList partList;
    QList<int> partIdList;
    QString temp;
    QString partString;
    QMap<int,QString> tempMap;
    int i;
    tempList = workOrderStr.split(",");
    if (tempList.count() > 2)
        temp = tempList.at(tempList.count() - 3);
    else
        return -1;
    temp.replace("@",",");
    partList = temp.split("$");
    for (i = 0;i < partList.count();i++)
    {
        if (partList[i] != "")
            partIdList.push_back(importPart(partList[i]));
    }
    for (i = 0; i < partIdList.count();i++)
    {
        if (partIdList[i] != -1)
            tempMap.insert(partIdList[i],partModel->getPartName(partIdList[i]));
    }

    for (int j = 0;j < tempList.count(); j++)
    {
        partString.append(tempList[j] + ",");
    }
    int partId = workOrderModel->importData(partString,tempMap);
    return partId;
}

void HmiAdaptor::addInsulation(QString insualtionId, QString temp, QString time)
{
    qDebug() << "addInsulation";
    ShrinkTubeData shrinkData;
    shrinkData.Name = insualtionId;
    shrinkData.temp = m_stringToVariant->ShrinkTemperatureToInt(temp);
    shrinkData.Time = m_stringToVariant->ShrinkTimeToInt(time);
    interfaceClass->StatusData.ShrinkTubeDefaults.append(shrinkData);
    interfaceClass->StatusData.WriteStatusDataToQSetting();
}

void HmiAdaptor::exportShrink(QString insualtionId, QString temp, QString time,QString fileUrl)
{
    QString fileSource = fileUrl;
    QString lineValue;
    if (fileSource.contains("file:///"))
        fileSource = fileSource.mid(8);

    lineValue.append(insualtionId + ",");
    lineValue.append(temp + ",");
    lineValue.append(time + ",");

    QFile csvFile(fileSource);
    if (csvFile.open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QTextStream out(&csvFile);
        out << "ShrinkData" << '\n' << lineValue;
        csvFile.close();
    }
}

void HmiAdaptor::removeShrink(int selectIndex)
{
    if (interfaceClass->StatusData.ShrinkTubeDefaults.size() >= selectIndex + 1)
    {
        interfaceClass->StatusData.ShrinkTubeDefaults.removeAt(selectIndex);
        interfaceClass->StatusData.WriteStatusDataToQSetting();
    }
}
void HmiAdaptor::setAlarmModelList(bool bIsNeedReset)
{
    alarmModel->setModelList(bIsNeedReset);
}

void HmiAdaptor::viewLibraryMovePart(int id, QString name)
{
    emit signalMovePart(id,name);
}

void HmiAdaptor::viewLibraryMoveSplice(int id, QString name)
{
    emit signalMoveSplice(id,name);
}
