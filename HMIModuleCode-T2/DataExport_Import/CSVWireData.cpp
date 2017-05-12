#include "CSVWireData.h"
#include "DataBase/DBWireTable.h"
#include "Interface/WireElement.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
CSVWireData* CSVWireData::_instance = NULL;
CSVWireData* CSVWireData::Instance()
{
    if(_instance == 0){
        _instance = new CSVWireData();
    }
    return _instance;
}

CSVWireData::CSVWireData()
{

}

CSVWireData::~CSVWireData()
{

}

bool CSVWireData::ExportData(int ID, QString fileUrl)
{
    DBWireTable* _WireDB = DBWireTable::Instance();
    QStringList ListStr;
    QString RowStr = "";
    QString fileSource;
    ListStr.clear();
    bool bResult = _WireDB->QueryOneRecordFromTable(ID, ListStr);
    if(bResult == false)
        return bResult;
    if(ListStr.size() != 15)
        return false;
    RowStr.clear();
    for(int i = 0; i< ListStr.size(); i++)
    {
        if(i == 4)
            RowStr.append(QString("-1,"));
        else
            RowStr.append(ListStr[i] + ",");
    }
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
    out << "WireData" << '\n' << RowStr;
    csvFile.close();
    return true;
}

QString CSVWireData::GetExportString(int ID)
{
    DBWireTable* _WireDB = DBWireTable::Instance();
    QStringList ListStr;
    QString RowStr = "";
    QString fileSource;
    ListStr.clear();
    bool bResult = _WireDB->QueryOneRecordFromTable(ID, ListStr);
    if(bResult == false)
        return RowStr;
    RowStr.clear();
    for(int i = 0; i < ListStr.size(); i++)
    {
        if(i == 4)
            RowStr.append(QString("-1."));
        else
            RowStr.append(ListStr[i] + ".");
    }
    return RowStr;
}

int CSVWireData::ImportData(QString StrValue)
{
    QString RowStr;
    QStringList DataList;
    bool bResult;
    WireElement WireObj;
    int ret = -1;
    DBWireTable* _WireDB = DBWireTable::Instance();
    RowStr = StrValue;
    DataList = RowStr.split(",");
    if(DataList.size() < 15)
        return ret;

    WireObj.WireID = QString(DataList[0]).toInt(&bResult, 10);
    WireObj.WireName = DataList[1];
    QDateTime TimeLabel =
            QDateTime::fromString(DataList[2], "yyyy/MM/dd hh:mm:ss");
    WireObj.CreatedDate = TimeLabel.toTime_t();
    WireObj.OperatorID = QString(DataList[3]).toInt(&bResult, 10);
    WireObj.SpliceID = QString(DataList[4]).toInt(&bResult, 10);
    WireObj.Color = DataList[5];
    WireObj.Stripe.TypeOfStripe = (STRIPE::StripeType)QString(DataList[6]).toInt(&bResult, 10);
    WireObj.Stripe.Color = DataList[7];
    WireObj.Gauge = QString(DataList[8]).toInt(&bResult, 10);
    WireObj.GaugeAWG = QString(DataList[9]).toInt(&bResult, 10);
    WireObj.TypeOfWire = (WireElement::MetalType)QString(DataList[10]).toInt(&bResult, 10);
    WireObj.TypeOfModule = (WireElement::ModuleType)QString(DataList[11]).toInt(&bResult, 10);
    WireObj.Side = (WireElement::HorizontalLocation)QString(DataList[12]).toInt(&bResult, 10);
    WireObj.VerticalSide = (WireElement::VerticalLocation)QString(DataList[13]).toInt(&bResult, 10);
    WireObj.Position = (WireElement::VerticalPosition)QString(DataList[14]).toInt(&bResult, 10);
    if(bResult == false)
        return ret;
    ret = _WireDB->InsertRecordIntoTable(&WireObj);
    while (ret == -1)
    {
        QMap<int ,QString> tmpMap;
        _WireDB->QueryOnlyUseName(WireObj.WireName, &tmpMap);
        if (tmpMap.size() > 0)
        {
            WireObj.WireName = WireObj.WireName + "(1)";
            ret = _WireDB->InsertRecordIntoTable(&WireObj);
        }
        else if (tmpMap.size() == 0)
            return -1;
    }
    return ret;
}
