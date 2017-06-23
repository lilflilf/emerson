#ifndef VARIANTTOSTRING_H
#define VARIANTTOSTRING_H
#include <QString>
#include "Modules/UtilityClass.h"
//#include "Modules/typedef.h"

#define OverLoadFault   0x1 //BIT0
#define TimeMinFault    0x20 //BIT5
#define PowerMinFault   0x40 //BIT6
#define HeightMinFault  0x80 //BIT7
//#define WidthFault    0x800
#define CutterFault     0x20000 //BIT17
#define TimeMaxFault    0x200000 //BIT21
#define PowerMaxFault   0x400000 //BIT22
#define HeightMaxFault  0x800000 //BIT23
#define AlarmsFault  (OverLoadFault | TimeMinFault | PowerMinFault | HeightMinFault | CutterFault | TimeMaxFault | PowerMaxFault | HeightMaxFault)

class VariantToString
{
private:
    static UtilityClass *_Utility;
public:
    struct BRANSONDATA GaugeToString(int Gauge, int GaugeAWG);
    QString CrossSectionToString(int);
    struct BRANSONDATA EnergyToString(int);
    struct BRANSONDATA AmplitudeToString(int);
    struct BRANSONDATA DefaultAmpToString(int);
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
    struct BRANSONDATA SequenceQuantity(int);
    struct BRANSONDATA TeachModeQuantity(int);



    // Only for Graph, The Graph Time unit is microsecond
    QString GraphTimeToString(int ActualTime);
    QString GraphPowerToString(int ActualPower);
    QString GraphHeightToString(int ActualHeight);
    //Weld History
    QString WeldModeToString(ADVANCESETTING::WELDMODE, STEPWELD::STEPWELDMODE);
    QString HistoryAmplitudeToString(int Amplitude1, int Amplitude2);
    QString AlarmToString(unsigned int Alarm);
    QString SampleRatioToString(WeldResultElement::SAMPLERATIO);
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
