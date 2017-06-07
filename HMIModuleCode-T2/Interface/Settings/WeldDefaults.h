#ifndef WELDDEFAULTS_H
#define WELDDEFAULTS_H
#include <QObject>
#include "Interface/SysConfiguration.h"
#include "Interface/Definition.h"

const QString FormulaIdentifer[] = {
    QObject::tr("Energy = Offset + (Cross Section X Multiplier)"),
    QObject::tr("Width = sqrt(Cross Section) X Multiplier"),
    QObject::tr("Pressure = Offset + (Cross Section X Multiplier)"),
    QObject::tr("Amplitude = Offset + (Cross Section X Multiplier)"),
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

struct FormulaRangeRef
{
    float MinimumRange;
    float MaximumRange;
};

class WeldDefaults : public QObject
{
    Q_OBJECT
public:
    enum RANGE_ITEM
    {
        RANGE1,
        RANGE2,
        RANGE3,
        RANGE4,
    };

private:
    struct FormulaRangeRef FormulaRangesRef[4];
private:
    void InitWeldSettings();
    void StatusData2FormulaRangeRef();
    void FormulaRangeRef2StatusData();
public:
    struct WeldSettingForScreen CurrentWeldSettings;
public:
    bool _Recall();
    bool _Set();
    void _Default();
    void FormulaUpdate();
public:
    explicit WeldDefaults(QObject *parent = 0);

signals:

public slots:

};

#endif // WELDDEFAULTS_H
