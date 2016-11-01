#include "DBPresetTable.h"
#include "Modules/UtilityClass.h"
#include <QDebug>

DBPresetTable* DBPresetTable::_instance = NULL;
QString DBPresetTable::SpliceDBFile = "Splice.db";
QString DBPresetTable::DatabaseDir = "c:\\BransonData\\Library\\";
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
            InsertTestDataIntoTable();
        }
    }
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
        tmpSplice.WeldSetting.Energy = 155;
        tmpSplice.WeldSetting.Amplitude = 55;
        tmpSplice.WeldSetting.Width = 800;
        tmpSplice.WeldSetting.Pressure = 80;
        tmpSplice.WeldSetting.TrigPres = 50;
        tmpSplice.QualitySetting.Time.Plus = 500;
        tmpSplice.QualitySetting.Time.Minus = 0;
        tmpSplice.QualitySetting.Power.Plus = 3960;
        tmpSplice.QualitySetting.Power.Minus = 0;
        tmpSplice.QualitySetting.Preheight.Plus = 1500;
        tmpSplice.QualitySetting.Preheight.Minus = 0;
        tmpSplice.QualitySetting.Height.Plus = 1500;
        tmpSplice.QualitySetting.Height.Minus = 0;
        tmpSplice.QualitySetting.Force.Plus = 55;
        tmpSplice.QualitySetting.Force.Minus = 0;
        tmpSplice.AdvanceSetting.WeldMode = ENERGY;
        tmpSplice.AdvanceSetting.StepWeld.StepWeldMode = STEPDISABLE;
        tmpSplice.AdvanceSetting.StepWeld.EnergyToStep = 55;
        tmpSplice.AdvanceSetting.StepWeld.TimeToStep = 1;
        tmpSplice.AdvanceSetting.StepWeld.PowerToStep = 500;
        tmpSplice.AdvanceSetting.StepWeld.Amplitude2 = 22;
        tmpSplice.AdvanceSetting.PreBurst = 1000;
        tmpSplice.AdvanceSetting.HoldTime = 100;
        tmpSplice.AdvanceSetting.SqzTime = 200;
        tmpSplice.AdvanceSetting.ABDelay = 300;
        tmpSplice.AdvanceSetting.ABDur = 400;
        tmpSplice.AdvanceSetting.CutOff = false;
        tmpSplice.AdvanceSetting.AntiSide = true;
        tmpSplice.AdvanceSetting.MeasuredWidth = 100;
        tmpSplice.AdvanceSetting.MeasuredHeight = 100;
        tmpSplice.AdvanceSetting.ShrinkTube.ShrinkOption = false;
        tmpSplice.AdvanceSetting.ShrinkTube.ShrinkTubeID = 0;
        tmpSplice.AdvanceSetting.ShrinkTube.ShrinkTime = 10;
        tmpSplice.AdvanceSetting.ShrinkTube.ShrinkTemperature = 260;
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

    bResult = query.exec(SQLSentence[CREATE_SPLICE_TABLE]);   //run SQL

    if(bResult == false)
        qDebug() << "SQL ERROR:"<< query.lastError();

    SpliceDBObj.close();

    return bResult;
}

bool DBPresetTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    if(_obj == NULL)
        return false;

    QSqlQuery query(SpliceDBObj);
    bResult = SpliceDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }

    UtilityClass *_Utility = UtilityClass::Instance();

    query.prepare(SQLSentence[INSERT_SPLICE_TABLE]);
    query.addBindValue(((PresetElement*)_obj)->SpliceName);
    QDateTime TimeLabel = QDateTime::fromTime_t(((PresetElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((PresetElement*)_obj)->OperatorID);
    query.addBindValue(((PresetElement*)_obj)->CrossSection);
    query.addBindValue(((PresetElement*)_obj)->PresetPicNamePath);
    query.addBindValue(((PresetElement*)_obj)->Verified);

    query.addBindValue(((PresetElement*)_obj)->WeldSetting.Energy);
    query.addBindValue(((PresetElement*)_obj)->WeldSetting.Amplitude);
    query.addBindValue(((PresetElement*)_obj)->WeldSetting.Width);
    query.addBindValue(((PresetElement*)_obj)->WeldSetting.Pressure);
    query.addBindValue(((PresetElement*)_obj)->WeldSetting.TrigPres);


    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Time.Plus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Time.Minus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Power.Plus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Power.Minus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Preheight.Plus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Preheight.Minus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Height.Plus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Height.Minus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Force.Plus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Force.Minus);

    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.WeldMode);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.StepWeld.StepWeldMode);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.StepWeld.EnergyToStep);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.StepWeld.TimeToStep);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.StepWeld.PowerToStep);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.StepWeld.Amplitude2);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.PreBurst);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.HoldTime);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.SqzTime);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.ABDelay);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.ABDur);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.CutOff);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.AntiSide);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.MeasuredWidth);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.MeasuredHeight);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.ShrinkTube.ShrinkOption);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.ShrinkTube.ShrinkTubeID);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.ShrinkTube.ShrinkTime);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.ShrinkTube.ShrinkTemperature);


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
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    SpliceDBObj.close();

    return bResult;

}

bool DBPresetTable::QueryEntireTable(QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;
    QSqlQuery query(SpliceDBObj);
    bool bResult = SpliceDBObj.open();
    if(bResult == false)
        return bResult;

    bResult = query.exec(SQLSentence[QUERY_ENTIRE_SPLICE_TABLE]);
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
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    SpliceDBObj.close();

    return bResult;
}

bool DBPresetTable::QueryOneRecordFromTable(int ID, QString Name, void *_obj)
{
    if(_obj == NULL)
        return false;
    QSqlQuery query(SpliceDBObj);
    bool bResult = SpliceDBObj.open();
    UtilityClass *_Utility = UtilityClass::Instance();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[QUERY_ONE_RECORD_SPLICE_TABLE]);
    query.addBindValue(ID);
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == false)
    {
        SpliceDBObj.close();
        qDebug() << "SQL ERROR:"<< query.lastError();
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
    ((PresetElement*)_obj)->CrossSection = query.value("Color").toInt();
    ((PresetElement*)_obj)->PresetPicNamePath = query.value("PresetPicPath").toString();
    ((PresetElement*)_obj)->Verified = query.value("Verified").toBool();
    ((PresetElement*)_obj)->WeldSetting.Energy = query.value("Energy").toInt();
    ((PresetElement*)_obj)->WeldSetting.Amplitude = query.value("Amplitude").toInt();
    ((PresetElement*)_obj)->WeldSetting.Width = query.value("Width").toInt();
    ((PresetElement*)_obj)->WeldSetting.Pressure = query.value("Pressure").toInt();
    ((PresetElement*)_obj)->WeldSetting.TrigPres = query.value("TrigPres").toInt();
    ((PresetElement*)_obj)->QualitySetting.Time.Plus = query.value("TimePlus").toInt();
    ((PresetElement*)_obj)->QualitySetting.Time.Minus = query.value("TimeMinus").toInt();
    ((PresetElement*)_obj)->QualitySetting.Power.Plus = query.value("PowerPlus").toInt();
    ((PresetElement*)_obj)->QualitySetting.Power.Minus = query.value("PowerMinus").toInt();
    ((PresetElement*)_obj)->QualitySetting.Preheight.Plus = query.value("PreheightPlus").toInt();
    ((PresetElement*)_obj)->QualitySetting.Preheight.Minus = query.value("PreheightMinus").toInt();
    ((PresetElement*)_obj)->QualitySetting.Height.Plus = query.value("HeightPlus").toInt();
    ((PresetElement*)_obj)->QualitySetting.Height.Minus = query.value("HeightMinus").toInt();
    ((PresetElement*)_obj)->QualitySetting.Force.Plus = query.value("ForcePlus").toInt();
    ((PresetElement*)_obj)->QualitySetting.Force.Minus = query.value("ForceMinus").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.WeldMode = (enum WELDMODE)query.value("WeldMode").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.StepWeld.StepWeldMode =
            (enum STEPWELDMODE)query.value("StepWeldMode").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.StepWeld.EnergyToStep =
            query.value("EnergyToStep").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.StepWeld.TimeToStep =
            query.value("TimeToStep").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.StepWeld.PowerToStep =
            query.value("PowerToStep").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.StepWeld.Amplitude2 =
            query.value("Amplitude2").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.PreBurst = query.value("PreBurst").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.HoldTime = query.value("HoldTime").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.SqzTime = query.value("SqueezeTime").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.ABDelay = query.value("AfterBurstDelay").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.ABDur = query.value("AfterBurstDuring").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.CutOff = query.value("CutOff").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.AntiSide = query.value("AntiSide").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.MeasuredWidth = query.value("MeasuredWidth").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.MeasuredHeight = query.value("MeasuredHeight").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.ShrinkTube.ShrinkOption =
            query.value("ShrinkOption").toBool();
    ((PresetElement*)_obj)->AdvanceSetting.ShrinkTube.ShrinkTubeID = query.value("ShrinkTubeID").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.ShrinkTube.ShrinkTime = query.value("ShrinkTubeTime").toInt();
    ((PresetElement*)_obj)->AdvanceSetting.ShrinkTube.ShrinkTemperature =
            query.value("ShrinkTemperature").toInt();
    QString tmpStr = query.value("JSONWire").toString();
    _Utility->StringJsonToMap(tmpStr, &((PresetElement*)_obj)->WireIndex);
    ((PresetElement*)_obj)->NoOfWires = ((PresetElement*)_obj)->WireIndex.size();

    ((PresetElement*)_obj)->TestSetting.Qutanty = query.value("Qutanty").toInt();
    ((PresetElement*)_obj)->TestSetting.StopCount = query.value("StopCount").toInt();
    ((PresetElement*)_obj)->TestSetting.TestMode =
            (enum TESTMODE)query.value("TestMode").toInt();
    ((PresetElement*)_obj)->TestSetting.TeachModeSetting.TeachModeType =
            (enum TEACHMODETYPE)query.value("TeachModeType").toInt();

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
    bool bResult = SpliceDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.exec(SQLSentence[DELETE_ENTIRE_SPLICE_TABLE]);
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    SpliceDBObj.close();
    return bResult;
}

bool DBPresetTable::DeleteOneRecordFromTable(int ID, QString Name)
{
    QSqlQuery query(SpliceDBObj);
    bool bResult = SpliceDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[DELETE_ONE_RECORD_SPLICE_TABLE]);
    query.addBindValue(ID);
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
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
    bool bResult = SpliceDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[UPDATE_ONE_RECORD_SPLICE_TABLE]);
    query.addBindValue(((PresetElement*)_obj)->SpliceName);
    QDateTime TimeLabel = QDateTime::fromTime_t(((PresetElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((PresetElement*)_obj)->OperatorID);
    query.addBindValue(((PresetElement*)_obj)->CrossSection);
    query.addBindValue(((PresetElement*)_obj)->PresetPicNamePath);
    query.addBindValue(((PresetElement*)_obj)->Verified);
    query.addBindValue(((PresetElement*)_obj)->WeldSetting.Energy);
    query.addBindValue(((PresetElement*)_obj)->WeldSetting.Amplitude);
    query.addBindValue(((PresetElement*)_obj)->WeldSetting.Width);
    query.addBindValue(((PresetElement*)_obj)->WeldSetting.Pressure);
    query.addBindValue(((PresetElement*)_obj)->WeldSetting.TrigPres);

    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Time.Plus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Time.Minus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Power.Plus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Power.Minus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Preheight.Plus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Preheight.Minus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Height.Plus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Height.Minus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Force.Plus);
    query.addBindValue(((PresetElement*)_obj)->QualitySetting.Force.Minus);

    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.WeldMode);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.StepWeld.StepWeldMode);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.StepWeld.EnergyToStep);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.StepWeld.TimeToStep);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.StepWeld.PowerToStep);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.StepWeld.Amplitude2);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.PreBurst);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.HoldTime);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.SqzTime);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.ABDelay);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.ABDur);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.CutOff);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.AntiSide);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.MeasuredWidth);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.MeasuredHeight);

    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.ShrinkTube.ShrinkOption);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.ShrinkTube.ShrinkTubeID);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.ShrinkTube.ShrinkTime);
    query.addBindValue(((PresetElement*)_obj)->AdvanceSetting.ShrinkTube.ShrinkTemperature);

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
        qDebug() << "SQL ERROR:"<< query.lastError();
    }
    SpliceDBObj.close();
    return bResult;
}

bool DBPresetTable::QueryOnlyUseName(QString Name, QMap<int, QString> *_obj)
{

    if(_obj == NULL)
        return false;

    QSqlQuery query(SpliceDBObj);
    bool bResult = SpliceDBObj.open();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, SpliceName FROM Splice WHERE SpliceName = ?");
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
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    SpliceDBObj.close();
    return bResult;
}

bool DBPresetTable::QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(SpliceDBObj);
    bool bResult = SpliceDBObj.open();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, SpliceName FROM Splice WHERE CreatedDate >= ?"
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
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    SpliceDBObj.close();
    return bResult;
}
