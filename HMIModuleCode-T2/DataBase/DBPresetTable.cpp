#include "DBPresetTable.h"
#include "Modules/UtilityClass.h"
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

    /*AdvanceSetting*/                                          /* 15 items */
    "WeldMode INT, StepWeldMode INT, EnergyToStep INT, TimeToStep INT, "
    "PowerToStep INT, Amplitude2 INT, PreBurst INT, HoldTime INT, "
    "SqueezeTime INT, AfterBurstDelay INT, AfterBurstDuring INT, "
    "CutOff BOOLEAN, CutOffSpliceTime INT, AntiSide BOOLEAN, AntiSideSpliceTime INT, "
    "MeasuredWidth INT, MeasuredHeight INT, "

    "HashCode INT, "

    /*Shrink Tube Setting*/
    "ShrinkOption BOOLEAN, ShrinkTubeID INT, ShrinkTime INT, "
    "ShrinkTemperature INT, "                                   /*4 items */

    /*Testing*/
    "Qutanty INT, StopCount INT, TestMode INT, TEACHMODETYPE ENUM, "
    "TimePLRG INT, TimeMSRG INT, PowerPLRG INT, PowerMSRG INT, "
    "PreHeightPLRG INT, PreHeightMSRG INT, HeightPLRG INT, HeightMSRG INT, "
    "ForcePLRG INT, ForceMSRG INT, TimeConfigPL INT, TimeConfigMS INT, "
    "PowerConfigPL INT, PowerConfigMS INT, PreHeightConfigPL INT, PreHeightConfigMS INT, "
    "HeightConfigPL INT, HeightCOnfigMS INT, TestingDone BOOLEAN, "                /* 23 items */

    "NoOfWires INT, "
    /*JSON Structure WireID, WireName*/
    "JSONWire VARCHAR)",                 /*2 items */

    "INSERT INTO Preset ("                      /*1 Insert record into Preset Table*/
    "SpliceName, CreatedDate, OperatorID, CrossSection, PresetPicPath, Verified, "

    /*WeldSetting*/
    "Energy, Amplitude, Width, Pressure, TrigPres, "

    /*QualityWindowSetting*/
    "TimePlus, TimeMinus, PowerPlus, PowerMinus, PreheightPlus, PreheightMinus, "
    "HeightPlus, HeightMinus, ForcePlus, ForceMinus, "

    /*AdvanceSetting*/
    "WeldMode, StepWeldMode, EnergyToStep, TimeToStep, PowerToStep, Amplitude2, "
    "PreBurst, HoldTime, SqueezeTime, AfterBurstDelay, AfterBurstDuring, CutOff, "
    "CutOffSpliceTime, AntiSide, AntiSideSpliceTime, MeasuredWidth, MeasuredHeight, "

    /*Shrink Tube Setting*/
    "ShrinkOption, ShrinkTubeID, ShrinkTime, ShrinkTemperature, "

    "HashCode, "

    /*Testing*/
    "Qutanty, StopCount, TestMode, TEACHMODETYPE, TimePLRG, TimeMSRG, "
    "PowerPLRG, PowerMSRG, PreHeightPLRG, PreHeightMSRG, HeightPLRG, HeightMSRG, "
    "ForcePLRG, ForceMSRG, TimeConfigPL, TimeConfigMS, PowerConfigPL, PowerConfigMS, "
    "PreHeightConfigPL, PreHeightConfigMS, HeightConfigPL, HeightCOnfigMS, TestingDone, "

    /*JSON Structure WireID, WireName*/
    "NoOfWires, JSONWire) "
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
    "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
    "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",

    "SELECT ID, SpliceName FROM Preset",        /*2 Query Entire Preset Table */

    "SELECT * FROM Preset WHERE ID = ? AND SpliceName = ?",
                                                /*3 Query One Record From Part Table */

    "SELECT * FROM Preset WHERE ID = ?",        /*4 Query One Record Only Use ID */

    "DELETE FROM Preset",                       /*4 Delete Entire Splice Table*/

    "DELETE FROM Preset WHERE ID = ? AND SpliceName = ?",
                                                /*5 Delete One Record from Splice Table*/

    "UPDATE Preset Set SpliceName = ?, CreatedDate = ?, OperatorID = ?, "
    "CrossSection = ?, PresetPicPath = ?, Verified = ?, " /* item 6 */
    "Energy = ?, Amplitude = ?, Width = ?, Pressure = ?, TrigPres= ?, " /* item 5 */

    "TimePlus = ?, TimeMinus = ?, PowerPlus = ?, PowerMinus = ?, "    /* item 10 */
    "PreheightPlus = ?, PreheightMinus= ?, HeightPlus = ?, HeightMinus = ?, "
    "ForcePlus = ?, ForceMinus = ?, "

    "WeldMode = ?, StepWeldMode = ?, EnergyToStep = ?, TimeToStep = ?, PowerToStep = ?, "
    "Amplitude2 = ?, PreBurst = ?, HoldTime = ?, SqueezeTime = ?, AfterBurstDelay = ?, "
    "AfterBurstDuring = ?, CutOff = ?, CutOffSpliceTime = ?, "
    "AntiSide = ?, AntiSideSpliceTime = ?, MeasuredWidth = ?, MeasuredHeight = ?, "  /* item 17 */

    "ShrinkOption = ?, ShrinkTubeID = ?, ShrinkTime = ?, ShrinkTemperature = ?, "

    "HashCode = ?, "

    "Qutanty = ?, StopCount = ?, TestMode = ?, TEACHMODETYPE = ?, "
    "TimePLRG = ?, TimeMSRG = ?, PowerPLRG = ?, PowerMSRG = ?, "
    "PreHeightPLRG = ?, PreHeightMSRG = ?, HeightPLRG = ?, HeightMSRG = ?, "
    "ForcePLRG = ?, ForceMSRG = ?, TimeConfigPL = ?, TimeConfigMS = ?, "
    "PowerConfigPL = ?, PowerConfigMS = ?, PreHeightConfigPL = ?, PreHeightConfigMS = ?, "
    "HeightConfigPL = ?, HeightCOnfigMS = ?, TestingDone = ?, "

    "NoOfWires = ?, JSONWire = ? "
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
//            InsertTestDataIntoTable();
        }
    }
    SpliceDBObj.close();
    wireTable = DBWireTable::Instance();
}

bool DBPresetTable::OpenDBObject()
{
    bool bResult = false;
    struct BransonMessageBox tmpMsgBox;
    InterfaceClass* _Interface = InterfaceClass::Instance();
    QDir DBDirectory;
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

void DBPresetTable::InsertTestDataIntoTable()
{
    struct PresetElement tmpSplice;
    QMap<int, QString> TestMap;
    TestMap.insert(0, "WANG");
    TestMap.insert(1,"Mr.Li");
    TestMap.insert(2, "Zhang");
    for (int i = 0; i < 6; i++)
    {
        if ( i == 0)
            tmpSplice.SpliceName = "KW001.0032";
        if ( i == 1)
            tmpSplice.SpliceName = "KW004.0013";
        if ( i == 2)
            tmpSplice.SpliceName = "mod_50742305_proc_1";
        if ( i == 3)
            tmpSplice.SpliceName = "mod_50742298_proc_1";
        tmpSplice.CreatedDate = QDateTime::currentDateTime().toTime_t();
        tmpSplice.OperatorID = 2;
        tmpSplice.CrossSection = 100;
        tmpSplice.PresetPicNamePath = "C:\\";
        tmpSplice.Verified = false;
        tmpSplice.WeldSettings.BasicSetting.Energy = 155;
        tmpSplice.WeldSettings.BasicSetting.Amplitude = 55;
        tmpSplice.WeldSettings.BasicSetting.Width = 800;
        tmpSplice.WeldSettings.BasicSetting.Pressure = 80;
        tmpSplice.WeldSettings.BasicSetting.TrigPres = 50;
        tmpSplice.WeldSettings.QualitySetting.Time.Plus = 500;
        tmpSplice.WeldSettings.QualitySetting.Time.Minus = 0;
        tmpSplice.WeldSettings.QualitySetting.Power.Plus = 3960;
        tmpSplice.WeldSettings.QualitySetting.Power.Minus = 0;
        tmpSplice.WeldSettings.QualitySetting.Preheight.Plus = 1500;
        tmpSplice.WeldSettings.QualitySetting.Preheight.Minus = 0;
        tmpSplice.WeldSettings.QualitySetting.Height.Plus = 1500;
        tmpSplice.WeldSettings.QualitySetting.Height.Minus = 0;
        tmpSplice.WeldSettings.QualitySetting.Force.Plus = 55;
        tmpSplice.WeldSettings.QualitySetting.Force.Minus = 0;
        tmpSplice.WeldSettings.AdvanceSetting.WeldMode = ENERGY;
        tmpSplice.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode = STEPDISABLE;
        tmpSplice.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep = 55;
        tmpSplice.WeldSettings.AdvanceSetting.StepWeld.TimeToStep = 1;
        tmpSplice.WeldSettings.AdvanceSetting.StepWeld.PowerToStep = 500;
        tmpSplice.WeldSettings.AdvanceSetting.StepWeld.Amplitude2 = 22;
        tmpSplice.WeldSettings.AdvanceSetting.PreBurst = 1000;
        tmpSplice.WeldSettings.AdvanceSetting.HoldTime = 100;
        tmpSplice.WeldSettings.AdvanceSetting.SqzTime = 200;
        tmpSplice.WeldSettings.AdvanceSetting.ABDelay = 300;
        tmpSplice.WeldSettings.AdvanceSetting.ABDur = 400;
        tmpSplice.WeldSettings.AdvanceSetting.CutOff = false;
        tmpSplice.WeldSettings.AdvanceSetting.CutOffSpliceTime = -1;
        tmpSplice.WeldSettings.AdvanceSetting.AntiSide = true;
        tmpSplice.WeldSettings.AdvanceSetting.AntiSideSpliceTime = -1;
        tmpSplice.WeldSettings.AdvanceSetting.MeasuredWidth = 100;
        tmpSplice.WeldSettings.AdvanceSetting.MeasuredHeight = 100;
        tmpSplice.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption = false;
        tmpSplice.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID = "0";
        tmpSplice.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime = 10;
        tmpSplice.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature = 260;
        tmpSplice.HashCode = qHashBits(&tmpSplice.WeldSettings, sizeof(tmpSplice.WeldSettings), 0);
        tmpSplice.TestSetting.Qutanty = 10;
        tmpSplice.TestSetting.StopCount = 20;
        tmpSplice.TestSetting.TestMode = UNCONSTRAINED;
        tmpSplice.TestSetting.TeachModeSetting.TeachModeType = UNDEFINED;
        for(int i=0;i< 18;i++)
            tmpSplice.TestSetting.TeachModeSetting.TeachModequal_Window[i] = 40;
        tmpSplice.TestSetting.TestingDone = true;
        QMap<int, QString>::const_iterator it = TestMap.constBegin();
        while (it != TestMap.constEnd()) {
            tmpSplice.WireIndex.insert(it.key(),it.value());
            ++it;
        }
        tmpSplice.NoOfWires = tmpSplice.WireIndex.size();

        InsertRecordIntoTable(&tmpSplice);
    }
}

DBPresetTable::~DBPresetTable()
{
    SpliceDBObj.close();
}

bool DBPresetTable::CreateNewTable()
{
    QSqlQuery query(SpliceDBObj);
    bool bResult = SpliceDBObj.open();

    bResult = query.exec(SQLSentence[CREATE]);   //run SQL

    if(bResult == false)
        qDebug() << "Preset Table SQL ERROR:"<< query.lastError();

    SpliceDBObj.close();

    return bResult;
}

int DBPresetTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    int iResult = -1;
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

    query.prepare(SQLSentence[INSERT]);
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
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOff);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffSpliceTime);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.AntiSide);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.AntiSideSpliceTime);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.MeasuredWidth);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.MeasuredHeight);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature);

    unsigned int HashCode = qHashBits(&(((PresetElement*)_obj)->WeldSettings), sizeof(((PresetElement*)_obj)->WeldSettings), 0);
    query.addBindValue(HashCode);

    query.addBindValue(((PresetElement*)_obj)->TestSetting.Qutanty);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.StopCount);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.TestMode);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModeType);
    for(int i = 0; i< 18; i++)
    {
        query.addBindValue(((PresetElement*)_obj)->TestSetting.
                            TeachModeSetting.TeachModequal_Window[i]);
    }
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
        iResult = -1;
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

    bResult = query.exec(SQLSentence[QUERY_ENTIRE_TABLE]);
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

    query.prepare(SQLSentence[QUERY_ONE_RECORD]);
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
            (enum WELDMODE)query.value("WeldMode").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.StepWeldMode =
            (enum STEPWELDMODE)query.value("StepWeldMode").toInt();
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
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOff = query.value("CutOff").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffSpliceTime =
            query.value("CutOffSpliceTime").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.AntiSide = query.value("AntiSide").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.AntiSideSpliceTime =
            query.value("AntiSideSpliceTime").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.MeasuredWidth = query.value("MeasuredWidth").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.MeasuredHeight = query.value("MeasuredHeight").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption =
            query.value("ShrinkOption").toBool();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID = query.value("ShrinkTubeID").toString();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime = query.value("ShrinkTime").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature =
            query.value("ShrinkTemperature").toInt();
    ((PresetElement*)_obj)->HashCode = query.value("HashCode").toInt();

    QString tmpStr = query.value("JSONWire").toString();
    _Utility->StringJsonToMap(tmpStr, &((PresetElement*)_obj)->WireIndex);
    ((PresetElement*)_obj)->NoOfWires = ((PresetElement*)_obj)->WireIndex.size();

    ((PresetElement*)_obj)->TestSetting.Qutanty = query.value("Qutanty").toInt();
    ((PresetElement*)_obj)->TestSetting.StopCount = query.value("StopCount").toInt();
    ((PresetElement*)_obj)->TestSetting.TestMode =
            (enum TESTMODE)query.value("TestMode").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModeType =
            (enum TEACH_MODE_TYPE)query.value("TeachModeType").toInt();

    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[0] =
            query.value("TimePLRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[1] =
            query.value("TimeMSRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[2] =
            query.value("PowerPLRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[3] =
            query.value("PowerMSRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[4] =
            query.value("PreHeightPLRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[5] =
            query.value("PreHeightMSRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[6] =
            query.value("HeightPLRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[7] =
            query.value("HeightMSRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[8] =
            query.value("ForcePLRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[9] =
            query.value("ForceMSRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[10] =
            query.value("TimeConfigPL").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[11] =
            query.value("TimeConfigMS").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[12] =
            query.value("PowerConfigPL").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[13] =
            query.value("PowerConfigMS").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[14] =
            query.value("PreHeightConfigPL").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[15] =
            query.value("PreHeightConfigMS").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[16] =
            query.value("HeightConfigPL").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[17] =
            query.value("HeightCOnfigMS").toInt();
    ((PresetElement*)_obj)->TestSetting.TestingDone = query.value("TestingDone").toBool();

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

    query.prepare(SQLSentence[QUERY_ONE_RECORD_ONLY_ID]);
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
            (enum WELDMODE)query.value("WeldMode").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.StepWeldMode =
            (enum STEPWELDMODE)query.value("StepWeldMode").toInt();
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
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOff = query.value("CutOff").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffSpliceTime =
            query.value("CutOffSpliceTime").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.AntiSide = query.value("AntiSide").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.AntiSideSpliceTime =
            query.value("AntiSideSpliceTime").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.MeasuredWidth = query.value("MeasuredWidth").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.MeasuredHeight = query.value("MeasuredHeight").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption =
            query.value("ShrinkOption").toBool();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID = query.value("ShrinkTubeID").toString();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime = query.value("ShrinkTime").toInt();
    ((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature =
            query.value("ShrinkTemperature").toInt();
    ((PresetElement*)_obj)->HashCode = query.value("HashCode").toInt();

    QString tmpStr = query.value("JSONWire").toString();
    _Utility->StringJsonToMap(tmpStr, &((PresetElement*)_obj)->WireIndex);
    ((PresetElement*)_obj)->NoOfWires = ((PresetElement*)_obj)->WireIndex.size();

    ((PresetElement*)_obj)->TestSetting.Qutanty = query.value("Qutanty").toInt();
    ((PresetElement*)_obj)->TestSetting.StopCount = query.value("StopCount").toInt();
    ((PresetElement*)_obj)->TestSetting.TestMode =
            (enum TESTMODE)query.value("TestMode").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModeType =
            (enum TEACH_MODE_TYPE)query.value("TeachModeType").toInt();

    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[0] =
            query.value("TimePLRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[1] =
            query.value("TimeMSRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[2] =
            query.value("PowerPLRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[3] =
            query.value("PowerMSRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[4] =
            query.value("PreHeightPLRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[5] =
            query.value("PreHeightMSRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[6] =
            query.value("HeightPLRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[7] =
            query.value("HeightMSRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[8] =
            query.value("ForcePLRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[9] =
            query.value("ForceMSRG").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[10] =
            query.value("TimeConfigPL").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[11] =
            query.value("TimeConfigMS").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[12] =
            query.value("PowerConfigPL").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[13] =
            query.value("PowerConfigMS").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[14] =
            query.value("PreHeightConfigPL").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[15] =
            query.value("PreHeightConfigMS").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[16] =
            query.value("HeightConfigPL").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[17] =
            query.value("HeightCOnfigMS").toInt();
    ((PresetElement*)_obj)->TestSetting.TestingDone = query.value("TestingDone").toBool();

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

    bResult = query.exec(SQLSentence[DELETE_ENTIRE_TABLE]);
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

    query.prepare(SQLSentence[DELETE_ONE_RECORD]);
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

    query.prepare(SQLSentence[UPDATE_ONE_RECORD]);
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
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOff);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.CutOffSpliceTime);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.AntiSide);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.AntiSideSpliceTime);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.MeasuredWidth);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.MeasuredHeight);

    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime);
    query.addBindValue(((PresetElement*)_obj)->WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature);
    query.addBindValue(((PresetElement*)_obj)->HashCode);

    query.addBindValue(((PresetElement*)_obj)->TestSetting.Qutanty);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.StopCount);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.TestMode);
    query.addBindValue(((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModeType);
    for(int i = 0; i < 18; i++)
        query.addBindValue(((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModequal_Window[i]);
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

bool DBPresetTable::exportData(int spliceId, QString fileUrl)
{
    QString queryStr;
    QString lineValue = "";
    QSqlQuery query(SpliceDBObj);
    QString wireData;
    bool bResult = OpenDBObject();
    bool ok;
    QString tempWireData;
    QString fileSource;
    if(bResult == true)
    {
        queryStr = QString("SELECT * FROM Preset WHERE ID == '%1'").arg(spliceId);
        query.prepare(queryStr);
        bResult = query.exec();
        if (bResult) {
            bResult = query.next();
            if(bResult) {
                for (int i = 0;i < 69;i++)
                {
                    if (i == 68)
                    {
                        QJsonParseError json_error;
                        QJsonDocument parse_document = QJsonDocument::fromJson(query.value(i).toString().toLatin1(), &json_error);
                        if(json_error.error == QJsonParseError::NoError)
                        {
                            if(parse_document.isObject())
                            {
                                QJsonObject obj = parse_document.object();
                                QJsonObject::const_iterator iterator = obj.constBegin();
                                for(int i = 0; i< obj.count(); i++)
                                {
                                    iterator = obj.constFind(QString::number(i, 10));
                                    if(iterator != obj.constEnd())
                                    {
                                        QString value = iterator.value().toString();
                                        QStringList strList = value.split(";");
                                        tempWireData = wireTable->GetExportString(((QString)strList.at(0)).toInt());
                                        wireData.append(tempWireData + ";");
                                    }
                                }
                            }
                        }
                        lineValue.append(wireData + ",");
                    }
                    else
                        lineValue.append(query.value(i).toString() + ",");
                }

                fileSource = fileUrl;
                if (fileSource.contains("file:///"))
                    fileSource = fileSource.mid(8);
                QFile csvFile(fileSource);
                if (csvFile.open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Truncate))
                {
                    QTextStream out(&csvFile);
                    out << "SpliceData" << '\n' << lineValue;
                    csvFile.close();
                }
            }
        }
        SpliceDBObj.close();
    }
    return bResult;
}

int DBPresetTable::importData(QString value, QMap<int, QString> wireIdMap)
{
    QString spliceString;
    QStringList spliceList;
    PresetElement mySplice;
    bool ok;
    int ret;
    UtilityClass* _Utility = UtilityClass::Instance();

    spliceString = value;
    spliceList = spliceString.split(",");
    if (spliceList.count() > 60)
    {
        mySplice.SpliceName = spliceList[1];
        mySplice.OperatorID = QString(spliceList[3]).toInt(&ok,10);
        mySplice.CrossSection = QString(spliceList[4]).toInt(&ok,10);
        mySplice.PresetPicNamePath = spliceList[5];
        mySplice.Verified = spliceList[6] == "0" ? false : true;
        mySplice.WeldSettings.BasicSetting.Energy = QString(spliceList[7]).toInt(&ok,10);
        mySplice.WeldSettings.BasicSetting.Amplitude = QString(spliceList[8]).toInt(&ok,10);
        mySplice.WeldSettings.BasicSetting.Width = QString(spliceList[9]).toInt(&ok,10);
        mySplice.WeldSettings.BasicSetting.Pressure = QString(spliceList[10]).toInt(&ok,10);
        mySplice.WeldSettings.BasicSetting.TrigPres = QString(spliceList[11]).toInt(&ok,10);

        mySplice.WeldSettings.QualitySetting.Time.Plus = QString(spliceList[12]).toInt(&ok,10);
        mySplice.WeldSettings.QualitySetting.Time.Minus = QString(spliceList[13]).toInt(&ok,10);
        mySplice.WeldSettings.QualitySetting.Power.Plus = QString(spliceList[14]).toInt(&ok,10);
        mySplice.WeldSettings.QualitySetting.Power.Minus = QString(spliceList[15]).toInt(&ok,10);
        mySplice.WeldSettings.QualitySetting.Preheight.Plus = QString(spliceList[16]).toInt(&ok,10);
        mySplice.WeldSettings.QualitySetting.Preheight.Minus = QString(spliceList[17]).toInt(&ok,10);
        mySplice.WeldSettings.QualitySetting.Height.Plus = QString(spliceList[18]).toInt(&ok,10);
        mySplice.WeldSettings.QualitySetting.Height.Minus = QString(spliceList[19]).toInt(&ok,10);
        mySplice.WeldSettings.QualitySetting.Force.Plus = QString(spliceList[20]).toInt(&ok,10);
        mySplice.WeldSettings.QualitySetting.Force.Minus = QString(spliceList[21]).toInt(&ok,10);

        mySplice.WeldSettings.AdvanceSetting.WeldMode = (WELDMODE)QString(spliceList[22]).toInt(&ok,10);
        mySplice.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode = (STEPWELDMODE)QString(spliceList[23]).toInt(&ok,10);
        mySplice.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep = QString(spliceList[24]).toInt(&ok,10);
        mySplice.WeldSettings.AdvanceSetting.StepWeld.TimeToStep = QString(spliceList[25]).toInt(&ok,10);
        mySplice.WeldSettings.AdvanceSetting.StepWeld.PowerToStep = QString(spliceList[26]).toInt(&ok,10);
        mySplice.WeldSettings.AdvanceSetting.StepWeld.Amplitude2 = QString(spliceList[27]).toInt(&ok,10);
        mySplice.WeldSettings.AdvanceSetting.PreBurst = QString(spliceList[28]).toInt(&ok,10);
        mySplice.WeldSettings.AdvanceSetting.HoldTime = QString(spliceList[29]).toInt(&ok,10);
        mySplice.WeldSettings.AdvanceSetting.SqzTime = QString(spliceList[30]).toInt(&ok,10);
        mySplice.WeldSettings.AdvanceSetting.ABDelay = QString(spliceList[31]).toInt(&ok,10);
        mySplice.WeldSettings.AdvanceSetting.ABDur = QString(spliceList[32]).toInt(&ok,10);
        mySplice.WeldSettings.AdvanceSetting.CutOff = QString(spliceList[33]).toInt(&ok,10);
        mySplice.WeldSettings.AdvanceSetting.CutOffSpliceTime = QString(spliceList[34]).toInt(&ok,10);
        mySplice.WeldSettings.AdvanceSetting.AntiSide = QString(spliceList[35]).toInt(&ok,10);
        mySplice.WeldSettings.AdvanceSetting.AntiSideSpliceTime = QString(spliceList[36]).toInt(&ok,10);
        mySplice.WeldSettings.AdvanceSetting.MeasuredWidth = QString(spliceList[37]).toInt(&ok,10);
        mySplice.WeldSettings.AdvanceSetting.MeasuredHeight = QString(spliceList[38]).toInt(&ok,10);

        mySplice.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption = spliceList[39] == "0" ? false : true;
        mySplice.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID = spliceList[40];
        mySplice.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime = QString(spliceList[41]).toInt(&ok,10);
        mySplice.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature = QString(spliceList[42]).toInt(&ok,10);
        mySplice.HashCode = QString(spliceList[43]).toUInt(&ok,10);

        mySplice.TestSetting.Qutanty = QString(spliceList[44]).toInt(&ok,10);
        mySplice.TestSetting.StopCount = QString(spliceList[45]).toInt(&ok,10);
        mySplice.TestSetting.TestMode = (TESTMODE)QString(spliceList[46]).toInt(&ok,10);
        mySplice.TestSetting.TeachModeSetting.TeachModeType = (TEACH_MODE_TYPE)QString(spliceList[47]).toInt(&ok,10);
        for(int i = 0; i < 18; i++)
            mySplice.TestSetting.TeachModeSetting.TeachModequal_Window[i] = QString(spliceList[i + 48]).toInt(&ok,10);
        mySplice.TestSetting.TestingDone = spliceList[66] == "0" ? false : true;

        QString tmpStr;
        mySplice.WireIndex = wireIdMap;
        mySplice.NoOfWires =  mySplice.WireIndex.size();
        ret =  InsertRecordIntoTable(&mySplice);
        while (ret == -1) {
            qDebug() << "splice";
            QMap<int ,QString> tempMap;
            QueryOnlyUseName(mySplice.SpliceName, &tempMap);
            if (tempMap.size() > 0) {
                mySplice.SpliceName = mySplice.SpliceName + "(1)";
                ret = InsertRecordIntoTable(&mySplice);
            }
            else if (tempMap.size() == 0)
                return -1;
        }
    }
    return ret;
}

QString DBPresetTable::GetExportString(int spliceId)
{
    QString tempWireData;
    QString wireData;
    QString queryStr;
    QString lineValue = "";
    QSqlQuery query(SpliceDBObj);
    bool bResult = OpenDBObject();
    if(bResult == true)
    {
        queryStr = QString("SELECT * FROM Preset WHERE ID == '%1'").arg(spliceId);
        query.prepare(queryStr);
        bResult = query.exec();
        if (bResult) {
            bResult = query.next();
            if(bResult) {
                for (int i = 0;i < 69;i++)
                {
                    if (i == 68)
                    {
                        QJsonParseError json_error;
                        QJsonDocument parse_document = QJsonDocument::fromJson(query.value(i).toString().toLatin1(), &json_error);
                        if(json_error.error == QJsonParseError::NoError)
                        {
                            if(parse_document.isObject())
                            {
                                QJsonObject obj = parse_document.object();
                                QJsonObject::const_iterator iterator = obj.constBegin();
                                for(int i = 0; i< obj.count(); i++)
                                {
                                    iterator = obj.constFind(QString::number(i, 10));
                                    if(iterator != obj.constEnd())
                                    {
                                        QString value = iterator.value().toString();
                                        QStringList strList = value.split(";");
                                        tempWireData = wireTable->GetExportString(((QString)strList.at(0)).toInt());
                                        wireData.append(tempWireData + ";");
                                    }
                                }
                            }
                        }
                        lineValue.append(wireData + "*");
                    }
                    else
                        lineValue.append(query.value(i).toString() + "*");
                }

            }
        }
        SpliceDBObj.close();
    }
    return lineValue;
}
