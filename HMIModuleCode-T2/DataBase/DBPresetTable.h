#ifndef DBPRESETTABLE_H
#define DBPRESETTABLE_H

#include "Sqlit3Class.h"
#include "DBWireTable.h"
class DBPresetTable : public SQLITCLASS
{
private:
    static QString SpliceDBFile;
    static QString DatabaseDir;
    static QString ModularDatabaseDir;
private:
    QSqlDatabase SpliceDBObj;
    bool mIsModularProduction;
private:
    bool OpenDBObject();
public:
    virtual bool CreateNewTable();
    virtual int InsertRecordIntoTable(void* _obj);
    virtual bool UpdateRecordIntoTable(void* _obj);
    virtual bool QueryEntireTable(QMap<int, QString>* _obj);
    virtual bool QueryOneRecordFromTable(int ID, QString Name, void* _obj);
    virtual bool QueryOneRecordFromTable(int ID, void* _obj);
    virtual bool DeleteEntireTable();
    virtual bool DeleteOneRecordFromTable(int ID, QString Name);

    virtual bool QueryOnlyUseName(QString Name, QMap<int, QString> *_obj);
    virtual bool QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj);
    virtual bool QueryUseNameAndTime(QString Name, unsigned int time_from,
                unsigned int time_to, QMap<int, QString>* _obj);
    virtual void SwitchDBObject(bool IsModularProduction);

    bool exportData(int spliceId, QString fileUrl);
    int importData(QString value,QMap<int, QString> wireIdMap);
    QString GetExportString(int spliceId);
public:
    static DBPresetTable* Instance();
protected:
    DBPresetTable();
    void InsertTestDataIntoTable();
    DBWireTable *wireTable;
private:
    static DBPresetTable* _instance;
public:
    ~DBPresetTable();
};

#endif // DBPRESETTABLE_H
