#include "CSVWeldResultData.h"
#include "Modules/typedef.h"
#include "DataBase/DBWeldResultTable.h"
#include "Interface/WeldResultElement.h"

CSVWeldResultData* CSVWeldResultData::_instance = NULL;
CSVWeldResultData* CSVWeldResultData::Instance()
{
    if(_instance == 0){
        _instance = new CSVWeldResultData();
    }
    return _instance;
}

CSVWeldResultData::CSVWeldResultData()
{

}

CSVWeldResultData::~CSVWeldResultData()
{

}

bool CSVWeldResultData::ExportData(int ID, QString fileUrl)
{
    DBWeldResultTable* _WeldResultDB = DBWeldResultTable::Instance();
    QStringList ListStr;
    QString RowStr = "";
    QString fileSource;
    ListStr.clear();
    return true;
}

QString CSVWeldResultData::GetExportString(int ID)
{
    UNUSED(ID);
    return "";
}

int CSVWeldResultData::ImportData(QString StrValue)
{
    UNUSED(StrValue);
    return 0;
}
