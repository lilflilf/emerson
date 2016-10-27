#include "ScreenShowConvertTest.h"
#include "Modules/UtilityClass.h"
#include "Modules/utilitydefine.h"
#include "QDebug"
ScreenShowConvertTest::ScreenShowConvertTest()
{

}

void ScreenShowConvertTest::DataToScreenStringTest()
{
    UtilityClass *_Utility = UtilityClass::Instance();
    qDebug()<<"Width: "<< _Utility->FormatedDataToString(DINWidth, 800);
}

void ScreenShowConvertTest::ScreenStringToDataTest()
{
    UtilityClass *_Utility = UtilityClass::Instance();
    qDebug()<<"Energy: "<<_Utility->StringToFormatedData(DINEnergy, "799J");
}
