#include "hmiadaptor.h"
#include "Modules/typedef.h"
#include "DataExport_Import/CSVPresetData.h"
#include "DataExport_Import/CSVSequenceData.h"
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
#include <QCoreApplication>
#include <QProcess>
#include <QDir>
#include <QWebChannel>
HmiAdaptor::HmiAdaptor(QObject *parent) : QObject(parent)
{
    interfaceClass = InterfaceClass::Instance();
//    workOrderModel = new WorkOrderModel(this);
    operateProcess = MakeWeldProcess::Instance();

    QStringList list;
//    list << "WorkOrderId" << "WorkOrderName" << "DateCreated" << "PART" << "QUANTITY";
//    workOrderModel->setRoles(list);
//    workOrderModel->setModelList();

    harnessModel = new PartModel(this);
    list.clear();
    list << "PartId" << "HarnessName" << "DateCreated" << "OperatorName" << "TotalSplices" << "ProcessMode" << "ofWorkstation" << "#ofSplicesperWorkstation" << "Rows" << "Columns" << "MaxSplicesPerZone";
    harnessModel->setRoles(list);
    harnessModel->setModelList();

    wireModel = new WireModel(this);
    list.clear();
    list <<"WireId"<< "WireName" << "DateCreated" << "OperatorName" << "Color" << "StripeType" << "StripeColor" << "Gauge" << "MetalType" << "HorizontalLocation" << "VerticalLocation" << "VerticalPosition";
    wireModel->setRoles(list);
    wireModel->setModelList();
    wireModel->setTemplateModelList();


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

    sequenceModel = new SequenceModel(this);
    QStringList sequenceList;
    sequenceList << "SequenceId" << "SequenceName" << "DateCreated" << "OperatorName" << "TotalSplices" << "QUANTITY";
    sequenceModel->setRoles(sequenceList);
    sequenceModel->setModelList();

    advanceMaintenance = new AdvancedMaintenance;
    calibration = new Calibration;
    maintenanceCount = new MaintenanceCounter;
    maintenanceLog = new MaintenanceLogElement;
    toolChange = new ToolChange;
    statisticalTrend = new StatisticalTrend;
    interfaceClass = InterfaceClass::Instance();
    m_variantToString = VariantToString::Instance();
    m_stringToVariant = StringToVariant::Instance();
    connect(advanceMaintenance, SIGNAL(IOstatusFeedbackSignal(ulong)),this,SLOT(slotButtonState(ulong)));
    connect(advanceMaintenance, SIGNAL(CurrentPowerAndFrequencySignal(int,QString)), this, SIGNAL(signalAdvanceMaintenancePowerAndFrequency(int, QString)));
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
    editPartId = -1;
    bIsPhysicalKey = interfaceClass->StatusData.PhysicalKeyMode;
    m102ia = M102IA::Instance();
    connect(m102ia,SIGNAL(PhysicalKeySignal(bool&)),this,SLOT(slotPhysicalKeySignal(bool&)));

}

HmiAdaptor::~HmiAdaptor()
{

}

void HmiAdaptor::recvFromJs(QString indexId)
{
    emit signalRecvFromJs(indexId);
}

void HmiAdaptor::setTestSpliceId(int spliceId)
{
    testSpliceId = spliceId;
}

int HmiAdaptor::getTestSpliceId()
{
    int id;
    id = testSpliceId;
    return id;
}

void HmiAdaptor::setEditWireId(int wireId)
{
    editWireId = wireId;
}

int HmiAdaptor::getEditWireId()
{
    int id;
    id = editWireId;
    return id;
}

void HmiAdaptor::setEditPartId(int partId)
{
    editPartId = partId;
}

int HmiAdaptor::getEditPartId()
{
    int id;
    id = editPartId;
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

void HmiAdaptor::advancedMaintenanceRecall()
{
    advanceMaintenance->RecallAdvancedParameter();
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
        case 1:
            value = maintenanceCount->CurrentMaintenanceCounter.HornPartNumber;
            break;
        case 2:
            value = maintenanceCount->CurrentMaintenanceCounter.HornCurrentCount;
            break;
        case 3:
            value = maintenanceCount->CurrentMaintenanceCounter.HornCurrentEnergy;
            break;
        case 4:
            value = maintenanceCount->CurrentMaintenanceCounter.HornCounterLimit.Current;
            break;
        case 5:
            value = maintenanceCount->CurrentMaintenanceCounter.HornEnergyLimit.Current;
            break;
        case 6:
            value = maintenanceCount->CurrentMaintenanceCounter.HornDateStarted;
            break;
        case 7:
            value = maintenanceCount->CurrentMaintenanceCounter.HornCounterLimit.Maximum;
            break;
        case 8:
            value = maintenanceCount->CurrentMaintenanceCounter.HornCounterLimit.Minimum;
            break;
        case 9:
            value = maintenanceCount->CurrentMaintenanceCounter.HornEnergyLimit.Maximum;
            break;
        case 10:
            value = maintenanceCount->CurrentMaintenanceCounter.HornEnergyLimit.Minimum;
            break;
        case 11:
            bResult = maintenanceCount->CurrentMaintenanceCounter.HornCounter80PercentAlarm;
            if(bResult == true)
                value = "left";
            else
                value = "right";
            break;
        case 12:
            bResult = maintenanceCount->CurrentMaintenanceCounter.HornEnergy80PercentAlarm;
            if(bResult == true)
                value = "left";
            else
                value = "right";
            break;
        case 13:
            bResult = maintenanceCount->CurrentMaintenanceCounter.HornCounter100PercentLock;
            if(bResult == true)
                value = "left";
            else
                value = "right";
            break;
        case 14:
            bResult = maintenanceCount->CurrentMaintenanceCounter.HornEnergy100PercentLock;
            if(bResult == true)
                value = "left";
            else
                value = "right";
            break;
        default:
            break;
        }
    }
    else if (code == 1)
    {
        switch (index) {
        case 1:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilPartNumber;
            break;
        case 2:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilCurrentCount;
            break;
        case 3:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilCurrentEnergy;
            break;
        case 4:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilCounterLimit.Current;
            break;
        case 5:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilEnergyLimit.Current;
            break;
        case 6:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilDateStarted;
            break;
        case 7:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilCounterLimit.Maximum;
            break;
        case 8:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilCounterLimit.Minimum;
            break;
        case 9:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilEnergyLimit.Maximum;
            break;
        case 10:
            value = maintenanceCount->CurrentMaintenanceCounter.AnvilEnergyLimit.Minimum;
            break;
        case 11:
            bResult = maintenanceCount->CurrentMaintenanceCounter.AnvilCounter80PercentAlarm;
            if(bResult == true)
                value = "left";
            else
                value = "right";
            break;
        case 12:
            bResult = maintenanceCount->CurrentMaintenanceCounter.AnvilEnergy80PercentAlarm;
            if(bResult == true)
                value = "left";
            else
                value = "right";
            break;
        case 13:
            bResult = maintenanceCount->CurrentMaintenanceCounter.AnvilCounter100PercentLock;
            if(bResult == true)
                value = "left";
            else
                value = "right";
            break;
        case 14:
            bResult = maintenanceCount->CurrentMaintenanceCounter.AnvilEnergy100PercentLock;
            if(bResult == true)
                value = "left";
            else
                value = "right";
            break;
        default:
            break;
        }
    }
    else if (code == 2)
    {
        switch (index) {
        case 1:
            value = maintenanceCount->CurrentMaintenanceCounter.GatherPartNumber;
            break;
        case 2:
            value = maintenanceCount->CurrentMaintenanceCounter.GatherCurrentCount;
            break;
        case 3:
            value = maintenanceCount->CurrentMaintenanceCounter.GatherCurrentEnergy;
            break;
        case 4:
            value = maintenanceCount->CurrentMaintenanceCounter.GatherCounterLimit.Current;
            break;
        case 5:
            value = maintenanceCount->CurrentMaintenanceCounter.GatherEnergyLimit.Current;
            break;
        case 6:
            value = maintenanceCount->CurrentMaintenanceCounter.GatherDateStarted;
            break;
        case 7:
            value = maintenanceCount->CurrentMaintenanceCounter.GatherCounterLimit.Maximum;
            break;
        case 8:
            value = maintenanceCount->CurrentMaintenanceCounter.GatherCounterLimit.Minimum;
            break;
        case 9:
            value = maintenanceCount->CurrentMaintenanceCounter.GatherEnergyLimit.Maximum;
            break;
        case 10:
            value = maintenanceCount->CurrentMaintenanceCounter.GatherEnergyLimit.Minimum;
            break;
        case 11:
            bResult = maintenanceCount->CurrentMaintenanceCounter.GatherCounter80PercentAlarm;
            if(bResult == true)
                value = "left";
            else
                value = "right";
            break;
        case 12:
            bResult = maintenanceCount->CurrentMaintenanceCounter.GatherEnergy80PercentAlarm;
            if(bResult == true)
                value = "left";
            else
                value = "right";
            break;
        case 13:
            bResult = maintenanceCount->CurrentMaintenanceCounter.GatherCounter100PercentLock;
            if(bResult == true)
                value = "left";
            else
                value = "right";
            break;
        case 14:
            bResult = maintenanceCount->CurrentMaintenanceCounter.GatherEnergy100PercentLock;
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
        case 1:
            value = maintenanceCount->CurrentMaintenanceCounter.GuidePartNumber;
            break;
        case 2:
            value = maintenanceCount->CurrentMaintenanceCounter.GuideCurrentCount;
            break;
        case 3:
            value = maintenanceCount->CurrentMaintenanceCounter.GuideCurrentEnergy;
            break;
        case 4:
            value = maintenanceCount->CurrentMaintenanceCounter.GuideCounterLimit.Current;
            break;
        case 5:
            value = maintenanceCount->CurrentMaintenanceCounter.GuideEnergyLimit.Current;
            break;
        case 6:
            value = maintenanceCount->CurrentMaintenanceCounter.GuideDateStarted;
            break;
        case 7:
            value = maintenanceCount->CurrentMaintenanceCounter.GuideCounterLimit.Maximum;
            break;
        case 8:
            value = maintenanceCount->CurrentMaintenanceCounter.GuideCounterLimit.Minimum;
            break;
        case 9:
            value = maintenanceCount->CurrentMaintenanceCounter.GuideEnergyLimit.Maximum;
            break;
        case 10:
            value = maintenanceCount->CurrentMaintenanceCounter.GuideEnergyLimit.Minimum;
            break;
        case 11:
            bResult = maintenanceCount->CurrentMaintenanceCounter.GuideCounter80PercentAlarm;
            if(bResult == true)
                value = "left";
            else
                value = "right";
            break;
        case 12:
            bResult = maintenanceCount->CurrentMaintenanceCounter.GuideEnergy80PercentAlarm;
            if(bResult == true)
                value = "left";
            else
                value = "right";
            break;
        case 13:
            bResult = maintenanceCount->CurrentMaintenanceCounter.GuideCounter100PercentLock;
            if(bResult == true)
                value = "left";
            else
                value = "right";
            break;
        case 14:
            bResult = maintenanceCount->CurrentMaintenanceCounter.GuideEnergy100PercentLock;
            if(bResult == true)
                value = "left";
            else
                value = "right";
            break;
        default:
            break;
        }
    }
    else if (code == 4)
    {
        switch (index) {
        case 2:
            value = maintenanceCount->CurrentMaintenanceCounter.ActuatorCurrentCount;
            break;
        case 6:
            value = maintenanceCount->CurrentMaintenanceCounter.ActuatorDateStarted;
            break;
        default:
            break;
        }
    }
//    else if (code == 5)
//    {
//        switch (index) {
//        case 2:
//            value = "-";
//            break;
//        case 3:
//            value = maintenanceCount->CurrentMaintenanceCounter.ActuatorCurrentCount;
//            break;
//        case 4:
//            value = maintenanceCount->CurrentMaintenanceCounter.ActuatorDateStarted;
//            break;
//        case 5:
//            value = "-";
//            break;
//        case 6:
//            value = "-";
//            break;
//        default:
//            break;
//        }
//    }
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
        source = "qrc:/images/images/Anvil_Guide.JPG";
        break;
    case 4:
        source = "qrc:/images/images/Actuator.JPG";
        break;
    default:
        break;
    }
    return source;
}

QString HmiAdaptor::getMaintenanceVerson(int index)
{
    QString value = "";
//    switch (index) {
//    case 0:
//        value = maintenanceCount->CurrentMaintenanceCounter.ActuatorPartNumber;
//        break;
//    case 1:
//        value = maintenanceCount->CurrentMaintenanceCounter.ActuatorSoftwareVersion;
//        if(value.isEmpty() == true)
//            value = QObject::tr("Actuator not online!");
//        break;
//    case 2:
//        value = maintenanceCount->CurrentMaintenanceCounter.ActuatorSerialNumber;
//        break;
//    case 3:
//        value = maintenanceCount->CurrentMaintenanceCounter.ActuatorModuleNumber;
//        break;
//    default:
//        break;
//    }
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
        if(value.isEmpty() == true)
            value = QObject::tr("Controller not online!");
        break;
    case 5:
        value = _Interface->CurrentVersions.SoftwareVersion;
        qDebug()<<"Software Version"<<value;
        break;
    case 6:
        value = _Interface->CurrentVersions.ActuatorVersion;
        if(value.isEmpty() == true)
            value = QObject::tr("Actuator not online!");
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
    qDebug() << code;
    if (code == "Horn")
        maintenanceCount->_execute(MaintenanceLogElement::HORN_COUNT_RESET);
    else if (code == "Anvil")
        maintenanceCount->_execute(MaintenanceLogElement::ANVIL_COUNT_RESET);
    else if (code == "Gather")
        maintenanceCount->_execute(MaintenanceLogElement::GATHER_COUNT_RESET);
    else if (code == "Guide")
        maintenanceCount->_execute(MaintenanceLogElement::GUIDE_COUNT_RESET);
}

void HmiAdaptor::maintenanceCountSetLimit(QString code, QString value)
{
    if (code == "Horn")
    {
        maintenanceCount->CurrentMaintenanceCounter.HornCounterLimit.Current = value;
        maintenanceCount->_execute(MaintenanceLogElement::HORN_COUNT_LIMIT);
    }
    else if (code == "Anvil")
    {
        maintenanceCount->CurrentMaintenanceCounter.AnvilCounterLimit.Current = value;
        maintenanceCount->_execute(MaintenanceLogElement::ANVIL_COUNT_LIMIT);
    }
    else if (code == "Gather")
    {
        maintenanceCount->CurrentMaintenanceCounter.GatherCounterLimit.Current = value;
        maintenanceCount->_execute(MaintenanceLogElement::GATHER_COUNT_LIMIT);
    }
    else if (code == "Guide")
    {
        maintenanceCount->CurrentMaintenanceCounter.GuideCounterLimit.Current = value;
        maintenanceCount->_execute(MaintenanceLogElement::GUIDE_COUNT_LIMIT);
    }
}

void HmiAdaptor::maintenanceCount80PercentAlarm(QString code, QString value)
{
//    listModel.append({mytitle:qsTr("Horn")})
//    listModel.append({mytitle:qsTr("Anvil")})
//    listModel.append({mytitle:qsTr("Gather")})
//    listModel.append({mytitle:qsTr("Guide")})
    UNUSED(value);
    if (code == "Horn") {
        if (value == "switch1")
            maintenanceCount->_execute(MaintenanceLogElement::HORN_COUNT_80PERCENT_ALARM);
        else if (value == "switch2")
            maintenanceCount->_execute(MaintenanceLogElement::HORN_ENERGY_80PERCENT_ALARM);
        else if (value == "switch3")
            maintenanceCount->_execute(MaintenanceLogElement::HORN_COUNT_100PERCENT_LOCK);
        else if (value == "switch4")
            maintenanceCount->_execute(MaintenanceLogElement::HORN_ENERGY_100PERCENT_LOCK);
    }
    else if (code == "Anvil") {
        if (value == "switch1")
            maintenanceCount->_execute(MaintenanceLogElement::ANVIL_COUNT_80PERCENT_ALARM);
        else if (value == "switch2")
            maintenanceCount->_execute(MaintenanceLogElement::ANVIL_ENERGY_80PERCENT_ALARM);
        else if (value == "switch3")
            maintenanceCount->_execute(MaintenanceLogElement::HORN_COUNT_100PERCENT_LOCK);
        else if (value == "switch4")
            maintenanceCount->_execute(MaintenanceLogElement::HORN_ENERGY_100PERCENT_LOCK);
    }
    else if (code == "Gather") {
        if (value == "switch1")
            maintenanceCount->_execute(MaintenanceLogElement::GATHER_COUNT_80PERCENT_ALARM);
        else if (value == "switch2")
            maintenanceCount->_execute(MaintenanceLogElement::GATHER_ENERGY_80PERCENT_ALARM);
        else if (value == "switch3")
            maintenanceCount->_execute(MaintenanceLogElement::GATHER_COUNT_100PERCENT_LOCK);
        else if (value == "switch4")
            maintenanceCount->_execute(MaintenanceLogElement::GATHER_ENERGY_100PERCENT_LOCK);
    }
    else if (code == "Guide") {
        if (value == "switch1")
            maintenanceCount->_execute(MaintenanceLogElement::GUIDE_COUNT_80PERCENT_ALARM);
        else if (value == "switch2")
            maintenanceCount->_execute(MaintenanceLogElement::GUIDE_ENERGY_80PERCENT_ALARM);
        else if (value == "switch3")
            maintenanceCount->_execute(MaintenanceLogElement::GUIDE_COUNT_100PERCENT_LOCK);
        else if (value == "switch4")
            maintenanceCount->_execute(MaintenanceLogElement::GUIDE_ENERGY_100PERCENT_LOCK);

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

QString HmiAdaptor::getAdvancedMaintenanceValue(int index, QString key)
{
    QString ValueStr;
    if (key == "current")
        ValueStr = advanceMaintenance->AdvParameter[index].Current;
    else if (key == "max")
        ValueStr = advanceMaintenance->AdvParameter[index].Maximum;
    else if (key == "min")
        ValueStr = advanceMaintenance->AdvParameter[index].Minimum;
    return ValueStr;
}

void HmiAdaptor::setAdvancedMaintenanceValue(int index, QString value)
{
//    advanceMaintenance->AdvParameter[index].Current = value;
    switch(index)
    {
    case AdvancedMaintenance::AMPLITUDE:
        advanceMaintenance->AmplitudeSetText(value);
        break;
    case AdvancedMaintenance::POWER:
        advanceMaintenance->PowerSetText(value);
        break;
    case AdvancedMaintenance::TUNEPOINT:
        advanceMaintenance->TunePointText(value);
        break;
    case AdvancedMaintenance::FREQOFFSET:
        advanceMaintenance->FrequencyOffsetText(value);
        break;
    default:
        break;
    }
}

int HmiAdaptor::getAdvancedMaintenanceMaxPower()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    return (int)_Interface->StatusData.Soft_Settings.SonicGenWatts;
}

void HmiAdaptor::pressedAdvancedMaintenanceSonics()
{
    advanceMaintenance->RunSonicsPressed();
}

void HmiAdaptor::pressedAdvancedMaintenance100Sonics()
{
    advanceMaintenance->RunSonics100Pressed();
}

void HmiAdaptor::releasedAdvancedMaintenanceSonics()
{
    advanceMaintenance->RunSonicsUnPressed();
}

void HmiAdaptor::releasedAdvancedMaintenance100Sonics()
{
    advanceMaintenance->RunSonics100UnPressed();
}

bool HmiAdaptor::login(QString passwd)
{
    OperatorElement myOperator;
    bool isLog = operatorModel->login(passwd, &myOperator);
    qDebug() << isLog << (int)myOperator.PermissionLevel;
    if (isLog)
    {
        if (myOperator.PermissionLevel == OperatorElement::PHYKEY) {
            if (isLog && !bIsPhysicalKey)
                emit signalPhysicalKeyMessage();
            isLog = isLog & bIsPhysicalKey;
        }
        if (isLog)
            interfaceClass->CurrentOperator = myOperator;
    }
//    else
//    {
//        if (passwd == "0000")
//            isLog = true;
//    }

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
        if (funcIndex == -1) {
            if (myOperator.PermissionLevel != OperatorElement::PHYKEY)
                return true;
            else if (myOperator.PermissionLevel == OperatorElement::PHYKEY)
                return bIsPhysicalKey;
        }
        levelIndex = (int)myOperator.PermissionLevel;
        if (levelIndex == 1)
            reb = permissionSetting->CurrentPermissionList.at(funcIndex).Level1;
        else if (levelIndex == 2)
            reb = permissionSetting->CurrentPermissionList.at(funcIndex).Level2;
        else if (levelIndex == 3)
            reb = permissionSetting->CurrentPermissionList.at(funcIndex).Level3;
        else if (levelIndex == 4)
            reb = permissionSetting->CurrentPermissionList.at(funcIndex).Level4;
        else if (levelIndex == 0) {
            reb = permissionSetting->CurrentPermissionList.at(funcIndex).PhyKey;
            if (!bIsPhysicalKey)
                emit signalPhysicalKeyMessage();
            reb = bIsPhysicalKey;
        }
        if (reb)
            interfaceClass->CurrentOperator = myOperator;
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

void HmiAdaptor::hornCalibrationComplete(QString AmplitudeStr)
{
    int iAmplitude = m_stringToVariant->AmplitudeToInt(AmplitudeStr);
    calibration->HornCalibrationComplete(iAmplitude);
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
    QString type = source.right(4);
    QString toPath = TOPATH + QDateTime::currentDateTime().toString("yyMMddhhmmss") + type;
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
        return false;
    levelIndex = (int)interfaceClass->CurrentOperator.PermissionLevel;

    if (levelIndex == 0)
        reb = permissionSetting->CurrentPermissionList.at(funcIndex).PhyKey;
    else if (levelIndex == 1)
        reb = permissionSetting->CurrentPermissionList.at(funcIndex).Level1;
    else if (levelIndex == 2)
        reb = permissionSetting->CurrentPermissionList.at(funcIndex).Level2;
    else if (levelIndex == 3)
        reb = permissionSetting->CurrentPermissionList.at(funcIndex).Level3;
    else if (levelIndex == 4)
        reb = permissionSetting->CurrentPermissionList.at(funcIndex).Level4;

    qDebug() << "needPassWord" << pageName << funcIndex << levelIndex << reb;
    return !reb;
}

QStringList HmiAdaptor::permissionsettingGetValue(QString code)
{
    QStringList currentIdentifier;
    currentIdentifier.empty();
    if (code == "AllFunctionNameList")
        currentIdentifier = permissionSetting->AllFunctionNameList;
    else if (code == "FourLevelIdentifier")
        currentIdentifier = permissionSetting->FiveLevelIdentifier;
    else if (code == "CurrentIdentifier"){
        for (int i = 0; i < permissionSetting->CurrentPermissionList.count(); i++)
        {
            currentIdentifier << permissionSetting->CurrentPermissionList.at(i).Identifier;
        }
    }
    return currentIdentifier;
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
    case 0:
        reb = permissionSetting->CurrentPermissionList.at(index).PhyKey;
        break;
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

bool HmiAdaptor::permissionsettingSetValue(QString name, bool level1, bool level2, bool level3, bool level4,bool level5)
{
    PermissionSettingForScreen temp;
    temp.Identifier = name;
    temp.Level1 = level1;
    temp.Level2 = level2;
    temp.Level3 = level3;
    temp.Level4 = level4;
    temp.PhyKey = level5;
    permissionSetting->CurrentPermissionList.append(temp);
    return true;
}

bool HmiAdaptor::permissionsettingSetFourValue(QStringList fourName)
{
    permissionSetting->FiveLevelIdentifier = fourName;
    return true;
}

bool HmiAdaptor::weldDefaultsExecute(QString code)
{
    if (code == "_Recall")
        return weldDefaults->_Recall();
    else if (code == "_Set") {
        return weldDefaults->_Set();
    }
    else if (code == "_Default"){
        weldDefaults->_Default();
    }
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
        if (weldDefaults->CurrentWeldSettings.CurrentCoolingMode == Status_Data::ENERGYMODE)
            reb = true;
        else if (weldDefaults->CurrentWeldSettings.CurrentCoolingMode == Status_Data::OFF)
            reb = false;
        else if (weldDefaults->CurrentWeldSettings.CurrentCoolingMode == Status_Data::ON)
            reb = true;
    }
    else if (index == "cooling(1sec/100J)") {
        if (weldDefaults->CurrentWeldSettings.CurrentCoolingMode == Status_Data::ENERGYMODE)
            reb = true;
        else if (weldDefaults->CurrentWeldSettings.CurrentCoolingMode == Status_Data::OFF)
            reb = false;
        else if (weldDefaults->CurrentWeldSettings.CurrentCoolingMode == Status_Data::ON)
            reb = false;
    }
    else if (index == "Cooling Tooling")
        reb = weldDefaults->CurrentWeldSettings.CoolingForTooling;
    else if (index == "Unit Conversion")
        reb = weldDefaults->CurrentWeldSettings.Square2Unit;
    else if (index == "Graph Data Sampling 1ms")
        reb = weldDefaults->CurrentWeldSettings.SampleRatio == WeldResultElement::SampleWith1ms ? true : false;
    else if (index == "Graph Data Sampling 5ms")
        reb = weldDefaults->CurrentWeldSettings.SampleRatio == WeldResultElement::SampleWith5ms ? true : false;
    else if (index == "Graph Data Sampling 10ms")
        reb = weldDefaults->CurrentWeldSettings.SampleRatio == WeldResultElement::SampleWith10ms ? true : false;
    else if (index == "Graph Data Sampling 20ms")
        reb = weldDefaults->CurrentWeldSettings.SampleRatio == WeldResultElement::SampleWith20ms ? true : false;
    return reb;
}

QStringList HmiAdaptor::weldDefaultsGetValue(int index)
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
    weldDefaults->CurrentWeldSettings.SampleRatio = (WeldResultElement::SAMPLERATIO)sampleIndex;
    weldDefaults->CurrentWeldSettings.CurrentCoolingDur.Current = coolingDur;
    weldDefaults->CurrentWeldSettings.CurrentCoolingDel.Current = coolingDel;

    weldDefaults->CurrentWeldSettings.WidthEncoder = boolList[0];
    weldDefaults->CurrentWeldSettings.HeightEncoder = boolList[1];
    weldDefaults->CurrentWeldSettings.FootPedalAbort = boolList[2];
    weldDefaults->CurrentWeldSettings.Seek = boolList[3];
    if (!boolList[4])
    {
        weldDefaults->CurrentWeldSettings.CurrentCoolingMode = Status_Data::OFF;
        weldDefaults->CurrentWeldSettings.CoolingForTooling = false;
    }
    else if (boolList[4])
    {
        if (boolList[5])
            weldDefaults->CurrentWeldSettings.CurrentCoolingMode = Status_Data::ENERGYMODE;
        else
            weldDefaults->CurrentWeldSettings.CurrentCoolingMode = Status_Data::ON;
        weldDefaults->CurrentWeldSettings.CoolingForTooling = boolList[6];
    }
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR1].Range.Current = strList[0];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR1].Offset.Current = strList[1];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR1].Multiplier.Current = strList[2];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR2].Range.Current = strList[3];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR2].Offset.Current = strList[4];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR2].Multiplier.Current = strList[5];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR3].Range.Current = strList[6];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR3].Offset.Current = strList[7];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR3].Multiplier.Current = strList[8];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR4].Range.Current = strList[9];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR4].Offset.Current = strList[10];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR4].Multiplier.Current = strList[11];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR1].Range.Current = strList[12];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR1].Offset.Current = strList[13];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR1].Multiplier.Current = strList[14];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR2].Range.Current = strList[15];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR2].Offset.Current = strList[16];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR2].Multiplier.Current = strList[17];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR3].Range.Current = strList[18];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR3].Offset.Current = strList[19];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR3].Multiplier.Current = strList[20];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR4].Range.Current = strList[21];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR4].Offset.Current = strList[22];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR4].Multiplier.Current = strList[23];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR1].Range.Current = strList[24];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR1].Offset.Current = strList[25];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR1].Multiplier.Current = strList[26];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR2].Range.Current = strList[27];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR2].Offset.Current = strList[28];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR2].Multiplier.Current = strList[29];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR3].Range.Current = strList[30];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR3].Offset.Current = strList[31];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR3].Multiplier.Current = strList[32];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR4].Range.Current = strList[33];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR4].Offset.Current = strList[34];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR4].Multiplier.Current = strList[35];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR1].Range.Current = strList[36];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR1].Offset.Current = strList[37];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR1].Multiplier.Current = strList[38];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR2].Range.Current = strList[39];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR2].Offset.Current = strList[40];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR2].Multiplier.Current = strList[41];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR3].Range.Current = strList[42];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR3].Offset.Current = strList[43];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR3].Multiplier.Current = strList[44];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR4].Range.Current = strList[45];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR4].Offset.Current = strList[46];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR4].Multiplier.Current = strList[47];

    return true;
}

bool HmiAdaptor::weldDefaultsSetValue2(int index, int checkIndex)
{
    if (index == 0)
        weldDefaults->CurrentWeldSettings.Pressure2Unit = (BRANSON_INI_STRUCT::PRESSUREUNIT)checkIndex;
    else if (index == 1)
        weldDefaults->CurrentWeldSettings.Square2Unit = (BRANSON_INI_STRUCT::SQUAREUNIT)checkIndex;
    else if (index == 2)
        weldDefaults->CurrentWeldSettings.Length2Unit = (BRANSON_INI_STRUCT::LENGTHUNIT)checkIndex;
    return true;
}

bool HmiAdaptor::weldDefaultsGetValue2(int index, int checkIndex)
{
    bool bResult = false;
    if (index == 0)
    {
        if (checkIndex == 0)
        {
            if(weldDefaults->CurrentWeldSettings.Pressure2Unit == BRANSON_INI_STRUCT::PRESSUREUNIT::ToPSI)
                bResult = true;
            else
                bResult = false;
        }
        else if (checkIndex == 1)
        {
            if(weldDefaults->CurrentWeldSettings.Pressure2Unit == BRANSON_INI_STRUCT::PRESSUREUNIT::ToBar)
                bResult = true;
            else
                bResult = false;
        }
    }
    else if (index == 1)
    {
        if (checkIndex == 0)
        {
            if(weldDefaults->CurrentWeldSettings.Square2Unit == BRANSON_INI_STRUCT::SQUAREUNIT::ToSqrMM)
                bResult = true;
            else
                bResult = false;
        }
        else if (checkIndex == 1)
        {
            if(weldDefaults->CurrentWeldSettings.Square2Unit == BRANSON_INI_STRUCT::SQUAREUNIT::ToAWG)
                bResult = true;
            else
                bResult = false;
        }
    }
    else if (index == 2)
    {
        if (checkIndex == 0)
        {
            if(weldDefaults->CurrentWeldSettings.Length2Unit == BRANSON_INI_STRUCT::LENGTHUNIT::ToMM)
                bResult = true;
            else
                bResult = false;
        }
        else if (checkIndex == 1)
        {
            if(weldDefaults->CurrentWeldSettings.Length2Unit == BRANSON_INI_STRUCT::LENGTHUNIT::ToINCH)
                bResult = true;
            else
                bResult = false;
        }
    }
    return bResult;
}

bool HmiAdaptor::weldDefaultsSetValue3(QStringList strList)
{
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR1].Range.Current = strList[0];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR1].Offset.Current = strList[1];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR1].Multiplier.Current = strList[2];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR2].Range.Current = strList[3];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR2].Offset.Current = strList[4];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR2].Multiplier.Current = strList[5];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR3].Range.Current = strList[6];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR3].Offset.Current = strList[7];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR3].Multiplier.Current = strList[8];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR4].Range.Current = strList[9];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR4].Offset.Current = strList[10];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[EnergyR4].Multiplier.Current = strList[11];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR1].Range.Current = strList[12];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR1].Offset.Current = strList[13];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR1].Multiplier.Current = strList[14];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR2].Range.Current = strList[15];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR2].Offset.Current = strList[16];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR2].Multiplier.Current = strList[17];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR3].Range.Current = strList[18];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR3].Offset.Current = strList[19];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR3].Multiplier.Current = strList[20];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR4].Range.Current = strList[21];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR4].Offset.Current = strList[22];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[WidthR4].Multiplier.Current = strList[23];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR1].Range.Current = strList[24];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR1].Offset.Current = strList[25];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR1].Multiplier.Current = strList[26];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR2].Range.Current = strList[27];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR2].Offset.Current = strList[28];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR2].Multiplier.Current = strList[29];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR3].Range.Current = strList[30];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR3].Offset.Current = strList[31];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR3].Multiplier.Current = strList[32];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR4].Range.Current = strList[33];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR4].Offset.Current = strList[34];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[PressureR4].Multiplier.Current = strList[35];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR1].Range.Current = strList[36];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR1].Offset.Current = strList[37];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR1].Multiplier.Current = strList[38];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR2].Range.Current = strList[39];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR2].Offset.Current = strList[40];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR2].Multiplier.Current = strList[41];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR3].Range.Current = strList[42];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR3].Offset.Current = strList[43];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR3].Multiplier.Current = strList[44];

    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR4].Range.Current = strList[45];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR4].Offset.Current = strList[46];
    weldDefaults->CurrentWeldSettings.WeldSettingFormula[AmplitudeR4].Multiplier.Current = strList[47];

    return true;
}

bool HmiAdaptor::weldDefaultFormulaUpdate()
{
    weldDefaults->FormulaUpdate();
    return true;
}

QString HmiAdaptor::weldDefaultsGetCutterNum(QString key, QString index)
{
    QString value;
    if (key == "Load Time")
    {
        if (index == "current")
            value = m_variantToString->CutOffSpliceTimeToString(weldDefaults->CurrentWeldSettings.CutOffOption.CutOffSpliceTime).Current;
        else if (index == "max")
            value = m_variantToString->CutOffSpliceTimeToString(weldDefaults->CurrentWeldSettings.CutOffOption.CutOffSpliceTime).Maximum;
        else if (index == "min")
            value = m_variantToString->CutOffSpliceTimeToString(weldDefaults->CurrentWeldSettings.CutOffOption.CutOffSpliceTime).Minimum;
    }
    else if (key == "Unload Time")
    {
        if (index == "current")
        {
            value = m_variantToString->AntiSideSpliceTimeToString(weldDefaults->
                    CurrentWeldSettings.AntiSideOption.AntiSideSpliceTime).Current;
        }
        else if (index == "max")
        {
            value = m_variantToString->AntiSideSpliceTimeToString(weldDefaults->
                    CurrentWeldSettings.AntiSideOption.AntiSideSpliceTime).Maximum;
        }
        else if (index == "min")
        {
            value = m_variantToString->AntiSideSpliceTimeToString(weldDefaults->
                    CurrentWeldSettings.AntiSideOption.AntiSideSpliceTime).Minimum;
        }
    }
    else if (key == "Cut Off")
    {
        if (weldDefaults->CurrentWeldSettings.CutOffOption.CutOff)
            value = "left";
        else
            value = "right";
    }
    else if (key == "Anti-Side")
    {
        if (weldDefaults->CurrentWeldSettings.AntiSideOption.AntiSideMode)
            value = "left";
        else
            value = "right";
    }
    else if (key == "Time")
    {
        if (weldDefaults->CurrentWeldSettings.CutOffOption.Cutter4TimeAlarm)
            value = "left";
        else
            value = "right";
    }
    else if (key == "Peak Power")
    {
        if (weldDefaults->CurrentWeldSettings.CutOffOption.Cutter4PowerAlarm)
            value = "left";
        else
            value = "right";
    }
    else if (key == "Pre-Height")
    {
        if (weldDefaults->CurrentWeldSettings.CutOffOption.Cutter4PreHeightAlarm)
            value = "left";
        else
            value = "right";
    }
    else if (key == "Post-Height")
    {
        if (weldDefaults->CurrentWeldSettings.CutOffOption.Cutter4HeightAlarm)
            value = "left";
        else
            value = "right";
    }
    return value;
}

void HmiAdaptor::weldDefaultsSetCutterNum(QString key, QString index)
{
    if (key == "Load Time")
    {
        weldDefaults->CurrentWeldSettings.CutOffOption.CutOffSpliceTime =
                m_stringToVariant->CutOffSpliceTimeToInt(index);
    }
    else if (key == "Unload Time")
    {
         weldDefaults->CurrentWeldSettings.AntiSideOption.AntiSideSpliceTime =
                 m_stringToVariant->AntiSideSpliceTimeToInt(index);
    }
    else if (key == "Cut Off")
    {
        if (index == "left")
            weldDefaults->CurrentWeldSettings.CutOffOption.CutOff = true;
        else
            weldDefaults->CurrentWeldSettings.CutOffOption.CutOff = false;
    }
    else if (key == "Anti-Side")
    {
        if (index == "left")
            weldDefaults->CurrentWeldSettings.AntiSideOption.AntiSideMode = true;
        else
            weldDefaults->CurrentWeldSettings.AntiSideOption.AntiSideMode = false;
    }
    else if (key == "Time")
    {
        if (index == "left")
            weldDefaults->CurrentWeldSettings.CutOffOption.Cutter4TimeAlarm = true;
        else
            weldDefaults->CurrentWeldSettings.CutOffOption.Cutter4TimeAlarm = false;
    }
    else if (key == "Peak Power")
    {
        if (index == "left")
            weldDefaults->CurrentWeldSettings.CutOffOption.Cutter4PowerAlarm = true;
        else
            weldDefaults->CurrentWeldSettings.CutOffOption.Cutter4PowerAlarm = false;
    }
    else if (key == "Pre-Height")
    {
        if (index == "left")
            weldDefaults->CurrentWeldSettings.CutOffOption.Cutter4PreHeightAlarm = true;
        else
            weldDefaults->CurrentWeldSettings.CutOffOption.Cutter4PreHeightAlarm = false;
    }
    else if (key == "Post-Height")
    {
        if (index == "left")
            weldDefaults->CurrentWeldSettings.CutOffOption.Cutter4HeightAlarm = true;
        else
            weldDefaults->CurrentWeldSettings.CutOffOption.Cutter4HeightAlarm = false;
    }
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
        reb = dataCommunication->CurrentDataCommunication.EthernetModeEnable;
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
        for (int i = 0; i < interfaceClass->StatusData.ShrinkTubeDefaults.size();i++)
        {
            list << interfaceClass->StatusData.ShrinkTubeDefaults.at(i).Name
                 << m_variantToString->ShrinkTemperatureToString(interfaceClass->StatusData.ShrinkTubeDefaults.at(i).temp).Current
                 << m_variantToString->ShrinkTimeToString(interfaceClass->StatusData.ShrinkTubeDefaults.at(i).Time).Current;
        }
    }
//    else if (index == "shrinkLimit")
//    {
//        list << dataCommunication->CurrentDataCommunication.MaxmmTemp
//             << dataCommunication->CurrentDataCommunication.MinmmTemp
//             << dataCommunication->CurrentDataCommunication.MaxmmTime
//             << dataCommunication->CurrentDataCommunication.MinmmTime;
//    }
    return list;
}

bool HmiAdaptor::dataCommunicationSetValue(QList<bool> boolList, QStringList strList, QString ip, QString port)
{
    UNUSED(strList);
    UNUSED(ip);
    dataCommunication->CurrentDataCommunication.EthernetModeEnable = boolList[0];
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

void HmiAdaptor::dataCommunicationShrinkTubeTesting()
{
    dataCommunication->ShrinkTubeTesting();
}

void HmiAdaptor::slotWeldCycleCompleted(bool result)
{
    qDebug() << "slotWeldCycleCompleted in hmiadaptor" << result;
    if (result) {
        alarmModel->weldResultElement = operateProcess->CurrentWeldResult;
        emit signalWeldCycleCompleted(result);

        //        maintenanceCountExecute("_Recall");
//        int count = maintenanceCountGetValue(0,3).toInt();
        emit signalMantenaneceCount(interfaceClass->StatusData.CurrentCountMaintenanceLimits[0]);
    }
}

void HmiAdaptor::slotGetAlarmFlag()
{
    emit alarmModel->signalShowFlag(true);
}

void HmiAdaptor::reboot()
{
    QString program = QCoreApplication::applicationFilePath();
    QStringList arguments = QCoreApplication::arguments();
    QString workingDirectory = QDir::currentPath();
    QProcess::startDetached(program, arguments, workingDirectory);
    QCoreApplication::exit();
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
    UNUSED(MsgBox);
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
    bool reb;
    if (theValue.toFloat(&ok) >= minNum.toFloat(&ok) && theValue.toFloat(&ok) <= maxNum.toFloat(&ok)) {
        reb = true;
    } else {
        reb = false;
    }
    return reb;
}

int HmiAdaptor::timeChangeToInt(QString time)
{
    QDateTime temptime = QDateTime::fromString(time, "yyyy-MM-dd hh:mm:ss");
    return temptime.toTime_t();
}

void HmiAdaptor::setProcess()
{
    operateProcess->CurrentSplice = spliceModel->processPresetElement;
}

void HmiAdaptor::setOperateProcess(int spliceId, bool isText)
{
    m_spliceAdaptor->QueryOneRecordFromTable(spliceId,&operateProcess->CurrentSplice);
//    operateProcess->CurrentNecessaryInfo.IsTestProcess = isText;
//    operateProcess->CurrentNecessaryInfo.CurrentWorkOrder.WorkOrderID = workOrderModel->getStructValue("WorkOrderId").toInt();
//    operateProcess->CurrentNecessaryInfo.CurrentWorkOrder.WorkOrderName = workOrderModel->getStructValue("WorkOrderName").toString();
//    DEBUG_PRINT(operateProcess->CurrentNecessaryInfo.CurrentWorkOrder.WorkOrderName);
//    operateProcess->CurrentNecessaryInfo.CurrentHarness.HarnessID = partModel->getStruceValue("PartId").toInt();
//    operateProcess->CurrentNecessaryInfo.CurrentHarness.HarnessName = partModel->getStruceValue("PartName").toString();

}

void HmiAdaptor::operateProcessExec(QString type)
{
    qDebug() << "operateProcessExec" << type;
    if (type == "Start")
        operateProcess->_start();
    else if (type == "Stop") {
        operateProcess->_stop();
    }
    else if (type == "Execute")
        operateProcess->_execute();
}

int HmiAdaptor::controlLimitProcess(QString type, QList<int> list, int redMax, int redMin)
{
    int upper;
    int lower;
    int iResult = -1;
    if(type == "Time+")
    {
//        operateProcess->ControlLimitProcess(QUALITYTIME,list,redMax,redMin,&upper,&lower);
        iResult = upper;
    }
    else if(type == "Time-")
    {
//        operateProcess->ControlLimitProcess(QUALITYTIME,list,redMax,redMin,&upper,&lower);
        iResult = lower;
    }
    else if(type == "Power+")
    {
//        operateProcess->ControlLimitProcess(QUALITYPOWER,list,redMax,redMin,&upper,&lower);
        qDebug() << "controlLimitProcess" << list << redMax << redMin << upper<< lower;
        iResult = upper;
    }
    else if(type == "Power-")
    {
//        operateProcess->ControlLimitProcess(QUALITYPOWER,list,redMax,redMin,&upper,&lower);
        iResult = lower;
    }
    else if(type == "Pre-Height+")
    {
//        operateProcess->ControlLimitProcess(QUALITYPREHEIGHT,list,redMax,redMin,&upper,&lower);
        iResult = upper;
    }
    else if(type == "Pre-Height-")
    {
//        operateProcess->ControlLimitProcess(QUALITYPREHEIGHT,list,redMax,redMin,&upper,&lower);
        iResult = lower;
    }
    else if(type == "Post-Height+")
    {
//        operateProcess->ControlLimitProcess(QUALITYPOSTHEIGHT,list,redMax,redMin,&upper,&lower);
        iResult = upper;
    }
    else if(type == "Post-Height-")
    {
//        operateProcess->ControlLimitProcess(QUALITYPOSTHEIGHT,list,redMax,redMin,&upper,&lower);
        iResult = lower;
    }
    else
    {
        iResult = -1;
    }
    return iResult;
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

QStringList HmiAdaptor::getWeldActualParameterDataList(int index, int type)
{
    QStringList list;
    if (statisticalTrend->CurrentWeldParameterList.count() == 0) {
        return list;
    }
    if (type == 0)
    {
        list.append(statisticalTrend->CurrentWeldParameterList[index].CrossSection);
        list.append(statisticalTrend->CurrentWeldParameterList[index].Time);
        list.append(statisticalTrend->CurrentWeldParameterList[index].Energy);
        list.append(statisticalTrend->CurrentWeldParameterList[index].PeakPower);
        list.append(statisticalTrend->CurrentWeldParameterList[index].WeldPressure);
        list.append(statisticalTrend->CurrentWeldParameterList[index].PreHeight);
        list.append(statisticalTrend->CurrentWeldParameterList[index].TriggerPressure);
        list.append(statisticalTrend->CurrentWeldParameterList[index].PostHeight);
        list.append(statisticalTrend->CurrentWeldParameterList[index].Amplitude);
        list.append("");

        list.append(statisticalTrend->CurrentWeldParameterList[index].Width);
        list.append("");

    }
    else if (type == 1)
    {
        list.append(statisticalTrend->CurrentWeldParameterList[index].HarnessName);
        list.append(statisticalTrend->CurrentWeldParameterList[index].SequenceName);
        list.append(statisticalTrend->CurrentWeldParameterList[index].DateCreated);
    }
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

int HmiAdaptor::getCurrentStatisticsParameterLimit(QString key, int index)
{
    if (key == "max")
        return statisticalTrend->CurrentStatisticsParameter[index].UpperSpecLimit;
    else if (key == "min")
        return statisticalTrend->CurrentStatisticsParameter[index].LowerSpecLimit;
}

void HmiAdaptor::msgBoxClick(bool clickOK)
{
    if (clickOK && this->func_ptr != NULL && bransonMessageBox._Object != NULL) {
        qDebug() << "msgBoxClick" << this->func_ptr << bransonMessageBox._Object;
        this->func_ptr(bransonMessageBox._Object);
    }
}

QString HmiAdaptor::getDefaultAmplitudeToString(int value, int TypeEnum)
{
    interfaceClass = InterfaceClass::Instance();
    QString ResultStr = "";
    int tmpValue = 0;

    switch(TypeEnum) {
    case CUR_VALUE:
        tmpValue = interfaceClass->StatusData.Soft_Settings.Horn_Calibrate;
        ResultStr = m_variantToString->DefaultAmpToString(tmpValue).Current;
        break;
    case MIN_VALUE:
        ResultStr = m_variantToString->DefaultAmpToString(value).Minimum;
        break;
    case MAX_VALUE:
        ResultStr = m_variantToString->DefaultAmpToString(value).Maximum;
        break;
    default:
        ResultStr = m_variantToString->DefaultAmpToString(0).Current;
    }
    return ResultStr;
}

QString HmiAdaptor::getAmplitudeToString(int value, int TypeEnum)
{
    interfaceClass = InterfaceClass::Instance();
    QString ResultStr = "";
    int tmpValue = 0;

    switch(TypeEnum) {
    case CUR_VALUE:
        tmpValue = interfaceClass->StatusData.Soft_Settings.Horn_Calibrate;
        ResultStr = m_variantToString->AmplitudeToString(tmpValue).Current;
        break;
    case MIN_VALUE:
        ResultStr = m_variantToString->AmplitudeToString(value).Minimum;
        break;
    case MAX_VALUE:
        ResultStr = m_variantToString->AmplitudeToString(value).Maximum;
        break;
    default:
        ResultStr = m_variantToString->AmplitudeToString(0).Current;
    }
    return ResultStr;
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
            importHarness(CSVList[1]);
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
    CSVPresetData *_PresetData = CSVPresetData::Instance();
    int spliceId = _PresetData->ImportData(spliceStr);
    wireModel->setModelList();
    spliceModel->setModelList();
    return spliceId;
}

int HmiAdaptor::importHarness(QString harnessStr)
{
    CSVHarnessData *_HarnessData = CSVHarnessData::Instance();
    int partId = _HarnessData->ImportData(harnessStr);
    wireModel->setModelList();
    spliceModel->setModelList();
    harnessModel->setModelList();
    return partId;
}

int HmiAdaptor::importSequence(QString sequenceStr)
{
    CSVSequenceData *_SequenceData = CSVSequenceData::Instance();
    int sequenceId = _SequenceData->ImportData(sequenceStr);
    wireModel->setModelList();
    spliceModel->setModelList();
    sequenceModel->setModelList();
    return sequenceId;
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
            partIdList.push_back(importHarness(partList[i]));
    }
    for (i = 0; i < partIdList.count();i++)
    {
        if (partIdList[i] != -1)
            tempMap.insert(partIdList[i],harnessModel->getPartName(partIdList[i]));
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

int HmiAdaptor::stringToInt(QString temp)
{
    bool ok;
    return temp.toInt(&ok,10);
}

void HmiAdaptor::setWorkFlow(int workMode, int workId)
{
    interfaceClass->CurrentWorkOrder.WorkOrderMode = (WorkOrderElement::WORKORDERMODE)workMode;
    if (workMode == 0)
    {
        interfaceClass->CurrentWorkOrder.WorkOrderID = workId;
        interfaceClass->CurrentWorkOrder.WorkOrderName = spliceModel->getSpliceName(workId);
        spliceModel->editNew(workId);
        interfaceClass->CurrentWorkOrder.CurrentSpliceIndex = 0;
    }
    else if (workMode == 1)
    {
        interfaceClass->CurrentWorkOrder.WorkOrderID = workId;
        interfaceClass->CurrentWorkOrder.WorkOrderName = sequenceModel->getSequenceName(workId);
        sequenceModel->editNew(workId);
    }
    else if (workMode == 2)
    {
        interfaceClass->CurrentWorkOrder.WorkOrderID = workId;
        interfaceClass->CurrentWorkOrder.WorkOrderName = harnessModel->getPartName(workId);
        harnessModel->editNew(workId);
    }
    else if (workMode == 3)
    {
        interfaceClass->CurrentWorkOrder.WorkOrderID = -1;
        interfaceClass->CurrentWorkOrder.WorkOrderName.clear();
        interfaceClass->CurrentWorkOrder.CreatedDate.clear();
        interfaceClass->CurrentWorkOrder.OperatorID = -1;
        interfaceClass->CurrentWorkOrder.CurrentSpliceIndex = 0;
        interfaceClass->CurrentWorkOrder.BatchSize = 0;
        interfaceClass->CurrentWorkOrder.MissPartList.clear();
        interfaceClass->CurrentWorkOrder.CurrentPartIndex.PartID = 0;
        interfaceClass->CurrentWorkOrder.CurrentPartIndex.PartName.clear();
    }
    interfaceClass->CurrentWorkOrder.WriteWorkOrderToQSetting();
    qDebug() << "setWorkFlow" << workMode << workId;

}

QVariant HmiAdaptor::getWorkFlow(QString workKey)
{
    QVariant value;
    if (workKey == "WorkMode") {
        value = (int)interfaceClass->CurrentWorkOrder.WorkOrderMode;
        if (value == 0)
            spliceModel->editNew(interfaceClass->CurrentWorkOrder.WorkOrderID);
        else if (value == 1) {
            sequenceModel->editNew(interfaceClass->CurrentWorkOrder.WorkOrderID);
            if (interfaceClass->CurrentWorkOrder.CurrentPartIndex.PartID != 0)
                spliceModel->editNew(interfaceClass->CurrentWorkOrder.CurrentPartIndex.PartID);
            else
                spliceModel->editNew(sequenceModel->getSpliceList().at(0));
        }
        else if (value == 2) {
            harnessModel->editNew(interfaceClass->CurrentWorkOrder.WorkOrderID);
            if (interfaceClass->CurrentWorkOrder.CurrentPartIndex.PartID != 0)
                spliceModel->editNew(interfaceClass->CurrentWorkOrder.CurrentPartIndex.PartID);
            else
                spliceModel->editNew(harnessModel->getSpliceList().at(0));

        }
    }
    else if (workKey == "WorkId") {
        value = (int)interfaceClass->CurrentWorkOrder.WorkOrderID;
    }
    else if ((workKey) == "WorkIndex") {
        value = (int)interfaceClass->CurrentWorkOrder.CurrentSpliceIndex;
    }
    qDebug() << "getWorkFlow" << workKey << value;

    return value;
}

void HmiAdaptor::readWorkFlow()
{
    interfaceClass->CurrentWorkOrder.ReadWorkOrderFromQSetting();
}

void HmiAdaptor::setWorkValue(QString key, QString value)
{
    bool ok;
    if (key == "WorkCount") {
        if (value == "-1")
            interfaceClass->CurrentWorkOrder.IsConstrainedFlag = true;
        else
        {
            interfaceClass->CurrentWorkOrder.IsConstrainedFlag = false;
            interfaceClass->CurrentWorkOrder.BatchSize = value.toInt(&ok,10);
        }
    }
    else if (key == "PartCount")
    {
        interfaceClass->CurrentWorkOrder.CurrentSpliceIndex = value.toInt(&ok,10);
    }
    else if (key == "CurrentSplice")
    {
        interfaceClass->CurrentWorkOrder.CurrentPartIndex.PartID = value.toInt(&ok,10);
    }
    else if (key == "MissSplice")
    {

    }
    interfaceClass->CurrentWorkOrder.WriteWorkOrderToQSetting();

    qDebug() << "setWorkValue " << key << value;
}

QVariant HmiAdaptor::getWorkValue(QString workKey)
{
    QVariant value;
    if (workKey == "WorkCount") {
        if (interfaceClass->CurrentWorkOrder.IsConstrainedFlag)
            value = -1;
        else
            value = interfaceClass->CurrentWorkOrder.BatchSize;
    }
    else if (workKey == "PartCount")
    {
        value = interfaceClass->CurrentWorkOrder.CurrentSpliceIndex;
    }
    else if (workKey == "CurrentSplice")
    {
        value = interfaceClass->CurrentWorkOrder.CurrentPartIndex.PartID;
        if (value == 0)
            value = spliceModel->getStructValue("SpliceId","");
    }
    qDebug() << "getWorkValue" << workKey << value;
    return value;
}

QList<int> HmiAdaptor::getWorkMissList()
{
    QMap<int,QString>::iterator it; //遍历map
    QList<int> list;
    for ( it = interfaceClass->CurrentWorkOrder.MissPartList.begin(); it != interfaceClass->CurrentWorkOrder.MissPartList.end(); ++it ) {
        list.append(it.key());
    }
    qDebug() << "getWorkMissList" << list;
    return list;
}

void HmiAdaptor::setWorkMissList(int spliceId)
{
    interfaceClass->CurrentWorkOrder.MissPartList.insert(spliceId,spliceModel->getSpliceName(spliceId));
    interfaceClass->CurrentWorkOrder.WriteWorkOrderToQSetting();
}

QString HmiAdaptor::getUserManualPath()
{
    QString path = QCoreApplication::applicationDirPath();
    path = "file:///" + path + "/usermanual/User Manual.html";
    return path;
}

QString HmiAdaptor::getUserManualCatalog()
{
    QString path = QCoreApplication::applicationDirPath();
    path = "file:///" + path + "/usermanual/Contents.html";
//    return "file:///d:\\mytest.html";
    return path;

}

QString HmiAdaptor::getApplicationDirPathPath()
{
    QString path = QCoreApplication::applicationDirPath();
//    path = "file:///" + path + "/usermanual/Special Double Hit Mode functionality for Delphi Ground Terminal Welder II.html";
    return path;
}

QString HmiAdaptor::getToolChangeFileName(QString filePath)
{
    return filePath.left(filePath.size()-4);
}

void HmiAdaptor::setLanguage(int row, int column)
{
    interfaceClass->StatusData.Soft_Settings.Lang_Support =
            (BRANSON_INI_STRUCT::LangSupport) (row * 7 + column);
    interfaceClass->StatusData.WriteStatusDataToQSetting();
    BransonMessageBox tmpMsgBox;
    tmpMsgBox.MsgPrompt = QObject::tr("All the setting will be avaliable after the system restart.");
    tmpMsgBox.MsgTitle = QObject::tr("Information");
    tmpMsgBox.TipsMode = (OKOnly + Information);
    tmpMsgBox.func_ptr = InterfaceClass::HotRestartSys;
    tmpMsgBox._Object = interfaceClass;
    interfaceClass->cMsgBox(&tmpMsgBox);
}

QString HmiAdaptor::getLanguageImage()
{
    QString source = "qrc:/images/images/us&English.png";
    switch(interfaceClass->StatusData.Soft_Settings.Lang_Support)
    {
    case BRANSON_INI_STRUCT::ENGLISH_lang:    //0 English
        source = "qrc:/images/images/us&English.png";
        break;
    case BRANSON_INI_STRUCT::JAPANESE_Lang:    //1 Japanese
        source = "qrc:/images/images/Japanese.png";
        break;
    case BRANSON_INI_STRUCT::SIMPCHINESE_Lang: //2 Simplifed chinese
        source = "qrc:/images/images/chinese.png";
        break;
    case BRANSON_INI_STRUCT::TRADCHINESE_Lang: //3 Traditional chinese
        source = "qrc:/images/images/chinese.png";
        break;
    case BRANSON_INI_STRUCT::INDONESIAN_Lang:  //4 Indonesian
        source = "qrc:/images/images/Indonesian.png";
        break;
    case BRANSON_INI_STRUCT::SPANISH_Lang:     //5 Spanish
        source = "qrc:/images/images/Spanish&Mexcio.png";
        break;
    case BRANSON_INI_STRUCT::Vietnam_Lang:     //6 Vietnam
        source = "qrc:/images/images/Vietnam.png";
        break;
    case BRANSON_INI_STRUCT::TURKISH_Lang:     //7 Turkish
        source = "qrc:/images/images/Turkish.png";
        break;
    case BRANSON_INI_STRUCT::Thai_Lang:        //8 Thai
        source = "qrc:/images/images/Thai.png";
        break;
    case BRANSON_INI_STRUCT::PORTUGUESE_Lang:  //9 Portuguese
        source = "qrc:/images/images/Portuguese&Brazil.png";
        break;
    case BRANSON_INI_STRUCT::GERMAN_Lang:      //10 German
        source = "qrc:/images/images/German.png";
        break;
    case BRANSON_INI_STRUCT::FRENCH_Lang:      //11 French
        source = "qrc:/images/images/french.png";
        break;
    case BRANSON_INI_STRUCT::RUSSIAN_Lang:     //12 Russian
        source = "qrc:/images/images/russian.png";
        break;
    case BRANSON_INI_STRUCT::POLISH_Lang:      //13 Polish
        source = "qrc:/images/images/polish.png";
        break;
    case BRANSON_INI_STRUCT::KOREAN_Lang:      //14 Korean
        source = "qrc:/images/images/Korean.png";
        break;
    case BRANSON_INI_STRUCT::ITALIAN_Lang:     //15 Italian
        source = "qrc:/images/images/Italian.png";
        break;
    case BRANSON_INI_STRUCT::SLOVAK_Lang:      //16 Slovak
        source = "qrc:/images/images/Slovak.png";
        break;
    case BRANSON_INI_STRUCT::ROMANIAN_Lang:    //17 Romanian
        source = "qrc:/images/images/Romanian.png";
        break;
    case BRANSON_INI_STRUCT::HUNGARIAN_Lang:   //18 Hungarian
        source = "qrc:/images/images/Hungarian.png";
        break;
    case BRANSON_INI_STRUCT::DUTCH_Lang:       //19 Dutch
        source = "qrc:/images/images/dutch.png";
        break;
    case BRANSON_INI_STRUCT::CZECH_Lang:       //20 Czech
        source = "qrc:/images/images/Czech.png";
        break;
    case BRANSON_INI_STRUCT::MALAYSIAN_Lang:   //21 Malaysian
        source = "qrc:/images/images/Malaysian.png";
        break;
    case BRANSON_INI_STRUCT::ARABIC_Lang:      //22 Arabic
        source = "qrc:/images/images/Arabic.png";
        break;
    case BRANSON_INI_STRUCT::UnitedARAB_Lang:  //23 United-Arab-Emirates
        source = "qrc:/images/images/United-Arab-Emirates.png";
        break;
    case BRANSON_INI_STRUCT::HINDI_Lang:       //24 Hindi
        source = "qrc:/images/images/Hindi.png";
        break;
    default:
        source = "qrc:/images/images/us&English.png";
        break;
    }
    return source;
}

void HmiAdaptor::slotPhysicalKeySignal(bool &status)
{
    bIsPhysicalKey = interfaceClass->StatusData.PhysicalKeyMode;
    emit signalPhysicalKeySignal(status);
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
