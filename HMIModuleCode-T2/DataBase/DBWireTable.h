#ifndef DBWIRETABLE_H
#define DBWIRETABLE_H

#include "Sqlit3Class.h"

class DBWireTable : public SQLITCLASS
{
private:
    static QString WireDBFile;
    static QString DatabaseDir;
    static QString ModularDatabaseDir;
private:
    QSqlDatabase WireDBObj;
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
    virtual bool QueryOneRecordFromTable(int ID, QStringList &ResultStr);
    virtual bool DeleteEntireTable();
    virtual bool DeleteOneRecordFromTable(int ID, QString Name);

    virtual bool QueryOnlyUseName(QString Name, QMap<int, QString> *_obj);
    virtual bool QueryOnlyUseTime(unsigned int time_from, unsigned int time_to, QMap<int, QString> *_obj);
    virtual bool QueryUseNameAndTime(QString Name, unsigned int time_from,
                unsigned int time_to, QMap<int, QString>* _obj);
    virtual void SwitchDBObject(bool IsModularProduction);

    bool QueryOnlyUseField(QString FieldName, QString value, QMap<int, QString> *_obj, bool Orderby = true);

//    bool ExportData(int wireId, QString fileUrl);
//    QString GetExportString(int wireId);

//    int ImportData(QString value);
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
