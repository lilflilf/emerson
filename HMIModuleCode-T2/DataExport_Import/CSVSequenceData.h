#ifndef CSVSEQUENCEDATA_H
#define CSVSEQUENCEDATA_H
#include "DataClass.h"

class CSVSequenceData : public DataClass
{
public:
    virtual bool ExportData(int ID, QString fileUrl);
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
