#include "CSVPresetData.h"
#include "CSVWireData.h"
#include "DataBase/DBPresetTable.h"
#include "Interface/PresetElement.h"
#include "Modules/UtilityClass.h"
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
        if(i == 88)
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
    out << "WireData" << '\n' << RowStr;
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
        if(i == 68)
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

int CSVPresetData::ImportData(QString StrValue, QMap<int, QString> WireIDMap)
{
    QString RowStr;
    QStringList DataList;
    bool bResult;
    PresetElement PresetObj;
    int ret = -1;
    DBPresetTable* _PresetDB = DBPresetTable::Instance();
    RowStr = StrValue;
    DataList = RowStr.split(",");
    if(DataList.size() < 87)
        return ret;

    PresetObj.SpliceID = QString(DataList[0]).toInt(&bResult, 10);
    PresetObj.SpliceName = DataList[1];
    QDateTime TimeLabel =
            QDateTime::fromString(DataList[2], "yyyy/MM/dd hh:mm:ss");
    PresetObj.CreatedDate = TimeLabel.toTime_t();
    PresetObj.OperatorID = QString(DataList[3]).toInt(&bResult, 10);
    PresetObj.CrossSection = QString(DataList[4]).toInt(&bResult, 10);
    PresetObj.PresetPicNamePath = DataList[5];
    PresetObj.Verified = (bool)QString(DataList[6]).toInt(&bResult, 10);
    PresetObj.WeldSettings.BasicSetting.Energy =
            QString(DataList[7]).toInt(&bResult, 10);
    PresetObj.WeldSettings.BasicSetting.Amplitude =
            QString(DataList[8]).toInt(&bResult, 10);
    PresetObj.WeldSettings.BasicSetting.Width =
            QString(DataList[9]).toInt(&bResult, 10);
    PresetObj.WeldSettings.BasicSetting.Pressure =
            QString(DataList[10]).toInt(&bResult, 10);
    PresetObj.WeldSettings.BasicSetting.TrigPres =
            QString(DataList[11]).toInt(&bResult, 10);
    PresetObj.WeldSettings.QualitySetting.Time.Plus =
            QString(DataList[12]).toInt(&bResult, 10);
    PresetObj.WeldSettings.QualitySetting.Time.Minus =
            QString(DataList[13]).toInt(&bResult, 10);
    PresetObj.WeldSettings.QualitySetting.Power.Plus =
            QString(DataList[14]).toInt(&bResult, 10);
    PresetObj.WeldSettings.QualitySetting.Power.Minus =
            QString(DataList[15]).toInt(&bResult, 10);
    PresetObj.WeldSettings.QualitySetting.Preheight.Plus =
            QString(DataList[16]).toInt(&bResult, 10);
    PresetObj.WeldSettings.QualitySetting.Preheight.Minus =
            QString(DataList[17]).toInt(&bResult, 10);
    PresetObj.WeldSettings.QualitySetting.Height.Plus =
            QString(DataList[18]).toInt(&bResult, 10);
    PresetObj.WeldSettings.QualitySetting.Height.Minus =
            QString(DataList[19]).toInt(&bResult, 10);
    PresetObj.WeldSettings.QualitySetting.Force.Plus =
            QString(DataList[20]).toInt(&bResult, 10);
    PresetObj.WeldSettings.QualitySetting.Force.Minus =
            QString(DataList[21]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.WeldMode =
            (ADVANCESETTING::WELDMODE)QString(DataList[22]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode =
            (STEPWELD::STEPWELDMODE)QString(DataList[23]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep =
            QString(DataList[24]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.StepWeld.TimeToStep =
            QString(DataList[25]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.StepWeld.PowerToStep =
            QString(DataList[26]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.StepWeld.Amplitude2 =
            QString(DataList[27]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.PreBurst =
            QString(DataList[28]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.HoldTime =
            QString(DataList[29]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.SqzTime =
            QString(DataList[30]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.ABDelay =
            QString(DataList[31]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.ABDur =
            QString(DataList[32]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.CutOffOption.CutOff =
            (bool)QString(DataList[33]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.CutOffOption.CutOffSpliceTime =
            QString(DataList[34]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.CutOffOption.Cutter4HeightAlarm =
            (bool)QString(DataList[35]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.CutOffOption.Cutter4PowerAlarm =
            (bool)QString(DataList[36]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.CutOffOption.Cutter4PreHeightAlarm =
            (bool)QString(DataList[37]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.CutOffOption.Cutter4TimeAlarm =
            (bool)QString(DataList[38]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.AntiSideOption.AntiSideMode =
            (bool)QString(DataList[39]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.AntiSideOption.AntiSideSpliceTime =
            (bool)QString(DataList[40]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.OffsetOption.MeasuredWidth =
            QString(DataList[41]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.OffsetOption.MeasuredHeight =
            QString(DataList[42]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.OffsetOption.DisplayWidth =
            QString(DataList[43]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.OffsetOption.DisplayHeight =
            QString(DataList[44]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption =
            (bool)QString(DataList[45]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID = DataList[46];
    PresetObj.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime =
            QString(DataList[47]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature =
            QString(DataList[48]).toInt(&bResult, 10);
    PresetObj.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkMutex =
            (bool)QString(DataList[49]).toInt(&bResult, 10);
    PresetObj.HashCode = QString(DataList[50]).toInt(&bResult, 10);

    PresetObj.TestSetting.BatchSize = QString(DataList[51]).toInt(&bResult, 10);
    PresetObj.TestSetting.StopCount = QString(DataList[52]).toInt(&bResult, 10);
    PresetObj.TestSetting.TestMode =
            (TESTSETTING::TESTMODE)QString(DataList[53]).toInt(&bResult, 10);
    PresetObj.TestSetting.TeachModeSetting.TeachModeType =
            (TEACHMODESETTING::TEACH_MODE_TYPE)QString(DataList[54]).toInt(&bResult, 10);

    for(int i = 0; i< ENERGY_ADJ; i++)
        PresetObj.TestSetting.TeachModeSetting.TeachModequal_Window[i] =
            QString(DataList[i + 55]).toInt(&bResult, 10);

    PresetObj.TestSetting.TeachModeSetting.StandardRunQuantity =
            QString(DataList[83]).toInt(&bResult, 10);
    PresetObj.TestSetting.TeachModeSetting.AutoRunQuantity =
            QString(DataList[84]).toInt(&bResult, 10);
    PresetObj.TestSetting.TeachModeSetting.SigmaRunQuantity =
            QString(DataList[85]).toInt(&bResult, 10);
    PresetObj.TestSetting.TestingDone =
            (bool)QString(DataList[86]).toInt(&bResult, 10);

    PresetObj.WireIndex = WireIDMap;
    PresetObj.NoOfWires = PresetObj.WireIndex.size();
    ret = _PresetDB->InsertRecordIntoTable(&PresetObj);
    while(ret == -1)
    {
        qDebug()<<"splice";
        QMap<int, QString> tmpMap;
        _PresetDB->QueryOnlyUseName(PresetObj.SpliceName, &tmpMap);
        if(tmpMap.size() > 0)
        {
            PresetObj.SpliceName = PresetObj.SpliceName + "(1)";
            ret = _PresetDB->InsertRecordIntoTable(&PresetObj);
        }else if(tmpMap.size() == 0)
            return -1;
    }
    return ret;
}
