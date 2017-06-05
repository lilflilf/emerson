#ifndef WELDDEFAULTS_H
#define WELDDEFAULTS_H
#include <QObject>
#include "Interface/SysConfiguration.h"
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
    bool Seek;
    bool LockOnAlarm;
    Status_Data::CoolingMode CurrentCoolingMode;
    bool CoolingForTooling;
    struct BRANSONDATA CurrentCoolingDur;
    struct BRANSONDATA CurrentCoolingDel;
//    bool Imperical2Metric; // true is Imperical, false is Metric
    BRANSON_INI_STRUCT::PRESSUREUNIT Pressure2Unit;
    BRANSON_INI_STRUCT::SQUAREUNIT Square2Unit;
    BRANSON_INI_STRUCT::LENGTHUNIT Length2Unit;
    WeldResultElement::SAMPLERATIO SampleRatio; //that for Post-Height & power graph data sampling
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

class WeldDefaults : public QObject
{
    Q_OBJECT
private:
    struct WeldSettingInfo WeldSettingsInfo[4];
private:
    void InitWeldSettings();
public:
    struct WeldSettingForScreen CurrentWeldSettings;
public:
    bool _Recall();
    bool _Set();
    void _Default();
public:
    explicit WeldDefaults(QObject *parent = 0);

signals:

public slots:

};

#endif // WELDDEFAULTS_H
