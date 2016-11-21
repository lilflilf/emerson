#ifndef WELDDEFAULTS_H
#define WELDDEFAULTS_H
#include "Interface/Settings/SysConfiguration.h"
#include "Interface/Definition.h"

const QString FormulaIdentifer[] = {
    QObject::tr("Offset + (AREA X Multiplier)"),
    QObject::tr("sqrt(AREA) X Multiplier"),
};

struct WeldSettingFormulaStruct
{
    struct BRANSONDATA Range;
    struct BRANSONDATA Offset;
    struct BRANSONDATA Multiplier;
    QString Identifier;
};

struct WeldSettingForScreen
{
    bool WidthEncoder;
    bool HeightEncoder;
    bool FootPedalAbort;
    enum CoolingMode CurrentCoolingMode;
    bool CoolingForTooling;
    struct BRANSONDATA CurrentCoolingDur;
    struct BRANSONDATA CurrentCoolingDel;
    bool Imperical2Metric; // true is Imperical, false is Metric
    enum SAMPLERATIO SampleRatio; //that for Post-Height & power graph data sampling
    struct WeldSettingFormulaStruct WeldSettingFormula[FormulaRangSize];

};

struct WeldSettingInfo
{
    float MultRatio;
    float MultMin;
    float MultMax;
    QString MultFormat;
    float OffsetRatio;
    float OffsetMin;
    float OffsetMax;
    QString OffsetFormat;
};

class WeldDefaults
{
private:
    struct WeldSettingInfo WeldSettingsInfo[4];
private:
    void InitWeldSettings();
public:
    void _Recall(void*);
    void _Set(void*);
    void _Default();
public:
    WeldDefaults();
};

#endif // WELDDEFAULTS_H
