#ifndef VARIANTTOSTRING_H
#define VARIANTTOSTRING_H
#include <QString>
#include "Modules/UtilityClass.h"

#define OverLoadFault 0x01
#define TimeFault     0x20
#define PowerFault    0x40
#define HeightFault   0x80
#define WidthFault    0x800
#define AlarmsFault   (OverLoadFault | TimeFault | PowerFault | HeightFault | WidthFault)

class VariantToString
{
private:
    static UtilityClass *_Utility;
public:
    struct BRANSONDATA GaugeToString(int Gauge, int GaugeAWG);
    QString CrossSectionToString(int);
    struct BRANSONDATA EnergyToString(int);
    struct BRANSONDATA AmplitudeToString(int);
    struct BRANSONDATA WidthToString(int);
    struct BRANSONDATA TriggerPressureToString(int);
    struct BRANSONDATA WeldPressureToString(int);
    struct BRANSONDATA TimePlusToString(int);
    struct BRANSONDATA TimeMinusToString(int);
    struct BRANSONDATA PowerPlusToString(int);
    struct BRANSONDATA PowerMinusToString(int);
    struct BRANSONDATA PreHeightPlusToString(int);
    struct BRANSONDATA PreHeightMinusToString(int);
    struct BRANSONDATA HeightPlusToString(int);
    struct BRANSONDATA HeightMinusToString(int);
    struct BRANSONDATA AfterBurstDelayToString(int);
    struct BRANSONDATA AfterBurstDuringToString(int);
    struct BRANSONDATA AntiSideSpliceTimeToString(int);
    struct BRANSONDATA CutOffSpliceTimeToString(int);
    struct BRANSONDATA HoldTimeToString(int);
    struct BRANSONDATA MeasureWidthToString(int);
    struct BRANSONDATA MeasureHeightToString(int);
    struct BRANSONDATA PreBurstTimeToString(int);
    struct BRANSONDATA SqueezeTimeToString(int);
    struct BRANSONDATA Amplitude2ToString(int);
    struct BRANSONDATA StepEnergyToString(int);
    struct BRANSONDATA StepPowerToString(int);
    struct BRANSONDATA StepTimeToString(int);
    struct BRANSONDATA ShrinkTemperatureToString(int);
    struct BRANSONDATA ShrinkTimeToString(int);

    struct BRANSONDATA StandardAutoTeachModeToString(int);
    struct BRANSONDATA SigmaTeachModeToString(int);

    struct BRANSONDATA TestQuantity(int);



    // Only for Graph, The Graph Time unit is microsecond
    QString GraphTimeToString(int ActualTime);
    QString GraphPowerToString(int ActualPower);
    QString GraphHeightToString(int ActualHeight);
    //Weld History
    QString WeldModeToString(enum WELDMODE, enum STEPWELDMODE);
    QString HistoryAmplitudeToString(int Amplitude1, int Amplitude2);
    QString AlarmToString(unsigned int Alarm);
    QString SampleRatioToString(enum SAMPLERATIO);
    QString ActualTimeToString(int ActualTime);
    QString ActualPowerToString(int ActualPower);
    QString ActualPreHeightToString(int ActualPreHeight);
    QString ActualHeightToString(int ActualHeight);

    QString Time_PlusToString(int);
    QString Time_MinusToString(int);
    QString Power_PlusToString(int);
    QString Power_MinusToString(int);
    QString PreHeight_PlusToString(int);
    QString PreHeight_MinusToString(int);
    QString Height_PlusToString(int);
    QString Height_MinusToString(int);

    //Alarm History
    QString AlarmTypeToString(enum ALARMTYPE);
    QString AlarmLevelToString(enum ALARMTYPE);
    QString AlarmLevelToString(QString AlarmType);

public:
    static VariantToString* Instance();
private:
    static VariantToString* _instance;
private:
    VariantToString();
};

#endif // VARIANTTOSTRING_H
