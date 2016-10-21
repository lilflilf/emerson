#ifndef DATABASETEST_H
#define DATABASETEST_H
#include <QString>

class DataBaseTest
{
private:
    QString TestStr;
public:
    void TestInsertOneRecordIntoWireTable();
    void TestInsertOneRecordIntoPresetTable();
    void TestInsertOneRecordIntoPartTable();
    void TestInsertOneRecordIntoWorkOrderTable();
    void TestQueryEntireWireTable();
    void TestQueryEntireSpliceTable();
    void TestQueryEntirePartTable();
    void TestQueryEntireWorkOrderTable();
    void TestQueryOneWireTable();
    void TestMapJsonToString();
    void TestStringJsonToMap();
public:
    DataBaseTest();
};

#endif // DATABASETEST_H
