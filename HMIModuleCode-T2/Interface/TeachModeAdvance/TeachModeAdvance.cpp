#include "TeachModeAdvance.h"
#include "Interface/interface.h"
TeachModeAdvance* TeachModeAdvance::_instance = NULL;
TeachModeAdvance* TeachModeAdvance::Instance()
{
    if(_instance == NULL){
        _instance = new TeachModeAdvance();
    }
    return _instance;
}

TeachModeAdvance::TeachModeAdvance()
{

}

void TeachModeAdvance::_set()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    for(int i = 0; i < WIDTH_ADJ; i++)
        _Interface->StatusData.Cust_Data.cust_qual_range[i] =
                _Interface->tempStatusData.Cust_Data.cust_qual_range[i];
//    _Interface->StatusData.Cust_Data.PresetTeachModeSetting =
//            _Interface->tempStatusData.Cust_Data.PresetTeachModeSetting;
    _Interface->StatusData.Cust_Data.StandardRunQuantity =
            _Interface->tempStatusData.Cust_Data.StandardRunQuantity;
    _Interface->StatusData.Cust_Data.AutoRunQuantity =
            _Interface->tempStatusData.Cust_Data.AutoRunQuantity;
    _Interface->StatusData.Cust_Data.SigmaRunQuantity =
            _Interface->tempStatusData.Cust_Data.SigmaRunQuantity;
    _Interface->StatusData.WriteStatusDataToQSetting();
}

void TeachModeAdvance::_default()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    for(int i = 0; i < WIDTH_ADJ; i++)
        _Interface->StatusData.Cust_Data.cust_qual_range[i] =
                _Interface->DefaultStatusData.Cust_Data.cust_qual_range[i];
//    _Interface->StatusData.Cust_Data.PresetTeachModeSetting =
//            _Interface->DefaultStatusData.Cust_Data.PresetTeachModeSetting;
    _Interface->StatusData.Cust_Data.StandardRunQuantity =
            _Interface->DefaultStatusData.Cust_Data.StandardRunQuantity;
    _Interface->StatusData.Cust_Data.AutoRunQuantity =
            _Interface->DefaultStatusData.Cust_Data.AutoRunQuantity;
    _Interface->StatusData.Cust_Data.SigmaRunQuantity =
            _Interface->DefaultStatusData.Cust_Data.SigmaRunQuantity;
    _Interface->StatusData.WriteStatusDataToQSetting();
}
