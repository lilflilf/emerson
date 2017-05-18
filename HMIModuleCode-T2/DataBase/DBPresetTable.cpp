#include "DBPresetTable.h"
#include "Modules/UtilityClass.h"
#include "Modules/typedef.h"
#include "Interface/PresetElement.h"
#include "Interface/interface.h"
#include <QHash>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QJsonParseError>
#include <QFile>
#include <QDir>

DBPresetTable* DBPresetTable::_instance = NULL;
QString DBPresetTable::SpliceDBFile = "Splice.db";
QString DBPresetTable::DatabaseDir = "c:\\BransonData\\Library\\";
QString DBPresetTable::ModularDatabaseDir = "c:\\BransonData\\Modular Production\\";

const QString SQLSentence[] = {
    "CREATE TABLE Preset ("                 /*0 Create Preset Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    "SpliceName VARCHAR UNIQUE, "
    "CreatedDate VARCHAR, OperatorID INT, CrossSection INT, "
    "PresetPicPath VARCHAR, Verified BOOLEAN,"                  /* 7 items */

    /*WeldSetting*/                                             /* 5 items */
    "Energy INT, Amplitude INT, Width INT, Pressure INT, TrigPres INT, "

    /*QualityWindowSetting*/
    "TimePlus INT, TimeMinus INT, PowerPlus INT, PowerMinus INT, "
    "PreheightPlus INT, PreheightMinus INT, HeightPlus INT, HeightMinus INT, "
    "ForcePlus INT, ForceMinus INT, "                           /* 10 items */

    /*AdvanceSetting*/                                          /* 23 items */
    "WeldMode INT, StepWeldMode INT, EnergyToStep INT, TimeToStep INT, "
    "PowerToStep INT, Amplitude2 INT, PreBurst INT, HoldTime INT, "
    "SqueezeTime INT, AfterBurstDelay INT, AfterBurstDuring INT, "
    "CutOff BOOLEAN, CutOffSpliceTime INT, "
    "CutOffHeightAlarm BOOLEAN, CutOffPowerAlarm BOOLEAN, "
    "CutOffPreHeightAlarm BOOLEAN, CutOffTimeAlarm BOOLEAN, "

    "AntiSide BOOLEAN, AntiSideSpliceTime INT, "

    "MeasuredWidth INT, MeasuredHeight INT, "
    "DisplayWidth INT, DisplayHeight INT, "

    /*Shrink Tube Setting*/
    "ShrinkOption BOOLEAN, ShrinkTubeID INT, ShrinkTime INT, "
    "ShrinkTemperature INT, ShrinkMutex BOOLEAN, "              /*5 items */

    "HashCode INT, "                                            /*1 items */

    /*Testing*/
    "BatchSize INT, StopCount INT, TestMode INT, TEACHMODETYPE ENUM, "
    "TimePLRG_STD INT, TimeMSRG_STD INT, PowerPLRG_STD INT, PowerMSRG_STD INT, "
    "PreHeightPLRG_STD INT, PreHeightMSRG_STD INT, HeightPLRG_STD INT, HeightMSRG_STD INT, "
    "ForcePLRG_STD INT, ForceMSRG_STD INT, "

    "TimePLRG_AUTO INT, TimeMSRG_AUTO INT, PowerPLRG_AUTO INT, PowerMSRG_AUTO INT, "
    "PreHeightPLRG_AUTO INT, PreHeightMSRG_AUTO INT, HeightPLRG_AUTO INT, HeightMSRG_AUTO INT, "
    "ForcePLRG_AUTO INT, ForceMSRG_AUTO INT, "

    "TimeConfigPL INT, TimeConfigMS INT, "
    "PowerConfigPL INT, PowerConfigMS INT, PreHeightConfigPL INT, PreHeightConfigMS INT, "
    "HeightConfigPL INT, HeightConfigMS INT, "
    "StandardQuantity INT, AutoQuantity INT, SigmaQuantity INT, "
    "TestingDone BOOLEAN, "                /* 36 items */

    "NoOfWires INT, "
    /*JSON Structure WireID, WireName*/
    "JSONWire VARCHAR)",                 /*2 items */

    "INSERT INTO Preset ("                      /*1 Insert record into Preset Table*/
                                                /* 6 items */
    "SpliceName, CreatedDate, OperatorID, CrossSection, PresetPicPath, Verified, "

    /*WeldSetting*/                             /* 5 items */
    "Energy, Amplitude, Width, Pressure, TrigPres, "

    /*QualityWindowSetting*/                    /* 10 items */
    "TimePlus, TimeMinus, PowerPlus, PowerMinus, PreheightPlus, PreheightMinus, "
    "HeightPlus, HeightMinus, ForcePlus, ForceMinus, "

    /*AdvanceSetting*/                          /* 23 items */
    "WeldMode, StepWeldMode, EnergyToStep, TimeToStep, PowerToStep, Amplitude2, "
    "PreBurst, HoldTime, SqueezeTime, AfterBurstDelay, AfterBurstDuring, "
    "CutOff, CutOffSpliceTime, "
    "CutOffHeightAlarm, CutOffPowerAlarm, CutOffPreHeightAlarm, CutOffTimeAlarm, "
    "AntiSide, AntiSideSpliceTime, "
    "MeasuredWidth, MeasuredHeight, DisplayWidth, DisplayHeight, "

    /*Shrink Tube Setting*/                     /* 5 items */
    "ShrinkOption, ShrinkTubeID, ShrinkTime, ShrinkTemperature, ShrinkMutex, "

    "HashCode, "                                /* 1 item */

    /*Testing*/                                 /* 36 items */
    "BatchSize, StopCount, TestMode, TEACHMODETYPE, "
    "TimePLRG_STD, TimeMSRG_STD, PowerPLRG_STD, PowerMSRG_STD, "
    "PreHeightPLRG_STD, PreHeightMSRG_STD, HeightPLRG_STD, HeightMSRG_STD, "
    "ForcePLRG_STD, ForceMSRG_STD, "

    "TimePLRG_AUTO, TimeMSRG_AUTO, PowerPLRG_AUTO, PowerMSRG_AUTO, "
    "PreHeightPLRG_AUTO, PreHeightMSRG_AUTO, HeightPLRG_AUTO, HeightMSRG_AUTO, "
    "ForcePLRG_AUTO, ForceMSRG_AUTO, "

    "TimeConfigPL, TimeConfigMS, PowerConfigPL, PowerConfigMS, "
    "PreHeightConfigPL, PreHeightConfigMS, HeightConfigPL, HeightConfigMS, "
    "StandardQuantity, AutoQuantity, SigmaQuantity, "
    "TestingDone, "

    /*JSON Structure WireID, WireName*/
    "NoOfWires, JSONWire) "                     /* 2 items */
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
    "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
    "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
    "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
    "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
    "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
    "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
    "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
    "?, ?, ?, ?, ?, ?, ?, ?)",

    "SELECT ID, SpliceName FROM Preset",        /*2 Query Entire Preset Table */

    "SELECT * FROM Preset WHERE ID = ? AND SpliceName = ?",
                                                /*3 Query One Record From Part Table */

    "SELECT * FROM Preset WHERE ID = ?",        /*4 Query One Record Only Use ID */

    "DELETE FROM Preset",                       /*4 Delete Entire Splice Table*/

    "DELETE FROM Preset WHERE ID = ? AND SpliceName = ?",
                                                /*5 Delete One Record from Splice Table*/

    "UPDATE Preset Set SpliceName = ?, CreatedDate = ?, OperatorID = ?, "
    "CrossSection = ?, PresetPicPath = ?, Verified = ?, "               /* item 6 */
    "Energy = ?, Amplitude = ?, Width = ?, Pressure = ?, TrigPres= ?, " /* item 5 */

    "TimePlus = ?, TimeMinus = ?, PowerPlus = ?, PowerMinus = ?, "      /* item 10 */
    "PreheightPlus = ?, PreheightMinus= ?, HeightPlus = ?, HeightMinus = ?, "
    "ForcePlus = ?, ForceMinus = ?, "

    "WeldMode = ?, StepWeldMode = ?, EnergyToStep = ?, TimeToStep = ?, PowerToStep = ?, "
    "Amplitude2 = ?, PreBurst = ?, HoldTime = ?, SqueezeTime = ?, AfterBurstDelay = ?, "
    "AfterBurstDuring = ?, "
    "CutOff = ?, CutOffSpliceTime = ?, CutOffHeightAlarm = ?, CutOffPowerAlarm = ?, "
    "CutOffPreHeightAlarm = ?, CutOffTimeAlarm = ?, "
    "AntiSide = ?, AntiSideSpliceTime = ?, "
    "MeasuredWidth = ?, MeasuredHeight = ?, DisplayWidth = ?, DisplayHeight = ?, "  /* item 23 */

    "ShrinkOption = ?, ShrinkTubeID = ?, ShrinkTime = ?, ShrinkTemperature = ?, "   /* items 5 */
    "ShrinkMutex = ?, "

    "HashCode = ?, "                                                                /* item 1 */

    "BatchSize = ?, StopCount = ?, TestMode = ?, TEACHMODETYPE = ?, "               /* items 36 */
    "TimePLRG_STD = ?, TimeMSRG_STD = ?, PowerPLRG_STD = ?, PowerMSRG_STD = ?, "
    "PreHeightPLRG_STD = ?, PreHeightMSRG_STD = ?, HeightPLRG_STD = ?, HeightMSRG_STD = ?, "
    "ForcePLRG_STD = ?, ForceMSRG_STD = ?, "
    "TimePLRG_AUTO = ?, TimeMSRG_AUTO = ?, PowerPLRG_AUTO = ?, PowerMSRG_AUTO = ?, "
    "PreHeightPLRG_AUTO = ?, PreHeightMSRG_AUTO = ?, HeightPLRG_AUTO = ?, HeightMSRG_AUTO = ?, "
    "ForcePLRG_AUTO = ?, ForceMSRG_AUTO = ?, "
    "TimeConfigPL = ?, TimeConfigMS = ?, "
    "PowerConfigPL = ?, PowerConfigMS = ?, PreHeightConfigPL = ?, PreHeightConfigMS = ?, "
    "HeightConfigPL = ?, HeightCOnfigMS = ?, "
    "StandardQuantity = ?, AutoQuantity = ?, SigmaQuantity = ?, "
    "TestingDone = ?, "

    "NoOfWires = ?, JSONWire = ? "                                                     /* items 2 */
    "WHERE ID = ?",                                 /*6 Update One Record to Splice Table*/

};

DBPresetTable* DBPresetTable::Instance()
{
    if(_instance == 0){
        _instance = new DBPresetTable();
    }
    return _instance;
}

DBPresetTable::DBPresetTable()
{
    SpliceDBObj = QSqlDatabase::addDatabase("QSQLITE","SpliceDBObjConnect");
    SpliceDBObj.setDatabaseName(DatabaseDir + SpliceDBFile);
    if(SpliceDBObj.open())
    {
        if(!SpliceDBObj.tables().contains("Preset")){
            CreateNewTable();
        }
    }
    SpliceDBObj.close();
}

bool DBPresetTable::OpenDBObject()
{
    bool bResult = false;
    struct BransonMessageBox tmpMsgBox;
    InterfaceClass* _Interface = InterfaceClass::Instance();
    QDir DBDirectory;
    mIsModularProduction = _Interface->StatusData.EnableModularFlag;
    if(mIsModularProduction == true)
    {
        if (DBDirectory.exists(ModularDatabaseDir + SpliceDBFile) == false)
        {
            tmpMsgBox.MsgTitle = QObject::tr("ERROR");
            tmpMsgBox.MsgPrompt = QObject::tr("Please make sure All the production files has been in the Modular Production!");
            tmpMsgBox.TipsMode = Critical;
            tmpMsgBox.func_ptr = NULL;
            _Interface->cMsgBox(&tmpMsgBox);
            qDebug()<<"Send Alarm signal";
            return bResult;
        }
    }

    QSqlQuery query(SpliceDBObj);
    if(SpliceDBObj.open() == false)
    {

        qDebug() << "SQL Open:"<< query.lastError();
        bResult = false;
    }else
        bResult = true;
    return bResult;
}

void DBPresetTable::SwitchDBObject(bool IsModularProduction)
{
    mIsModularProduction = IsModularProduction;
    {SpliceDBObj.close();}
    if(mIsModularProduction == true)
    {
        SpliceDBObj.setDatabaseName(ModularDatabaseDir + SpliceDBFile);
    }
    else
    {
        SpliceDBObj.setDatabaseName(DatabaseDir + SpliceDBFile);
    }

    OpenDBObject();
    SpliceDBObj.close();
}

DBPresetTable::~DBPresetTable()
{
    SpliceDBObj.close();
}

bool DBPresetTable::CreateNewTable()
{
    QSqlQuery query(SpliceDBObj);
    bool bResult = SpliceDBObj.open();

    bResult = query.exec(SQLSentence[SQLITCLASS::CREATE]);   //run SQL

    if(bResult == false)
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();

    SpliceDBObj.close();

    return bResult;
}

int DBPresetTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    int iResult = ERROR;
    if(_obj == NULL)
        return false;

    QSqlQuery query(SpliceDBObj);
    bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }

    UtilityClass *_Utility = UtilityClass::Instance();

    query.prepare(SQLSentence[SQLITCLASS::INSERT]);
    query.addBindValue(((PresetElement*)_obj)->SpliceName);
    QDateTime TimeLabel = QDateTime::currentDateTime();
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((PresetElement*)_obj)->OperatorID);
    query.addBindValue(((PresetElement*)_obj)->CrossSection);
    query.addBindValue(((PresetElement*)_obj)->PresetPicNamePath);
    query.addBindValue(((PresetElement*)_obj)->Verified);

    query.addBindValue(((PresetElement*)_obj)->WeldSettings.BasicSetting.Energy);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.BasicSetting.Amplitude);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.BasicSetting.Width);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.BasicSetting.Pressure);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.BasicSetting.TrigPres);


    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Time.Plus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Time.Minus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Power.Plus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Power.Minus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Preheight.Plus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Preheight.Minus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Height.Plus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Height.Minus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Force.Plus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Force.Minus);

    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.WeldMode);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.StepWeldMode);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.EnergyToStep);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.TimeToStep);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.PowerToStep);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.Amplitude2);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.PreBurst);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.HoldTime);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.SqzTime);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ABDelay);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ABDur);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.CutOff);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.CutOffSpliceTime);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.Cutter4HeightAlarm);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.Cutter4PowerAlarm);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.Cutter4PreHeightAlarm);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.Cutter4TimeAlarm);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.AntiSideOption.AntiSideMode);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.AntiSideOption.AntiSideSpliceTime);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.OffsetOption.MeasuredWidth);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.OffsetOption.MeasuredHeight);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.OffsetOption.DisplayWidth);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.OffsetOption.DisplayHeight);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkMutex);

    unsigned int HashCode = qHashBits(&(((PresetElement*)_obj)->WeldSettings), sizeof(((PresetElement*)_obj)->WeldSettings), 0);
    query.addBindValue(HashCode);

    query.addBindValue(((PresetElement*)_obj)->TestSetting.BatchSize);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.StopCount);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.TestMode);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModeType);
    for(int i = 0; i< ENERGY_ADJ; i++)
    {
        query.addBindValue(((PresetElement*)_obj)->TestSetting.
                            TeachModeSetting.TeachModequal_Window[i]);
    }
    query.addBindValue(((PresetElement*)_obj)->TestSetting.
                       TeachModeSetting.StandardRunQuantity);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.
                       TeachModeSetting.AutoRunQuantity);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.
                       TeachModeSetting.SigmaRunQuantity);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.TestingDone);

    query.addBindValue(((PresetElement*)_obj)->NoOfWires);

    QString tmpJson;
    _Utility->MapJsonToString(&((PresetElement*)_obj)->WireIndex,tmpJson);
    query.addBindValue(tmpJson);

    bResult = query.exec();   //run SQL

    if (bResult == false)
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();
    else
        iResult = query.lastInsertId().toInt(&bResult);
    if(bResult == false)
        iResult = ERROR;
    SpliceDBObj.close();
    return iResult;

}

bool DBPresetTable::QueryEntireTable(QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;
    QSqlQuery query(SpliceDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
        return bResult;

    bResult = query.exec(SQLSentence[SQLITCLASS::QUERY_ENTIRE_TABLE]);
    if (bResult == true)
    {
        _obj->clear();
        while(query.next())
        {
            _obj->insert(query.value("ID").toInt(),
                           query.value("SpliceName").toString());
        }
    }
    else
    {
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();
    }

    SpliceDBObj.close();

    return bResult;
}

bool DBPresetTable::QueryOneRecordFromTable(int ID, QString Name, void *_obj)
{
    if(_obj == NULL)
        return false;
    QSqlQuery query(SpliceDBObj);
    bool bResult = OpenDBObject();
    UtilityClass *_Utility = UtilityClass::Instance();
    if(bResult == false)
    {
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD]);
    query.addBindValue(ID);
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == false)
    {
        SpliceDBObj.close();
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        SpliceDBObj.close();
        return bResult;
    }

    ((PresetElement*)_obj)->SpliceID = query.value("ID").toInt();
    ((PresetElement*)_obj)->SpliceName = query.value("SpliceName").toString();
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((PresetElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((PresetElement*)_obj)->OperatorID = query.value("OperatorID").toInt();
    ((PresetElement*)_obj)->CrossSection = query.value("CrossSection").toInt();
    ((PresetElement*)_obj)->PresetPicNamePath = query.value("PresetPicPath").toString();
    ((PresetElement*)_obj)->Verified = query.value("Verified").toBool();
    ((PresetElement*)_obj)->WeldSettings.BasicSetting.Energy =
            query.value("Energy").toInt();
    ((PresetElement*)_obj)->WeldSettings.BasicSetting.Amplitude =
            query.value("Amplitude").toInt();
    ((PresetElement*)_obj)->WeldSettings.BasicSetting.Width =
            query.value("Width").toInt();
    ((PresetElement*)_obj)->WeldSettings.BasicSetting.Pressure =
            query.value("Pressure").toInt();
    ((PresetElement*)_obj)->WeldSettings.BasicSetting.TrigPres =
            query.value("TrigPres").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Time.Plus =
            query.value("TimePlus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Time.Minus =
            query.value("TimeMinus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Power.Plus =
            query.value("PowerPlus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Power.Minus =
            query.value("PowerMinus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Preheight.Plus =
            query.value("PreheightPlus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Preheight.Minus =
            query.value("PreheightMinus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Height.Plus =
            query.value("HeightPlus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Height.Minus =
            query.value("HeightMinus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Force.Plus =
            query.value("ForcePlus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Force.Minus =
            query.value("ForceMinus").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.WeldMode =
            (ADVANCESETTING::WELDMODE)query.value("WeldMode").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.StepWeldMode =
            (STEPWELD::STEPWELDMODE)query.value("StepWeldMode").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.EnergyToStep =
            query.value("EnergyToStep").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.TimeToStep =
            query.value("TimeToStep").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.PowerToStep =
            query.value("PowerToStep").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.Amplitude2 =
            query.value("Amplitude2").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.PreBurst = query.value("PreBurst").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.HoldTime = query.value("HoldTime").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.SqzTime = query.value("SqueezeTime").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ABDelay = query.value("AfterBurstDelay").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ABDur = query.value("AfterBurstDuring").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.CutOff =
            query.value("CutOff").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.CutOffSpliceTime =
            query.value("CutOffSpliceTime").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.Cutter4HeightAlarm =
            query.value("CutOffHeightAlarm").toBool();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.Cutter4PowerAlarm =
            query.value("CutOffPowerAlarm").toBool();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.Cutter4PreHeightAlarm =
            query.value("CutOffPreHeightAlarm").toBool();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.Cutter4TimeAlarm =
            query.value("CutOffTimeAlarm").toBool();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.AntiSideOption.AntiSideMode =
            query.value("AntiSide").toBool();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.AntiSideOption.AntiSideSpliceTime =
            query.value("AntiSideSpliceTime").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.OffsetOption.MeasuredWidth =
            query.value("MeasuredWidth").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.OffsetOption.MeasuredHeight =
            query.value("MeasuredHeight").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.OffsetOption.DisplayWidth =
            query.value("DisplayWidth").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.OffsetOption.DisplayHeight =
            query.value("DisplayHeight").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption =
            query.value("ShrinkOption").toBool();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID =
            query.value("ShrinkTubeID").toString();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime =
            query.value("ShrinkTime").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature =
            query.value("ShrinkTemperature").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkMutex =
            query.value("ShrinkMutex").toBool();
    ((PresetElement*)_obj)->HashCode = query.value("HashCode").toInt();

    ((PresetElement*)_obj)->TestSetting.BatchSize = query.value("BatchSize").toInt();
    ((PresetElement*)_obj)->TestSetting.StopCount = query.value("StopCount").toInt();
    ((PresetElement*)_obj)->TestSetting.TestMode =
            (TESTSETTING::TESTMODE)query.value("TestMode").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModeType =
            (TEACHMODESETTING::TEACH_MODE_TYPE)query.value("TeachModeType").toInt();

    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[0] =
            query.value("TimePLRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[1] =
            query.value("TimeMSRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[2] =
            query.value("PowerPLRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[3] =
            query.value("PowerMSRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[4] =
            query.value("PreHeightPLRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[5] =
            query.value("PreHeightMSRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[6] =
            query.value("HeightPLRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[7] =
            query.value("HeightMSRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[8] =
            query.value("ForcePLRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[9] =
            query.value("ForceMSRG_STD").toInt();

    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[10] =
            query.value("TimePLRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[11] =
            query.value("TimeMSRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[12] =
            query.value("PowerPLRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[13] =
            query.value("PowerMSRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[14] =
            query.value("PreHeightPLRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[15] =
            query.value("PreHeightMSRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[16] =
            query.value("HeightPLRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[17] =
            query.value("HeightMSRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[18] =
            query.value("ForcePLRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[19] =
            query.value("ForceMSRG_AUTO").toInt();

    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[20] =
            query.value("TimeConfigPL").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[21] =
            query.value("TimeConfigMS").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[22] =
            query.value("PowerConfigPL").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[23] =
            query.value("PowerConfigMS").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[24] =
            query.value("PreHeightConfigPL").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[25] =
            query.value("PreHeightConfigMS").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[26] =
            query.value("HeightConfigPL").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[27] =
            query.value("HeightCOnfigMS").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.StandardRunQuantity =
            query.value("StandardQuantity").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.AutoRunQuantity =
            query.value("AutoQuantity").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.SigmaRunQuantity =
            query.value("SigmaQuantity").toInt();
    ((PresetElement*)_obj)->TestSetting.TestingDone = query.value("TestingDone").toBool();

    QString tmpStr = query.value("JSONWire").toString();
    _Utility->StringJsonToMap(tmpStr, &((PresetElement*)_obj)->WireIndex);
    ((PresetElement*)_obj)->NoOfWires = ((PresetElement*)_obj)->WireIndex.size();

    SpliceDBObj.close();
    return bResult;
}

bool DBPresetTable::QueryOneRecordFromTable(int ID, void *_obj)
{
    if(_obj == NULL)
        return false;
    QSqlQuery query(SpliceDBObj);
    bool bResult = OpenDBObject();
    UtilityClass *_Utility = UtilityClass::Instance();
    if(bResult == false)
    {
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD_ONLY_ID]);
    query.addBindValue(ID);

    bResult = query.exec();
    if(bResult == false)
    {
        SpliceDBObj.close();
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        SpliceDBObj.close();
        return bResult;
    }

    ((PresetElement*)_obj)->SpliceID = query.value("ID").toInt();
    ((PresetElement*)_obj)->SpliceName = query.value("SpliceName").toString();
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((PresetElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((PresetElement*)_obj)->OperatorID = query.value("OperatorID").toInt();
    ((PresetElement*)_obj)->CrossSection = query.value("CrossSection").toInt();
    ((PresetElement*)_obj)->PresetPicNamePath = query.value("PresetPicPath").toString();
    ((PresetElement*)_obj)->Verified = query.value("Verified").toBool();
    ((PresetElement*)_obj)->WeldSettings.BasicSetting.Energy =
            query.value("Energy").toInt();
    ((PresetElement*)_obj)->WeldSettings.BasicSetting.Amplitude =
            query.value("Amplitude").toInt();
    ((PresetElement*)_obj)->WeldSettings.BasicSetting.Width =
            query.value("Width").toInt();
    ((PresetElement*)_obj)->WeldSettings.BasicSetting.Pressure =
            query.value("Pressure").toInt();
    ((PresetElement*)_obj)->WeldSettings.BasicSetting.TrigPres =
            query.value("TrigPres").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Time.Plus =
            query.value("TimePlus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Time.Minus =
            query.value("TimeMinus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Power.Plus =
            query.value("PowerPlus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Power.Minus =
            query.value("PowerMinus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Preheight.Plus =
            query.value("PreheightPlus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Preheight.Minus =
            query.value("PreheightMinus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Height.Plus =
            query.value("HeightPlus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Height.Minus =
            query.value("HeightMinus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Force.Plus =
            query.value("ForcePlus").toInt();
    ((PresetElement*)_obj)->WeldSettings.QualitySetting.Force.Minus =
            query.value("ForceMinus").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.WeldMode =
            (ADVANCESETTING::WELDMODE)query.value("WeldMode").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.StepWeldMode =
            (STEPWELD::STEPWELDMODE)query.value("StepWeldMode").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.EnergyToStep =
            query.value("EnergyToStep").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.TimeToStep =
            query.value("TimeToStep").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.PowerToStep =
            query.value("PowerToStep").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.Amplitude2 =
            query.value("Amplitude2").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.PreBurst = query.value("PreBurst").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.HoldTime = query.value("HoldTime").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.SqzTime = query.value("SqueezeTime").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ABDelay = query.value("AfterBurstDelay").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ABDur = query.value("AfterBurstDuring").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.CutOff =
            query.value("CutOff").toBool();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.CutOffSpliceTime =
            query.value("CutOffSpliceTime").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.Cutter4HeightAlarm =
            query.value("CutOffHeightAlarm").toBool();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.Cutter4PowerAlarm =
            query.value("CutOffPowerAlarm").toBool();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.Cutter4PreHeightAlarm =
            query.value("CutOffPreHeightAlarm").toBool();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.Cutter4TimeAlarm =
            query.value("CutOffTimeAlarm").toBool();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.AntiSideOption.AntiSideMode =
            query.value("AntiSide").toBool();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.AntiSideOption.AntiSideSpliceTime =
            query.value("AntiSideSpliceTime").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.OffsetOption.MeasuredWidth =
            query.value("MeasuredWidth").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.OffsetOption.MeasuredHeight =
            query.value("MeasuredHeight").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.OffsetOption.DisplayWidth =
            query.value("DisplayWidth").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.OffsetOption.DisplayHeight =
            query.value("DisplayHeight").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption =
            query.value("ShrinkOption").toBool();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID = query.value("ShrinkTubeID").toString();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime = query.value("ShrinkTime").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature =
            query.value("ShrinkTemperature").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkMutex =
            query.value("ShrinkMutex").toBool();
    ((PresetElement*)_obj)->HashCode = query.value("HashCode").toInt();

    ((PresetElement*)_obj)->TestSetting.BatchSize = query.value("BatchSize").toInt();
    ((PresetElement*)_obj)->TestSetting.StopCount = query.value("StopCount").toInt();
    ((PresetElement*)_obj)->TestSetting.TestMode =
            (TESTSETTING::TESTMODE)query.value("TestMode").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModeType =
            (TEACHMODESETTING::TEACH_MODE_TYPE)query.value("TeachModeType").toInt();

    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[0] =
            query.value("TimePLRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[1] =
            query.value("TimeMSRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[2] =
            query.value("PowerPLRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[3] =
            query.value("PowerMSRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[4] =
            query.value("PreHeightPLRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[5] =
            query.value("PreHeightMSRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[6] =
            query.value("HeightPLRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[7] =
            query.value("HeightMSRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[8] =
            query.value("ForcePLRG_STD").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[9] =
            query.value("ForceMSRG_STD").toInt();

    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[10] =
            query.value("TimePLRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[11] =
            query.value("TimeMSRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[12] =
            query.value("PowerPLRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[13] =
            query.value("PowerMSRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[14] =
            query.value("PreHeightPLRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[15] =
            query.value("PreHeightMSRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[16] =
            query.value("HeightPLRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[17] =
            query.value("HeightMSRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[18] =
            query.value("ForcePLRG_AUTO").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[19] =
            query.value("ForceMSRG_AUTO").toInt();

    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[20] =
            query.value("TimeConfigPL").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[21] =
            query.value("TimeConfigMS").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[22] =
            query.value("PowerConfigPL").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[23] =
            query.value("PowerConfigMS").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[24] =
            query.value("PreHeightConfigPL").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[25] =
            query.value("PreHeightConfigMS").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[26] =
            query.value("HeightConfigPL").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[27] =
            query.value("HeightCOnfigMS").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.StandardRunQuantity =
            query.value("StandardQuantity").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.AutoRunQuantity =
            query.value("AutoQuantity").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.SigmaRunQuantity =
            query.value("SigmaQuantity").toInt();
    ((PresetElement*)_obj)->TestSetting.TestingDone = query.value("TestingDone").toBool();

    QString tmpStr = query.value("JSONWire").toString();
    _Utility->StringJsonToMap(tmpStr, &((PresetElement*)_obj)->WireIndex);
    ((PresetElement*)_obj)->NoOfWires = ((PresetElement*)_obj)->WireIndex.size();

    SpliceDBObj.close();
    return bResult;
}

bool DBPresetTable::QueryOneRecordFromTable(int ID, QStringList &ResultStr)
{
    QSqlQuery query(SpliceDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD_ONLY_ID]);
    query.addBindValue(ID);

    bResult = query.exec();
    if(bResult == false)
    {
        SpliceDBObj.close();
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        SpliceDBObj.close();
        return bResult;
    }

    ResultStr.append(query.value("ID").toString());
    ResultStr.append(query.value("SpliceName").toString());
    ResultStr.append(query.value("CreatedDate").toString());
    ResultStr.append(query.value("OperatorID").toString());
    ResultStr.append(query.value("CrossSection").toString());
    ResultStr.append(query.value("PresetPicPath").toString());
    ResultStr.append(query.value("Verified").toString());
    ResultStr.append(query.value("Energy").toString());
    ResultStr.append(query.value("Amplitude").toString());
    ResultStr.append(query.value("Width").toString());
    ResultStr.append(query.value("Pressure").toString());
    ResultStr.append(query.value("TrigPres").toString());
    ResultStr.append(query.value("TimePlus").toString());
    ResultStr.append(query.value("TimeMinus").toString());
    ResultStr.append(query.value("PowerPlus").toString());
    ResultStr.append(query.value("PowerMinus").toString());
    ResultStr.append(query.value("PreheightPlus").toString());
    ResultStr.append(query.value("PreheightMinus").toString());
    ResultStr.append(query.value("HeightPlus").toString());
    ResultStr.append(query.value("HeightMinus").toString());
    ResultStr.append(query.value("ForcePlus").toString());
    ResultStr.append(query.value("ForceMinus").toString());
    ResultStr.append(query.value("WeldMode").toString());
    ResultStr.append(query.value("StepWeldMode").toString());
    ResultStr.append(query.value("EnergyToStep").toString());
    ResultStr.append(query.value("TimeToStep").toString());
    ResultStr.append(query.value("PowerToStep").toString());
    ResultStr.append(query.value("Amplitude2").toString());
    ResultStr.append(query.value("PreBurst").toString());
    ResultStr.append(query.value("HoldTime").toString());
    ResultStr.append(query.value("SqueezeTime").toString());
    ResultStr.append(query.value("AfterBurstDelay").toString());
    ResultStr.append(query.value("AfterBurstDuring").toString());
    ResultStr.append(query.value("CutOff").toString());
    ResultStr.append(query.value("CutOffSpliceTime").toString());
    ResultStr.append(query.value("CutOffHeightAlarm").toString());
    ResultStr.append(query.value("CutOffPowerAlarm").toString());
    ResultStr.append(query.value("CutOffPreHeightAlarm").toString());
    ResultStr.append(query.value("CutOffTimeAlarm").toString());
    ResultStr.append(query.value("AntiSide").toString());
    ResultStr.append(query.value("AntiSideSpliceTime").toString());
    ResultStr.append(query.value("MeasuredWidth").toString());
    ResultStr.append(query.value("MeasuredHeight").toString());
    ResultStr.append(query.value("DisplayWidth").toString());
    ResultStr.append(query.value("DisplayHeight").toString());
    ResultStr.append(query.value("ShrinkOption").toString());
    ResultStr.append(query.value("ShrinkTubeID").toString());
    ResultStr.append(query.value("ShrinkTime").toString());
    ResultStr.append(query.value("ShrinkTemperature").toString());
    ResultStr.append(query.value("ShrinkMutex").toString());
    ResultStr.append(query.value("HashCode").toString());

    ResultStr.append(query.value("BatchSize").toString());
    ResultStr.append(query.value("StopCount").toString());
    ResultStr.append(query.value("TestMode").toString());
    ResultStr.append(query.value("TeachModeType").toString());

    ResultStr.append(query.value("TimePLRG_STD").toString());
    ResultStr.append(query.value("TimeMSRG_STD").toString());
    ResultStr.append(query.value("PowerPLRG_STD").toString());
    ResultStr.append(query.value("PowerMSRG_STD").toString());
    ResultStr.append(query.value("PreHeightPLRG_STD").toString());
    ResultStr.append(query.value("PreHeightMSRG_STD").toString());
    ResultStr.append(query.value("HeightPLRG_STD").toString());
    ResultStr.append(query.value("HeightMSRG_STD").toString());
    ResultStr.append(query.value("ForcePLRG_STD").toString());
    ResultStr.append(query.value("ForceMSRG_STD").toString());

    ResultStr.append(query.value("TimePLRG_AUTO").toString());
    ResultStr.append(query.value("TimeMSRG_AUTO").toString());
    ResultStr.append(query.value("PowerPLRG_AUTO").toString());
    ResultStr.append(query.value("PowerMSRG_AUTO").toString());
    ResultStr.append(query.value("PreHeightPLRG_AUTO").toString());
    ResultStr.append(query.value("PreHeightMSRG_AUTO").toString());
    ResultStr.append(query.value("HeightPLRG_AUTO").toString());
    ResultStr.append(query.value("HeightMSRG_AUTO").toString());
    ResultStr.append(query.value("ForcePLRG_AUTO").toString());
    ResultStr.append(query.value("ForceMSRG_AUTO").toString());

    ResultStr.append(query.value("TimeConfigPL").toString());
    ResultStr.append(query.value("TimeConfigMS").toString());
    ResultStr.append(query.value("PowerConfigPL").toString());
    ResultStr.append(query.value("PowerConfigMS").toString());
    ResultStr.append(query.value("PreHeightConfigPL").toString());
    ResultStr.append(query.value("PreHeightConfigMS").toString());
    ResultStr.append(query.value("HeightConfigPL").toString());
    ResultStr.append(query.value("HeightCOnfigMS").toString());
    ResultStr.append(query.value("StandardQuantity").toString());
    ResultStr.append(query.value("AutoQuantity").toString());
    ResultStr.append(query.value("SigmaQuantity").toString());
    ResultStr.append(query.value("TestingDone").toString());

    ResultStr.append(query.value("NoOfWires").toString());
    ResultStr.append(query.value("JSONWire").toString());

    SpliceDBObj.close();
    return bResult;
}

bool DBPresetTable::DeleteEntireTable()
{
    QSqlQuery query(SpliceDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.exec(SQLSentence[SQLITCLASS::DELETE_ENTIRE_TABLE]);
    if(bResult == false)
    {
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();
    }

    SpliceDBObj.close();
    return bResult;
}

bool DBPresetTable::DeleteOneRecordFromTable(int ID, QString Name)
{
    QSqlQuery query(SpliceDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::DELETE_ONE_RECORD]);
    query.addBindValue(ID);
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();
    }
    SpliceDBObj.close();
    return bResult;
}

bool DBPresetTable::UpdateRecordIntoTable(void *_obj)
{
    if(_obj == NULL)
        return false;
    UtilityClass* _Utility = UtilityClass::Instance();
    QSqlQuery query(SpliceDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
    {
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::UPDATE_ONE_RECORD]);
    query.addBindValue(((PresetElement*)_obj)->SpliceName);
    QDateTime TimeLabel = QDateTime::fromTime_t(((PresetElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((PresetElement*)_obj)->OperatorID);
    query.addBindValue(((PresetElement*)_obj)->CrossSection);
    query.addBindValue(((PresetElement*)_obj)->PresetPicNamePath);
    query.addBindValue(((PresetElement*)_obj)->Verified);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.BasicSetting.Energy);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.BasicSetting.Amplitude);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.BasicSetting.Width);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.BasicSetting.Pressure);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.BasicSetting.TrigPres);

    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Time.Plus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Time.Minus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Power.Plus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Power.Minus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Preheight.Plus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Preheight.Minus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Height.Plus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Height.Minus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Force.Plus);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.QualitySetting.Force.Minus);

    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.WeldMode);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.StepWeldMode);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.EnergyToStep);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.TimeToStep);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.PowerToStep);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.Amplitude2);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.PreBurst);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.HoldTime);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.SqzTime);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ABDelay);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ABDur);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.CutOff);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.CutOffSpliceTime);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.Cutter4HeightAlarm);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.Cutter4PowerAlarm);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.Cutter4PreHeightAlarm);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffOption.Cutter4TimeAlarm);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.AntiSideOption.AntiSideMode);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.AntiSideOption.AntiSideSpliceTime);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.OffsetOption.MeasuredWidth);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.OffsetOption.MeasuredHeight);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.OffsetOption.DisplayWidth);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.OffsetOption.DisplayHeight);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkMutex);
    query.addBindValue(((PresetElement*)_obj)->HashCode);

    query.addBindValue(((PresetElement*)_obj)->TestSetting.BatchSize);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.StopCount);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.TestMode);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModeType);
    for(int i = 0; i < ENERGY_ADJ; i++)
        query.addBindValue(((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[i]);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.TeachModeSetting.StandardRunQuantity);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.TeachModeSetting.AutoRunQuantity);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.TeachModeSetting.SigmaRunQuantity);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.TestingDone);

    QString tmpStr;
    _Utility->MapJsonToString(&((PresetElement*)_obj)->WireIndex, tmpStr);
    query.addBindValue(((PresetElement*)_obj)->WireIndex.size()); //NoOfWire
    query.addBindValue(tmpStr); //PresetElement->WireIndex
    query.addBindValue(((PresetElement*)_obj)->SpliceID);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();
    }
    SpliceDBObj.close();
    return bResult;
}

bool DBPresetTable::QueryOnlyUseName(QString Name, QMap<int, QString> *_obj)
{

    if(_obj == NULL)
        return false;

    QSqlQuery query(SpliceDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, SpliceName FROM Preset WHERE SpliceName = ?");
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == true)
    {
        _obj->clear();
        while(query.next())
            _obj->insert(query.value("ID").toInt(),
                           query.value("SpliceName").toString());
    }
    else
    {
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();
    }

    SpliceDBObj.close();
    return bResult;
}

bool DBPresetTable::QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(SpliceDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, SpliceName FROM Preset WHERE CreatedDate >= ?"
                  " AND CreatedDate <= ?");
    QDateTime TimeLabel = QDateTime::fromTime_t(time_from);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    TimeLabel = QDateTime::fromTime_t(time_to);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));

    bResult = query.exec();
    if(bResult == true)
    {
        _obj->clear();
        while(query.next())
            _obj->insert(query.value("ID").toInt(),
                           query.value("SpliceName").toString());
    }
    else
    {
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();
    }

    SpliceDBObj.close();
    return bResult;
}

bool DBPresetTable::QueryUseNameAndTime(QString Name, unsigned int time_from,
                unsigned int time_to, QMap<int, QString>* _obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(SpliceDBObj);
    bool bResult = OpenDBObject();
    if(bResult == false)
        return bResult;

    query.prepare("SELECT ID, SpliceName FROM Preset WHERE CreatedDate >= ? "
                  "AND CreatedDate <= ? AND SpliceName == ?");
    QDateTime TimeLabel = QDateTime::fromTime_t(time_from);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    TimeLabel = QDateTime::fromTime_t(time_to);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(Name);
    bResult = query.exec();
    if(bResult == true)
    {
        _obj->clear();
        while(query.next())
            _obj->insert(query.value("ID").toInt(),
                           query.value("SpliceName").toString());
    }
    else
    {
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();
    }

    SpliceDBObj.close();
    return bResult;
}
