#ifndef DBPRESETTABLE_H
#define DBPRESETTABLE_H

#include "Sqlit3Class.h"
class DBPresetTable : public SQLITCLASS
{
private:
    static QString SpliceDBFile;
    static QString DatabaseDir;
private:
    QSqlDatabase SpliceDBObj;

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

public:
    static DBPresetTable* Instance();
protected:
    DBPresetTable();
private:
    static DBPresetTable* _instance;
public:
    ~DBPresetTable();
};

#endif // DBPRESETTABLE_H
