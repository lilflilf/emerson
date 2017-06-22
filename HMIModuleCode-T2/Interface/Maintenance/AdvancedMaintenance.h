#ifndef ADVANCEDMAINTENANCE_H
#define ADVANCEDMAINTENANCE_H

#include "Maintenance.h"
#include "Interface/definition.h"
#include <QTimer>

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

    CRASH_ON =  0x01000000,
    CUTTER_ON = 0x02000000,
    TOOLINGCOOL_ON = 0x04000000,
};



class AdvancedMaintenance : public Maintenance
{
    Q_OBJECT
public:
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
    enum ADVANCEDPARAMETER
    {
        AMPLITUDE,
        POWER,
        TUNEPOINT,
        FREQOFFSET,
    };

private:
    static bool GatherTest;
    static bool AnvilTest;
    static bool Aux3Test;
    static bool Aux4Test;
    static bool Aux5Test;
    static bool ConverterCoolingTest;
    static bool ToolingCoolingTest;
    static unsigned long PreviousIO;
    static QList<QTimer*> *_TimerList;
    static bool SonicsOnFlag;


public:
    static bool HornTest;
    struct BRANSONDATA AdvParameter[4];
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
    static void AdvancedMaintenanceHandle(void*);
private:
    void AnvilArm_Click();
    void Anvil_Click();
    void Gather_Click();
    void Cutter_Click();
    void Crash_Click();
    void Safety_Click();
    void ConverterCooling_Click();
    void ToolingCooling_click();
public:
    virtual bool _start();
    virtual bool _stop();
    virtual bool _execute(int funCode);
public:
    //Branson Speical
    void Reset();
    void RunSonicsPressed();
    void RunSonicsUnPressed();
    void RunSonics100Pressed();
    void RunSonics100UnPressed();
    void AmplitudeSetText(QString AmplitudeStr);
    void PowerSetText(QString PowerStr);
    void TunePointText(QString TunePointHzStr);
    void FrequencyOffsetText(QString FrequencyHzStr);
    void RecallAdvancedParameter();
    bool GetReliabilityOption();
    void SetReliabilityOption(bool status);

public:
    explicit AdvancedMaintenance();
signals:
    void IOstatusFeedbackSignal(const unsigned long &_status);
    void CurrentPowerAndFrequencySignal(const int power, const QString Frequency);
public slots:
    void TimeoutEventSlot();
};

#endif // ADVANCEDMAINTENANCE_H
