#ifndef CSVPRESETDATA_H
#define CSVPRESETDATA_H
#include "DataClass.h"

class CSVPresetData //: public DataClass
{
public:
    virtual bool ExportData(int ID, QString fileUrl);
    virtual QString GetExportString(int ID);
//    virtual int ImportData(QString StrValue);
    virtual int ImportData(QString StrValue, QMap<int, QString> WireIDMap);
public:
    static CSVPresetData* Instance();
protected:
    CSVPresetData();
private:
    static CSVPresetData* _instance;
public:
    ~CSVPresetData();
};

#endif // CSVDATACLASS_H
