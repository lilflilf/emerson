#include "DataCommunication.h"
#include "Interface/Interface.h"
#include "Modules/UtilityClass.h"
#include "Modules/BransonServer.h"
#include "Modules/ShrinkTubeSerial.h"
#include "DataBase/DBHarnessTable.h"
#include "DataBase/DBSequenceTable.h"
#include "DataBase/DBPresetTable.h"
#include "DataBase/DBWireTable.h"
#include <QDebug>
DataCommunication::DataCommunication()
{

}

bool DataCommunication::_Recall()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    BransonServer* _Server = BransonServer::Instance();
    qDebug()<<"_Recall";
    CurrentDataCommunication.GlobalShrinkTubeModeEnable = _Interface->StatusData.ShrinkTubeModeEnable;
//    CurrentDataCommunication.MaxmmTemp
//            = _Utility->FormatedDataToString(DINShrinkTubeTemperature, ShrinkTubeMaxTemp);
//    CurrentDataCommunication.MinmmTemp
//            = _Utility->FormatedDataToString(DINShrinkTubeTemperature, ShrinkTubeMinTemp);
//    CurrentDataCommunication.MaxmmTime
//            = _Utility->FormatedDataToString(DINShrinkTubeTime, (float)ShrinkTubeMaxTime);
//    CurrentDataCommunication.MinmmTime
//            = _Utility->FormatedDataToString(DINShrinkTubeTime, ShrinkTubeMinTime);
    CurrentDataCommunication.EthernetModeEnable = _Interface->StatusData.NetworkingEnabled;
    CurrentDataCommunication.RemoteDataLogging = _Interface->StatusData.RemoteDataLogging;
    CurrentDataCommunication.RemoteGraphData = _Interface->StatusData.RemoteGraphData;
    CurrentDataCommunication.ModularProduction = _Interface->StatusData.ModularProductionEnabled;
    QString str = _Utility->FormatedDataToString(DINServerPortNumber, _Interface->StatusData.ServerPort);
    CurrentDataCommunication.ServerPort.Current = str;
    str = _Utility->FormatedDataToString(DINServerPortNumber, MAXSERVER_PORT_NUMBER);
    CurrentDataCommunication.ServerPort.Maximum = str;
    str = _Utility->FormatedDataToString(DINServerPortNumber, MINSERVER_PORT_NUMBER);
    CurrentDataCommunication.ServerPort.Minimum = str;
    CurrentDataCommunication.IPConfiguration = _Server->GetHostAddress();
    return true;
}

bool DataCommunication::_Set()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    DBHarnessTable*   _HarnessTable   = DBHarnessTable::Instance();
    DBSequenceTable* _SequenceTable = DBSequenceTable::Instance();
    DBPresetTable*    _SpliceTable    = DBPresetTable::Instance();
    DBWireTable*      _WireTable      = DBWireTable::Instance();
    qDebug()<<"_Set";
    _Interface->StatusData.ShrinkTubeModeEnable =
            CurrentDataCommunication.GlobalShrinkTubeModeEnable;

    _Interface->StatusData.NetworkingEnabled = CurrentDataCommunication.EthernetModeEnable;
    _Interface->StatusData.RemoteDataLogging = CurrentDataCommunication.RemoteDataLogging;
    _Interface->StatusData.RemoteGraphData = CurrentDataCommunication.RemoteGraphData;
    if(_Interface->StatusData.ModularProductionEnabled != CurrentDataCommunication.ModularProduction)
    {
        _Interface->StatusData.ModularProductionEnabled = CurrentDataCommunication.ModularProduction;
        _SequenceTable->SwitchDBObject(_Interface->StatusData.ModularProductionEnabled);
        _HarnessTable->SwitchDBObject(_Interface->StatusData.ModularProductionEnabled);
        _SpliceTable->SwitchDBObject(_Interface->StatusData.ModularProductionEnabled);
        _WireTable->SwitchDBObject(_Interface->StatusData.ModularProductionEnabled);
    }
    QString str = CurrentDataCommunication.ServerPort.Current;
    _Interface->StatusData.ServerPort = _Utility->StringToFormatedData(DINServerPortNumber,str);
    _Interface->StatusData.WriteStatusDataToQSetting();
    return true;
}

void DataCommunication::_Default()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    _Interface->StatusData.ShrinkTubeModeEnable =
            _Interface->DefaultStatusData.ShrinkTubeModeEnable;
    _Interface->StatusData.NetworkingEnabled =
            _Interface->DefaultStatusData.NetworkingEnabled;
    _Interface->StatusData.RemoteDataLogging =
            _Interface->DefaultStatusData.RemoteDataLogging;
    _Interface->StatusData.RemoteGraphData =
            _Interface->DefaultStatusData.RemoteGraphData;
    _Interface->StatusData.ModularProductionEnabled =
            _Interface->DefaultStatusData.ModularProductionEnabled;
    _Interface->StatusData.ServerPort =
            _Interface->StatusData.ServerPort;
    _Interface->StatusData.WriteStatusDataToQSetting();
}

void DataCommunication::ShrinkTubeTesting()
{
    ShrinkTubeSerial* _ShrinkTubeObj = ShrinkTubeSerial::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    int Temperature = _Interface->StatusData.ShrinkTubeDefaults[M10INI::STIR1].temp;
    float Time = _Interface->StatusData.ShrinkTubeDefaults[M10INI::STIR1].temp;
    ShrinkTubeSerial::IsTest = true;
    _ShrinkTubeObj->FormatShrinkTubeData(M10INI::STIR1, Time, Temperature);
}
