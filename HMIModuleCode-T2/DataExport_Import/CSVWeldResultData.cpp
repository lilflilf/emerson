#include "CSVWeldResultData.h"
#include "Modules/typedef.h"
#include "Modules/Statistics.h"
#include "DataBase/DBWeldResultTable.h"
#include "DataBase/DBPresetTable.h"
#include "Interface/WeldResultElement.h"
#include "Interface/PresetElement.h"

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
    DBPresetTable* _PresetDB = DBPresetTable::Instance();
    Statistics* _Statistics = Statistics::Instance();
    QString RowStr = "";
    QString HeadStr = "";
    QString fileSource;
    WeldResultElement WeldResultObj;
    PresetElement PresetObj;
    bool bResult = _WeldResultDB->QueryOneRecordWithGraph(ID, &WeldResultObj);
    if(bResult == false)
        return bResult;
    bResult = _PresetDB->QueryOneRecordFromTable(WeldResultObj.CurrentSplice.PartID,
            &PresetObj);
    if(bResult == false)
        return bResult;
    RowStr = _Statistics->HistoryEvent(&WeldResultObj, &PresetObj);
    HeadStr = _Statistics->HeaderString();

    fileSource = fileUrl;
    bResult = fileSource.contains("file:///");
    if(bResult == false)
        return bResult;
    fileSource = fileSource.mid(8);
    QFile csvFile(fileSource);
    bResult = csvFile.open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Truncate);
    if(bResult == false)
        return bResult;

    QTextStream out(&csvFile);
    out << "Weld Result Data" << '\n'
        << HeadStr << '\n'
        << RowStr;
    csvFile.close();

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
