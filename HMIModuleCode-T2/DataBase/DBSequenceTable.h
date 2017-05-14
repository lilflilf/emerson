#ifndef DBSEQUENCETABLE_H
#define DBSEQUENCETABLE_H
#include "Sqlit3Class.h"

class DBSequenceTable : public SQLITCLASS
{
private:
    static QString SequenceDBFile;
    static QString DatabaseDir;
    static QString ModularDatabaseDir;
private:
    QSqlDatabase SequenceDBObj;
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

//    bool exportData(int partId, QString fileUrl);
//    int importData(QString value,QMap<int, QString> spliceIdMap);
//    QString GetExportString(int partId);
public:
    static DBSequenceTable* Instance();
protected:
    DBSequenceTable();
//    void InsertTestDataIntoTable();
//    DBPresetTable *spliceTable;
private:
    static DBSequenceTable* _instance;
public:
    ~DBSequenceTable();
};

#endif // DBSEQUENCETABLE_H
