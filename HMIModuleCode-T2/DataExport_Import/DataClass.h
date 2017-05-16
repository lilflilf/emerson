#ifndef DATACLASS_H
#define DATACLASS_H
#include <QString>
class DataClass
{
public:
    virtual bool ExportData(int ID, QString fileUrl) = 0;
    virtual QString GetExportString(int ID) = 0;
    virtual int ImportData(QString StrValue) = 0;
};

#endif // DATACLASS_H