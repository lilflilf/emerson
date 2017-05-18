#ifndef CSVWIREDATA_H
#define CSVWIREDATA_H
#include "DataClass.h"

class CSVWireData //: public DataClass
{
public:
    enum WireItem{
        WireID = 0,
        WireName = 1,
        CreatedDate = 2,
        OperatorID = 3,
        SpliceID = 4,
        Color = 5,
        StripeType = 6,
        StripeColor = 7,
        Gauge = 8,
        GaugeAWG = 9,
        MetalType = 10,
        ModuleType = 11,
        HorizontalLocation = 12,
        VerticalLocation = 13,
        VerticalPosition = 14,
        WireEnd = 15
    };

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
