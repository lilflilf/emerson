#ifndef CSVHARNESSDATA_H
#define CSVHARNESSDATA_H
#include "DataClass.h"

class CSVHarnessData //: public DataClass
{
public:
    enum HarnessItem
    {
        HarnessID = 0,
        HarnessName = 1,
        CreatedDate = 2,
        OperatorID = 3,
        /* PartTypeSetting */
        ProcessMode = 4,
        TotalWorkstation = 5,
        MaxSplicesPerWorkstation = 6,
        Rows = 7,
        Columns = 8,
        MaxSplicesPerZone =9,
        NoOfSplice = 10,
        JSONSplice = 11,
        HarnessEnd = 12
    };

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
