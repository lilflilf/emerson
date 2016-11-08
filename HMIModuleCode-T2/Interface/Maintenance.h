#ifndef MAINTENANCE_H
#define MAINTENANCE_H
#include <QString>
#include <QObject>
#include <QMetaType>
#include "Modules/UtilityClass.h"
const QString MaintenanceTypeString[] = {
    QObject::tr("Calibration"),
    QObject::tr("Tooling Change"),
    QObject::tr("Advanced Maintenance"),
    QObject::tr("Maintenance Counter"),
};

const QString MaintenanceMessageString[] = {
    QObject::tr("Width & Height Calibration Process Start"),
    QObject::tr("Width & Height Calibration Process Complete"),
    QObject::tr("Width & Height Calibration Process Cancel"),
    QObject::tr("Amplitude Calibration Process Start"),
    QObject::tr("Amplitude Calibration Process Complete"),
    QObject::tr("Amplitude Calibration Process Cancel"),
    QObject::tr("Tooling Change Process Start"),
    QObject::tr("Tooling Change Process Finish"),
    QObject::tr("Anvil Arm Movement"),
    QObject::tr("Gather Movement"),
    QObject::tr("Cutter Movement"),
    QObject::tr("Crash Movement"),
    QObject::tr("Safety Movement"),
    QObject::tr("Horn Counter Limit Change"),
    QObject::tr("Horn Counter Reset"),
    QObject::tr("Anvil Tip Counter Limit Change"),
    QObject::tr("Anvil Tip Counter Reset"),
    QObject::tr("Gather Counter Limit Change"),
    QObject::tr("Gather Counter Reset"),
    QObject::tr("Anvil Guide Counter Limit Change"),
    QObject::tr("Anvil Guide Counter Reset"),
    QObject::tr("Converter Counter Limit Change"),
    QObject::tr("Converter Counter Reset"),
};

enum MAINTAINTYPE
{
    CALIBRATE,
    TOOLCHANGE,
    ADVMAINTAIN,
    MAINTAINCOUNT,

};
/* Output:  bit31,  bit30, bit29, bit28
 *          bit27, ToolingCooling On, CutterOn, CrashOn,
 *                        bit26         bit25    bit24
 * Input:   bit23 ,bit22, bit21 ,bit20,
 *          Setup_Lock, IN4,  IN3, IN2,
 *            bit19    bit18 bit17 bit16
 * Output:  SeekOn, ReadyOn, HornOn, ClampOn,
 *           bit15   bit14    bit13   bit12
 *          GatherOn, ConverterCoolingOn, AlarmOn, SonicsOn,
 *           bit11           bit10          bit9      bit8
 * Input:   PalmBut2, PalmBut1, EStop_R, EStop_NO,
 *            bit7      bit6     bit5      bit4
 *          Air_Mon, CoverClose, IN0, Opsignal,
 *            bit3      bit2     bit1    bit0     */
enum BUTTONSTATUS
{
    OPSIGNAL_OFF = 0x01,
    IN0_OFF      = 0x02,
    COVER_OPEN   = 0x04,
    AIRMON_OFF   = 0x08,
    ESTOPNO_OFF  = 0x10,
    ESTOPR_OFF   = 0x20,
    PALMBUT1_OFF = 0x40,
    PALMBUT2_OFF = 0x80,
    SONICS_ON = 0x0100,
    ALARM_ON = 0x0200,
    CONVERTERCOOL_ON = 0x0400,
    GATHER_ON = 0x0800,
    CLAMP_ON = 0x1000,
    HORN_ON = 0x2000,
    READY_ON = 0x4000,
    SEEK_ON = 0x8000,
    IN2_OFF = 0x010000,
    IN3_OFF = 0x020000,
    IN4_OFF = 0x040000,
    LOCK_OFF = 0x080000,

    CRASH_ON = 0x01000000,
    CUTTER_ON = 0x02000000,
    TOOLINGCOOL_ON = 0x04000000,
};

class MaintenanceLogElement
{
public:
    int RevCode;
    int MaintenanceLogID;
    enum MAINTAINTYPE MaintenanceType;
    int MaintenanceMsgIndex;
    unsigned int CreatedDate;
    int OperatorID;

};

class Maintenance : public QObject
{
    Q_OBJECT
private:
    static bool HornTest;
    static bool GatherTest;
    static bool AnvilTest;
    static bool Aux3Test;
    static bool Aux4Test;
    static bool Aux5Test;
    static bool ConverterCoolingTest;
    static bool ToolingCoolingTest;
    static unsigned long PreviousIO;
    ThreadClass* m_Thread;
private:
    static void UpdateAnvilArm();
    static void UpdateAnvil();
    static void UpdateGather();
    static void UpdateSafety();
    static void UpdateConverterCooling();
    static void UpdateIN2();
    static void UpdateCrash();
    static void UpdateCutter();
    static void UpdateToolingCooling();
    void WidthCalibration();
    void HeightCalibration();
    void HornCalibration();
    static void AdvancedMaintenanceHandle(void*);
public:
    //Calibration
    void CalibrationStart();
    void CalibrationStop();

    //Tool Change
    void ToolChangeStart();
    void ToolChangeFinish();

    //Advanced Maintenance
    void AdvancedMaintenanceStart();
    void AdvancedMaintenanceStop();
    void AnvilArm_Click();
    void Anvil_Click();
    void Gather_Click();
    void Cutter_Click();
    void Crash_Click();
    void Safety_Click();
    void ConverterCooling_Click();
    void ToolingCooling_click();

    //Maintenance Counter
    void MaintenanceCounterStart();
    void MaintenanceCounterStop();

    //Maintenance Log
signals:
    void IOstatusFeedback(const unsigned long &_status);
public slots:

public:
    _start();
    _stop();
    _execute();

public:
    explicit Maintenance(QObject *parent = 0);
    ~Maintenance();
};

#endif // MAINTENANCE_H
