#ifndef CSVWIREDATA_H
#define CSVWIREDATA_H
#include "DataClass.h"

class CSVWireData //: public DataClass
{
public:
    virtual bool ExportData(int ID, QString fileUrl);
    virtual QString GetExportString(int ID);
    virtual int ImportData(QString StrValue);
public:
    static CSVWireData* Instance();
protected:
    CSVWireData();
private:
    static CSVWireData* _instance;
public:
    ~CSVWireData();
};

#endif // CSVDATACLASS_H
