#ifndef CSVSEQUENCEDATA_H
#define CSVSEQUENCEDATA_H
#include "DataClass.h"
#include <QMap>

class CSVSequenceData : public DataClass
{
public:
    enum SequenceItem
    {
        SequenceID = 0,
        SequenceName = 1,
        CreatedDate = 2,
        OperatorID = 3,
        NoOfSplice = 4,
        JSONSplice = 5,
        SpliceString = 6,
        SequenceEnd = 7
    };
private:
    QMap<int, struct SEQUENCEATTRIBUTE> SpliceIndexMap;
    QList<int> SpliceIndexList;
private:
    bool ParseSpliceData(QString StrSplice);
    void ParseSequenceJOSN(QString SequenceJOSN);
public:
    virtual bool ExportData(int ID, QString fileUrl);
    virtual bool ExportData(QList<int> IDList, QString fileUrl);
    virtual QString GetExportString(int ID);
    virtual int ImportData(QString StrValue);
public:
    static CSVSequenceData* Instance();
protected:
    CSVSequenceData();
private:
    static CSVSequenceData* _instance;
public:
    ~CSVSequenceData();
};

#endif // CSVSEQUENCEDATA_H
