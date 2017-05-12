#ifndef CSVHARNESSDATA_H
#define CSVHARNESSDATA_H
#include "DataClass.h"

class CSVHarnessData //: public DataClass
{
public:
    virtual bool ExportData(int ID, QString fileUrl);
    virtual QString GetExportString(int ID);
    virtual int ImportData(QString StrValue, QMap<int, QString> SpliceIDMap);
public:
    static CSVHarnessData* Instance();
protected:
    CSVHarnessData();
private:
    static CSVHarnessData* _instance;
public:
    ~CSVHarnessData();
};

#endif // CSVHARNESSDATA_H
