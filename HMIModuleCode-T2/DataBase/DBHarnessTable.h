#ifndef DBPARTTABLE_H
#define DBPARTTABLE_H

#include "Sqlit3Class.h"
#include "DBPresetTable.h"
class DBHarnessTable : public SQLITCLASS
{
private:
    static QString HarnessDBFile;
    static QString DatabaseDir;
    static QString ModularDatabaseDir;
private:
    QSqlDatabase HarnessDBObj;
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

    bool exportData(int partId, QString fileUrl);
    int importData(QString value,QMap<int, QString> spliceIdMap);
    QString GetExportString(int partId);
public:
    static DBHarnessTable* Instance();
protected:
    DBHarnessTable();
    void InsertTestDataIntoTable();
    DBPresetTable *spliceTable;
private:
    static DBHarnessTable* _instance;
public:
    ~DBHarnessTable();
};

#endif // DBPARTTABLE_H
