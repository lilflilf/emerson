#ifndef DBWELDRESULTTABLE_H
#define DBWELDRESULTTABLE_H

#include "Sqlit3Class.h"
enum FieldType
{
    WorkOrderType,
    PartType,
    SpliceType,
    CreatedDateType,
};

class DBWeldResultTable : public SQLITCLASS
{
private:
    static QString WeldResultDBFile;
    static QString DatabaseDir;
    static QString DatabaseGraphDir;
    static QMap<int, QString> TableNameList;
private:
    QSqlDatabase WeldResultDBObj;

private:
    bool JsonStringToQSetting(QString sPathName, QString PowerGraph, QString HeightGraph);
    bool QSettingToJsonString(QString sPathName, QString &PowerGraph, QString &HeightGraph);
public:
    virtual bool CreateNewTable();
    virtual bool InsertRecordIntoTable(void* _obj);
    virtual bool UpdateRecordIntoTable(void* _obj);
    virtual bool QueryEntireTable(QMap<int, QString>* _obj);
    virtual bool QueryOneRecordFromTable(int ID, QString Name, void* _obj);
    virtual bool DeleteEntireTable();
    virtual bool DeleteOneRecordFromTable(int ID, QString Name);

    virtual bool QueryOnlyUseName(QString Name, QMap<int, QString> *_obj);
    virtual bool QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj);

    bool QueryOnlyUseField(QString FieldName, QMap<int, QString> *_obj, bool Orderby = true);
    bool QueryBySomeFields(QString WorkOrderName, QString PartName, QString SpliceName,
                           unsigned int time_from, unsigned int time_to,
                           enum FieldType OrderField, bool Orderby, QMap<int, QString> *_obj);
    bool QueryOneRecordWithGraph(int ID, QString Name, void* _obj);
public:
    static DBWeldResultTable* Instance();
protected:
    DBWeldResultTable();
private:
    static DBWeldResultTable* _instance;
public:
    ~DBWeldResultTable();
};

#endif // DBWELDRESULTTABLE_H
