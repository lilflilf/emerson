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
    setModelList();
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
    m_operatorAdaptor = DBOperatorTable::Instance();
    splices = new QMap<int, QString>();
    variantToString = VariantToString::Instance();
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
//             << "Width" << "TriggerPressure" << "WeldPressure" << "Time+" << "Time-" << "Power+" << "Power-" << "Pre-Height+" << "Pre-Height-" << "Height+" << "Height-";

        PresetElement mySplice;
        OperatorElement myOperator;
        m_spliceAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&mySplice);
        m_operatorAdaptor->QueryOneRecordFromTable(mySplice.OperatorID,&myOperator);
        QString temp;
        if (columnIdx == 0)
            value = QVariant::fromValue(mySplice.SpliceID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(mySplice.SpliceName);
        else if (columnIdx == 2)
            value = QVariant::fromValue(QDateTime::fromTime_t(mySplice.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 3)
            value = QVariant::fromValue(myOperator.OperatorName);
        else if (columnIdx == 4) {
            temp = variantToString->CrossSectionToString(mySplice.CrossSection);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 5)
            value = QVariant::fromValue(mySplice.NoOfWires);
        else if (columnIdx == 6)
            value = QVariant::fromValue(mySplice.Verified);
        else if (columnIdx == 7) {
            temp = variantToString->WeldModeToString(mySplice.WeldSettings.AdvanceSetting.WeldMode,mySplice.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 8) {
            temp = variantToString->EnergyToString(mySplice.WeldSettings.BasicSetting.Energy).Current;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 9) {
            temp = variantToString->AmplitudeToString(mySplice.WeldSettings.BasicSetting.Amplitude).Current;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 10) {
            temp = variantToString->WidthToString(mySplice.WeldSettings.BasicSetting.Width).Current;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 11) {
            temp = variantToString->TriggerPressureToString(mySplice.WeldSettings.BasicSetting.TrigPres).Current;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 12) {
            temp = variantToString->WeldPressureToString(mySplice.WeldSettings.BasicSetting.Pressure).Current;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 13) {
            temp = variantToString->Time_PlusToString(mySplice.WeldSettings.QualitySetting.Time.Plus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 14) {
            temp = variantToString->Time_MinusToString(mySplice.WeldSettings.QualitySetting.Time.Minus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 15) {
            temp = variantToString->Power_PlusToString(mySplice.WeldSettings.QualitySetting.Power.Plus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 16) {
            temp = variantToString->Power_MinusToString(mySplice.WeldSettings.QualitySetting.Power.Minus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 17) {
            temp = variantToString->PreHeight_PlusToString(mySplice.WeldSettings.QualitySetting.Preheight.Plus);
            value = QVariant::fromValue(2);
        } else if (columnIdx == 18) {
            temp = variantToString->PreHeight_MinusToString(mySplice.WeldSettings.QualitySetting.Preheight.Minus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 19) {
            temp = variantToString->Height_PlusToString(mySplice.WeldSettings.QualitySetting.Height.Plus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 20) {
            temp = variantToString->Height_MinusToString(mySplice.WeldSettings.QualitySetting.Height.Minus);
            value = QVariant::fromValue(2);
        }
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
    if (valueKey == "Energy") {
        if (valueType == "current")
            return variantToString->EnergyToString(presetElement.WeldSettings.BasicSetting.Energy).Current;
        else if (valueType == "max")
            return variantToString->EnergyToString(presetElement.WeldSettings.BasicSetting.Energy).Maximum;
        else if (valueType == "min")
            return variantToString->EnergyToString(presetElement.WeldSettings.BasicSetting.Energy).Minimum;
    }
    else if (valueKey == "Trigger Pressure") {
        if (valueType == "current")
            return variantToString->TriggerPressureToString(presetElement.WeldSettings.BasicSetting.TrigPres).Current;
        else if (valueType == "max")
            return variantToString->TriggerPressureToString(presetElement.WeldSettings.BasicSetting.TrigPres).Maximum;
        else if (valueType == "min")
            return variantToString->TriggerPressureToString(presetElement.WeldSettings.BasicSetting.TrigPres).Minimum;
    }
    else if (valueKey == "Amplitude") {
        if (valueType == "current")
            return variantToString->AmplitudeToString(presetElement.WeldSettings.BasicSetting.Amplitude).Current;
        else if (valueType == "max")
            return variantToString->AmplitudeToString(presetElement.WeldSettings.BasicSetting.Amplitude).Maximum;
        else if (valueType == "min")
            return variantToString->AmplitudeToString(presetElement.WeldSettings.BasicSetting.Amplitude).Minimum;
    }
    else if (valueKey == "Weld Pressure") {
        if (valueType == "current")
            return variantToString->WeldPressureToString(presetElement.WeldSettings.BasicSetting.Pressure).Current;
        else if (valueType == "max")
            return variantToString->WeldPressureToString(presetElement.WeldSettings.BasicSetting.Pressure).Maximum;
        else if (valueType == "min")
            return variantToString->WeldPressureToString(presetElement.WeldSettings.BasicSetting.Pressure).Minimum;
    }
    else if (valueKey == "Width") {
        if (valueType == "current")
            return variantToString->WidthToString(presetElement.WeldSettings.BasicSetting.Width).Current;
        else if (valueType == "max")
            return variantToString->WidthToString(presetElement.WeldSettings.BasicSetting.Width).Maximum;
        else if (valueType == "min")
            return variantToString->WidthToString(presetElement.WeldSettings.BasicSetting.Width).Minimum;
    }
    else if (valueKey == "Time-") {
        if (valueType == "current")
            return variantToString->TimeMinusToString(presetElement.WeldSettings.QualitySetting.Time.Minus).Current;
        else if (valueType == "max")
            return variantToString->TimeMinusToString(presetElement.WeldSettings.QualitySetting.Time.Minus).Maximum;
        else if (valueType == "min")
            return variantToString->TimeMinusToString(presetElement.WeldSettings.QualitySetting.Time.Minus).Minimum;
    }
    else if (valueKey == "Time+") {
        if (valueType == "current")
            return variantToString->TimePlusToString(presetElement.WeldSettings.QualitySetting.Time.Plus).Current;
        else if (valueType == "max")
            return variantToString->TimePlusToString(presetElement.WeldSettings.QualitySetting.Time.Plus).Maximum;
        else if (valueType == "min")
            return variantToString->TimePlusToString(presetElement.WeldSettings.QualitySetting.Time.Plus).Minimum;
    }
    else if (valueKey == "Power-") {
        if (valueType == "current")
            return variantToString->PowerMinusToString(presetElement.WeldSettings.QualitySetting.Power.Minus).Current;
        else if (valueType == "max")
            return variantToString->PowerMinusToString(presetElement.WeldSettings.QualitySetting.Power.Minus).Maximum;
        else if (valueType == "min")
            return variantToString->PowerMinusToString(presetElement.WeldSettings.QualitySetting.Power.Minus).Minimum;
    }
    else if (valueKey == "Power+") {
        if (valueType == "current")
            return variantToString->PowerPlusToString(presetElement.WeldSettings.QualitySetting.Power.Plus).Current;
        else if (valueType == "max")
            return variantToString->PowerPlusToString(presetElement.WeldSettings.QualitySetting.Power.Plus).Maximum;
        else if (valueType == "min")
            return variantToString->PowerPlusToString(presetElement.WeldSettings.QualitySetting.Power.Plus).Minimum;
    }
    else if (valueKey == "Pre-Height-") {
        if (valueType == "current")
            return variantToString->PreHeightMinusToString(presetElement.WeldSettings.QualitySetting.Preheight.Minus).Current;
        else if (valueType == "max")
            return variantToString->PreHeightMinusToString(presetElement.WeldSettings.QualitySetting.Preheight.Minus).Maximum;
        else if (valueType == "min")
            return variantToString->PreHeightMinusToString(presetElement.WeldSettings.QualitySetting.Preheight.Minus).Minimum;
    }
    else if (valueKey == "Pre-Height+") {
        if (valueType == "current")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight.Plus).Current;
        else if (valueType == "max")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight.Plus).Maximum;
        else if (valueType == "min")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight.Plus).Minimum;
    }
    else if (valueKey == "Post-Height-") {
        if (valueType == "current")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight.Minus).Current;
        else if (valueType == "max")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight.Minus).Maximum;
        else if (valueType == "min")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight.Minus).Minimum;
    }
    else if (valueKey == "Post-Height+") {
        if (valueType == "current")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight.Plus).Current;
        else if (valueType == "max")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight.Plus).Maximum;
        else if (valueType == "min")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight.Plus).Minimum;
    }
    else
        return "";
}

void SpliceModel::createNew()
{
    PresetElement temp;
    presetElement = temp;
}

QString SpliceModel::getString(QString type, int value)
{
    if (type == "CrossSection")
        return variantToString->CrossSectionToString(value);
}

void SpliceModel::removeValue(int id, QString name)
{
    m_spliceAdaptor->DeleteOneRecordFromTable(id,name);
    setModelList();
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
    OperatorElement myOperator;
    m_spliceAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&mySplice);
    m_operatorAdaptor->QueryOneRecordFromTable(mySplice.OperatorID,&myOperator);
    QHash<QString, QVariant> SpliceModelHash;
    qDebug()<<"33333333333333333333333"<<mySplice.SpliceID;
    SpliceModelHash.insert("SpliceId",mySplice.SpliceID);
    SpliceModelHash.insert("SpliceName",mySplice.SpliceName);
    SpliceModelHash.insert("DateCreated",QDateTime::fromTime_t(mySplice.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    SpliceModelHash.insert("OperatorName",myOperator.OperatorName);
    SpliceModelHash.insert("CrossSection",variantToString->CrossSectionToString(mySplice.CrossSection));
    SpliceModelHash.insert("TotalWires",mySplice.NoOfWires);
    SpliceModelHash.insert("Verified",mySplice.Verified);
    SpliceModelHash.insert("WeldMode",variantToString->WeldModeToString(mySplice.WeldSettings.AdvanceSetting.WeldMode,mySplice.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode));
    SpliceModelHash.insert("Energy",variantToString->EnergyToString(mySplice.WeldSettings.BasicSetting.Energy).Current);
    SpliceModelHash.insert("Amplitude",variantToString->AmplitudeToString(mySplice.WeldSettings.BasicSetting.Amplitude).Current);
    SpliceModelHash.insert("Width",variantToString->WidthToString(mySplice.WeldSettings.BasicSetting.Width).Current);
    SpliceModelHash.insert("TriggerPressure",variantToString->TriggerPressureToString(mySplice.WeldSettings.BasicSetting.TrigPres).Current);
    SpliceModelHash.insert("WeldPressure",variantToString->WeldPressureToString(mySplice.WeldSettings.BasicSetting.Pressure).Current);
    SpliceModelHash.insert("Time+",variantToString->Time_PlusToString(mySplice.WeldSettings.QualitySetting.Time.Plus));
    SpliceModelHash.insert("Time-",variantToString->Time_MinusToString(mySplice.WeldSettings.QualitySetting.Time.Minus));
    SpliceModelHash.insert("Power+",variantToString->Power_PlusToString(mySplice.WeldSettings.QualitySetting.Power.Plus));
    SpliceModelHash.insert("Power-",variantToString->Power_MinusToString(mySplice.WeldSettings.QualitySetting.Power.Minus));
    SpliceModelHash.insert("Pre-Height+",variantToString->PreHeight_PlusToString(mySplice.WeldSettings.QualitySetting.Preheight.Plus));
    SpliceModelHash.insert("Pre-Height-",variantToString->PreHeight_MinusToString(mySplice.WeldSettings.QualitySetting.Preheight.Minus));
    SpliceModelHash.insert("Height+",variantToString->Height_PlusToString(mySplice.WeldSettings.QualitySetting.Height.Plus));
    SpliceModelHash.insert("Height-",variantToString->Height_MinusToString(mySplice.WeldSettings.QualitySetting.Height.Minus));

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
    m_operatorAdaptor = DBOperatorTable::Instance();
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
        OperatorElement myOperator;
        m_partAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myPart);
        m_operatorAdaptor->QueryOneRecordFromTable(myPart.OperatorID,&myOperator);
        if (columnIdx == 0)
            value = QVariant::fromValue(myPart.PartID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(myPart.PartName);
        else if (columnIdx == 2)
            value = QVariant::fromValue(QDateTime::fromTime_t(myPart.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 3)
            value = QVariant::fromValue(myOperator.OperatorName);
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
    OperatorElement myOperator;
    m_partAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myPart);
    m_operatorAdaptor->QueryOneRecordFromTable(myPart.OperatorID,&myOperator);
    QHash<QString, QVariant> PartModelHash;
    PartModelHash.insert("PartId",myPart.PartID);
    PartModelHash.insert("PartName",myPart.PartName);
    PartModelHash.insert("DateCreated",QDateTime::fromTime_t(myPart.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    PartModelHash.insert("OperatorName",myOperator.OperatorName);
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
    setModelList();
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
    setModelList();
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
    m_weldHistoryAdaptor = DBWeldResultTable::Instance();
    alarms = new QMap<int, QString>();
    variantToString = VariantToString::Instance();
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
        WeldResultElement weldResult;
        m_alarmAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myAlarm);
        m_weldHistoryAdaptor->QueryOneRecordFromTable(myAlarm.WeldResultID,&weldResult);
        QString temp;
        if (columnIdx == 0)
            value = QVariant::fromValue(myAlarm.AlarmID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(QDateTime::fromTime_t(myAlarm.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 2) {
            temp = variantToString->AlarmTypeToString(myAlarm.AlarmType);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 3) {
            temp = variantToString->AlarmLevelToString(myAlarm.AlarmType);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 4)
            value = QVariant::fromValue(myAlarm.AlarmMsg);
        else if (columnIdx == 5) {
            value = QVariant::fromValue(weldResult.CurrentSplice.SpliceName);
        }
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
    WeldResultElement weldResult;
    m_alarmAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myAlarm);
    m_weldHistoryAdaptor->QueryOneRecordFromTable(myAlarm.WeldResultID,&weldResult);
    QHash<QString, QVariant> AlarmModelHash;
    AlarmModelHash.insert("AlarmId",myAlarm.AlarmID);
    AlarmModelHash.insert("CreatedDate",QDateTime::fromTime_t(myAlarm.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    AlarmModelHash.insert("Alarm/ErrorType",variantToString->AlarmTypeToString(myAlarm.AlarmType));
    AlarmModelHash.insert("Alarm/ErrorLevel",variantToString->AlarmLevelToString(myAlarm.AlarmType));
    AlarmModelHash.insert("Message",myAlarm.AlarmMsg);//myOperator.PermissionLevel;
    AlarmModelHash.insert("SpliceName",weldResult.CurrentSplice.SpliceName);//myOperator.PermissionLevel;

    if (key == "") {
        return AlarmModelHash;
    } else {
        return AlarmModelHash.value(key);
    }
}

void AlarmModel::removeValue(int id, QString name)
{
    m_alarmAdaptor->DeleteOneRecordFromTable(id,name);
    setModelList();
}

/*****************WorkOrderHistory************************/

WeldHistoryModel::WeldHistoryModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_weldHistoryAdaptor = DBWeldResultTable::Instance();
    historys = new QMap<int, QString>();
    variantToString = VariantToString::Instance();
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
            value = QVariant::fromValue(variantToString->CrossSectionToString(myHistory.CrossSection));
        else if (columnIdx == 7)
            value = QVariant::fromValue(variantToString->WeldModeToString(presetElement.WeldSettings.AdvanceSetting.WeldMode,presetElement.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode));
        else if (columnIdx == 8) {
            temp = variantToString->EnergyToString(myHistory.ActualResult.ActualEnergy).Current;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 9) {
            temp = variantToString->AmplitudeToString(myHistory.ActualResult.ActualAmplitude).Current;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 10) {
            temp = variantToString->WidthToString(myHistory.ActualResult.ActualWidth).Current;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 11) {
            temp = variantToString->TriggerPressureToString(myHistory.ActualResult.ActualTPressure).Current;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 12) {
            temp = variantToString->WeldPressureToString(myHistory.ActualResult.ActualPressure).Current;
            value = QVariant::fromValue(temp);
        }
        else if (columnIdx == 13) {
            temp = variantToString->Time_PlusToString(presetElement.WeldSettings.QualitySetting.Time.Plus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 14) {
            temp = variantToString->Time_MinusToString(presetElement.WeldSettings.QualitySetting.Time.Minus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 15) {
            temp = variantToString->ActualTimeToString(myHistory.ActualResult.ActualTime);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 16) {
            temp = variantToString->Power_PlusToString(presetElement.WeldSettings.QualitySetting.Power.Plus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 17) {
            temp = variantToString->Power_MinusToString(presetElement.WeldSettings.QualitySetting.Power.Minus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 18) {
            temp = variantToString->ActualPowerToString(myHistory.ActualResult.ActualPeakPower);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 19) {
            temp = variantToString->PreHeight_PlusToString(presetElement.WeldSettings.QualitySetting.Preheight.Plus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 20) {
            temp = variantToString->PreHeight_MinusToString(presetElement.WeldSettings.QualitySetting.Preheight.Minus);
            value = QVariant::fromValue(myHistory.ActualResult.ActualPreheight);
        } else if (columnIdx == 21) {
            temp = variantToString->ActualPreHeightToString(myHistory.ActualResult.ActualPreheight);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 22) {
            temp = variantToString->Height_PlusToString(presetElement.WeldSettings.QualitySetting.Height.Plus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 23) {
            temp = variantToString->Height_MinusToString(presetElement.WeldSettings.QualitySetting.Height.Minus);
            value = QVariant::fromValue(myHistory.ActualResult.ActualPostheight);
        } else if (columnIdx == 24) {
            temp = variantToString->ActualHeightToString(myHistory.ActualResult.ActualPostheight);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 25) {
            temp = variantToString->AlarmTypeToString((ALARMTYPE)myHistory.ActualResult.ActualAlarmflags);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 26) {
            temp = variantToString->SampleRatioToString(myHistory.SampleRatio);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 27) {
            temp = "GraphData";
            value = QVariant::fromValue(temp);
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
    setModelList();
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
    PresetElement presetElement;
    m_spliceTable->QueryOneRecordFromTable(myHistory.CurrentSplice.SpliceID,myHistory.CurrentSplice.SpliceName,&presetElement);
    QHash<QString, QVariant> WeldHistoryModelHash;
    WeldHistoryModelHash.insert("WeldHistoryId",myHistory.WeldResultID);
    WeldHistoryModelHash.insert("WorkOrderName",myHistory.CurrentWorkOrder.WorkOrderName);
    WeldHistoryModelHash.insert("PartName",myHistory.CurrentPart.PartName);
    WeldHistoryModelHash.insert("SpliceName",myHistory.CurrentSplice.SpliceName);
    WeldHistoryModelHash.insert("OperatorName",myHistory.OperatorName);
    WeldHistoryModelHash.insert("DateCreated",QDateTime::fromTime_t(myHistory.CreatedDate).toString("MM/dd/yyyy hh:mm"));

    WeldHistoryModelHash.insert("CrossSection",variantToString->CrossSectionToString(myHistory.CrossSection)); //contain in splice
    WeldHistoryModelHash.insert("WeldMode",variantToString->WeldModeToString(presetElement.WeldSettings.AdvanceSetting.WeldMode,presetElement.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode));     //contain in splice
    WeldHistoryModelHash.insert("Energy",variantToString->EnergyToString(myHistory.ActualResult.ActualEnergy).Current);
    WeldHistoryModelHash.insert("Amplitude",variantToString->AmplitudeToString(myHistory.ActualResult.ActualAmplitude).Current);
    WeldHistoryModelHash.insert("Width",variantToString->WidthToString(myHistory.ActualResult.ActualWidth).Current);
    WeldHistoryModelHash.insert("TriggerPressure",variantToString->TriggerPressureToString(myHistory.ActualResult.ActualTPressure).Current);
    WeldHistoryModelHash.insert("WeldPressure",variantToString->WeldPressureToString(myHistory.ActualResult.ActualPressure).Current);
    WeldHistoryModelHash.insert("Time+",variantToString->Time_PlusToString(presetElement.WeldSettings.QualitySetting.Time.Plus)); //contain in splice QUALITYWINDONSETTING
    WeldHistoryModelHash.insert("Timer-",variantToString->Time_MinusToString(presetElement.WeldSettings.QualitySetting.Time.Minus));
    WeldHistoryModelHash.insert("Time",variantToString->ActualTimeToString(myHistory.ActualResult.ActualTime));
    WeldHistoryModelHash.insert("Power+",variantToString->Power_PlusToString(presetElement.WeldSettings.QualitySetting.Power.Plus));
    WeldHistoryModelHash.insert("Power-",variantToString->Power_MinusToString(presetElement.WeldSettings.QualitySetting.Power.Minus));
    WeldHistoryModelHash.insert("Power",variantToString->ActualPowerToString(myHistory.ActualResult.ActualPeakPower));
    WeldHistoryModelHash.insert("Pre-Height+",variantToString->PreHeight_PlusToString(presetElement.WeldSettings.QualitySetting.Preheight.Plus));
    WeldHistoryModelHash.insert("Pre-Height-",variantToString->PreHeight_MinusToString(presetElement.WeldSettings.QualitySetting.Preheight.Minus));
    WeldHistoryModelHash.insert("Pre-Height",variantToString->ActualPreHeightToString(myHistory.ActualResult.ActualPreheight));
    WeldHistoryModelHash.insert("Height+",variantToString->Height_PlusToString(presetElement.WeldSettings.QualitySetting.Height.Plus));
    WeldHistoryModelHash.insert("Height-",variantToString->Height_MinusToString(presetElement.WeldSettings.QualitySetting.Height.Minus));
    WeldHistoryModelHash.insert("Height",variantToString->ActualHeightToString(myHistory.ActualResult.ActualPostheight));
    WeldHistoryModelHash.insert("Alarm",variantToString->AlarmTypeToString((ALARMTYPE)myHistory.ActualResult.ActualAlarmflags)); //myHistory.ActualResult.ActualAlarmflags
    WeldHistoryModelHash.insert("SampleRatio",variantToString->SampleRatioToString(myHistory.SampleRatio));
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
    m_operatorAdaptor = DBOperatorTable::Instance();
    wires = new QMap<int, QString>();
    variantToString = VariantToString::Instance();
    stringToVariant = StringToVariant::Instance();
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
        OperatorElement myOperator;
        //    list <<"WireId" << "WireName" << "DateCreated" << "OperatorName" << "Color" << "StripeType" << "StripeColor" << "Gauge" << "MetalType" << "HorizontalLocation" << "VerticalLocation" << "VerticalPosition";

        m_wireAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myWire);
        m_operatorAdaptor->QueryOneRecordFromTable(myWire.OperatorID,&myOperator);
        QString temp;
        if (columnIdx == 0)
            value = QVariant::fromValue(myWire.WireID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(myWire.WireName);
        else if (columnIdx == 2)
            value = QVariant::fromValue(QDateTime::fromTime_t(myWire.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 3)
            value = QVariant::fromValue(myOperator.OperatorName);
        else if (columnIdx == 4)
            value = QVariant::fromValue(myWire.Color);
        else if (columnIdx == 5)
            value = QVariant::fromValue((int)myWire.Stripe.TypeOfStripe);
        else if (columnIdx == 6)
            value = QVariant::fromValue(myWire.Stripe.Color);
        else if (columnIdx == 7) {
            temp = variantToString->GaugeToString(myWire.Gauge,myWire.GaugeAWG).Current;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 8) {
            QString metalType;
            if (myWire.TypeOfWire == 0) {
                metalType = "Copper";
            } else {
                metalType = "Aluminum";
            }
            value = QVariant::fromValue(metalType);
        } else if (columnIdx == 9)
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
    setModelList();
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
    QString metalType;
    if (wireElement.TypeOfWire == 0) {
        metalType = "Copper";
    } else {
        metalType = "Aluminum";
    }
    WireModelHash.insert("WireType",metalType);

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
            return variantToString->GaugeToString(wireElement.Gauge,wireElement.GaugeAWG).Current;
        else if (type == "max")
            return variantToString->GaugeToString(wireElement.Gauge,wireElement.GaugeAWG).Maximum;
        else if (type == "min")
            return variantToString->GaugeToString(wireElement.Gauge,wireElement.GaugeAWG).Minimum;
    }
    else if (key == "StripeColor")
        return wireElement.Stripe.Color;

}

int WireModel::getStructValue3(QString key, QString value)
{
    int gauge;
    int awg;
    if (key == "Gauge"){
        stringToVariant->GaugeToInt(value,awg,gauge);
        return gauge;
    }
    else if (key == "awg") {
        stringToVariant->GaugeToInt(value,awg,gauge);
        return awg;
    }
    else if (key == "StripeType")
        return (int)wireElement.Stripe.TypeOfStripe;
}

QString WireModel::getStructValue4(int gauge, int awg)
{
    return variantToString->GaugeToString(gauge,awg).Current;
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
    OperatorElement myOperator;
    m_wireAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myWire);
    m_operatorAdaptor->QueryOneRecordFromTable(myWire.OperatorID,&myOperator);
    //    list <<"WireId" << "WireName" << "DateCreated" << "OperatorName" << "Color" << "StripeType" << "StripeColor" << "Gauge" << "MetalType" << "HorizontalLocation" << "VerticalLocation" << "VerticalPosition";
    QHash<QString, QVariant> WireModelHash;
    WireModelHash.insert("WireId",myWire.WireID);
    WireModelHash.insert("WireName",myWire.WireName);
    WireModelHash.insert("DateCreated",QDateTime::fromTime_t(myWire.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    WireModelHash.insert("OperatorName",myOperator.OperatorName);
    WireModelHash.insert("Color",myWire.Color);
    WireModelHash.insert("StripeType",(int)myWire.Stripe.TypeOfStripe);
    WireModelHash.insert("StripeColor",myWire.Stripe.Color);
    WireModelHash.insert("Gauge",myWire.Gauge);
    QString metalType;
    if (myWire.TypeOfWire == 0) {
        metalType = "Copper";
    } else {
        metalType = "Aluminum";
    }
    WireModelHash.insert("MetalType",metalType);
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
    setModelList();
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
