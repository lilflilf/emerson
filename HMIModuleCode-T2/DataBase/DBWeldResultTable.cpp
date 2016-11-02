#include "DBWeldResultTable.h"
#include "Modules/UtilityClass.h"
#include <QDebug>

DBWeldResultTable* DBWeldResultTable::_instance = NULL;
QString DBWeldResultTable::WeldResultDBFile = "WeldResultHistory.db";
QString DBWeldResultTable::DatabaseDir = "c:\\BransonData\\History\\";
DBWeldResultTable* DBWeldResultTable::Instance()
{
    if(_instance == 0){
        _instance = new DBWeldResultTable();
    }
    return _instance;
}

DBWeldResultTable::DBWeldResultTable()
{
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

bool DBWeldResultTable::CreateNewTable()
{
    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();

//    bResult = query.exec(SQLSentence[CREATE_OPERATOR_TABLE]);   //run SQL

    if(bResult == false)
        qDebug() << "SQL ERROR:"<< query.lastError();

    WeldResultDBObj.close();

    return bResult;
}

bool DBWeldResultTable::InsertRecordIntoTable(void *_obj)
{
    bool bResult = false;
    if(_obj == NULL)
        return false;

    QSqlQuery query(WeldResultDBObj);
    bResult = WeldResultDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL Open:"<< query.lastError();
        return bResult;
    }

//    query.prepare(SQLSentence[INSERT_OPERATOR_TABLE]);
    query.addBindValue(((WeldResultElement*)_obj)->OperatorName);
    QDateTime TimeLabel = QDateTime::fromTime_t(((WeldResultElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((WeldResultElement*)_obj)->CurrentWorkOrder.WorkOrderID);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentWorkOrder.WorkOrderName);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentPart.PartID);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentPart.PartName);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentSplice.SpliceID);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentSplice.SpliceName);
    query.addBindValue(((WeldResultElement*)_obj)->WeldCount);
    query.addBindValue(((WeldResultElement*)_obj)->PartCount);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualAlarmflags);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualAmplitude);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualAmplitude2);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualEnergy);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualPeakPower);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualPostheight);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualPreheight);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualPressure);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualTime);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualTPressure);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualWidth);
    query.addBindValue(((WeldResultElement*)_obj)->SampleRatio);
    query.addBindValue(((WeldResultElement*)_obj)->PowerGraph.size()); //NoOfSamples
    UtilityClass *_Utility = UtilityClass::Instance();
    QString tmpJson;
    _Utility->MapJsonToString(&((WeldResultElement*)_obj)->PowerGraph,tmpJson);
    query.addBindValue(tmpJson);
    _Utility->MapJsonToString(&((WeldResultElement*)_obj)->PostHeightGraph, tmpJson);
    query.addBindValue(tmpJson);

    bResult = query.exec();
    if (bResult == false)   //run SQL
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    WeldResultDBObj.close();
    return bResult;
}

bool DBWeldResultTable::QueryEntireTable(QMap<int, QString> *_obj)
{
    if(_obj == NULL)
        return false;

    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();
    if(bResult == false)
        return bResult;

//    bResult = query.exec(SQLSentence[QUERY_ENTIRE_OPERATOR_TABLE]);
    if (bResult == true)
    {
        _obj->clear();
        while(query.next())
        {
            _obj->insert(query.value("ID").toInt(),
                           query.value("Operator").toString());
        }
    }
    else
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
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
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

//    query.prepare(SQLSentence[QUERY_ONE_RECORD_OPERATOR_TABLE]);
    query.addBindValue(ID);
    query.addBindValue(OperatorName);

    bResult = query.exec();
    if(bResult == false)
    {
        WeldResultDBObj.close();
        qDebug() << "SQL ERROR:"<< query.lastError();
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
            = query.value("CurrentWorkOrderID").toInt();
    ((WeldResultElement*)_obj)->CurrentWorkOrder.WorkOrderName
            = query.value("CurrentWorkOrderName").toString();
    ((WeldResultElement*)_obj)->CurrentPart.PartID
            = query.value("CurrentPartID").toInt();
    ((WeldResultElement*)_obj)->CurrentPart.PartName
            = query.value("CurrentPartName").toString();
    ((WeldResultElement*)_obj)->CurrentSplice.SpliceID
            = query.value("CurrentSpliceID").toInt();
    ((WeldResultElement*)_obj)->CurrentSplice.SpliceName
            = query.value("CurrentSpliceName").toString();
    ((WeldResultElement*)_obj)->WeldCount = query.value("WeldCount").toInt();
    ((WeldResultElement*)_obj)->PartCount = query.value("PartCount").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualAlarmflags
            = query.value("ActualAlarmFlags").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualAmplitude
            = query.value("ActualAmplitude").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualAmplitude2
            = query.value("ActualAmplitude2").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualEnergy
            = query.value("ActualEnergy").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPeakPower
            = query.value("ActualPeakPower").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPostheight
            = query.value("ActualPostHeight").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPreheight
            = query.value("ActualPreheight").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualPressure
            = query.value("ActualPressure").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualTime
            = query.value("ActualTime").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualTPressure
            = query.value("ActualTPressure").toInt();
    ((WeldResultElement*)_obj)->ActualResult.ActualWidth
            = query.value("ActualWidth").toInt();
    ((WeldResultElement*)_obj)->SampleRatio
            = (enum SAMPLERATIO)query.value("SampleRatio").toInt();
    UtilityClass *_Utility = UtilityClass::Instance();
    QString strJson = query.value("PowerGraphJson").toString();;
    _Utility->StringJsonToMap(strJson,&((WeldResultElement*)_obj)->PowerGraph);
    strJson = query.value("PostHeightJson").toString();
    _Utility->StringJsonToMap(strJson,&((WeldResultElement*)_obj)->PostHeightGraph);
    ((WeldResultElement*)_obj)->NoOfSamples
            = ((WeldResultElement*)_obj)->PowerGraph.size();
    WeldResultDBObj.close();
    return bResult;
}

bool DBWeldResultTable::DeleteEntireTable()
{
    QSqlQuery query(WeldResultDBObj);
    bool bResult = WeldResultDBObj.open();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

//    bResult = query.exec(SQLSentence[DELETE_ENTIRE_OPERATOR_TABLE]);
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
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
        qDebug() << "SQL ERROR:"<< query.lastError();
        return bResult;
    }

//    query.prepare(SQLSentence[DELETE_ONE_RECORD_OPERATOR_TABLE]);
    query.addBindValue(ID);
    query.addBindValue(OperatorName);

    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
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

//    query.prepare(SQLSentence[UPDATE_ONE_RECORD_OPERATOR_TABLE]);
    query.addBindValue(((WeldResultElement*)_obj)->OperatorName);
    QDateTime TimeLabel = QDateTime::fromTime_t(((WeldResultElement*)_obj)->CreatedDate);
    query.addBindValue(TimeLabel.toString("yyyy/MM/dd hh:mm:ss"));
    query.addBindValue(((WeldResultElement*)_obj)->CurrentWorkOrder.WorkOrderID);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentWorkOrder.WorkOrderName);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentPart.PartID);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentPart.PartName);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentSplice.SpliceID);
    query.addBindValue(((WeldResultElement*)_obj)->CurrentSplice.SpliceName);
    query.addBindValue(((WeldResultElement*)_obj)->WeldCount);
    query.addBindValue(((WeldResultElement*)_obj)->PartCount);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualAlarmflags);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualAmplitude);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualAmplitude2);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualEnergy);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualPeakPower);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualPostheight);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualPreheight);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualPressure);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualTime);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualTPressure);
    query.addBindValue(((WeldResultElement*)_obj)->ActualResult.ActualWidth);
    query.addBindValue(((WeldResultElement*)_obj)->SampleRatio);

    query.addBindValue(((WeldResultElement*)_obj)->PowerGraph.size()); //NoOfSamples
    UtilityClass *_Utility = UtilityClass::Instance();
    QString tmpJson;
    _Utility->MapJsonToString(&((WeldResultElement*)_obj)->PowerGraph,tmpJson);
    query.addBindValue(tmpJson);
    _Utility->MapJsonToString(&((WeldResultElement*)_obj)->PostHeightGraph, tmpJson);
    query.addBindValue(tmpJson);
    bResult = query.exec();
    if(bResult == false)
    {
        qDebug() << "SQL ERROR:"<< query.lastError();
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
//    query.prepare("SELECT ID, PartName FROM Part WHERE PartName = ?");
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
        qDebug() << "SQL ERROR:"<< query.lastError();
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
//    query.prepare("SELECT ID, OperatorName FROM Operator WHERE CreatedDate >= ?"
//                  " AND CreatedDate <= ?");
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
        qDebug() << "SQL ERROR:"<< query.lastError();
    }

    WeldResultDBObj.close();
    return bResult;
}

