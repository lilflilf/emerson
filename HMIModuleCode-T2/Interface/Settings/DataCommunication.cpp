#include "DataCommunication.h"
#include "Interface/Interface.h"
#include "Modules/UtilityClass.h"
#include <QDebug>
DataCommunication::DataCommunication()
{

}

bool DataCommunication::_Recall()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    CurrentDataCommunication.GlobalShrinkTubeMode = _Interface->StatusData.ShrinkTubeMode;
    CurrentDataCommunication.MaxmmTemp
            = _Utility->FormatedDataToString(DINShrinkTubeTemperature, ShrinkTubeMaxTemp);
    CurrentDataCommunication.MinmmTemp
            = _Utility->FormatedDataToString(DINShrinkTubeTemperature, ShrinkTubeMinTemp);
    CurrentDataCommunication.MaxmmTime
            = _Utility->FormatedDataToString(DINShrinkTubeTime, (float)ShrinkTubeMaxTime);
    CurrentDataCommunication.MinmmTime
            = _Utility->FormatedDataToString(DINShrinkTubeTime, ShrinkTubeMinTime);
    int tmperature = 0;
    float time = 0;
    QString str;
    CurrentDataCommunication.ShrinkTubeDefault.clear();
    struct ShrinkTubeReference tmpShrinkTube;
    for(int i = 0; i< _Interface->StatusData.ShrinkTubeDefaults.size();i++)
    {
        tmpShrinkTube.Name = _Interface->StatusData.ShrinkTubeDefaults.at(i).Name;
        tmperature = _Interface->StatusData.ShrinkTubeDefaults.at(i).temp;
        str = _Utility->FormatedDataToString(DINShrinkTubeTemperature,tmperature);
        tmpShrinkTube.Temp = str;
        time = _Interface->StatusData.ShrinkTubeDefaults.at(i).Time;
        str = _Utility->FormatedDataToString(DINShrinkTubeTime, time);
        tmpShrinkTube.Time = str;
        CurrentDataCommunication.ShrinkTubeDefault.insert(i, tmpShrinkTube);
    }
    CurrentDataCommunication.EthernetMode = _Interface->StatusData.NetworkingEnabled;
    CurrentDataCommunication.RemoteDataLogging = _Interface->StatusData.RemoteDataLogging;
    CurrentDataCommunication.RemoteGraphData = _Interface->StatusData.RemoteGraphData;
    CurrentDataCommunication.ModularProduction = _Interface->StatusData.ModularProductionEnabled;
    str = _Utility->FormatedDataToString(DINServerPortNumber, _Interface->StatusData.ServerPort);
    CurrentDataCommunication.ServerPort.Current = str;
    str = _Utility->FormatedDataToString(DINServerPortNumber, MAXSERVER_PORT_NUMBER);
    CurrentDataCommunication.ServerPort.Maximum = str;
    str = _Utility->FormatedDataToString(DINServerPortNumber, MINSERVER_PORT_NUMBER);
    CurrentDataCommunication.ServerPort.Minimum = str;
    return true;
}

bool DataCommunication::_Set()
{
    InterfaceClass* _Interface = InterfaceClass::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    _Interface->StatusData.ShrinkTubeMode =
            CurrentDataCommunication.GlobalShrinkTubeMode;

    QString str;
    _Interface->StatusData.ShrinkTubeDefaults.clear();
    struct ShrinkTubeData tmpShrinkTube;
    for(int i = 0; i< CurrentDataCommunication.ShrinkTubeDefault.size();i++)
    {
        tmpShrinkTube.Name = CurrentDataCommunication.ShrinkTubeDefault.at(i).Name;
        str = CurrentDataCommunication.ShrinkTubeDefault.at(i).Temp;
        tmpShrinkTube.temp = (int)_Utility->StringToFormatedData(DINShrinkTubeTemperature, str);
        str = CurrentDataCommunication.ShrinkTubeDefault.at(i).Time;
        tmpShrinkTube.Time = _Utility->StringToFormatedData(DINShrinkTubeTime, str);
        _Interface->StatusData.ShrinkTubeDefaults.insert(i, tmpShrinkTube);
    }
    _Interface->StatusData.NetworkingEnabled = CurrentDataCommunication.EthernetMode;
    _Interface->StatusData.RemoteDataLogging = CurrentDataCommunication.RemoteDataLogging;
    _Interface->StatusData.RemoteGraphData = CurrentDataCommunication.RemoteGraphData;
    _Interface->StatusData.ModularProductionEnabled = CurrentDataCommunication.ModularProduction;
    str = CurrentDataCommunication.ServerPort.Current;
    _Interface->StatusData.ServerPort = _Utility->StringToFormatedData(DINServerPortNumber,str);
    return true;
}
