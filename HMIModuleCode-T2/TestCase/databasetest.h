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

    void TestUpdateOneRecordIntoWireTable();
    void TestUpdateOneRecordIntoPresetTable();
    void TestUpdateOneRecordIntoPartTable();
    void TestUpdateOneRecordIntoWorkOrderTable();

    void TestQueryEntireWireTable();
    void TestQueryEntireSpliceTable();
    void TestQueryEntirePartTable();
    void TestQueryEntireWorkOrderTable();
    void TestQueryOneWireTable();
    void TestMapJsonToString();
    void TestStringJsonToMap();

    void TestDeleteEntireWireTable();
    void TestDeleteEntirePresetTable();
    void TestDeleteEntirePartTable();
    void TestDeleteEntireWorkOrderTable();

    void TestDeleteOneWireTable();
    void TestDeleteOnePresetTable();
    void TestDeleteOnePartTable();
    void TestDeleteOneWorkOrderTable();
public:
    DataBaseTest();
};

#endif // DATABASETEST_H
