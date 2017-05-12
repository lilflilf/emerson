#ifndef DBOPERATORTABLE_H
#define DBOPERATORTABLE_H

#include "Sqlit3Class.h"

class DBOperatorTable : public SQLITCLASS
{
private:
    static QString OperatorDBFile;
    static QString DatabaseDir;
private:
    QSqlDatabase OperatorDBObj;
public:
    virtual bool CreateNewTable();
    virtual int InsertRecordIntoTable(void* _obj);
    virtual bool UpdateRecordIntoTable(void* _obj);
    virtual bool QueryEntireTable(QMap<int, QString>* _obj);
    virtual bool QueryOneRecordFromTable(int ID, QString Name, void* _obj);
    virtual bool QueryOneRecordFromTable(int ID, void* _obj);
    virtual bool QueryOneRecordFromTable(int ID, QStringList &ResultStr);
    virtual bool DeleteEntireTable();
    virtual bool DeleteOneRecordFromTable(int ID, QString Name);

    virtual bool QueryOnlyUseName(QString Name, QMap<int, QString> *_obj);
    virtual bool QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj);
    virtual bool QueryUseNameAndTime(QString Name, unsigned int time_from,
                unsigned int time_to, QMap<int, QString>* _obj);
    virtual void SwitchDBObject(bool IsModularProduction);
public:
    static DBOperatorTable* Instance();
protected:
    DBOperatorTable();
private:
    static DBOperatorTable* _instance;
public:
    ~DBOperatorTable();
};

#endif // DBOPERATORTABLE_H
