#include "WeldDefaults.h"
#include "Interface/Interface.h"
#include "Interface/Settings/SysConfiguration.h"
#include "Modules/M10INI.h"
#include "Modules/M10definitions.h"
WeldDefaults::WeldDefaults()
{
    InitWeldSettings();
}

void WeldDefaults::InitWeldSettings()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    M10INI* _M10INI = M10INI::Instance();
    if(_Interface->tempStatusData.WeldSettings4Build[0].Multplier <
            Minmm2EnergyMult)
    {
        _M10INI->SetDefaultWeldFormula(&_Interface->tempStatusData);
    }
    WeldSettingsInfo[SDNEnergy].MultRatio = 1;
    WeldSettingsInfo[SDNEnergy].MultMin = Minmm2EnergyMult;
    WeldSettingsInfo[SDNEnergy].MultMax = Maxmm2EnergyMult;
    WeldSettingsInfo[SDNEnergy].MultFormat = "%.2fJ";
    WeldSettingsInfo[SDNEnergy].OffsetRatio = 1;
    WeldSettingsInfo[SDNEnergy].OffsetMin = Minmm2EnergyOffset;
    WeldSettingsInfo[SDNEnergy].OffsetMax = Maxmm2EnergyOffset;
    WeldSettingsInfo[SDNEnergy].OffsetFormat = "%.2fJ";

    WeldSettingsInfo[SDNWidth].MultRatio = 100;
    WeldSettingsInfo[SDNWidth].MultMin = Minmm2WidthAreaRatio;
    WeldSettingsInfo[SDNWidth].MultMax = Maxmm2WidthAreaRatio;
    WeldSettingsInfo[SDNWidth].MultFormat = "%.2f";
    WeldSettingsInfo[SDNWidth].OffsetRatio = 1;
    WeldSettingsInfo[SDNWidth].OffsetMin = 0;
    WeldSettingsInfo[SDNWidth].OffsetMax = 0;
    WeldSettingsInfo[SDNWidth].OffsetFormat = "%d";

    WeldSettingsInfo[SDNWeldPressure].MultRatio = 100;
    WeldSettingsInfo[SDNWeldPressure].MultMin = Minmm2PressMult;
    WeldSettingsInfo[SDNWeldPressure].MultMax = Maxmm2PressMult;
    WeldSettingsInfo[SDNWeldPressure].MultFormat = "%.2f";
    WeldSettingsInfo[SDNWeldPressure].OffsetRatio = 10;
    WeldSettingsInfo[SDNWeldPressure].OffsetMin = Minmm2PressOffset;
    WeldSettingsInfo[SDNWeldPressure].OffsetMax = Maxmm2PressOffset;
    WeldSettingsInfo[SDNWeldPressure].OffsetFormat = "%.1fPSI";

    WeldSettingsInfo[SDNAmplitude].MultRatio = 10;
    WeldSettingsInfo[SDNAmplitude].MultMin = Minmm2AmplitudeMult;
    WeldSettingsInfo[SDNAmplitude].MultMax = Maxmm2AmplitudeMult;
    WeldSettingsInfo[SDNAmplitude].MultFormat = "%.2f";
    WeldSettingsInfo[SDNAmplitude].OffsetRatio = 1;
    WeldSettingsInfo[SDNAmplitude].OffsetMin = Minmm2AmplitudeOffset;
    WeldSettingsInfo[SDNAmplitude].OffsetMax = Maxmm2AmplitudeOffset;
    WeldSettingsInfo[SDNAmplitude].OffsetFormat = "%.2f";
}

void WeldDefaults::_Default()
{

}

void WeldDefaults::_Recall(void *)
{

}

void WeldDefaults::_Set(void *)
{

}
