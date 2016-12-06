#include "tablemodel.h"
#include <QDebug>
#include <QQmlPropertyMap>

WorkOrderModel::WorkOrderModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_workOrderAdaptor = DBWorkOrderTable::Instance();
    workOrders = new QMap<int, QString>();
}

QVariant WorkOrderModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if(role < Qt::UserRole)
    {
        qDebug() << "WorkOrderModel::data(const QModelIndex &index, int role) const";
    }
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        int rowId;
        QMap<int,QString>::iterator it; //遍历map
        int i = 0;
        for ( it = workOrders->begin(); it != workOrders->end(); ++it ) {
            if (i == index.row()){
                rowId = it.key();
                break;
            }
            else {
                i++;
            }
        }
        WorkOrderElement myWorkOrder;
        m_workOrderAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myWorkOrder);

        if (columnIdx == 0)
            value = QVariant::fromValue(myWorkOrder.WorkOrderID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(myWorkOrder.WorkOrderName);
        else if (columnIdx == 2)
            value = QVariant::fromValue(QDateTime::fromTime_t(myWorkOrder.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 3)
            value = QVariant::fromValue(myWorkOrder.PartIndex.begin().value());
        else if (columnIdx == 4)
            value = QVariant::fromValue(myWorkOrder.Quantity);
    }
    return value;
}



void WorkOrderModel::setModelList(unsigned int time_from, unsigned int time_to)
{
    beginResetModel();
    workOrders->clear();
    if (m_workOrderAdaptor->QueryOnlyUseTime(time_from,time_to,workOrders))
        qDebug( )<< "setModelList WorkOrderModel" << workOrders->count();
    endResetModel();
}

void WorkOrderModel::setModelList()
{
    beginResetModel();
    workOrders->clear();
    if (m_workOrderAdaptor->QueryEntireTable(workOrders))
        qDebug( )<< "setModelList WorkOrderModel" << workOrders->count();
    endResetModel();
}


int WorkOrderModel::rowCount(const QModelIndex & parent) const
{
    return workOrders->count();
}


int WorkOrderModel::count()
{
    return workOrders->count();
}


int WorkOrderModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant WorkOrderModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

void WorkOrderModel::setRoles(const QStringList &names)
{
    m_roleNames.clear();
    for(int idx=0; idx<names.count(); idx++)
    {
        m_roleNames[Qt::UserRole + idx + 1] = names[idx].toLocal8Bit();
    }
}

QHash<int, QByteArray> WorkOrderModel::roleNames() const
{
    return m_roleNames;
}

int WorkOrderModel::getCurrentIndex(QString info)
{
    int temp = 0;
    temp = m_idList.indexOf(info);
    return temp;
}

bool WorkOrderModel::updateRecordIntoTable(int workId,QString oldWorkName, QString workName, int partId, QString partName, int count)
{
    qDebug() << "updateRecordIntoTable" << workId << oldWorkName << workName << partId << partName << count;
    struct WorkOrderElement tempWorkOrder;
    m_workOrderAdaptor->QueryOneRecordFromTable(workId, oldWorkName,&tempWorkOrder);
    tempWorkOrder.WorkOrderName = workName;
    tempWorkOrder.PartIndex.insert(partId, partName);
    tempWorkOrder.Quantity = count;
    m_workOrderAdaptor->UpdateRecordIntoTable(&tempWorkOrder);
    setModelList();
}

bool WorkOrderModel::insertRecordIntoTable(QString workName, int partId, QString partName, int count)
{
    struct WorkOrderElement tempWorkOrder;
    tempWorkOrder.WorkOrderName = workName;
    tempWorkOrder.Quantity = count;
    tempWorkOrder.PartIndex.insert(partId,partName);
    m_workOrderAdaptor->InsertRecordIntoTable(&tempWorkOrder);
    setModelList();
}

QVariant WorkOrderModel::getWorkOrderValue(int index, QString key)
{
    QMap<int,QString>::iterator it; //遍历map
    int i = 0;
    int orderId;
    for ( it = workOrders->begin(); it != workOrders->end(); ++it ) {
        if (i == index){
            orderId = it.key();
            break;
        }
        else {
            i++;
        }
    }
    WorkOrderElement myWorkOrder;
    m_workOrderAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myWorkOrder);
    QHash<QString, QVariant> WorkOrderModelHash;
    WorkOrderModelHash.insert("workOrderId",myWorkOrder.WorkOrderID);
    WorkOrderModelHash.insert("name",myWorkOrder.WorkOrderName);
    WorkOrderModelHash.insert("date",QDateTime::fromTime_t(myWorkOrder.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    WorkOrderModelHash.insert("middle",myWorkOrder.PartIndex.begin().value());
    WorkOrderModelHash.insert("count",myWorkOrder.Quantity);
    //list << "name" << "date" << "middle" << "count";
    if (key == "") {
        return WorkOrderModelHash;
    } else {
        return WorkOrderModelHash.value(key);
    }
}

void WorkOrderModel::removeValue(int id, QString name)
{
    m_workOrderAdaptor->DeleteOneRecordFromTable(id,name);
}

//QString WorkOrderModel::getContacterName(QString contacterId)
//{
//    Contacter contacter;
//    contacter = m_contacterAdaptor->getContacter(contacterId);
//    return contacter.surname + contacter.name;
//}

/*info:id*/


//void WorkOrderModel::removeContacter(QString info, int rows)
//{
//    int temp = 0;
//    bool bIsFind = false;
//    for (int i = 0; i < rows; i++) {
//        if (m_idList.at(i) == info) {
//            bIsFind = true;
//            temp = i;
//            break;
//        }
//    }
//    if (bIsFind) {
//        beginRemoveRows(QModelIndex(),temp,temp);
//        m_idList.removeAt(temp);
//        endRemoveRows();
//    }
//}



SpliceModel::SpliceModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_spliceAdaptor = DBPresetTable::Instance();
    splices = new QMap<int, QString>();
}

QVariant SpliceModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if(role < Qt::UserRole)
    {
        qDebug() << "SpliceModel::data(const QModelIndex &index, int role) const";
    }
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        int rowId;
        QMap<int,QString>::iterator it; //遍历map
        int i = 0;
        for ( it = splices->begin(); it != splices->end(); ++it ) {
            if (i == index.row()){
                rowId = it.key();
                break;
            }
            else {
                i++;
            }
        }
//        list << "SpliceId" << "SpliceName" << "DateCreated" << "OperatorName" << "CrossSection" << "TotalWires" << "Verified" << "WeldMode" << "Energy" << "Amplitude"
//             << "Width" << "TriggerPressure" << "WeldPressure" << "Time+" << "Time-" << "Power+" << "Power-" << "Pre-Height+" << "Pre-Height-" << "Height+" << "Height-" << "count";

        PresetElement mySplice;
        m_spliceAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&mySplice);
        if (columnIdx == 0)
            value = QVariant::fromValue(mySplice.SpliceID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(mySplice.SpliceName);
        else if (columnIdx == 2)
            value = QVariant::fromValue(QDateTime::fromTime_t(mySplice.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 3)
            value = QVariant::fromValue(mySplice.OperatorID);
        else if (columnIdx == 4)
            value = QVariant::fromValue(mySplice.CrossSection);
        else if (columnIdx == 5)
            value = QVariant::fromValue(mySplice.NoOfWires);
        else if (columnIdx == 6)
            value = QVariant::fromValue(mySplice.Verified);
        else if (columnIdx == 7)
            value = QVariant::fromValue((int)mySplice.WeldSettings.AdvanceSetting.WeldMode);
        else if (columnIdx == 8)
            value = QVariant::fromValue(mySplice.WeldSettings.BasicSetting.Energy);
        else if (columnIdx == 9)
            value = QVariant::fromValue(mySplice.WeldSettings.BasicSetting.Amplitude);
        else if (columnIdx == 10)
            value = QVariant::fromValue(mySplice.WeldSettings.BasicSetting.Width);
        else if (columnIdx == 11)
            value = QVariant::fromValue(mySplice.WeldSettings.BasicSetting.TrigPres);
        else if (columnIdx == 12)
            value = QVariant::fromValue(mySplice.WeldSettings.BasicSetting.Pressure);
        else if (columnIdx == 13)
            value = QVariant::fromValue(1);
        else if (columnIdx == 14)
            value = QVariant::fromValue(1);
        else if (columnIdx == 15)
            value = QVariant::fromValue(2);
        else if (columnIdx == 16)
            value = QVariant::fromValue(2);
        else if (columnIdx == 17)
            value = QVariant::fromValue(2);
        else if (columnIdx == 18)
            value = QVariant::fromValue(2);
        else if (columnIdx == 19)
            value = QVariant::fromValue(2);
        else if (columnIdx == 20)
            value = QVariant::fromValue(2);
        else if (columnIdx == 21)
            value = QVariant::fromValue(mySplice.WeldSettings.QualitySetting.Time.Minus);

    }
    return value;
}



void SpliceModel::setModelList(unsigned int time_from, unsigned int time_to)
{
    beginResetModel();
    splices->clear();
    if (m_spliceAdaptor->QueryOnlyUseTime(time_from,time_to,splices))
        qDebug( )<< "setModelList SpliceModel" << splices->count();
    endResetModel();
}

void SpliceModel::setModelList()
{
    beginResetModel();
    splices->clear();
    if (m_spliceAdaptor->QueryEntireTable(splices))
        qDebug( )<< "setModelList WorkOrderModel" << splices->count();
    endResetModel();
}

int SpliceModel::rowCount(const QModelIndex & parent) const
{
    return splices->count();
}

int SpliceModel::count()
{
    return splices->count();
}

QString SpliceModel::getStructValue(QString valueKey, QString valueType)
{

    //                    settingsModel.append({"topText":"Energy","bottomText":"30J"})
    //                    settingsModel.append({"topText":"Trigger Pressure","bottomText":"50PSI"})
    //                    settingsModel.append({"topText":"Amplitude","bottomText":"25um"})
    //                    settingsModel.append({"topText":"Weld Pressure","bottomText":"50PSI"})
    //                    settingsModel.append({"topText":"Width","bottomText":"12.5mm"})
    if (valueKey == "Energy") {
        if (valueType == "current")
            return variantToString.EnergyToString(presetElement.WeldSettings.BasicSetting.Energy).Current;
        else if (valueType == "max")
            return variantToString.EnergyToString(presetElement.WeldSettings.BasicSetting.Energy).Maximum;
        else if (valueType == "min")
            return variantToString.EnergyToString(presetElement.WeldSettings.BasicSetting.Energy).Minimum;
    }
    else if (valueKey == "Trigger Pressure") {
        if (valueType == "current")
            return variantToString.TriggerPressureToString(presetElement.WeldSettings.BasicSetting.TrigPres).Current;
        else if (valueType == "max")
            return variantToString.TriggerPressureToString(presetElement.WeldSettings.BasicSetting.TrigPres).Maximum;
        else if (valueType == "min")
            return variantToString.TriggerPressureToString(presetElement.WeldSettings.BasicSetting.TrigPres).Minimum;
    }
    else if (valueKey == "Amplitude") {
        if (valueType == "current")
            return variantToString.AmplitudeToString(presetElement.WeldSettings.BasicSetting.Amplitude).Current;
        else if (valueType == "max")
            return variantToString.AmplitudeToString(presetElement.WeldSettings.BasicSetting.Amplitude).Maximum;
        else if (valueType == "min")
            return variantToString.AmplitudeToString(presetElement.WeldSettings.BasicSetting.Amplitude).Minimum;
    }
    else if (valueKey == "Weld Pressure") {
        if (valueType == "current")
            return variantToString.WeldPressureToString(presetElement.WeldSettings.BasicSetting.Pressure).Current;
        else if (valueType == "max")
            return variantToString.WeldPressureToString(presetElement.WeldSettings.BasicSetting.Pressure).Maximum;
        else if (valueType == "min")
            return variantToString.WeldPressureToString(presetElement.WeldSettings.BasicSetting.Pressure).Minimum;
    }
    else if (valueKey == "Width") {
        if (valueType == "current")
            return variantToString.WidthToString(presetElement.WeldSettings.BasicSetting.Width).Current;
        else if (valueType == "max")
            return variantToString.WidthToString(presetElement.WeldSettings.BasicSetting.Width).Maximum;
        else if (valueType == "min")
            return variantToString.WidthToString(presetElement.WeldSettings.BasicSetting.Width).Minimum;
    }
    else if (valueKey == "Time-") {
        if (valueType == "current")
            return variantToString.TimeMinusToString(presetElement.WeldSettings.QualitySetting.Time.Minus).Current;
        else if (valueType == "max")
            return variantToString.TimeMinusToString(presetElement.WeldSettings.QualitySetting.Time.Minus).Maximum;
        else if (valueType == "min")
            return variantToString.TimeMinusToString(presetElement.WeldSettings.QualitySetting.Time.Minus).Minimum;
    }
    else if (valueKey == "Time+") {
        if (valueType == "current")
            return variantToString.TimePlusToString(presetElement.WeldSettings.QualitySetting.Time.Plus).Current;
        else if (valueType == "max")
            return variantToString.TimePlusToString(presetElement.WeldSettings.QualitySetting.Time.Plus).Maximum;
        else if (valueType == "min")
            return variantToString.TimePlusToString(presetElement.WeldSettings.QualitySetting.Time.Plus).Minimum;
    }
//    else if (valueKey == "Power-") {
//        if (valueType == "current")
//            return variantToString.PowerMinusToString(presetElement.WeldSettings.QualitySetting.Power).Current;
//        else if (valueType == "max")
//            return variantToString.PowerMinusToString(presetElement.WeldSettings.QualitySetting.Power).Maximum;
//        else if (valueType == "min")
//            return variantToString.PowerMinusToString(presetElement.WeldSettings.QualitySetting.Power).Minimum;
//    }
//    else if (valueKey == "Power+") {
//        if (valueType == "current")
//            return variantToString.PowerPlusToString(presetElement.WeldSettings.QualitySetting.Power).Current;
//        else if (valueType == "max")
//            return variantToString.PowerPlusToString(presetElement.WeldSettings.QualitySetting.Power).Maximum;
//        else if (valueType == "min")
//            return variantToString.PowerPlusToString(presetElement.WeldSettings.QualitySetting.Power).Minimum;
//    }
//    else if (valueKey == "Pre-Height-") {
//        if (valueType == "current")
//            return variantToString.PreHeightMinusToString(presetElement.WeldSettings.QualitySetting.Preheight).Current;
//        else if (valueType == "max")
//            return variantToString.PreHeightMinusToString(presetElement.WeldSettings.QualitySetting.Preheight).Maximum;
//        else if (valueType == "min")
//            return variantToString.PreHeightMinusToString(presetElement.WeldSettings.QualitySetting.Preheight).Minimum;
//    }
//    else if (valueKey == "Pre-Height+") {
//        if (valueType == "current")
//            return variantToString.PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight).Current;
//        else if (valueType == "max")
//            return variantToString.PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight).Maximum;
//        else if (valueType == "min")
//            return variantToString.PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight).Minimum;
//    }
//    else if (valueKey == "Post-Height-") {
//        if (valueType == "current")
//            return variantToString.PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight).Current;
//        else if (valueType == "max")
//            return variantToString.PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight).Maximum;
//        else if (valueType == "min")
//            return variantToString.PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight).Minimum;
//    }
//    else if (valueKey == "Pre-Height+") {
//        if (valueType == "current")
//            return variantToString.PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight).Current;
//        else if (valueType == "max")
//            return variantToString.PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight).Maximum;
//        else if (valueType == "min")
//            return variantToString.PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight).Minimum;
//    }
    else
        return "";
}

void SpliceModel::createNew()
{
    PresetElement temp;
    presetElement = temp;
}

void SpliceModel::removeValue(int id, QString name)
{
    m_spliceAdaptor->DeleteOneRecordFromTable(id,name);
}

int SpliceModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant SpliceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

void SpliceModel::setRoles(const QStringList &names)
{
    m_roleNames.clear();
    for(int idx=0; idx<names.count(); idx++)
    {
        m_roleNames[Qt::UserRole + idx + 1] = names[idx].toLocal8Bit();
    }
}

QHash<int, QByteArray> SpliceModel::roleNames() const
{
    return m_roleNames;
}

QVariant SpliceModel::getValue(int index, QString key)
{
    QMap<int,QString>::iterator it; //遍历map
    int i = 0;
    int orderId;
    for ( it = splices->begin(); it != splices->end(); ++it ) {
        if (i == index){
            orderId = it.key();
            break;
        }
        else {
            i++;
        }
    }
    //        list << "SpliceId" << "SpliceName" << "DateCreated" << "OperatorName" << "CrossSection" << "TotalWires" << "Verified" << "WeldMode" << "Energy" << "Amplitude"
    //             << "Width" << "TriggerPressure" << "WeldPressure" << "Time+" << "Time-" << "Power+" << "Power-" << "Pre-Height+" << "Pre-Height-" << "Height+" << "Height-" << "count";
    PresetElement mySplice;
    m_spliceAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&mySplice);
    QHash<QString, QVariant> SpliceModelHash;
    SpliceModelHash.insert("SpliceId",mySplice.SpliceName);
    SpliceModelHash.insert("SpliceName",mySplice.SpliceName);
    SpliceModelHash.insert("DateCreated",QDateTime::fromTime_t(mySplice.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    SpliceModelHash.insert("OperatorName",mySplice.NoOfWires);
    SpliceModelHash.insert("CrossSection",mySplice.CrossSection);
    SpliceModelHash.insert("TotalWires",mySplice.NoOfWires);
    SpliceModelHash.insert("Verified",mySplice.Verified);
    SpliceModelHash.insert("WeldMode",(int)mySplice.WeldSettings.AdvanceSetting.WeldMode);
    SpliceModelHash.insert("Energy",mySplice.WeldSettings.BasicSetting.Energy);
    SpliceModelHash.insert("Amplitude",mySplice.WeldSettings.BasicSetting.Amplitude);
    SpliceModelHash.insert("Width",mySplice.WeldSettings.BasicSetting.Width);
    SpliceModelHash.insert("TriggerPressure",mySplice.WeldSettings.BasicSetting.TrigPres);
    SpliceModelHash.insert("WeldPressure",mySplice.WeldSettings.BasicSetting.Pressure);
    SpliceModelHash.insert("Time+","Time+");
    SpliceModelHash.insert("Time-","Time-");
    SpliceModelHash.insert("Power+","Power+");
    SpliceModelHash.insert("Power-","Power-");
    SpliceModelHash.insert("Pre-Height+","Pre-Height+");
    SpliceModelHash.insert("Pre-Height-","Pre-Height-");
    SpliceModelHash.insert("Height+","Height+");
    SpliceModelHash.insert("Height-","Height-");
    SpliceModelHash.insert("count",mySplice.WeldSettings.QualitySetting.Time.Minus);

    if (key == "") {
        return SpliceModelHash;
    } else {
        return SpliceModelHash.value(key);
    }
}
/****************************PartModel**************************/
PartModel::PartModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_partAdaptor = DBPartTable::Instance();
    parts = new QMap<int, QString>();
}

QVariant PartModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if(role < Qt::UserRole)
    {
        qDebug() << "PartModel::data(const QModelIndex &index, int role) const";
    }
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        int rowId;
        QMap<int,QString>::iterator it; //遍历map
        int i = 0;
        for ( it = parts->begin(); it != parts->end(); ++it ) {
            if (i == index.row()){
                rowId = it.key();
                break;
            }
            else {
                i++;
            }
        }

//        list << "PartId" << "PartName" << "DateCreated" << "OperatorName" << "TotalSplices" << "ProcessMode" << "#ofWorkstation" << "#ofSplicesperWorkstation" << "Rows" << "Columns" << "MaxSplicesPerZone";

        PartElement myPart;
        m_partAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myPart);
        if (columnIdx == 0)
            value = QVariant::fromValue(myPart.PartID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(myPart.PartName);
        else if (columnIdx == 2)
            value = QVariant::fromValue(QDateTime::fromTime_t(myPart.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 3)
            value = QVariant::fromValue(myPart.OperatorID);
        else if (columnIdx == 4)
            value = QVariant::fromValue(myPart.NoOfSplice);
        else if (columnIdx == 5) {
            QString processModel;
            if (myPart.PartTypeSetting.ProcessMode == BASIC)
                processModel = "BASIC";
            else if (myPart.PartTypeSetting.ProcessMode == ADVANCE)
                processModel = "ADVANCE";
            value = QVariant::fromValue(processModel);
        }
        else if (columnIdx == 6)
            value = QVariant::fromValue(myPart.PartTypeSetting.WorkStations.TotalWorkstation);
        else if (columnIdx == 7)
            value = QVariant::fromValue(myPart.NoOfSplice);
        else if (columnIdx == 8)
            value = QVariant::fromValue(myPart.PartTypeSetting.BoardLayout.Rows);
        else if (columnIdx == 9)
            value = QVariant::fromValue(myPart.PartTypeSetting.BoardLayout.Columns);
        else if (columnIdx == 10)
            value = QVariant::fromValue(myPart.PartTypeSetting.WorkStations.MaxSplicesPerWorkstation);
    }
    return value;
}



void PartModel::setModelList(unsigned int time_from, unsigned int time_to)
{
    beginResetModel();
    parts->clear();
    if (m_partAdaptor->QueryOnlyUseTime(time_from,time_to,parts))
        qDebug( )<< "PartModel " << parts->count();
    endResetModel();
}

void PartModel::setModelList()
{
    beginResetModel();
    parts->clear();
    if (m_partAdaptor->QueryEntireTable(parts))
        qDebug( )<< "PartModel" << parts->count();
    endResetModel();
}


int PartModel::rowCount(const QModelIndex & parent) const
{
    return parts->count();
}


int PartModel::count()
{
    return parts->count();
}


int PartModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant PartModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

void PartModel::setRoles(const QStringList &names)
{
    m_roleNames.clear();
    for(int idx=0; idx<names.count(); idx++)
    {
        m_roleNames[Qt::UserRole + idx + 1] = names[idx].toLocal8Bit();
    }
}

QHash<int, QByteArray> PartModel::roleNames() const
{
    return m_roleNames;
}


QVariant PartModel::getValue(int index, QString key)
{

    QMap<int,QString>::iterator it; //遍历map
    int i = 0;
    int orderId;
    for ( it = parts->begin(); it != parts->end(); ++it ) {
        if (i == index){
            orderId = it.key();
            break;
        }
        else {
            i++;
        }
    }
    //        list << "PartId" << "PartName" << "DateCreated" << "OperatorName" << "TotalSplices" << "ProcessMode" << "#ofWorkstation" << "#ofSplicesperWorkstation" << "Rows" << "Columns" << "MaxSplicesPerZone";
    PartElement myPart;
    m_partAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myPart);
    QHash<QString, QVariant> PartModelHash;
    PartModelHash.insert("PartId",myPart.PartID);
    PartModelHash.insert("PartName",myPart.PartName);
    PartModelHash.insert("DateCreated",QDateTime::fromTime_t(myPart.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    PartModelHash.insert("OperatorName",myPart.OperatorID);
    PartModelHash.insert("TotalSplices",myPart.NoOfSplice);
    QString processModel;
    if (myPart.PartTypeSetting.ProcessMode == BASIC)
        processModel = "BASIC";
    else if (myPart.PartTypeSetting.ProcessMode == ADVANCE)
        processModel = "ADVANCE";
    PartModelHash.insert("ProcessMode",processModel);
    PartModelHash.insert("#ofWorkstation",myPart.PartTypeSetting.WorkStations.TotalWorkstation);
    PartModelHash.insert("#ofSplicesperWorkstation",myPart.NoOfSplice);
    PartModelHash.insert("Rows",myPart.PartTypeSetting.BoardLayout.Rows);
    PartModelHash.insert("Columns",myPart.PartTypeSetting.BoardLayout.Columns);
    PartModelHash.insert("MaxSplicesPerZone",myPart.PartTypeSetting.WorkStations.MaxSplicesPerWorkstation);
    if (key == "") {
        return PartModelHash;
    } else {
        return PartModelHash.value(key);
    }
}

void PartModel::removeValue(int id, QString name)
{
    m_partAdaptor->DeleteOneRecordFromTable(id, name);
}

/*******************************OperaTorModel*****************************/


OperatorModel::OperatorModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_operatorAdaptor = DBOperatorTable::Instance();
    operators = new QMap<int, QString>();
}

QVariant OperatorModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if(role < Qt::UserRole)
    {
        qDebug() << "OperatorModel::data(const QModelIndex &index, int role) const";
    }
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        int rowId;
        QMap<int,QString>::iterator it; //遍历map
        int i = 0;
        for ( it = operators->begin(); it != operators->end(); ++it ) {
            if (i == index.row()){
                rowId = it.key();
                break;
            }
            else {
                i++;
            }
        }
        OperatorElement myOperator;
        m_operatorAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myOperator);
        if (columnIdx == 0)
            value = QVariant::fromValue(myOperator.OperatorID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(myOperator.OperatorName);
        else if (columnIdx == 2)
            value = QVariant::fromValue(QDateTime::fromTime_t(myOperator.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 3)
            value = QVariant::fromValue(myOperator.Password);
        else if (columnIdx == 4) {
            QString level = "";
            if (myOperator.PermissionLevel == PASSWORDCONTROL::SUPERUSER)
                level = "SUPERUSER";
            else if (myOperator.PermissionLevel == PASSWORDCONTROL::ADMINISTRATOR)
                level = "ADMINISTRATOR";
            else if (myOperator.PermissionLevel == PASSWORDCONTROL::TECHNICIAN)
                level = "TECHNICIAN";
            else if (myOperator.PermissionLevel == PASSWORDCONTROL::QUALITYCONTROL)
                level = "QUALITYCONTROL";
            else if (myOperator.PermissionLevel == PASSWORDCONTROL::OPEN)
                level = "OPEN";
            value = QVariant::fromValue(level);
        }
    }
    return value;
}

void OperatorModel::setModelList(unsigned int time_from, unsigned int time_to)
{
    beginResetModel();
    operators->clear();
    if (m_operatorAdaptor->QueryOnlyUseTime(time_from,time_to,operators))
        qDebug( )<< "OperatorModel " << operators->count();
    endResetModel();
}

void OperatorModel::setModelList()
{
    beginResetModel();
    operators->clear();
    if (m_operatorAdaptor->QueryEntireTable(operators))
        qDebug( )<< "OperatorModel" << operators->count();
    endResetModel();
}


int OperatorModel::rowCount(const QModelIndex & parent) const
{
    return operators->count();
}


int OperatorModel::count()
{
    return operators->count();
}

void OperatorModel::insertValue(QString name, QString passwd)
{
    qDebug() << "insertValue----------" << name << passwd;
    OperatorElement myOperator;
    myOperator.OperatorName = name;
    myOperator.Password = passwd;
    myOperator.PermissionLevel = PASSWORDCONTROL::OPEN;
    myOperator.CreatedDate = QDateTime::currentDateTime().toTime_t();

    m_operatorAdaptor->InsertRecordIntoTable(&myOperator);
}

bool OperatorModel::login(QString passwd, OperatorElement *operatot)
{
    QMap<int,QString>::iterator it; //遍历map
    OperatorElement myOperator;
    for ( it = operators->begin(); it != operators->end(); ++it ) {
        m_operatorAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myOperator);
        if (myOperator.Password == passwd) {
            operatot = &myOperator;
            return true;
        }
    }
    return false;
}

void OperatorModel::removeValue(int id, QString name)
{
    m_operatorAdaptor->DeleteOneRecordFromTable(id,name);
}


int OperatorModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant OperatorModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

void OperatorModel::setRoles(const QStringList &names)
{
    m_roleNames.clear();
    for(int idx=0; idx<names.count(); idx++)
    {
        m_roleNames[Qt::UserRole + idx + 1] = names[idx].toLocal8Bit();
    }

}

QHash<int, QByteArray> OperatorModel::roleNames() const
{
    return m_roleNames;
}


QVariant OperatorModel::getOperatorValue(int index, QString key)
{
    QMap<int,QString>::iterator it; //遍历map
    int i = 0;
    int orderId;
    for ( it = operators->begin(); it != operators->end(); ++it ) {
        if (i == index){
            orderId = it.key();
            break;
        }
        else {
            i++;
        }
    }
    OperatorElement myOperator;
    m_operatorAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myOperator);
    QHash<QString, QVariant> OperatorModelHash;
    OperatorModelHash.insert("operatorId",myOperator.OperatorID);
    OperatorModelHash.insert("name",myOperator.OperatorName);
    OperatorModelHash.insert("date",QDateTime::fromTime_t(myOperator.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    OperatorModelHash.insert("middle",myOperator.Password);
    QString level = "";
    if (myOperator.PermissionLevel == PASSWORDCONTROL::SUPERUSER)
        level = "SUPERUSER";
    else if (myOperator.PermissionLevel == PASSWORDCONTROL::ADMINISTRATOR)
        level = "ADMINISTRATOR";
    else if (myOperator.PermissionLevel == PASSWORDCONTROL::TECHNICIAN)
        level = "TECHNICIAN";
    else if (myOperator.PermissionLevel == PASSWORDCONTROL::QUALITYCONTROL)
        level = "QUALITYCONTROL";
    else if (myOperator.PermissionLevel == PASSWORDCONTROL::OPEN)
        level = "OPEN";
    OperatorModelHash.insert("count",level);//myOperator.PermissionLevel;
    //list << "name" << "date" << "middle" << "count";
    if (key == "") {
        return OperatorModelHash;
    } else {
        return OperatorModelHash.value(key);
    }
}

/****************************************AlarmLog****************************************/

AlarmModel::AlarmModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_alarmAdaptor = DBAlarmLogTable::Instance();
    alarms = new QMap<int, QString>();
}

QVariant AlarmModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if(role < Qt::UserRole)
    {
        qDebug() << "AlarmModel::data(const QModelIndex &index, int role) const";
    }
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        int rowId;
        QMap<int,QString>::iterator it; //遍历map
        int i = 0;
        for ( it = alarms->begin(); it != alarms->end(); ++it ) {
            if (i == index.row()){
                rowId = it.key();
                break;
            }
            else {
                i++;
            }
        }
//        list << "CreatedDate" << "Alarm/ErrorType" << "Alarm/ErrorLevel" << "Message" << "SpliceName";

        AlarmElement myAlarm;
        m_alarmAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myAlarm);
        if (columnIdx == 0)
            value = QVariant::fromValue(myAlarm.AlarmID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(QDateTime::fromTime_t(myAlarm.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 2)
            value = QVariant::fromValue((int)myAlarm.AlarmType);
        else if (columnIdx == 3)
            value = QVariant::fromValue(myAlarm.WeldResultID);
        else if (columnIdx == 4)
            value = QVariant::fromValue(myAlarm.AlarmMsg);
        else if (columnIdx == 5)
            value = QVariant::fromValue(myAlarm.WeldResultID);
    }
    return value;
}

void AlarmModel::setModelList(unsigned int time_from, unsigned int time_to)
{
    beginResetModel();
    alarms->clear();
    if (m_alarmAdaptor->QueryOnlyUseTime(time_from,time_to,alarms))
        qDebug( )<< "AlarmModel " << alarms->count();
    endResetModel();
}

void AlarmModel::setModelList()
{
    beginResetModel();
    alarms->clear();
    if (m_alarmAdaptor->QueryEntireTable(alarms))
        qDebug( )<< "AlarmModel" << alarms->count();
    endResetModel();
}


int AlarmModel::rowCount(const QModelIndex & parent) const
{
    return alarms->count();
}


int AlarmModel::count()
{
    return alarms->count();
}


int AlarmModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant AlarmModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

void AlarmModel::setRoles(const QStringList &names)
{
    m_roleNames.clear();
    for(int idx=0; idx<names.count(); idx++)
    {
        m_roleNames[Qt::UserRole + idx + 1] = names[idx].toLocal8Bit();
    }

}

QHash<int, QByteArray> AlarmModel::roleNames() const
{
    return m_roleNames;
}


QVariant AlarmModel::getAlarmValue(int index, QString key)
{
    QMap<int,QString>::iterator it; //遍历map
    int i = 0;
    int orderId;
    for ( it = alarms->begin(); it != alarms->end(); ++it ) {
        if (i == index){
            orderId = it.key();
            break;
        }
        else {
            i++;
        }
    }
    //        list << "CreatedDate" << "Alarm/ErrorType" << "Alarm/ErrorLevel" << "Message" << "SpliceName";

    AlarmElement myAlarm;
    m_alarmAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myAlarm);
    QHash<QString, QVariant> AlarmModelHash;
    AlarmModelHash.insert("AlarmId",myAlarm.AlarmID);
    AlarmModelHash.insert("CreatedDate",QDateTime::fromTime_t(myAlarm.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    AlarmModelHash.insert("Alarm/ErrorType",(int)myAlarm.AlarmType);
    AlarmModelHash.insert("Alarm/ErrorLevel",(int)myAlarm.AlarmType);
    AlarmModelHash.insert("Message",myAlarm.AlarmMsg);//myOperator.PermissionLevel;
    AlarmModelHash.insert("SpliceName",myAlarm.WeldResultID);//myOperator.PermissionLevel;

    if (key == "") {
        return AlarmModelHash;
    } else {
        return AlarmModelHash.value(key);
    }
}

void AlarmModel::removeValue(int id, QString name)
{
    m_alarmAdaptor->DeleteOneRecordFromTable(id,name);
}

/*****************WorkOrderHistory************************/

WeldHistoryModel::WeldHistoryModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_weldHistoryAdaptor = DBWeldResultTable::Instance();
    historys = new QMap<int, QString>();
    m_variant = new VariantToString;
    m_spliceTable = DBPresetTable::Instance();
}

QVariant WeldHistoryModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if(role < Qt::UserRole)
    {
        qDebug() << "WeldHistoryModel::data(const QModelIndex &index, int role) const";
    }
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        int rowId;
        QMap<int,QString>::iterator it; //遍历map
        int i = 0;
        for ( it = historys->begin(); it != historys->end(); ++it ) {
            if (i == index.row()){
                rowId = it.key();
                break;
            }
            else {
                i++;
            }
        }
        WeldResultElement myHistory;
        m_weldHistoryAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myHistory);
        PresetElement presetElement;
        m_spliceTable->QueryOneRecordFromTable(myHistory.CurrentSplice.SpliceID,myHistory.CurrentSplice.SpliceName,&presetElement);
        QString temp;
        if (columnIdx == 0)
            value = QVariant::fromValue(myHistory.WeldResultID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(myHistory.CurrentWorkOrder.WorkOrderName);
        else if (columnIdx == 2)
            value = QVariant::fromValue(myHistory.CurrentPart.PartName);
        else if (columnIdx == 3)
            value = QVariant::fromValue(myHistory.CurrentSplice.SpliceName);
        else if (columnIdx == 4)
            value = QVariant::fromValue(myHistory.OperatorName);
        else if (columnIdx == 5)
            value = QVariant::fromValue(QDateTime::fromTime_t(myHistory.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 6)
            value = QVariant::fromValue(m_variant->CrossSectionToString(myHistory.CrossSection));
        else if (columnIdx == 7)
            value = QVariant::fromValue(m_variant->WeldModeToString(presetElement.WeldSettings.AdvanceSetting.WeldMode,presetElement.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode));
        else if (columnIdx == 8) {
            temp = m_variant->EnergyToString(myHistory.ActualResult.ActualEnergy).Current;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 9) {
            temp = m_variant->AmplitudeToString(myHistory.ActualResult.ActualAmplitude).Current;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 10) {
            temp = m_variant->WidthToString(myHistory.ActualResult.ActualWidth).Current;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 11) {
            temp = m_variant->TriggerPressureToString(myHistory.ActualResult.ActualTPressure).Current;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 12) {
            temp = m_variant->WeldPressureToString(myHistory.ActualResult.ActualPressure).Current;
            value = QVariant::fromValue(temp);
        }
        else if (columnIdx == 13)
            value = QVariant::fromValue(myHistory.ActualResult.ActualTime);
        else if (columnIdx == 14)
            value = QVariant::fromValue(myHistory.ActualResult.ActualTime);
        else if (columnIdx == 15) {
            temp = m_variant->ActualTimeToString(myHistory.ActualResult.ActualTime);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 16) {
            value = QVariant::fromValue(myHistory.ActualResult.ActualPeakPower);
        }
        else if (columnIdx == 17)
            value = QVariant::fromValue(myHistory.ActualResult.ActualPeakPower);
        else if (columnIdx == 18) {
            temp = m_variant->ActualPowerToString(myHistory.ActualResult.ActualPeakPower);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 19) {
            value = QVariant::fromValue(myHistory.ActualResult.ActualPreheight);
        } else if (columnIdx == 20)
            value = QVariant::fromValue(myHistory.ActualResult.ActualPreheight);
        else if (columnIdx == 21) {
            temp = m_variant->ActualPreHeightToString(myHistory.ActualResult.ActualPreheight);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 22)
            value = QVariant::fromValue(myHistory.ActualResult.ActualPostheight);
        else if (columnIdx == 23)
            value = QVariant::fromValue(myHistory.ActualResult.ActualPostheight);
        else if (columnIdx == 24) {
            temp = m_variant->ActualHeightToString(myHistory.ActualResult.ActualPostheight);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 25) {
            temp = m_variant->AlarmTypeToString((ALARMTYPE)myHistory.ActualResult.ActualAlarmflags);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 26) {
            temp = m_variant->SampleRatioToString(myHistory.SampleRatio);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 27) {
            value = QVariant::fromValue(myHistory.ActualResult.ActualPostheight);
        }
    }
    return value;
}

void WeldHistoryModel::setModelList(unsigned int time_from, unsigned int time_to)
{
    beginResetModel();
    historys->clear();
    if (m_weldHistoryAdaptor->QueryOnlyUseTime(time_from,time_to,historys))
        qDebug( )<< "WeldHistoryModel " << historys->count();
    endResetModel();
}

void WeldHistoryModel::setModelList()
{
    beginResetModel();
    historys->clear();
    if (m_weldHistoryAdaptor->QueryEntireTable(historys))
        qDebug( )<< "WeldHistoryModel" << historys->count();
    endResetModel();
}


int WeldHistoryModel::rowCount(const QModelIndex & parent) const
{
    return historys->count();
}


int WeldHistoryModel::count()
{
    return historys->count();
}

void WeldHistoryModel::removeValue(int id, QString name)
{
    m_weldHistoryAdaptor->DeleteOneRecordFromTable(id,name);
}


int WeldHistoryModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant WeldHistoryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

void WeldHistoryModel::setRoles(const QStringList &names)
{
    m_roleNames.clear();
    for(int idx=0; idx<names.count(); idx++)
    {
        m_roleNames[Qt::UserRole + idx + 1] = names[idx].toLocal8Bit();
    }

}

QHash<int, QByteArray> WeldHistoryModel::roleNames() const
{
    return m_roleNames;
}


QVariant WeldHistoryModel::getValue(int index, QString key)
{
    QMap<int,QString>::iterator it; //遍历map
    int i = 0;
    int orderId;
    for ( it = historys->begin(); it != historys->end(); ++it ) {
        if (i == index){
            orderId = it.key();
            break;
        }
        else {
            i++;
        }
    }
    WeldResultElement myHistory;
    m_weldHistoryAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myHistory);
    QHash<QString, QVariant> WeldHistoryModelHash;
    WeldHistoryModelHash.insert("WeldHistoryId",myHistory.WeldResultID);
    WeldHistoryModelHash.insert("WorkOrderName",myHistory.CurrentWorkOrder.WorkOrderName);
    WeldHistoryModelHash.insert("PartName",myHistory.CurrentPart.PartName);
    WeldHistoryModelHash.insert("SpliceName",myHistory.CurrentSplice.SpliceName);
    WeldHistoryModelHash.insert("OperatorName",myHistory.OperatorName);
    WeldHistoryModelHash.insert("DateCreated",QDateTime::fromTime_t(myHistory.CreatedDate).toString("MM/dd/yyyy hh:mm"));

    WeldHistoryModelHash.insert("CrossSection",myHistory.PartCount); //contain in splice
    WeldHistoryModelHash.insert("WeldMode",myHistory.PartCount);     //contain in splice
    WeldHistoryModelHash.insert("Energy",myHistory.ActualResult.ActualEnergy);
    WeldHistoryModelHash.insert("Amplitude",myHistory.ActualResult.ActualAmplitude);
    WeldHistoryModelHash.insert("Width",myHistory.ActualResult.ActualWidth);
    WeldHistoryModelHash.insert("TriggerPressure",myHistory.ActualResult.ActualTPressure);
    WeldHistoryModelHash.insert("WeldPressure",myHistory.ActualResult.ActualPressure);
    WeldHistoryModelHash.insert("Time+",myHistory.ActualResult.ActualTime); //contain in splice QUALITYWINDONSETTING
    WeldHistoryModelHash.insert("Timer-",myHistory.ActualResult.ActualTime);
    WeldHistoryModelHash.insert("Time",myHistory.ActualResult.ActualTime);
    WeldHistoryModelHash.insert("Power+",myHistory.ActualResult.ActualPeakPower);
    WeldHistoryModelHash.insert("Power-",myHistory.ActualResult.ActualPeakPower);
    WeldHistoryModelHash.insert("Power",myHistory.ActualResult.ActualPeakPower);
    WeldHistoryModelHash.insert("Pre-Height+",myHistory.ActualResult.ActualPreheight);
    WeldHistoryModelHash.insert("Pre-Height-",myHistory.ActualResult.ActualPreheight);
    WeldHistoryModelHash.insert("Pre-Height",myHistory.ActualResult.ActualPreheight);
    WeldHistoryModelHash.insert("Height+",myHistory.ActualResult.ActualPostheight);
    WeldHistoryModelHash.insert("Height-",myHistory.ActualResult.ActualPostheight);
    WeldHistoryModelHash.insert("Height",myHistory.ActualResult.ActualPostheight);
    WeldHistoryModelHash.insert("Alarm",(int)myHistory.SampleRatio); //myHistory.ActualResult.ActualAlarmflags
    WeldHistoryModelHash.insert("SampleRatio",(int)myHistory.SampleRatio);
    WeldHistoryModelHash.insert("GraphData","GraphData");
    if (key == "") {
        return WeldHistoryModelHash;
    } else {
        return WeldHistoryModelHash.value(key);
    }
}


/***************************WireModel*******************************/

WireModel::WireModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_wireAdaptor = DBWireTable::Instance();
    wires = new QMap<int, QString>();
}

QVariant WireModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if(role < Qt::UserRole)
    {
        qDebug() << "WireModel::data(const QModelIndex &index, int role) const";
    }
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        int rowId;
        QMap<int,QString>::iterator it; //遍历map
        int i = 0;
        for ( it = wires->begin(); it != wires->end(); ++it ) {
            if (i == index.row()){
                rowId = it.key();
                break;
            }
            else {
                i++;
            }
        }
        WireElement myWire;
        //    list <<"WireId" << "WireName" << "DateCreated" << "OperatorName" << "Color" << "StripeType" << "StripeColor" << "Gauge" << "MetalType" << "HorizontalLocation" << "VerticalLocation" << "VerticalPosition";

        m_wireAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myWire);
        if (columnIdx == 0)
            value = QVariant::fromValue(myWire.WireID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(myWire.WireName);
        else if (columnIdx == 2)
            value = QVariant::fromValue(QDateTime::fromTime_t(myWire.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 3)
            value = QVariant::fromValue(myWire.OperatorID);
        else if (columnIdx == 4)
            value = QVariant::fromValue(myWire.Color);
        else if (columnIdx == 5)
            value = QVariant::fromValue((int)myWire.Stripe.TypeOfStripe);
        else if (columnIdx == 6)
            value = QVariant::fromValue(myWire.Stripe.Color);
        else if (columnIdx == 7)
            value = QVariant::fromValue(myWire.Gauge);
        else if (columnIdx == 8)
            value = QVariant::fromValue((int)myWire.TypeOfWire);
        else if (columnIdx == 9)
            value = QVariant::fromValue((int)myWire.Side);
        else if (columnIdx == 10)
            value = QVariant::fromValue((int)myWire.VerticalSide);
        else if (columnIdx == 11)
            value = QVariant::fromValue((int)myWire.Position);

    }
    return value;
}

void WireModel::setModelList(unsigned int time_from, unsigned int time_to)
{
    beginResetModel();
    wires->clear();
    if (m_wireAdaptor->QueryOnlyUseTime(time_from,time_to,wires))
        qDebug( )<< "WireModel " << wires->count();
    endResetModel();
}

void WireModel::setModelList()
{
    beginResetModel();
    wires->clear();
    if (m_wireAdaptor->QueryEntireTable(wires))
        qDebug( )<< "WireModel" << wires->count();
    endResetModel();
}

int WireModel::rowCount(const QModelIndex & parent) const
{
    return wires->count();
}

int WireModel::count()
{
    return wires->count();
}

void WireModel::removeValue(int id, QString name)
{
    m_wireAdaptor->DeleteOneRecordFromTable(id,name);
}

void WireModel::createNew()
{
    WireElement temp;
    wireElement = temp;
}

QVariant WireModel::getStructValue(QString key)
{
    QHash<QString, QVariant> WireModelHash;
    WireModelHash.insert("Gauge",wireElement.Gauge);
    WireModelHash.insert("AWG",wireElement.GaugeAWG);
    WireModelHash.insert("WireType",(int)wireElement.TypeOfWire);

//    WireModelHash.insert("OperatorName",myWire.OperatorID);
//    WireModelHash.insert("Color",myWire.Color);
//    WireModelHash.insert("StripeType",(int)myWire.Stripe.TypeOfStripe);
//    WireModelHash.insert("StripeColor",myWire.Stripe.Color);
//    WireModelHash.insert("Gauge",myWire.Gauge);
//    WireModelHash.insert("MetalType",(int)myWire.TypeOfWire);
//    WireModelHash.insert("HorizontalLocation",(int)myWire.Side);
//    WireModelHash.insert("VerticalLocation",(int)myWire.VerticalSide);
//    WireModelHash.insert("VerticalPosition",(int)myWire.Position);
    if (key == "") {
        return WireModelHash;
    } else {
        return WireModelHash.value(key);
    }
}

QString WireModel::getStructValue2(QString key, QString type)
{
    if (key == "Gauge"){
        if (type == "current")
            return variantToString.GaugeToString(wireElement.Gauge,wireElement.GaugeAWG).Current;
        else if (type == "max")
            return variantToString.GaugeToString(wireElement.Gauge,wireElement.GaugeAWG).Maximum;
        else if (type == "min")
            return variantToString.GaugeToString(wireElement.Gauge,wireElement.GaugeAWG).Minimum;
    }
    else if (key == "StripeColor")
        return wireElement.Stripe.Color;

}

int WireModel::getStructValue3(QString key, QString value)
{
    int gauge;
    int awg;
    if (key == "Gauge"){
        stringToVariant.GaugeToInt(value,awg,gauge);
        return gauge;
    }
    else if (key == "awg") {
        stringToVariant.GaugeToInt(value,awg,gauge);
        return awg;
    }
    else if (key == "StripeType")
        return (int)wireElement.Stripe.TypeOfStripe;
}

QString WireModel::getStructValue4(int gauge, int awg)
{
    return variantToString.GaugeToString(gauge,awg).Current;
}

int WireModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant WireModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

void WireModel::setRoles(const QStringList &names)
{
    m_roleNames.clear();
    for(int idx=0; idx<names.count(); idx++)
    {
        m_roleNames[Qt::UserRole + idx + 1] = names[idx].toLocal8Bit();
    }

}

QHash<int, QByteArray> WireModel::roleNames() const
{
    return m_roleNames;
}

QVariant WireModel::getValue(int index, QString key)
{
    QMap<int,QString>::iterator it; //遍历map
    int i = 0;
    int orderId;
    for ( it = wires->begin(); it != wires->end(); ++it ) {
        if (i == index){
            orderId = it.key();
            break;
        }
        else {
            i++;
        }
    }
    WireElement myWire;
    m_wireAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myWire);
    //    list <<"WireId" << "WireName" << "DateCreated" << "OperatorName" << "Color" << "StripeType" << "StripeColor" << "Gauge" << "MetalType" << "HorizontalLocation" << "VerticalLocation" << "VerticalPosition";
    QHash<QString, QVariant> WireModelHash;
    WireModelHash.insert("WireId",myWire.WireID);
    WireModelHash.insert("WireName",myWire.WireName);
    WireModelHash.insert("DateCreated",QDateTime::fromTime_t(myWire.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    WireModelHash.insert("OperatorName",myWire.OperatorID);
    WireModelHash.insert("Color",myWire.Color);
    WireModelHash.insert("StripeType",(int)myWire.Stripe.TypeOfStripe);
    WireModelHash.insert("StripeColor",myWire.Stripe.Color);
    WireModelHash.insert("Gauge",myWire.Gauge);
    WireModelHash.insert("MetalType",(int)myWire.TypeOfWire);
    WireModelHash.insert("HorizontalLocation",(int)myWire.Side);
    WireModelHash.insert("VerticalLocation",(int)myWire.VerticalSide);
    WireModelHash.insert("VerticalPosition",(int)myWire.Position);
    if (key == "") {
        return WireModelHash;
    } else {
        return WireModelHash.value(key);
    }
}

/*************************MaintenanceLog Model******************************/
MaintenanceLogModel::MaintenanceLogModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_maintenanceLogAdaptor = DBMaintenanceLogTable::Instance();
    logs = new QMap<int, QString>();
}

QVariant MaintenanceLogModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if(role < Qt::UserRole)
    {
        qDebug() << "MaintenanceLogModel::data(const QModelIndex &index, int role) const";
    }
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        int rowId;
        QMap<int,QString>::iterator it; //遍历map
        int i = 0;
        for ( it = logs->begin(); it != logs->end(); ++it ) {
            if (i == index.row()){
                rowId = it.key();
                break;
            }
            else {
                i++;
            }
        }
        MaintenanceLogElement myLog;

//        ListElement {key:"CreatedDate"}
//        ListElement {key:"OperatorName"}
//        ListElement {key:"Type"}
//        ListElement {key:"Message"}

        m_maintenanceLogAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myLog);
        if (columnIdx == 0)
            value = QVariant::fromValue(myLog.MaintenanceLogID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(QDateTime::fromTime_t(myLog.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 2)
            value = QVariant::fromValue(myLog.OperatorID);
        else if (columnIdx == 3)
            value = QVariant::fromValue(myLog.MaintenanceType);
        else if (columnIdx == 4)
            value = QVariant::fromValue(myLog.MaintenanceMsg);
    }
    return value;
}

void MaintenanceLogModel::setModelList(unsigned int time_from, unsigned int time_to)
{
    beginResetModel();
    logs->clear();
    if (m_maintenanceLogAdaptor->QueryOnlyUseTime(time_from,time_to,logs))
        qDebug( )<< "MaintenanceLogModel " << logs->count();
    endResetModel();
}

void MaintenanceLogModel::setModelList()
{
    beginResetModel();
    logs->clear();
    if (m_maintenanceLogAdaptor->QueryEntireTable(logs))
        qDebug( )<< "MaintenanceLogModel" << logs->count();
    endResetModel();
}

int MaintenanceLogModel::rowCount(const QModelIndex & parent) const
{
    return logs->count();
}

int MaintenanceLogModel::count()
{
    return logs->count();
}

void MaintenanceLogModel::removeValue(int id, QString name)
{
    m_maintenanceLogAdaptor->DeleteOneRecordFromTable(id,name);
}

int MaintenanceLogModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant MaintenanceLogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

void MaintenanceLogModel::setRoles(const QStringList &names)
{
    m_roleNames.clear();
    for(int idx=0; idx<names.count(); idx++)
    {
        m_roleNames[Qt::UserRole + idx + 1] = names[idx].toLocal8Bit();
    }

}

QHash<int, QByteArray> MaintenanceLogModel::roleNames() const
{
    return m_roleNames;
}

QVariant MaintenanceLogModel::getValue(int index, QString key)
{
    QMap<int,QString>::iterator it; //遍历map
    int i = 0;
    int orderId;
    for ( it = logs->begin(); it != logs->end(); ++it ) {
        if (i == index){
            orderId = it.key();
            break;
        }
        else {
            i++;
        }
    }
    MaintenanceLogElement myLog;
    m_maintenanceLogAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myLog);

    //        ListElement {key:"CreatedDate"}
    //        ListElement {key:"OperatorName"}
    //        ListElement {key:"Type"}
    //        ListElement {key:"Message"}

    QHash<QString, QVariant> MaintenanceModelHash;
    MaintenanceModelHash.insert("MaintenanceLogId",myLog.MaintenanceLogID);
    MaintenanceModelHash.insert("OperatorName",myLog.OperatorID);
    MaintenanceModelHash.insert("CreatedDate",QDateTime::fromTime_t(myLog.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    MaintenanceModelHash.insert("Type",myLog.MaintenanceType);
    MaintenanceModelHash.insert("Message",myLog.MaintenanceMsg);
    if (key == "") {
        return MaintenanceModelHash;
    } else {
        return MaintenanceModelHash.value(key);
    }
}
