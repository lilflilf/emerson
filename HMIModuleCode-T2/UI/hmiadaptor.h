#ifndef HMIADAPTOR_H
#define HMIADAPTOR_H

#include <QMetaType>
#include <QObject>
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


    explicit HmiAdaptor(QObject *parent = 0);
    Q_INVOKABLE void openFileDialog();
    Q_INVOKABLE void advancedMaintenanceExecute(int code);
    Q_INVOKABLE void maintenanceStart(int page);
    Q_INVOKABLE void maintenanceStop(int page);
    Q_INVOKABLE bool login(QString passwd);
    Q_INVOKABLE void calibrationMaintenanceExecute(int code);

    InterfaceClass *interfaceClass;

    WorkOrderModel *workOrderModel;
    SpliceModel *spliceModel;
    PartModel *partModel;
    OperatorModel *operatorModel;
    WireModel *wireModel;
    WeldHistoryModel *weldHistoryModel;
    AlarmModel *alarmModel;

    /********Maintenance**************/
    AdvancedMaintenance * advanceMaintenance;
    Calibration * calibration;
    MaintenanceCounter *maintenanceCount;
    MaintenanceLogElement *maintenanceLog;
    ToolChange *toolChange;
signals:
    void widthCalibrationFinish(const bool &_Result);
    void heightCalibrationFinish(const bool &_Result);
public slots:
};

#endif // HMIADAPTOR_H
