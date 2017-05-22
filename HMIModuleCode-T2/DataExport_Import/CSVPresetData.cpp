#include "CSVPresetData.h"
#include "CSVWireData.h"
#include "DataBase/DBPresetTable.h"
#include "DataBase/DBWireTable.h"
#include "Interface/PresetElement.h"
#include "Interface/WireElement.h"
#include "Modules/UtilityClass.h"
#include "Modules/typedef.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>
CSVPresetData* CSVPresetData::_instance = NULL;
CSVPresetData* CSVPresetData::Instance()
{
    if(_instance == 0){
        _instance = new CSVPresetData();
    }
    return _instance;
}

CSVPresetData::CSVPresetData()
{

}

CSVPresetData::~CSVPresetData()
{

}

bool CSVPresetData::ExportData(int ID, QString fileUrl)
{
    DBPresetTable* _PresetDB = DBPresetTable::Instance();
    CSVWireData* _WireData = CSVWireData::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QMap<int,QString> WireList;
    PresetElement PresetObj;
    QStringList ListStr;
    QString RowStr = "";
    QString WireData = "";
    QString tmpWireData;
    QString fileSource;
    ListStr.clear();
    bool bResult = _PresetDB->QueryOneRecordFromTable(ID, ListStr);
    if(bResult == false)
        return bResult;
    RowStr.clear();
    WireData.clear();
    WireList.clear();
    for(int i = 0; i < ListStr.size(); i++)
    {
        if(i == JSONWire)
        {
            _Utility->StringJsonToMap(ListStr[i], &WireList);
            QMap<int, QString>::const_iterator iterator = WireList.constBegin();
            while (iterator != WireList.constEnd()) {
                tmpWireData = _WireData->GetExportString(iterator.key());
                WireData.append(tmpWireData + ";");
                ++iterator;
            }
            RowStr.append(WireData + ",");
        }
        else
            RowStr.append(ListStr[i] + ",");
    }

    fileSource = fileUrl;
    bResult = fileSource.contains("file:///");
    if(bResult == false)
        return bResult;
    fileSource = fileSource.mid(8);
    QFile csvFile(fileSource);
    bResult = csvFile.open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Truncate);
    if(bResult == false)
        return bResult;
    QTextStream out(&csvFile);
    out << "Preset Data" << '\n' << RowStr;
    csvFile.close();
    return true;
}

QString CSVPresetData::GetExportString(int ID)
{
    DBPresetTable* _PresetDB = DBPresetTable::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    CSVWireData* _WireData = CSVWireData::Instance();
    QStringList ListStr;
    QString RowStr = "";
    QString tmpWireData;
    QString WireData = "";
    QString fileSource;
    QMap<int,QString> WireList;
    ListStr.clear();
    bool bResult = _PresetDB->QueryOneRecordFromTable(ID, ListStr);
    if(bResult == false)
        return RowStr;
    RowStr.clear();
    WireData.clear();
    WireList.clear();
    for(int i = 0; i< ListStr.size(); i++)
    {
        if(i == JSONWire)
        {
            _Utility->StringJsonToMap(ListStr[i], &WireList);
            QMap<int, QString>::const_iterator iterator = WireList.constBegin();
            while (iterator != WireList.constEnd()) {
                tmpWireData = _WireData->GetExportString(iterator.key());
                WireData.append(tmpWireData + ";");
                ++iterator;
            }
            RowStr.append(WireData + "*");
        }
        else
            RowStr.append(ListStr[i] + "*");
    }
    return RowStr;
}

bool CSVPresetData::ParseWireData(QString StrWire)
{
    CSVWireData* _WireData = CSVWireData::Instance();
    QStringList WireList;
    QString TmpStr = StrWire;
    WireElement WireObj;
    DBWireTable* _WireDB = DBWireTable::Instance();
    bool bResult = false;
    int i;
    WireIndexList.clear();
    TmpStr.replace(".",",");
    WireList = TmpStr.split(";");
    for (i = 0;i < WireList.count();i++)
    {
        if (WireList[i] != "")
            WireIndexList.append(_WireData->ImportData(WireList[i]));
    }
    WireIndexMap.clear();
    for (i = 0; i < WireIndexList.count();i++)
    {
        if (WireIndexList[i] != ERROR)
        {
            bResult = _WireDB->QueryOneRecordFromTable(WireIndexList[i], &WireObj);
            if(bResult == true)
                WireIndexMap.insert(WireObj.WireID, WireObj.WireName);
        }
    }
    return true;
}

void CSVPresetData::UpdateSpliceIdToWire(QList<int> WireList, int SpliceId)
{
    DBWireTable* _WireDB = DBWireTable::Instance();
    if (SpliceId == -1)
        return;
    WireElement WireObj;
    for(int i = 0; i < WireList.size(); i++)
    {
        if(_WireDB->QueryOneRecordFromTable(WireList[i], &WireObj))
        {
            WireObj.SpliceID = SpliceId;
            _WireDB->UpdateRecordIntoTable(&WireObj);
        }
    }
}

int CSVPresetData::ImportData(QString StrValue)
{
    QString RowStr;
    QString TmpStr;
    QStringList DataList;
    bool bResult;
    PresetElement PresetObj;
    int ret = -1;
    DBPresetTable* _PresetDB = DBPresetTable::Instance();
    RowStr = StrValue;
    DataList = RowStr.split(",");
    if(DataList.size() < PresetEnd)
        return ret;

    TmpStr = DataList[JSONWire];
    ParseWireData(TmpStr);

    PresetObj.SpliceID = QString(DataList[SpliceID]).toInt(&bResult, DECIMALISM);
    PresetObj.SpliceName = DataList[SpliceName];
    QDateTime TimeLabel =
        QDateTime::fromString(DataList[CreatedDate], "yyyy/MM/dd hh:mm:ss");
    PresetObj.CreatedDate = TimeLabel.toTime_t();
    PresetObj.OperatorID =
        QString(DataList[OperatorID]).toInt(&bResult, DECIMALISM);
    PresetObj.CrossSection =
        QString(DataList[CrossSection]).toInt(&bResult, DECIMALISM);
    PresetObj.PresetPicNamePath = DataList[PresetPicPath];
    PresetObj.Verified =
        (bool)QString(DataList[Verified]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.BasicSetting.Energy =
        QString(DataList[Energy]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.BasicSetting.Amplitude =
        QString(DataList[Amplitude]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.BasicSetting.Width =
        QString(DataList[Width]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.BasicSetting.Pressure =
        QString(DataList[Pressure]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.BasicSetting.TrigPres =
        QString(DataList[TrigPres]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.QualitySetting.Time.Plus =
        QString(DataList[TimePlus]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.QualitySetting.Time.Minus =
        QString(DataList[TimeMinus]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.QualitySetting.Power.Plus =
        QString(DataList[PowerPlus]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.QualitySetting.Power.Minus =
        QString(DataList[PowerMinus]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.QualitySetting.Preheight.Plus =
        QString(DataList[PreheightPlus]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.QualitySetting.Preheight.Minus =
        QString(DataList[PreheightMinus]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.QualitySetting.Height.Plus =
        QString(DataList[HeightPlus]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.QualitySetting.Height.Minus =
        QString(DataList[HeightMinus]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.QualitySetting.Force.Plus =
        QString(DataList[ForcePlus]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.QualitySetting.Force.Minus =
        QString(DataList[ForceMinus]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.WeldMode =
        (ADVANCESETTING::WELDMODE)QString(DataList[WeldMode]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode =
        (STEPWELD::STEPWELDMODE)QString(DataList[StepWeldMode]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep =
        QString(DataList[EnergyToStep]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.StepWeld.TimeToStep =
        QString(DataList[TimeToStep]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.StepWeld.PowerToStep =
        QString(DataList[PowerToStep]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.StepWeld.Amplitude2 =
        QString(DataList[Amplitude2]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.PreBurst =
        QString(DataList[PreBurst]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.HoldTime =
        QString(DataList[HoldTime]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.SqzTime =
        QString(DataList[SqueezeTime]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.ABDelay =
        QString(DataList[AfterBurstDelay]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.ABDur =
        QString(DataList[AfterBurstDuring]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.CutOffOption.CutOff =
        (bool)QString(DataList[CutOff]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.CutOffOption.CutOffSpliceTime =
        QString(DataList[CutOffSpliceTime]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.CutOffOption.Cutter4HeightAlarm =
        (bool)QString(DataList[CutOffHeightAlarm]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.CutOffOption.Cutter4PowerAlarm =
        (bool)QString(DataList[CutOffPowerAlarm]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.CutOffOption.Cutter4PreHeightAlarm =
        (bool)QString(DataList[CutOffPreHeightAlarm]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.CutOffOption.Cutter4TimeAlarm =
        (bool)QString(DataList[CutOffTimeAlarm]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.AntiSideOption.AntiSideMode =
        (bool)QString(DataList[AntiSide]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.AntiSideOption.AntiSideSpliceTime =
        (bool)QString(DataList[AntiSideSpliceTime]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.OffsetOption.MeasuredWidth =
        QString(DataList[MeasuredWidth]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.OffsetOption.MeasuredHeight =
        QString(DataList[MeasuredHeight]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.OffsetOption.DisplayWidth =
        QString(DataList[DisplayWidth]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.OffsetOption.DisplayHeight =
        QString(DataList[DisplayHeight]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption =
        (bool)QString(DataList[ShrinkOption]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID = DataList[ShrinkTubeID];
    PresetObj.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime =
        QString(DataList[ShrinkTime]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature =
        QString(DataList[ShrinkTemperature]).toInt(&bResult, DECIMALISM);
    PresetObj.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkMutex =
        (bool)QString(DataList[ShrinkMutex]).toInt(&bResult, DECIMALISM);
    PresetObj.HashCode = QString(DataList[HashCode]).toInt(&bResult, DECIMALISM);

    PresetObj.TestSetting.BatchSize =
        QString(DataList[BatchSize]).toInt(&bResult, DECIMALISM);
    PresetObj.TestSetting.StopCount =
        QString(DataList[StopCount]).toInt(&bResult, DECIMALISM);
    PresetObj.TestSetting.TestMode =
            (TESTSETTING::TESTMODE)QString(DataList[TestMode]).toInt(&bResult, DECIMALISM);
    PresetObj.TestSetting.TeachModeSetting.TeachModeType =
            (TEACHMODESETTING::TEACH_MODE_TYPE)QString(DataList[TEACHMODETYPE]).toInt(&bResult, DECIMALISM);

    for(int i = 0; i< ENERGY_ADJ; i++)
        PresetObj.TestSetting.TeachModeSetting.TeachModequal_Window[i] =
            QString(DataList[i + TimePLRG_STD]).toInt(&bResult, DECIMALISM);

    PresetObj.TestSetting.TeachModeSetting.StandardRunQuantity =
            QString(DataList[StandardQuantity]).toInt(&bResult, DECIMALISM);
    PresetObj.TestSetting.TeachModeSetting.AutoRunQuantity =
            QString(DataList[AutoQuantity]).toInt(&bResult, DECIMALISM);
    PresetObj.TestSetting.TeachModeSetting.SigmaRunQuantity =
            QString(DataList[SigmaQuantity]).toInt(&bResult, DECIMALISM);
    PresetObj.TestSetting.TestingDone =
            (bool)QString(DataList[TestingDone]).toInt(&bResult, DECIMALISM);

    PresetObj.WireIndex = WireIndexMap;
    PresetObj.NoOfWires = PresetObj.WireIndex.size();
    ret = _PresetDB->InsertRecordIntoTable(&PresetObj);
    while(ret == ERROR)
    {
        qDebug()<<"splice";
        QMap<int, QString> tmpMap;
        _PresetDB->QueryOnlyUseName(PresetObj.SpliceName, &tmpMap);
        if(tmpMap.size() > 0)
        {
            PresetObj.SpliceName = PresetObj.SpliceName + "(1)";
            ret = _PresetDB->InsertRecordIntoTable(&PresetObj);
        }else if(tmpMap.size() == 0)
            return ERROR;
    }
    UpdateSpliceIdToWire(WireIndexList,ret);
    return ret;
}
