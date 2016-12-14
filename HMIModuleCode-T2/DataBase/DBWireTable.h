#ifndef DBWIRETABLE_H
#define DBWIRETABLE_H

#include "Sqlit3Class.h"

class DBWireTable : public SQLITCLASS
{
private:
    static QString WireDBFile;
    static QString DatabaseDir;
private:
    QSqlDatabase WireDBObj;

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

    bool QueryOnlyUseField(QString FieldName, QString value, QMap<int, QString> *_obj, bool Orderby = true);
public:
    static DBWireTable* Instance();
protected:
    DBWireTable();
private:
    static DBWireTable* _instance;
public:
    ~DBWireTable();
};

#endif // DBWIRETABLE_H
