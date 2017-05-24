#include "CSVWireData.h"
#include "DataBase/DBWireTable.h"
#include "Interface/WireElement.h"
#include "Modules/typedef.h"
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
    if(ListStr.size() != WireEnd)
        return false;
    RowStr.clear();
    for(int i = 0; i< ListStr.size(); i++)
    {
        if(i == SpliceID)
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
    out << "Wire Data" << '\n' << RowStr;
    csvFile.close();
    return true;
}

bool CSVWireData::ExportData(QList<int> IDList, QString fileUrl)
{
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
        if(i == SpliceID)
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
    if(DataList.size() < WireEnd)
        return ret;

    WireObj.WireID = QString(DataList[WireID]).toInt(&bResult, DECIMALISM);
    WireObj.WireName = DataList[WireName];
    QDateTime TimeLabel =
        QDateTime::fromString(DataList[CreatedDate], "yyyy/MM/dd hh:mm:ss");
    WireObj.CreatedDate = TimeLabel.toTime_t();
    WireObj.OperatorID = QString(DataList[OperatorID]).toInt(&bResult, DECIMALISM);
    WireObj.SpliceID = QString(DataList[SpliceID]).toInt(&bResult, DECIMALISM);
    WireObj.Color = DataList[Color];
    WireObj.Stripe.TypeOfStripe =
        (STRIPE::StripeType)QString(DataList[StripeType]).toInt(&bResult, DECIMALISM);
    WireObj.Stripe.Color = DataList[StripeColor];
    WireObj.Gauge = QString(DataList[Gauge]).toInt(&bResult, DECIMALISM);
    WireObj.GaugeAWG =
        QString(DataList[GaugeAWG]).toInt(&bResult, DECIMALISM);
    WireObj.TypeOfWire =
        (WireElement::MetalType)QString(DataList[MetalType]).toInt(&bResult, DECIMALISM);
    WireObj.TypeOfModule =
        (WireElement::ModuleType)QString(DataList[ModuleType]).toInt(&bResult, DECIMALISM);
    WireObj.Side =
        (WireElement::HorizontalLocation)QString(DataList[HorizontalLocation]).toInt(&bResult, DECIMALISM);
    WireObj.VerticalSide =
        (WireElement::VerticalLocation)QString(DataList[VerticalLocation]).toInt(&bResult, DECIMALISM);
    WireObj.Position =
        (WireElement::VerticalPosition)QString(DataList[VerticalPosition]).toInt(&bResult, DECIMALISM);
    if(bResult == false)
        return ret;
    ret = _WireDB->InsertRecordIntoTable(&WireObj);
    while (ret == ERROR)
    {
        QMap<int ,QString> tmpMap;
        _WireDB->QueryOnlyUseName(WireObj.WireName, &tmpMap);
        if (tmpMap.size() > 0)
        {
            WireObj.WireName = WireObj.WireName + "(1)";
            ret = _WireDB->InsertRecordIntoTable(&WireObj);
        }
        else if (tmpMap.size() == 0)
            return ERROR;
    }
    return ret;
}
