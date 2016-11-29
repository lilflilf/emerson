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
    void TestInsertOneRecordIntoOperatorTable();
    void TestInsertOneRecordIntoWeldResultTable();

    void TestUpdateOneRecordIntoWireTable();
    void TestUpdateOneRecordIntoPresetTable();
    void TestUpdateOneRecordIntoPartTable();
    void TestUpdateOneRecordIntoWorkOrderTable();
    void TestUpdateOneRecordIntoOperatorTable();

    void TestQueryEntireWireTable();
    void TestQueryEntireSpliceTable();
    void TestQueryEntirePartTable();
    void TestQueryEntireWorkOrderTable();
    void TestQueryEntireOpertorTable();

    void TestQueryOnlyUseNameWireTable();
    void TestQueryOnlyUseNameSpliceTable();
    void TestQueryOnlyUseNamePartTable();
    void TestQueryOnlyUseNameWorkOrderTable();
    void TestQueryOnlyUseNameOperatorTable();

    void TestQueryOnlyTimeWireTable();
    void TestQueryOnlyTimeSpliceTable();
    void TestQueryOnlyTimePartTable();
    void TestQueryOnlyTimeWorkOrderTable();
    void TestQueryOnlyTimeOperatorTable();

    void TestQueryOneWireTable();
    void TestQueryOneOperatorTable();

    void TestQueryOnlyUseFieldWeldResult();

    void TestMapJsonToString();
    void TestStringJsonToMap();

    void TestDeleteEntireWireTable();
    void TestDeleteEntirePresetTable();
    void TestDeleteEntirePartTable();
    void TestDeleteEntireWorkOrderTable();
    void TestDeleteEntireOperator();

    void TestDeleteOneWireTable();
    void TestDeleteOnePresetTable();
    void TestDeleteOnePartTable();
    void TestDeleteOneWorkOrderTable();
    void TestDeleteOneOperatorTable();

public:
    DataBaseTest();
};

#endif // DATABASETEST_H
