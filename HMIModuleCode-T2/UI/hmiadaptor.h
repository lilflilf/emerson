#ifndef HMIADAPTOR_H
#define HMIADAPTOR_H

#include <QMetaType>
#include <QObject>
#include <QRegExpValidator>
#include "tablemodel.h"
#include "Interface/definition.h"
#include "Interface/Settings/OperatorLibrary.h"
#include "Interface/Maintenance/AdvancedMaintenance.h"
#include "Interface/Maintenance/Calibration.h"
#include "Interface/Maintenance/Maintenance.h"
#include "Interface/Maintenance/MaintenanceCounter.h"
#include "Interface/Maintenance/MaintenanceLog.h"
#include "Interface/Maintenance/ToolChange.h"
#include "Interface/interface.h"
#include "Interface/Settings/PermissionSetting.h"
#include "Interface/Settings/WeldDefaults.h"
#include "Interface/Settings/DataCommunication.h"

#define HMI_PRINT (qDebug() <<"HMI adapter:" << __FILE__ << __FUNCTION__ << __LINE__ << ": ")

class HmiAdaptor : public QObject
{
    Q_OBJECT
    Q_ENUMS(StripeType)
    Q_ENUMS(MetalType)
    Q_ENUMS(HorizontalLocation)
    Q_ENUMS(VerticalLocation)
    Q_ENUMS(VerticalPosition)
    Q_ENUMS(BUTTONCLICK)
    Q_ENUMS(CALIBRATE)
    Q_ENUMS(FormulaRange)

public:
    enum CALIBRATE
    {
        WIDTH_CALIBRATE,
        HEIGHT_CALIBRATE,
        AMPLITUDE_CALIBRATE_PRESS,
        AMPLITUDE_CALIBRATE_UPPRESS,
    };

    enum BUTTONCLICK
    {
        ANVILARMCLICK,
        ANVILCLICK,
        GATHERCLICK,
        CUTTERCLICK,
        CRASHCLICK,
        SAFETYCLICK,
        CONVERTERCOOLINGCLICK,
        TOOLINGCOOLINGCLICK,
    };
    enum FormulaRange
    {
        EnergyR1,
        EnergyR2,
        EnergyR3,
        WidthR1,
        WidthR2,
        WidthR3,
        PressureR1,
        PressureR2,
        PressureR3,
        AmplitudeR1,
        AmplitudeR2,
        AmplitudeR3,
        FormulaRangSize,
    };


    explicit HmiAdaptor(QObject *parent = 0);
    Q_INVOKABLE void openFileDialog();
    Q_INVOKABLE void advancedMaintenanceExecute(int code);
    Q_INVOKABLE void maintenanceCountExecute(QString code);
    Q_INVOKABLE QString maintenanceCountGetValue(int code, int index);
    Q_INVOKABLE void maintenanceCountReset(QString code);
    Q_INVOKABLE void maintenanceCountSetLimit(QString code, QString value);
    Q_INVOKABLE void maintenanceStart(int page);
    Q_INVOKABLE void maintenanceStop(int page);
    Q_INVOKABLE QString getMaintenanceVerson(int index);
    Q_INVOKABLE QString getSoftVerson(int index);
    Q_INVOKABLE bool login(QString passwd);
    Q_INVOKABLE void calibrationMaintenanceExecute(int code);
    Q_INVOKABLE int randPoint();

    /********permissionsetting func**************/
    Q_INVOKABLE bool permissionsettingExecute(QString code);
    Q_INVOKABLE QStringList permissionsettingGetValue(QString code);
    Q_INVOKABLE bool permissionsettingGetChecked(QString stringIndex, int level);
    Q_INVOKABLE bool permissionsettingSetValue(QString name,bool level1,bool level2,bool level3,bool level4);
    Q_INVOKABLE bool permissionsettingSetFourValue(QStringList fourName);
    Q_INVOKABLE bool stringRegexMatch(QString exp, QString value);
    Q_INVOKABLE bool keyNumStringMatch(QString minValue, QString maxValue, QString value);
    Q_INVOKABLE QString getStringUnit(QString value);
    Q_INVOKABLE QString getStringValue(QString value);
    Q_INVOKABLE bool comepareCurrentValue(QString minValue, QString maxValue, QString value);
    /********weldDefaults func**************/
    Q_INVOKABLE bool weldDefaultsExecute(QString code);
    Q_INVOKABLE bool weldDefaultsGetSwitch(QString index);
    Q_INVOKABLE QStringList weldDefaultsGetValue(FormulaRange index);
    Q_INVOKABLE QString weldDefaultsGetNum(QString index);
    Q_INVOKABLE bool weldDefaultsSetValue(QList<bool> boolList, QStringList strList, int sampleIndex, QString coolingDur, QString coolingDel);


    /********DataCommunication func**************/
    Q_INVOKABLE bool dataCommunicationExecute(QString code);
    Q_INVOKABLE bool dataCommunicationGetSwitch(QString index);
    Q_INVOKABLE QStringList dataCommunicationGetValue(QString index);
    Q_INVOKABLE bool dataCommunicationSetValue(QList<bool> boolList, QStringList strList, QString ip, QString port);

    InterfaceClass *interfaceClass;

    WorkOrderModel *workOrderModel;
    SpliceModel *spliceModel;
    PartModel *partModel;
    OperatorModel *operatorModel;
    WireModel *wireModel;
    WeldHistoryModel *weldHistoryModel;
    AlarmModel *alarmModel;
    MaintenanceLogModel *maintenanceLogModel;

    /********Maintenance**************/
    AdvancedMaintenance * advanceMaintenance;
    Calibration * calibration;
    MaintenanceCounter *maintenanceCount;
    MaintenanceLogElement *maintenanceLog;
    ToolChange *toolChange;

    /*********Setting*****************/
    PermissionSetting *permissionSetting;
    WeldDefaults *weldDefaults;
    DataCommunication *dataCommunication;
signals:
    void widthCalibrationFinish(const bool &_Result);
    void heightCalibrationFinish(const bool &_Result);
public slots:
};

#endif // HMIADAPTOR_H
