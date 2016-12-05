#ifndef STRINGTOVARIANT_H
#define STRINGTOVARIANT_H
#include <QString>

class StringToVariant
{
public:
    int GaugeToInt(QString Gauge, QString GaugeAWG);
    int CrossSectionToInt(QString);
    int EnergyToInt(QString);
    int AmplitudeToInt(QString);
    int WidthToInt(QString);
    int TriggerPressureToInt(QString);
    int WeldPressureToInt(QString);
    int TimePlusToInt(QString);
    int TimeMinusToInt(QString);
    int PowerPlusToInt(QString);
    int PowerMinusToInt(QString);
    int PreHeightPlusToInt(QString);
    int PreHeightMinusToInt(QString);
    int HeightPlusToInt(QString);
    int HeightMinusToInt(QString);
    int AfterBurstDelayToInt(QString);
    int AfterBurstDuringToInt(QString);
    int AntiSideSpliceTimeToInt(QString);
    int CutOffSpliceTimeToInt(QString);
    int HoldTimeToInt(QString);
    int MeasureWidthToInt(QString);
    int MeasureHeightToInt(QString);
    int PreBurstTimeToInt(QString);
    int SqueezeTimeToInt(QString);
    int Amplitude2ToInt(QString);
    int StepEnergyToInt(QString);
    int StepPowerToInt(QString);
    int StepTimeToInt(QString);
    int ShrinkTemperatureToInt(QString);
    int ShrinkTimeToInt(QString);
public:
    StringToVariant();
};

#endif // STRINGTOVARIANT_H
