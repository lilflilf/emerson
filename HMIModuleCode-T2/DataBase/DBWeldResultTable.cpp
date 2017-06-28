#include "DBWeldResultTable.h"
#include "Modules/UtilityClass.h"
#include "Interface/WeldResultElement.h"
#include "Modules/typedef.h"
#include <QSettings>
#include <QDir>
#include <QDebug>

DBWeldResultTable* DBWeldResultTable::_instance = NULL;
QString DBWeldResultTable::WeldResultDBFile = "WeldResultHistory.db";
QString DBWeldResultTable::DatabaseDir = "c:\\BransonData\\History\\";
QString DBWeldResultTable::DatabaseGraphDir = "c:\\BransonData\\History\\Graph\\";
QMap<int, QString> DBWeldResultTable::TableNameList;
const QString SQLSentence[] = {
    "CREATE TABLE WeldResultHistory ( "        /*0 Create WeldResult Table*/
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    "OperatorName VARCHAR, CreatedDate VARCHAR, WorkOrderID INT, WorkOrderName VARCHAR, "
    "HarnessID INT, HarnessName VARCHAR, SequenceID INT, SequenceName VARCHAR, "
    "SpliceID INT, SpliceName VARCHAR, SpliceHash INT, "        /* 12 items */
    "CrossSection INT, WeldCount INT, PartCount INT, "
    "OperateMode VARCHAR, ActualEnergy INT, ActualTPressure INT, "
    "ActualPressure INT, ActualAmplitude INT, ActualAmplitude2 INT, "
    "ActualWidth INT, ActualTime INT, ActualPeakPower INT, "
    "ActualPreheight INT, ActualPostheight INT, "
    "ActualAlarmFlags INT, "                                    /* 15 items */
    /*QualityWindowSetting*/
    "TimePlus INT, TimeMinus INT, PowerPlus INT, PowerMinus INT, "
    "PreheightPlus INT, PreheightMinus INT, HeightPlus INT, HeightMinus INT, "
    "ForcePlus INT, ForceMinus INT, "                           /* 10 items */
    /*AdvanceSetting*/
    "WeldMode INT, StepWeldMode INT, EnergyToStep INT, TimeToStep INT, "
    "PowerToStep INT, Amplitude2 INT, PreBurst INT, HoldTime INT, "
    "SqueezeTime INT, AfterBurstDelay INT, AfterBurstDuring INT, " /* 11 items */
    "SampleRatio INT, NoOfSamples INT, CurrentGraphDirectory VARCHAR)", /* 3 items*/

    "INSERT INTO WeldResultHistory ( "         /*1 Insert record into WeldResult Table*/
    "OperatorName, CreatedDate, WorkOrderID, WorkOrderName, HarnessID, "
    "HarnessName, SequenceID, SequenceName, SpliceID, SpliceName, SpliceHash, " /* 11 items*/
    "CrossSection, WeldCount, PartCount, OperateMode, ActualEnergy, ActualTPressure, "
    "ActualPressure, ActualAmplitude, ActualAmplitude2, ActualWidth, ActualTime, "
    "ActualPeakPower, ActualPreheight, ActualPostheight, ActualAlarmFlags, "    /* 15 items*/
    "TimePlus, TimeMinus, PowerPlus, PowerMinus, PreheightPlus, PreheightMinus, "
    "HeightPlus, HeightMinus, ForcePlus, ForceMinus, "                          /* 10 items */
    "WeldMode, StepWeldMode, EnergyToStep, TimeToStep, PowerToStep, Amplitude2, "
    "PreBurst, HoldTime, SqueezeTime, AfterBurstDelay, AfterBurstDuring, "      /* 11 items */

    "SampleRatio, NoOfSamples, CurrentGraphDirectory) "                         /* 3 items */
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
    "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
    "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
    "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
    "?, ?, ?",

    "SELECT ID, OperatorName FROM WeldResultHistory",
                                               /*2 Query Entire WeldResult Table */

    "SELECT * FROM WeldResultHistory WHERE ID = ? AND OperatorName = ?",
                                               /*3 Query One Record From WeldResult Table */
    "SELECT * FROM WeldResultHistory WHERE ID = ?",
                                               /*4 Query One Record Only Use ID */

    "DELETE FROM WeldResultHistory",                        /*5 Delete Entire Part Table*/

    "DELETE FROM WeldResultHistory WHERE ID = ? AND OperatorName = ?",
                                               /*6 Delete One Record from WeldResult Table*/

    "UPDATE WeldResultHistory SET "
    "OperatorName = ?, CreatedDate = ?, WorkOrderID = ?, WorkOrderName = ?, HarnessID = ?, "
    "HarnessName = ?, SequenceID = ?, SequenceName = ?, SpliceID = ?, "
    "SpliceName = ?, SpliceHash = ?, " /* 11 items */
    "CrossSection = ?, WeldCount = ?, PartCount = ?, OperateMode = ?, "
    "ActualEnergy = ?, ActualTPressure = ?, ActualPressure = ?, ActualAmplitude = ?, "
    "ActualAmplitude2 = ?, ActualWidth = ?, ActualTime = ?, ActualPeakPower = ?, "
    "ActualPreheight = ?, ActualPostheight = ?, "
    "ActualAlarmFlags = ?, "           /* 15 items */
    "TimePlus = ?, TimeMinus = ?, PowerPlus = ?, PowerMinus = ?, PreheightPlus = ?, "
    "PreheightMinus = ?, HeightPlus = ?, HeightMinus = ?, ForcePlus = ?, "
    "ForceMinus = ?, "                 /* 10 items*/
    "WeldMode = ?, StepWeldMode = ?, EnergyToStep = ?, TimeToStep = ?, PowerToStep = ?, "
    "Amplitude2 = ?, PreBurst = ?, HoldTime = ?, SqueezeTime = ?, AfterBurstDelay = ?, "
    "AfterBurstDuring = ?, "           /* 11 items*/
    "SampleRatio = ?, NoOfSamples = ?, CurrentGraphDirectory = ?, "
    "WHERE ID = ?",                             /*7 Update One Record to WeldResult Table*/
};

DBWeldResultTable* DBWeldResultTable::Instance()
{
    if(_instance == 0){
        _instance = new DBWeldResultTable();
    }
    return _instance;
}

DBWeldResultTable::DBWeldResultTable()
{
    TableNameList.clear();
    WeldResultDBObj = QSqlDatabase::addDatabase("QSQLITE", "WeldResultDBObjConnect");
    WeldResultDBObj.setDatabaseName(DatabaseDir + WeldResultDBFile);
    if(WeldResultDBObj.open())
    {
        if(!WeldResultDBObj.tables().contains("WeldResultHistory"))
            CreateNewTable();
    }
    WeldResultDBObj.close();
}


DBWeldResultTable::~DBWeldResultTable()
{
    WeldResultDBObj.close();
}

void DBWeldResultTable::SwitchDBObject(bool IsModularProduction)
{
    UNUSED(IsModularProduction);
    return;
}

bool DBWeldResultTable::CreateNewTable()
{
    QSqlQuery query(WeldResultDBObj);
    bool bResult = query.exec(SQLSentence[SQLITCLASS::CREATE]);
    if(bResult == false)
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
    return bResult;
}

bool DBWeldResultTable::JsonStringToQSetting(QString sPathName, QString PowerGraph, QString HeightGraph)
{
    QDir dir;
    bool bResult = true;
    if (dir.exists(sPathName) == false)
    {
        QSettings settings(sPathName, QSettings::IniFormat);
        settings.beginGroup("Graph");
        settings.setValue("PowerGraph", PowerGraph);
        settings.setValue("HeightGraph", HeightGraph);
        settings.endGroup();
    }else
        bResult = false;
    return bResult;
}

bool DBWeldResultTable::QSettingToJsonString(QString sPathName, QString &PowerGraph, QString &HeightGraph)
{
    QDir dir;
    bool bResult = true;
    if (dir.exists(sPathName) == true)
    {
        // Get the previously stored version strings.
        QSettings settings(sPathName, QSettings::IniFormat);
        settings.beginGroup("Graph");
        PowerGraph =
                settings.value("PowerGraph").value<QString>();
        HeightGraph =
                settings.value("HeightGraph").value<QString>();
        settings.endGroup();
    }else
    {
        PowerGraph.clear();
        HeightGraph.clear();
        bResult = false;
    }
    return bResult;
}

int DBWeldResultTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    int iResult = ERROR;
    if(_obj == NULL)
        return false;

    QSqlQuery query(WeldResultDBObj);
    bResult = WeldResultDBObj.open();

    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }
    if(bResult == true)
    {
        QDateTime TimeLabel = QDateTime::currentDateTime();
        QString sPathName = TimeLabel.toString("yyyyMMddhhmmss");
        sPathName = DatabaseGraphDir + sPathName + ".ini";
        UtilityClass *_Utility = UtilityClass::Instance();
        QString PowerJson;
        QString HeightJson;
        _Utility->ListJsonToString(&((WeldResultElement*)_obj)->PowerGraph,PowerJson);
        _Utility->ListJsonToString(&((WeldResultElement*)_obj)->PostHeightGraph, HeightJson);
        JsonStringToQSetting(sPathName, PowerJson, HeightJson);
        query.prepare(SQLSentence[SQLITCLASS::INSERT]);
        query.addBindValue(((WeldResultElement*)_obj)->OperatorName);
        query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
        query.addBindValue(((WeldResultElement*)_obj)->CurrentWorkOrder.WorkOrderID);
        query.addBindValue(((WeldResultElement*)_obj)->CurrentWorkOrder.WorkOrderName);
        query.addBindValue(((WeldResultElement*)_obj)->CurrentHarness.HarnessID);
        query.addBindValue(((WeldResultElement*)_obj)->CurrentHarness.HarnessName);
        query.addBindValue(((WeldResultElement*)_obj)->CurrentSequence.SequenceID);
        query.addBindValue(((WeldResultElement*)_obj)->CurrentSequence.SequenceName);
        query.addBindValue(((WeldResultElement*)_obj)->CurrentSplice.PartID);
        query.addBindValue(((WeldResultElement*)_obj)->CurrentSplice.PartName);
        query.addBindValue(((WeldResultElement*)_obj)->CurrentSplice.PartHash); /* 11 items */
        query.addBindValue(((WeldResultElement*)_obj)->CrossSection);
        query.addBindValue(((WeldResultElement*)_obj)->WeldCount);
        query.addBindValue(((WeldResultElement*)_obj)->PartCount);
        query.addBindValue(((WeldResultElement*)_obj)->OperateMode);
        query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualEnergy);
        query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualTPressure);
        query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualPressure);
        query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualAmplitude);
        query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualAmplitude2);
        query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualWidth);
        query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualTime);
        query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualPeakPower);
        query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualPreheight);
        query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualPostheight);
        query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualAlarmflags); /* 15 items */

        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Time.Plus);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Time.Minus);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Power.Plus);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Power.Minus);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Preheight.Plus);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Preheight.Minus);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Height.Plus);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Height.Minus);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Force.Plus);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Force.Minus); /* 10 items */

        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.WeldMode);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.StepWeldMode);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.EnergyToStep);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.TimeToStep);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.PowerToStep);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.Amplitude2);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.PreBurst);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.HoldTime);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.SqzTime);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.ABDelay);
        query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.ABDur); /* 11 items */

        query.addBindValue(((WeldResultElement*)_obj)->SampleRatio);
        query.addBindValue(((WeldResultElement*)_obj)->PowerGraph.size()); //NoOfSamples
        query.addBindValue(sPathName);
        bResult = query.exec();
    }
    if (bResult == false)   //run SQL
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
    else
        iResult = query.lastInsertId().toInt(&bResult);
    if(bResult == false)
        iResult = ERROR;
    WeldResultDBObj.close();
    return iResult;
}

bool DBWeldResultTable::QueryEntireTable(QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();
    if(bResult == false)
        return bResult;

    bResult = query.exec(SQLSentence[SQLITCLASS::QUERY_ENTIRE_TABLE]);
    if (bResult == true)
    {
        _obj->clear();
        while(query.next())
        {
            _obj->insert(query.value("ID").toInt(),
                           query.value("OperatorName").toString());
        }
    }
    else
    {
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
    }

    WeldResultDBObj.close();

    return bResult;
}

bool DBWeldResultTable::QueryOneRecordFromTable(int ID, QString OperatorName, void *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD]);
    query.addBindValue(ID);
    query.addBindValue(OperatorName);

    bResult = query.exec();
    if(bResult == false)
    {
        WeldResultDBObj.close();
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        WeldResultDBObj.close();
        return bResult;
    }

    ((WeldResultElement*)_obj)->WeldResultID = query.value("ID").toInt();
    ((WeldResultElement*)_obj)->OperatorName = query.value("OperatorName").toString();
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((WeldResultElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((WeldResultElement*)_obj)->CurrentWorkOrder.WorkOrderID
            = query.value("WorkOrderID").toInt();
    ((WeldResultElement*)_obj)->CurrentWorkOrder.WorkOrderName
            = query.value("WorkOrderName").toString();
    ((WeldResultElement*)_obj)->CurrentHarness.HarnessID
            = query.value("HarnessID").toInt();
    ((WeldResultElement*)_obj)->CurrentHarness.HarnessName
            = query.value("HarnessName").toString();
    ((WeldResultElement*)_obj)->CurrentSequence.SequenceID
            = query.value("SequenceID").toInt();
    ((WeldResultElement*)_obj)->CurrentSequence.SequenceName
            = query.value("SequenceName").toString();
    ((WeldResultElement*)_obj)->CurrentSplice.PartID
            = query.value("SpliceID").toInt();
    ((WeldResultElement*)_obj)->CurrentSplice.PartName
            = query.value("SpliceName").toString();
    ((WeldResultElement*)_obj)->CurrentSplice.PartHash
            = query.value("SpliceHash").toInt();       /* 11 items*/

    ((WeldResultElement*)_obj)->CrossSection = query.value("CrossSection").toInt();
    ((WeldResultElement*)_obj)->WeldCount = query.value("WeldCount").toInt();
    ((WeldResultElement*)_obj)->PartCount = query.value("PartCount").toInt();
    ((WeldResultElement*)_obj)->OperateMode = query.value("OperateMode").toString();
    ((WeldResultElement*)_obj)->ActualResult.ActualEnergy
            = query.value("ActualEnergy").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualTPressure
            = query.value("ActualTPressure").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPressure
            = query.value("ActualPressure").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualAmplitude
            = query.value("ActualAmplitude").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualAmplitude2
            = query.value("ActualAmplitude2").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualWidth
            = query.value("ActualWidth").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualTime
            = query.value("ActualTime").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPeakPower
            = query.value("ActualPeakPower").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPreheight
            = query.value("ActualPreheight").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPostheight
            = query.value("ActualPostHeight").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualAlarmflags
            = query.value("ActualAlarmFlags").toInt(); /* 14 items */

    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Time.Plus
            = query.value("TimePlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Time.Minus
            = query.value("TimeMinus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Power.Plus
            = query.value("PowerPlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Power.Minus
            = query.value("PowerMinus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Preheight.Plus
            = query.value("PreheightPlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Preheight.Minus
            = query.value("PreheightMinus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Height.Plus
            = query.value("HeightPlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Height.Minus
            = query.value("HeightMinus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Force.Plus
            = query.value("ForcePlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Force.Minus
            = query.value("ForceMinus").toInt(); /* 10 items */

    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.WeldMode
            = (ADVANCESETTING::WELDMODE)query.value("WeldMode").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.StepWeldMode
            = (STEPWELD::STEPWELDMODE)query.value("StepWeldMode").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.EnergyToStep
            = query.value("EnergyToStep").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.TimeToStep
            = query.value("TimeToStep").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.PowerToStep
            = query.value("PowerToStep").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.Amplitude2
            = query.value("Amplitude2").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.PreBurst
            = query.value("PreBurst").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.HoldTime
            = query.value("HoldTime").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.SqzTime
            = query.value("SqueezeTime").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.ABDelay
            = query.value("AfterBurstDelay").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.ABDur
            = query.value("AfterBurstDuring").toInt(); /* 11 items */

    ((WeldResultElement*)_obj)->SampleRatio
            = (WeldResultElement::SAMPLERATIO)query.value("SampleRatio").toInt();
    ((WeldResultElement*)_obj)->NoOfSamples
            = query.value("NoOfSamples").toInt();
    WeldResultDBObj.close();
    return bResult;
}

bool DBWeldResultTable::QueryOneRecordFromTable(int ID, void *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
        return bResult;
    }
    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD_ONLY_ID]);
    query.addBindValue(ID);
    bResult = query.exec();
    if(bResult == false)
    {
        WeldResultDBObj.close();
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        WeldResultDBObj.close();
        return bResult;
    }

    ((WeldResultElement*)_obj)->WeldResultID = query.value("ID").toInt();
    ((WeldResultElement*)_obj)->OperatorName = query.value("OperatorName").toString();
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((WeldResultElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((WeldResultElement*)_obj)->CurrentWorkOrder.WorkOrderID
            = query.value("WorkOrderID").toInt();
    ((WeldResultElement*)_obj)->CurrentWorkOrder.WorkOrderName
            = query.value("WorkOrderName").toString();
    ((WeldResultElement*)_obj)->CurrentHarness.HarnessID
            = query.value("HarnessID").toInt();
    ((WeldResultElement*)_obj)->CurrentHarness.HarnessName
            = query.value("HarnessName").toString();
    ((WeldResultElement*)_obj)->CurrentSequence.SequenceID
            = query.value("SequenceID").toInt();
    ((WeldResultElement*)_obj)->CurrentSequence.SequenceName
            = query.value("SequenceName").toString();
    ((WeldResultElement*)_obj)->CurrentSplice.PartID
            = query.value("SpliceID").toInt();
    ((WeldResultElement*)_obj)->CurrentSplice.PartName
            = query.value("SpliceName").toString();
    ((WeldResultElement*)_obj)->CurrentSplice.PartHash  /* 12 items */
            = query.value("SpliceHash").toInt();

    ((WeldResultElement*)_obj)->CrossSection = query.value("CrossSection").toInt();
    ((WeldResultElement*)_obj)->WeldCount = query.value("WeldCount").toInt();
    ((WeldResultElement*)_obj)->PartCount = query.value("PartCount").toInt();
    ((WeldResultElement*)_obj)->OperateMode = query.value("OperateMode").toString();
    ((WeldResultElement*)_obj)->ActualResult.ActualEnergy
            = query.value("ActualEnergy").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualTPressure
            = query.value("ActualTPressure").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPressure
            = query.value("ActualPressure").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualAmplitude
            = query.value("ActualAmplitude").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualAmplitude2
            = query.value("ActualAmplitude2").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualWidth
            = query.value("ActualWidth").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualTime
            = query.value("ActualTime").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPeakPower
            = query.value("ActualPeakPower").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPreheight
            = query.value("ActualPreheight").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPostheight
            = query.value("ActualPostHeight").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualAlarmflags /* 14 items */
            = query.value("ActualAlarmFlags").toInt();

    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Time.Plus
            = query.value("TimePlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Time.Minus
            = query.value("TimeMinus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Power.Plus
            = query.value("PowerPlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Power.Minus
            = query.value("PowerMinus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Preheight.Plus
            = query.value("PreheightPlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Preheight.Minus
            = query.value("PreheightMinus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Height.Plus
            = query.value("HeightPlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Height.Minus
            = query.value("HeightMinus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Force.Plus
            = query.value("ForcePlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Force.Minus
            = query.value("ForceMinus").toInt();              /* 10 items */

    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.WeldMode
            = (ADVANCESETTING::WELDMODE)query.value("WeldMode").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.StepWeldMode
            = (STEPWELD::STEPWELDMODE)query.value("StepWeldMode").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.EnergyToStep
            = query.value("EnergyToStep").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.TimeToStep
            = query.value("TimeToStep").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.PowerToStep
            = query.value("PowerToStep").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.Amplitude2
            = query.value("Amplitude2").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.PreBurst
            = query.value("PreBurst").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.HoldTime
            = query.value("HoldTime").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.SqzTime
            = query.value("SqueezeTime").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.ABDelay
            = query.value("AfterBurstDelay").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.ABDur
            = query.value("AfterBurstDuring").toInt();        /* 11 items */

    ((WeldResultElement*)_obj)->SampleRatio
            = (WeldResultElement::SAMPLERATIO)query.value("SampleRatio").toInt();
    ((WeldResultElement*)_obj)->NoOfSamples
            = query.value("NoOfSamples").toInt();
    WeldResultDBObj.close();
    return bResult;
}

bool DBWeldResultTable::QueryOneRecordFromTable(int ID, QStringList &ResultStr)
{
    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
        return bResult;
    }
    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD_ONLY_ID]);
    query.addBindValue(ID);
    bResult = query.exec();
    if(bResult == false)
    {
        WeldResultDBObj.close();
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        WeldResultDBObj.close();
        return bResult;
    }

    ResultStr.clear();
    ResultStr.append(query.value("ID").toString());
    ResultStr.append(query.value("OperatorName").toString());
    ResultStr.append(query.value("CreatedDate").toString());
    ResultStr.append(query.value("WorkOrderID").toString());
    ResultStr.append(query.value("WorkOrderName").toString());
    ResultStr.append(query.value("HarnessID").toString());
    ResultStr.append(query.value("HarnessName").toString());
    ResultStr.append(query.value("SequenceID").toString());
    ResultStr.append(query.value("SequenceName").toString());
    ResultStr.append(query.value("SpliceID").toString());
    ResultStr.append(query.value("SpliceName").toString());
    ResultStr.append(query.value("SpliceHash").toString()); /* 12 items * */
    ResultStr.append(query.value("CrossSection").toString());
    ResultStr.append(query.value("WeldCount").toString());
    ResultStr.append(query.value("PartCount").toString());
    ResultStr.append(query.value("OperateMode").toString());
    ResultStr.append(query.value("ActualEnergy").toString());
    ResultStr.append(query.value("ActualTPressure").toString());
    ResultStr.append(query.value("ActualPressure").toString());
    ResultStr.append(query.value("ActualAmplitude").toString());
    ResultStr.append(query.value("ActualAmplitude2").toString());
    ResultStr.append(query.value("ActualWidth").toString());
    ResultStr.append(query.value("ActualTime").toString());
    ResultStr.append(query.value("ActualPeakPower").toString());
    ResultStr.append(query.value("ActualPreheight").toString());
    ResultStr.append(query.value("ActualPostHeight").toString());
    ResultStr.append(query.value("ActualAlarmFlags").toString()); /* 15 items */

    ResultStr.append(query.value("TimePlus").toString());
    ResultStr.append(query.value("TimeMinus").toString());
    ResultStr.append(query.value("PowerPlus").toString());
    ResultStr.append(query.value("PowerMinus").toString());
    ResultStr.append(query.value("PreheightPlus").toString());
    ResultStr.append(query.value("PreheightMinus").toString());
    ResultStr.append(query.value("HeightPlus").toString());
    ResultStr.append(query.value("HeightMinus").toString());
    ResultStr.append(query.value("ForcePlus").toString());
    ResultStr.append(query.value("ForceMinus").toString());  /* 10 items */

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
    ResultStr.append(query.value("AfterBurstDuring").toString()); /* 11 items */

    ResultStr.append(query.value("SampleRatio").toString());
    ResultStr.append(query.value("NoOfSamples").toString());
    ResultStr.append(query.value("CurrentGraphDirectory").toString());
    WeldResultDBObj.close();
    return bResult;
}

bool DBWeldResultTable::DeleteEntireTable()
{
    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Weld Result Table SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.exec(SQLSentence[SQLITCLASS::DELETE_ENTIRE_TABLE]);
    if(bResult == false)
    {
        qDebug() << "Weld Result Table SQL ERROR:"<< query.lastError();
    }

    WeldResultDBObj.close();
    return bResult;
}

bool DBWeldResultTable::DeleteOneRecordFromTable(int ID, QString OperatorName)
{
    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::DELETE_ONE_RECORD]);
    query.addBindValue(ID);
    query.addBindValue(OperatorName);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
    }
    WeldResultDBObj.close();
    return bResult;
}

bool DBWeldResultTable::UpdateRecordIntoTable(void *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR1:"<< query.lastError();
        return bResult;
    }
    QString tmpTableName = QDateTime::currentDateTime().toString("yyyyMMdd");
    query.prepare(SQLSentence[SQLITCLASS::UPDATE_ONE_RECORD]);
    query.addBindValue(((WeldResultElement*)_obj)->OperatorName);
    QDateTime TimeLabel = QDateTime::fromTime_t(((WeldResultElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((WeldResultElement*)_obj)->CurrentWorkOrder.WorkOrderID);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentWorkOrder.WorkOrderName);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentHarness.HarnessID);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentHarness.HarnessName);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentSequence.SequenceID);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentSequence.SequenceName);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentSplice.PartID);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentSplice.PartName);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentSplice.PartHash); /* 11 items */
    query.addBindValue(((WeldResultElement*)_obj)->CrossSection);
    query.addBindValue(((WeldResultElement*)_obj)->WeldCount);
    query.addBindValue(((WeldResultElement*)_obj)->PartCount);
    query.addBindValue(((WeldResultElement*)_obj)->OperateMode);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualEnergy);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualTPressure);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualPressure);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualAmplitude);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualAmplitude2);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualWidth);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualTime);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualPeakPower);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualPreheight);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualPostheight);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualAlarmflags); /* 14 items */

    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Time.Plus);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Time.Minus);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Power.Plus);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Power.Minus);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Preheight.Plus);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Preheight.Minus);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Height.Plus);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Height.Minus);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Force.Plus);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Force.Minus); /* 10 items */

    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.WeldMode);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.StepWeldMode);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.EnergyToStep);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.TimeToStep);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.PowerToStep);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.Amplitude2);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.PreBurst);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.HoldTime);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.SqzTime);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.ABDelay);
    query.addBindValue(((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.ABDur); /* 11 items */

    query.addBindValue(((WeldResultElement*)_obj)->SampleRatio);
    query.addBindValue(((WeldResultElement*)_obj)->PowerGraph.size()); //NoOfSamples
    UtilityClass *_Utility = UtilityClass::Instance();
    QString tmpJson;
    _Utility->ListJsonToString(&((WeldResultElement*)_obj)->PowerGraph,tmpJson);
    query.addBindValue(tmpJson);
    _Utility->ListJsonToString(&((WeldResultElement*)_obj)->PostHeightGraph, tmpJson);
    query.addBindValue(tmpJson);
    query.addBindValue(((WeldResultElement*)_obj)->WeldResultID);
    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
    }
    WeldResultDBObj.close();
    return bResult;
}

bool DBWeldResultTable::QueryOnlyUseName(QString Name, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, OperatorName FROM WeldResultHistory WHERE OperatorName = ?");
    query.addBindValue(Name);

    bResult = query.exec();
    if(bResult == true)
    {
        _obj->clear();
        while(query.next())
            _obj->insert(query.value("ID").toInt(),
                           query.value("OperatorName").toString());
    }
    else
    {
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
    }

    WeldResultDBObj.close();
    return bResult;
}

bool DBWeldResultTable::QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, OperatorName FROM WeldResultHistory WHERE CreatedDate >= ?"
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
                           query.value("OperatorName").toString());
    }
    else
    {
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
    }

    WeldResultDBObj.close();
    return bResult;
}

bool DBWeldResultTable::QueryUseNameAndTime(QString Name, unsigned int time_from,
                unsigned int time_to, QMap<int, QString>* _obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();
    if(bResult == false)
        return bResult;

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_WIRE_TABLE]);
    query.prepare("SELECT ID, OperatorName FROM WeldResultHistory "
                  "WHERE OperatorName = ? AND CreatedDate >= ? "
                  "AND CreatedDate <= ?");
    query.addBindValue(Name);
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
                           query.value("OperatorName").toString());
    }
    else
    {
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
    }

    WeldResultDBObj.close();
    return bResult;
}

bool DBWeldResultTable::QueryOnlyUseField(QString FieldName, QMap<int, QString> *_obj, bool Orderby)
{
    QString queryStr;
    if(_obj == NULL)
        return false;

    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();
    if(bResult == true)
    {
        if(Orderby == true)
            queryStr = QString("SELECT DISTINCT ID, %1 FROM WeldResultHistory ORDER BY %1 ASC").arg(FieldName);
        else
            queryStr = QString("SELECT DISTINCT ID, %1 FROM WeldResultHistory ORDER BY %1 DESC").arg(FieldName);
        query.prepare(queryStr);
        bResult = query.exec();
    }
    if(bResult == true)
    {
        _obj->clear();
        while(query.next())
        {
            _obj->insert(query.value("ID").toInt(),
                                   query.value(FieldName).toString());
        }
    }

    WeldResultDBObj.close();
    return bResult;

}

bool DBWeldResultTable::QueryBySomeFields(QMap<int, QString> *_obj,
                        QString HarnessName, QString SequenceName, QString SpliceName,
                       unsigned int time_from, unsigned int time_to,
                       enum FieldType OrderField, bool Orderby)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();
    if(bResult == true){
        if((HarnessName.isEmpty() == true) && (SequenceName.isEmpty() == true)
                && (SpliceName.isEmpty() == true))
        {
            if(Orderby == true)
                query.prepare("SELECT ID, OperatorName FROM WeldResultHistory WHERE CreatedDate >= ?"
                    " AND CreatedDate <= ? ORDER BY CreatedDate ASC");
            else
                query.prepare("SELECT ID, OperatorName FROM WeldResultHistory WHERE CreatedDate >= ?"
                    " AND CreatedDate <= ? ORDER BY CreatedDate DESC");

            QDateTime TimeLabel = QDateTime::fromTime_t(time_from);
            query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
            TimeLabel = QDateTime::fromTime_t(time_to);
            query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
        }else if((HarnessName.isEmpty() == true) && (SequenceName.isEmpty() == true))
        {
            QString FieldName;
            switch (OrderField) {
            case SpliceType:
                FieldName = "SpliceName";
                break;
            case CreatedDateType:
                FieldName = "CreatedDate";
                break;
            default:
                FieldName = "CreatedDate";
                break;
            }
            QString QueryStr;
            if (Orderby == true)
                QueryStr = QString("SELECT ID, OperatorName FROM WeldResultHistory WHERE CreatedDate >= ?"
                " AND CreatedDate <= ? AND SpliceName == ? ORDER BY %1 ASC").arg(FieldName);
            else
                QueryStr = QString("SELECT ID, OperatorName FROM WeldResultHistory WHERE CreatedDate >= ?"
                " AND CreatedDate <= ? AND SpliceName == ? ORDER BY %1 DESC").arg(FieldName);
            query.prepare(QueryStr);
            QDateTime TimeLabel = QDateTime::fromTime_t(time_from);
            query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
            TimeLabel = QDateTime::fromTime_t(time_to);
            query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
            query.addBindValue(SpliceName);
        }else if((SpliceName.isEmpty() == true) && (SequenceName.isEmpty() == true))
        {
            QString FieldName;
            switch (OrderField) {
            case PartType:
                FieldName = "HarnessName";
                break;
            case CreatedDateType:
                FieldName = "CreatedDate";
                break;
            default:
                FieldName = "CreatedDate";
                break;
            }
            QString QueryStr;
            if (Orderby == true)
                QueryStr = QString("SELECT ID, OperatorName FROM WeldResultHistory WHERE CreatedDate >= ?"
                " AND CreatedDate <= ? AND HarnessName == ? ORDER BY %1 ASC").arg(FieldName);
            else
                QueryStr = QString("SELECT ID, OperatorName FROM WeldResultHistory WHERE CreatedDate >= ?"
                " AND CreatedDate <= ? AND HarnessName == ? ORDER BY %1 DESC").arg(FieldName);
            query.prepare(QueryStr);
            QDateTime TimeLabel = QDateTime::fromTime_t(time_from);
            query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
            TimeLabel = QDateTime::fromTime_t(time_to);
            query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
            query.addBindValue(HarnessName);
        }else if((HarnessName.isEmpty() == true) && (SpliceName.isEmpty() == true))
        {
            QString FieldName;
            switch (OrderField) {
            case WorkOrderType:
                FieldName = "SequenceName";
                break;
            case CreatedDateType:
                FieldName = "CreatedDate";
                break;
            default:
                FieldName = "CreatedDate";
                break;
            }
            QString QueryStr;
            if (Orderby == true)
                QueryStr = QString("SELECT ID, OperatorName FROM WeldResultHistory WHERE CreatedDate >= ?"
                " AND CreatedDate <= ? AND SequenceName == ? ORDER BY %1 ASC").arg(FieldName);
            else
                QueryStr = QString("SELECT ID, OperatorName FROM WeldResultHistory WHERE CreatedDate >= ?"
                " AND CreatedDate <= ? AND SequenceName == ? ORDER BY %1 DESC").arg(FieldName);
            query.prepare(QueryStr);
            QDateTime TimeLabel = QDateTime::fromTime_t(time_from);
            query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
            TimeLabel = QDateTime::fromTime_t(time_to);
            query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
            query.addBindValue(SequenceName);
        }else if(SequenceName.isEmpty() == true)
        {
            QString FieldName;
            switch (OrderField) {
            case SpliceType:
                FieldName = "SpliceName";
                break;
            case PartType:
                FieldName = "HarnessName";
                break;
            case CreatedDateType:
                FieldName = "CreatedDate";
                break;
            default:
                FieldName = "CreatedDate";
                break;
            }
            QString QueryStr;
            if (Orderby == true)
                QueryStr = QString("SELECT ID, OperatorName FROM WeldResultHistory WHERE CreatedDate >= ?"
                " AND CreatedDate <= ? AND SpliceName == ? AND HarnessName == ? ORDER BY %1 ASC").arg(FieldName);
            else
                QueryStr = QString("SELECT ID, OperatorName FROM WeldResultHistory WHERE CreatedDate >= ?"
                " AND CreatedDate <= ? AND SpliceName == ? AND HarnessName == ? ORDER BY %1 DESC").arg(FieldName);
            query.prepare(QueryStr);
            QDateTime TimeLabel = QDateTime::fromTime_t(time_from);
            query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
            TimeLabel = QDateTime::fromTime_t(time_to);
            query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
            query.addBindValue(SpliceName);
            query.addBindValue(HarnessName);
        }else if(HarnessName.isEmpty() == true)
        {
            QString FieldName;
            switch (OrderField) {
            case SpliceType:
                FieldName = "SpliceName";
                break;
            case WorkOrderType:
                FieldName = "SequenceName";
                break;
            case CreatedDateType:
                FieldName = "CreatedDate";
                break;
            default:
                FieldName = "CreatedDate";
                break;
            }
            QString QueryStr;
            if (Orderby == true)
                QueryStr = QString("SELECT ID, OperatorName FROM WeldResultHistory WHERE CreatedDate >= ?"
                " AND CreatedDate <= ? AND SpliceName == ? AND SequenceName == ? ORDER BY %1 ASC").arg(FieldName);
            else
                QueryStr = QString("SELECT ID, OperatorName FROM WeldResultHistory WHERE CreatedDate >= ?"
                " AND CreatedDate <= ? AND SpliceName == ? AND SequenceName == ? ORDER BY %1 DESC").arg(FieldName);
            query.prepare(QueryStr);
            QDateTime TimeLabel = QDateTime::fromTime_t(time_from);
            query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
            TimeLabel = QDateTime::fromTime_t(time_to);
            query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
            query.addBindValue(SpliceName);
            query.addBindValue(SequenceName);
        }else if(SpliceName.isEmpty() == true)
        {
            QString FieldName;
            switch (OrderField) {
            case WorkOrderType:
                FieldName = "SequenceName";
                break;
            case PartType:
                FieldName = "HarnessName";
                break;
            case CreatedDateType:
                FieldName = "CreatedDate";
                break;
            default:
                FieldName = "CreatedDate";
                break;
            }
            QString QueryStr;
            if (Orderby == true)
                QueryStr = QString("SELECT ID, OperatorName FROM WeldResultHistory WHERE CreatedDate >= ?"
                " AND CreatedDate <= ? AND SequenceName == ? AND HarnessName == ? ORDER BY %1 ASC").arg(FieldName);
            else
                QueryStr = QString("SELECT ID, OperatorName FROM WeldResultHistory WHERE CreatedDate >= ?"
                " AND CreatedDate <= ? AND SequenceName == ? AND HarnessName == ? ORDER BY %1 DESC").arg(FieldName);
            query.prepare(QueryStr);
            QDateTime TimeLabel = QDateTime::fromTime_t(time_from);
            query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
            TimeLabel = QDateTime::fromTime_t(time_to);
            query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
            query.addBindValue(SequenceName);
            query.addBindValue(HarnessName);
        }else{
            QString FieldName;
            switch (OrderField) {
            case SpliceType:
                FieldName = "SpliceName";
                break;
            case PartType:
                FieldName = "HarnessName";
                break;
            case WorkOrderType:
                FieldName = "SequenceName";
                break;
            case CreatedDateType:
                FieldName = "CreatedDate";
                break;
            default:
                FieldName = "CreatedDate";
                break;
            }
            QString QueryStr;
            if (Orderby == true)
                QueryStr = QString("SELECT ID, OperatorName FROM WeldResultHistory WHERE (CreatedDate >= ? "
                "AND CreatedDate <= ? AND SpliceName = ? "
                "AND HarnessName = ? AND SequenceName = ?) ORDER BY %1 ASC").arg(FieldName);
            else
                QueryStr = QString("SELECT ID, OperatorName FROM WeldResultHistory WHERE (CreatedDate >= ? "
                "AND CreatedDate <= ? AND SpliceName = ? "
                "AND HarnessName = ? AND SequenceName = ?) ORDER BY %1 DESC").arg(FieldName);
            query.prepare(QueryStr);
            QDateTime TimeLabel = QDateTime::fromTime_t(time_from);
            query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
            TimeLabel = QDateTime::fromTime_t(time_to);
            query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
            query.addBindValue(SpliceName);
            query.addBindValue(HarnessName);
            query.addBindValue(SequenceName);
        }
        bResult = query.exec();
        if(bResult == true)
        {
            _obj->clear();
            while(query.next())
                _obj->insert(query.value("ID").toInt(),
                               query.value("OperatorName").toString());
        }
        else
        {
            qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
        }
    }
    WeldResultDBObj.close();
    return bResult;
}

bool DBWeldResultTable::QueryBySomeFields(QString SpliceName, unsigned int HashCode,
                                          unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();
    if(bResult == true){
        query.prepare("SELECT ID, OperatorName FROM WeldResultHistory WHERE CreatedDate >= ?"
                " AND CreatedDate <= ? AND SpliceName == ? AND SpliceHash == ?");


        QDateTime TimeLabel = QDateTime::fromTime_t(time_from);
        query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
        TimeLabel = QDateTime::fromTime_t(time_to);
        query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
        query.addBindValue(SpliceName);
        query.addBindValue(HashCode);
        bResult = query.exec();
    }
    if(bResult == true)
    {
        _obj->clear();
        while(query.next())
            _obj->insert(query.value("ID").toInt(),
                           query.value("OperatorName").toString());
    }
    else
    {
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
    }

    return bResult;
}

bool DBWeldResultTable::QueryOneRecordWithGraph(int ID, QString OperatorName, void *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD]);
    query.addBindValue(ID);
    query.addBindValue(OperatorName);

    bResult = query.exec();
    if(bResult == false)
    {
        WeldResultDBObj.close();
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        WeldResultDBObj.close();
        return bResult;
    }

    ((WeldResultElement*)_obj)->WeldResultID = query.value("ID").toInt();
    ((WeldResultElement*)_obj)->OperatorName = query.value("OperatorName").toString();
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((WeldResultElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((WeldResultElement*)_obj)->CurrentWorkOrder.WorkOrderID
            = query.value("WorkOrderID").toInt();
    ((WeldResultElement*)_obj)->CurrentWorkOrder.WorkOrderName
            = query.value("WorkOrderName").toString();
    ((WeldResultElement*)_obj)->CurrentHarness.HarnessID
            = query.value("HarnessID").toInt();
    ((WeldResultElement*)_obj)->CurrentHarness.HarnessName
            = query.value("HarnessName").toString();
    ((WeldResultElement*)_obj)->CurrentSequence.SequenceID
            = query.value("SequenceID").toInt();
    ((WeldResultElement*)_obj)->CurrentSequence.SequenceName
            = query.value("SequenceName").toString();
    ((WeldResultElement*)_obj)->CurrentSplice.PartID
            = query.value("SpliceID").toInt();
    ((WeldResultElement*)_obj)->CurrentSplice.PartName
            = query.value("SpliceName").toString();
    ((WeldResultElement*)_obj)->CurrentSplice.PartHash
            = query.value("SpliceHash").toInt();
    ((WeldResultElement*)_obj)->CrossSection = query.value("CrossSection").toInt();
    ((WeldResultElement*)_obj)->WeldCount = query.value("WeldCount").toInt();
    ((WeldResultElement*)_obj)->PartCount = query.value("PartCount").toInt();
    ((WeldResultElement*)_obj)->OperateMode = query.value("OperateMode").toString();
    ((WeldResultElement*)_obj)->ActualResult.ActualEnergy
            = query.value("ActualEnergy").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualTPressure
            = query.value("ActualTPressure").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPressure
            = query.value("ActualPressure").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualAmplitude
            = query.value("ActualAmplitude").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualAmplitude2
            = query.value("ActualAmplitude2").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualWidth
            = query.value("ActualWidth").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualTime
            = query.value("ActualTime").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPeakPower
            = query.value("ActualPeakPower").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPreheight
            = query.value("ActualPreheight").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPostheight
            = query.value("ActualPostHeight").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualAlarmflags
            = query.value("ActualAlarmFlags").toInt();

    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Time.Plus
            = query.value("TimePlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Time.Minus
            = query.value("TimeMinus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Power.Plus
            = query.value("PowerPlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Power.Minus
            = query.value("PowerMinus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Preheight.Plus
            = query.value("PreheightPlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Preheight.Minus
            = query.value("PreheightMinus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Height.Plus
            = query.value("HeightPlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Height.Minus
            = query.value("HeightMinus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Force.Plus
            = query.value("ForcePlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Force.Minus
            = query.value("ForceMinus").toInt(); /* 10 items */

    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.WeldMode
            = (ADVANCESETTING::WELDMODE)query.value("WeldMode").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.StepWeldMode
            = (STEPWELD::STEPWELDMODE)query.value("StepWeldMode").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.EnergyToStep
            = query.value("EnergyToStep").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.TimeToStep
            = query.value("TimeToStep").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.PowerToStep
            = query.value("PowerToStep").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.Amplitude2
            = query.value("Amplitude2").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.PreBurst
            = query.value("PreBurst").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.HoldTime
            = query.value("HoldTime").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.SqzTime
            = query.value("SqueezeTime").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.ABDelay
            = query.value("AfterBurstDelay").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.ABDur
            = query.value("AfterBurstDuring").toInt(); /* 11 items */

    ((WeldResultElement*)_obj)->SampleRatio
            = (WeldResultElement::SAMPLERATIO)query.value("SampleRatio").toInt();
    QString sPathName = query.value("CurrentGraphDirectory").toString();
    UtilityClass *_Utility = UtilityClass::Instance();
    QString PowerJson;
    QString HeightJson;
    QSettingToJsonString(sPathName, PowerJson, HeightJson);
    _Utility->StringJsonToList(PowerJson,&((WeldResultElement*)_obj)->PowerGraph);
    _Utility->StringJsonToList(HeightJson,&((WeldResultElement*)_obj)->PostHeightGraph);
    ((WeldResultElement*)_obj)->NoOfSamples
            = ((WeldResultElement*)_obj)->PowerGraph.size();
    WeldResultDBObj.close();
    return bResult;
}

bool DBWeldResultTable::QueryOneRecordWithGraph(int ID, void *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();
    if(bResult == false)
    {
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
        return bResult;
    }

    query.prepare(SQLSentence[SQLITCLASS::QUERY_ONE_RECORD_ONLY_ID]);
    query.addBindValue(ID);

    bResult = query.exec();
    if(bResult == false)
    {
        WeldResultDBObj.close();
        qDebug() << "Weld Result SQL ERROR:"<< query.lastError();
        return bResult;
    }

    bResult = query.next();
    if(bResult == false)
    {
        WeldResultDBObj.close();
        return bResult;
    }

    ((WeldResultElement*)_obj)->WeldResultID = query.value("ID").toInt();
    ((WeldResultElement*)_obj)->OperatorName = query.value("OperatorName").toString();
    QDateTime TimeLabel = QDateTime::fromString(query.value("CreatedDate").toString(),
                                                "yyyy/MM/dd hh:mm:ss");
    ((WeldResultElement*)_obj)->CreatedDate = TimeLabel.toTime_t();
    ((WeldResultElement*)_obj)->CurrentWorkOrder.WorkOrderID
            = query.value("WorkOrderID").toInt();
    ((WeldResultElement*)_obj)->CurrentWorkOrder.WorkOrderName
            = query.value("WorkOrderName").toString();
    ((WeldResultElement*)_obj)->CurrentHarness.HarnessID
            = query.value("HarnessID").toInt();
    ((WeldResultElement*)_obj)->CurrentHarness.HarnessName
            = query.value("HarnessName").toString();
    ((WeldResultElement*)_obj)->CurrentSequence.SequenceID
            = query.value("SequenceID").toInt();
    ((WeldResultElement*)_obj)->CurrentSequence.SequenceName
            = query.value("SequenceName").toString();
    ((WeldResultElement*)_obj)->CurrentSplice.PartID
            = query.value("SpliceID").toInt();
    ((WeldResultElement*)_obj)->CurrentSplice.PartName
            = query.value("SpliceName").toString();
    ((WeldResultElement*)_obj)->CurrentSplice.PartHash
            = query.value("SpliceHash").toInt();
    ((WeldResultElement*)_obj)->CrossSection = query.value("CrossSection").toInt();
    ((WeldResultElement*)_obj)->WeldCount = query.value("WeldCount").toInt();
    ((WeldResultElement*)_obj)->PartCount = query.value("PartCount").toInt();
    ((WeldResultElement*)_obj)->OperateMode = query.value("OperateMode").toString();
    ((WeldResultElement*)_obj)->ActualResult.ActualEnergy
            = query.value("ActualEnergy").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualTPressure
            = query.value("ActualTPressure").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPressure
            = query.value("ActualPressure").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualAmplitude
            = query.value("ActualAmplitude").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualAmplitude2
            = query.value("ActualAmplitude2").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualWidth
            = query.value("ActualWidth").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualTime
            = query.value("ActualTime").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPeakPower
            = query.value("ActualPeakPower").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPreheight
            = query.value("ActualPreheight").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPostheight
            = query.value("ActualPostHeight").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualAlarmflags
            = query.value("ActualAlarmFlags").toInt();

    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Time.Plus
            = query.value("TimePlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Time.Minus
            = query.value("TimeMinus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Power.Plus
            = query.value("PowerPlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Power.Minus
            = query.value("PowerMinus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Preheight.Plus
            = query.value("PreheightPlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Preheight.Minus
            = query.value("PreheightMinus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Height.Plus
            = query.value("HeightPlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Height.Minus
            = query.value("HeightMinus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Force.Plus
            = query.value("ForcePlus").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.QualitySetting.Force.Minus
            = query.value("ForceMinus").toInt(); /* 10 items */

    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.WeldMode
            = (ADVANCESETTING::WELDMODE)query.value("WeldMode").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.StepWeldMode
            = (STEPWELD::STEPWELDMODE)query.value("StepWeldMode").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.EnergyToStep
            = query.value("EnergyToStep").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.TimeToStep
            = query.value("TimeToStep").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.PowerToStep
            = query.value("PowerToStep").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.StepWeld.Amplitude2
            = query.value("Amplitude2").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.PreBurst
            = query.value("PreBurst").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.HoldTime
            = query.value("HoldTime").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.SqzTime
            = query.value("SqueezeTime").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.ABDelay
            = query.value("AfterBurstDelay").toInt();
    ((WeldResultElement*)_obj)->WeldSettings.AdvanceSetting.ABDur
            = query.value("AfterBurstDuring").toInt(); /* 11 items */

    ((WeldResultElement*)_obj)->SampleRatio
            = (WeldResultElement::SAMPLERATIO)query.value("SampleRatio").toInt();
    QString sPathName = query.value("CurrentGraphDirectory").toString();
    UtilityClass *_Utility = UtilityClass::Instance();
    QString PowerJson;
    QString HeightJson;
    QSettingToJsonString(sPathName, PowerJson, HeightJson);
    _Utility->StringJsonToList(PowerJson,&((WeldResultElement*)_obj)->PowerGraph);
    _Utility->StringJsonToList(HeightJson,&((WeldResultElement*)_obj)->PostHeightGraph);
    ((WeldResultElement*)_obj)->NoOfSamples
            = ((WeldResultElement*)_obj)->PowerGraph.size();
    WeldResultDBObj.close();
    return bResult;
}
