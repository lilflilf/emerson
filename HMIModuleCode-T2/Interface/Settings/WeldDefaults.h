#ifndef WELDDEFAULTS_H
#define WELDDEFAULTS_H
#include "Interface/Settings/SysConfiguration.h"
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
    void _DefaultSetting();
    void _Cancel();
    void _OK();
public:
    WeldDefaults();
};

#endif // WELDDEFAULTS_H
