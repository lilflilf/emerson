#include "CSVSequenceData.h"
#include "Modules/typedef.h"
CSVSequenceData* CSVSequenceData::_instance = NULL;
CSVSequenceData* CSVSequenceData::Instance()
{
    if(_instance == 0){
        _instance = new CSVSequenceData();
    }
    return _instance;
}

CSVSequenceData::CSVSequenceData()
{

}

CSVSequenceData::~CSVSequenceData()
{

}

bool CSVSequenceData::ExportData(int ID, QString fileUrl)
{
    return true;
}

QString CSVSequenceData::GetExportString(int ID)
{
    return "";
}

int CSVSequenceData::ImportData(QString StrValue)
{
    return ERROR;
}
