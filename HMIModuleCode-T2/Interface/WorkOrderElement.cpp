#include "WorkOrderElement.h"
#include "Modules/UtilityClass.h"
#include "Modules/M10INI.h"
#include <QSettings>
#include <QDateTime>
#include <QDir>

WorkOrderElement::WorkOrderElement()
{
    RevCode = -1;
    WorkOrderID = -1;
    WorkOrderName.clear();
    CreatedDate.clear();
    OperatorID = -1;
    PartList.clear();
    CurrentSpliceIndex = -1;
    BatchSize = -1;
    CurrentPartCount = -1;
    MissPartList.clear();
    CurrentPartIndex.PartID = -1;
    CurrentPartIndex.PartName.clear();
    WorkOrderMode = WorkOrderElement::UNDEFINE;
}

WorkOrderElement::~WorkOrderElement()
{
    PartList.clear();
    MissPartList.clear();
}

WorkOrderElement WorkOrderElement::operator=(const WorkOrderElement &WorkOrderObject)
{
    if(this == &WorkOrderObject)
        return *this;
    this->RevCode = WorkOrderObject.RevCode;
    this->WorkOrderID = WorkOrderObject.WorkOrderID;
    this->WorkOrderName = WorkOrderObject.WorkOrderName;
    this->CreatedDate = WorkOrderObject.CreatedDate;
    this->OperatorID = WorkOrderObject.OperatorID;
    QMap<int, QString>::const_iterator i = WorkOrderObject.PartList.constBegin();
    while(i != WorkOrderObject.PartList.constEnd())
    {
        this->PartList.insert(i.key(),i.value());
        ++i;
    }
    this->CurrentSpliceIndex = WorkOrderObject.CurrentSpliceIndex;
    this->BatchSize = WorkOrderObject.BatchSize;
    this->CurrentPartCount = WorkOrderObject.CurrentPartCount;
    i = WorkOrderObject.MissPartList.constBegin();
    while(i != WorkOrderObject.MissPartList.constEnd())
    {
        this->MissPartList.insert(i.key(),i.value());
        ++i;
    }
    this->CurrentPartIndex.PartID = WorkOrderObject.CurrentPartIndex.PartID;
    this->CurrentPartIndex.PartName = WorkOrderObject.CurrentPartIndex.PartName;
    this->WorkOrderMode = WorkOrderObject.WorkOrderMode;
    return *this;
}

void WorkOrderElement::WriteWorkOrderToQSetting()
{
    QString str; //BransonInitial
    M10INI* _M10INI = M10INI::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString FileName = _M10INI->ConfigFilesPath + BRANSON_WORKORDER_FILE;
    QSettings settings(FileName, QSettings::IniFormat);
    settings.beginGroup("CurrentWorkOrder");
    settings.setValue("RevCode", RevCode);
    settings.setValue("WorkOrderID", WorkOrderID);
    settings.setValue("WorkOrderName", WorkOrderName);
    settings.setValue("CreatedDate", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    settings.setValue("OperatorID", OperatorID);
    settings.setValue("WorkOrderMode", WorkOrderMode);
    settings.setValue("CurrentSpliceIndex", CurrentSpliceIndex);
    settings.setValue("IsConstrainedFlag", IsConstrainedFlag);
    settings.setValue("BatchSize", BatchSize);
    settings.setValue("TeachMode", Teach_Mode);
    settings.setValue("CurrentPartCount", CurrentPartCount);

    settings.beginGroup("CurrentPartIndex");
    settings.setValue("PartID", CurrentPartIndex.PartID);
    settings.setValue("PartHash", CurrentPartIndex.PartHash);
    settings.setValue("PartName", CurrentPartIndex.PartName);
    settings.endGroup();

    settings.beginGroup("CurrentMissPartList");
    QString Str;
    _Utility->MapJsonToString(&MissPartList, Str);
    settings.setValue("MissPartList", Str);
    settings.endGroup();

    settings.beginGroup("CurrentPartList");
    Str.clear();
    _Utility->MapJsonToString(&PartList, Str);
    settings.setValue("PartList", Str);
    settings.endGroup();
    settings.endGroup();
}

bool WorkOrderElement::ReadWorkOrderFromQSetting()
{
    QDir dir;
    QString str = "";
    M10INI* _M10INI = M10INI::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    QString FileName = _M10INI->ConfigFilesPath + BRANSON_WORKORDER_FILE;
    if (dir.exists(FileName) == false)
        return false;

    QSettings settings(FileName, QSettings::IniFormat);
    settings.beginGroup("CurrentWorkOrder");
    RevCode = settings.value("RevCode").value<int>();
    WorkOrderID = settings.value("WorkOrderID").value<int>();
    WorkOrderName = settings.value("WorkOrderName").value<QString>();
    CreatedDate = settings.value("CreatedDate").value<QString>();
    OperatorID = settings.value("OperatorID").value<int>();
    WorkOrderMode = (WorkOrderElement::WORKORDERMODE)settings.value("WorkOrderMode").value<int>();
    CurrentSpliceIndex = settings.value("CurrentSpliceIndex").value<int>();
    IsConstrainedFlag = settings.value("IsConstrainedFlag").value<bool>();
    BatchSize = settings.value("BatchSize").value<int>();
    Teach_Mode = (TEACHMODESETTING::TEACH_MODE_TYPE)settings.value("TeachMode").value<int>();
    CurrentPartCount = settings.value("CurrentPartCount").value<int>();

    settings.beginGroup("CurrentPartIndex");
    CurrentPartIndex.PartID = settings.value("PartID").value<int>();
    CurrentPartIndex.PartHash = settings.value("PartHash").value<int>();
    CurrentPartIndex.PartName = settings.value("PartName").value<QString>();
    settings.endGroup();

    settings.beginGroup("CurrentMissPartList");
    QString Str = settings.value("MissPartList").value<QString>();
    _Utility->StringJsonToMap(Str, &MissPartList);
    settings.endGroup();

    settings.beginGroup("CurrentPartList");
    Str = settings.value("PartList").value<QString>();
    _Utility->StringJsonToMap(Str,&PartList);
    settings.endGroup();

    settings.endGroup();
    return true;
}
