#ifndef DBWELDRESULTTABLE_H
#define DBWELDRESULTTABLE_H

#include "Sqlit3Class.h"
class DBWeldResultTable : public SQLITCLASS
{
private:
    static QString WeldResultDBFile;
    static QString DatabaseDir;
private:
    QSqlDatabase WeldResultDBObj;
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
    static DBWeldResultTable* Instance();
protected:
    DBWeldResultTable();
private:
    static DBWeldResultTable* _instance;
public:
    ~DBWeldResultTable();
};

#endif // DBWELDRESULTTABLE_H
