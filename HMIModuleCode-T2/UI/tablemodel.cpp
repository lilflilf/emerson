#include "tablemodel.h"
#include "Modules/typedef.h"
#include <QDebug>
#include <QQmlPropertyMap>

WorkOrderModel::WorkOrderModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_harnessAdaptor = DBHarnessTable::Instance();
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
//        m_workOrderAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myWorkOrder);

        if (columnIdx == 0)
            value = QVariant::fromValue(myWorkOrder.WorkOrderID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(myWorkOrder.WorkOrderName);
        else if (columnIdx == 2)
            value = QVariant::fromValue(myWorkOrder.CreatedDate);
//        else if (columnIdx == 3)
//        {
//            QString temp = "";
//            if (myWorkOrder.PartList.count() > 0)
//                temp = myWorkOrder.PartList.begin().value();
//            value = QVariant::fromValue(temp);
//        }
        else if (columnIdx == 4)
            value = QVariant::fromValue(myWorkOrder.BatchSize);
    }
    return value;
}



void WorkOrderModel::setModelList(unsigned int time_from, unsigned int time_to)
{
    beginResetModel();
    workOrders->clear();
//    if (m_workOrderAdaptor->QueryOnlyUseTime(time_from,time_to,workOrders))
//        qDebug( )<< "setModelList WorkOrderModel" << workOrders->count();
    endResetModel();
}

void WorkOrderModel::setModelList()
{
    beginResetModel();
    workOrders->clear();
//    if (m_workOrderAdaptor->QueryEntireTable(workOrders))
//        qDebug( )<< "setModelList WorkOrderModel" << workOrders->count();
    endResetModel();
}


int WorkOrderModel::rowCount(const QModelIndex & parent) const
{
    UNUSED(parent);
    return workOrders->count();
}


int WorkOrderModel::count()
{
    return workOrders->count();
}


int WorkOrderModel::columnCount(const QModelIndex &parent) const
{
    UNUSED(parent);
    return 1;
}

QVariant WorkOrderModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    UNUSED(section);
    UNUSED(orientation);
    UNUSED(role);
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
    WorkOrderElement tempWorkOrder;
//    m_workOrderAdaptor->QueryOneRecordFromTable(workId, oldWorkName,&tempWorkOrder);
    tempWorkOrder.WorkOrderName = workName;
//    if (partName != tempWorkOrder.PartList.begin().value()) {
//        tempWorkOrder.PartList.remove(tempWorkOrder.PartList.begin().key());
//        tempWorkOrder.PartList.insert(partId, partName);
//    }
    tempWorkOrder.BatchSize = count;
//    m_workOrderAdaptor->UpdateRecordIntoTable(&tempWorkOrder);
    setModelList();
    return true;
}

bool WorkOrderModel::insertRecordIntoTable(QString workName, int partId, QString partName, int count)
{
    WorkOrderElement tempWorkOrder;
    tempWorkOrder.WorkOrderName = workName;
    tempWorkOrder.BatchSize = count;
//    tempWorkOrder.PartList.insert(partId,partName);
//    qDebug() << "insertRecordIntoTable"<<tempWorkOrder.PartList.count();
//    m_workOrderAdaptor->InsertRecordIntoTable(&tempWorkOrder);
    setModelList();
    return true;
}

bool WorkOrderModel::exportData(int workOrderId, QString fileUrl)
{
//    return m_workOrderAdaptor->exportData(workOrderId,fileUrl);
    return true;
}

int WorkOrderModel::importData(QString value, QMap<int, QString> partMap)
{
    int ret = 0;//m_workOrderAdaptor->importData(value,partMap);
    setModelList();
    return ret;
}

int WorkOrderModel::getPartId(int index)
{
    QMap<int,QString>::iterator it; //遍历map
    int i = 0;
    int orderId;
    UNUSED(orderId);
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
//    m_workOrderAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myWorkOrder);
//    return myWorkOrder.PartList.begin().key();
    return 0;
}

QList<int> WorkOrderModel::getSpliceList()
{
    QMap<int,struct HARNESSATTRIBUTE>::iterator it; //遍历map
    QList<int> list;
    for ( it = harnessElement.SpliceList.begin(); it != harnessElement.SpliceList.end(); ++it ) {
        list.append(it.value().SpliceID);
    }
    return list;
}

void WorkOrderModel::editNew(int index,int workOrderId)
{
    m_harnessAdaptor->QueryOneRecordFromTable(index,&harnessElement);
//    m_workOrderAdaptor->QueryOneRecordFromTable(workOrderId,&workOrderElement);
}

QVariant WorkOrderModel::getStructValue(QString key)
{
    QVariant ResultRtn;
    if (key == "WorkOrderId")
    {
        ResultRtn = workOrderElement.WorkOrderID;
        qDebug()<<"WorkOrderID"<<workOrderElement.WorkOrderID;
    }
    else if (key == "WorkOrderName")
        ResultRtn = workOrderElement.WorkOrderName;
    return ResultRtn;
}

QVariant WorkOrderModel::getValue(int index, QString key)
{
    QMap<int,QString>::iterator it; //遍历map
    int i = 0;
    int orderId;
    UNUSED(orderId);
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
//    m_workOrderAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myWorkOrder);
    QHash<QString, QVariant> WorkOrderModelHash;
    WorkOrderModelHash.insert("WorkOrderId",myWorkOrder.WorkOrderID);
    WorkOrderModelHash.insert("WorkOrderName",myWorkOrder.WorkOrderName);
    WorkOrderModelHash.insert("DateCreated",myWorkOrder.CreatedDate);
//    QString temp = "";
//    if (myWorkOrder.PartList.count() > 0)
//        temp = myWorkOrder.PartList.begin().value();
//    WorkOrderModelHash.insert("PART",temp);
    WorkOrderModelHash.insert("QUANTITY",myWorkOrder.BatchSize);
    if (key == "") {
        return WorkOrderModelHash;
    } else {
        return WorkOrderModelHash.value(key);
    }
}

void WorkOrderModel::removeValue(int id, QString name)
{
//    m_workOrderAdaptor->DeleteOneRecordFromTable(id,name);
    setModelList();
}

SplicesModel::SplicesModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_spliceAdaptor = DBPresetTable::Instance();
    m_operatorAdaptor = DBOperatorTable::Instance();
    m_wireAdaptor = DBWireTable::Instance();
    splices = new QMap<int, QString>();
    variantToString = VariantToString::Instance();
    stringToVariant = StringToVariant::Instance();
    m_interface = InterfaceClass::Instance();
    m_teachModeAdvance = TeachModeAdvance::Instance();
}

QVariant SplicesModel::data(const QModelIndex &index, int role) const
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
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 21) {
            value = QVariant::fromValue(mySplice.TestSetting.BatchSize);
        }
    }
    return value;
}



void SplicesModel::setModelList(unsigned int time_from, unsigned int time_to)
{
    beginResetModel();
    splices->clear();
    if (m_spliceAdaptor->QueryOnlyUseTime(time_from,time_to,splices))
        rowList = splices->keys();
    endResetModel();
}

void SplicesModel::setModelList()
{
    beginResetModel();
    splices->clear();
    if (m_spliceAdaptor->QueryEntireTable(splices))
        rowList = splices->keys();
    endResetModel();
}

int SplicesModel::rowCount(const QModelIndex & parent) const
{
    UNUSED(parent);
    return splices->count();
}

int SplicesModel::count()
{
    return splices->count();
}

void SplicesModel::calculateSpliceData()
{
    presetElement.CalculateSpliceData();
}

QString SplicesModel::getValueString(QString valueKey, QString value)
{

    return "";
}



void SplicesModel::saveTeachMode()
{
    m_teachModeAdvance->_set();
}

void SplicesModel::defaultTeachMode()
{
    m_teachModeAdvance->_default();

}


QString SplicesModel::getTeachModeValue(QString valueKey, QString valueType)
{
    QString ResultStr = "";

    if (valueKey == "TestStandardTime+") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_PLRG_STD]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_PLRG_STD]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_PLRG_STD]).Minimum;
    }
    else if (valueKey == "TestStandardTime-") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_MSRG_STD]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_MSRG_STD]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_MSRG_STD]).Minimum;
    }
    else if (valueKey == "TestStandardPower+") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_PLRG_STD]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_PLRG_STD]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_PLRG_STD]).Minimum;
    }
    else if (valueKey == "TestStandardPower-") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_MSRG_STD]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_MSRG_STD]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_MSRG_STD]).Minimum;
    }
    else if (valueKey == "TestStandardPre+") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_PLRG_STD]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_PLRG_STD]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_PLRG_STD]).Minimum;
    }
    else if (valueKey == "TestStandardPre-") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_MSRG_STD]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_MSRG_STD]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_MSRG_STD]).Minimum;
    }
    else if (valueKey == "TestStandardPost+") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_PLRG_STD]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_PLRG_STD]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_PLRG_STD]).Minimum;
    }
    else if (valueKey == "TestStandardPost-") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_MSRG_STD]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_MSRG_STD]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_MSRG_STD]).Minimum;
    }
    else if (valueKey == "TestAutoTime+") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_PLRG_AUTO]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_PLRG_AUTO]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_PLRG_AUTO]).Minimum;
    }
    else if (valueKey == "TestAutoTime-") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_MSRG_AUTO]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_MSRG_AUTO]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_MSRG_AUTO]).Minimum;
    }
    else if (valueKey == "TestAutoPower+") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_PLRG_AUTO]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_PLRG_AUTO]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_PLRG_AUTO]).Minimum;
    }
    else if (valueKey == "TestAutoPower-") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_MSRG_AUTO]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_MSRG_AUTO]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_MSRG_AUTO]).Minimum;
    }
    else if (valueKey == "TestAutoPre+") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_PLRG_AUTO]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_PLRG_AUTO]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_PLRG_AUTO]).Minimum;
    }
    else if (valueKey == "TestAutoPre-") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_MSRG_AUTO]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_MSRG_AUTO]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_MSRG_AUTO]).Minimum;
    }
    else if (valueKey == "TestAutoPost+") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_PLRG_AUTO]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_PLRG_AUTO]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_PLRG_AUTO]).Minimum;
    }
    else if (valueKey == "TestAutoPost-") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_MSRG_AUTO]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_MSRG_AUTO]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_MSRG_AUTO]).Minimum;
    }
    else if (valueKey == "TestSigmaTime+") {
        if (valueType == "current")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_CONFRG_PL]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_CONFRG_PL]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_CONFRG_PL]).Minimum;
    }
    else if (valueKey == "TestSigmaTime-") {
        if (valueType == "current")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_CONFRG_MS]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_CONFRG_MS]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[TIME_CONFRG_MS]).Minimum;
    }
    else if (valueKey == "TestSigmaPower+") {
        if (valueType == "current")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_CONFRG_PL]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_CONFRG_PL]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_CONFRG_PL]).Minimum;
    }
    else if (valueKey == "TestSigmaPower-") {
        if (valueType == "current")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_CONFRG_MS]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_CONFRG_MS]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[POWER_CONFRG_MS]).Minimum;
    }
    else if (valueKey == "TestSigmaPre+") {
        if (valueType == "current")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_CONFRG_PL]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_CONFRG_PL]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_CONFRG_PL]).Minimum;
    }
    else if (valueKey == "TestSigmaPre-") {
        if (valueType == "current")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_CONFRG_MS]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_CONFRG_MS]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[PRE_HGT_CONFRG_MS]).Minimum;
    }
    else if (valueKey == "TestSigmaPost+") {
        if (valueType == "current")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_CONFRG_PL]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_CONFRG_PL]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_CONFRG_PL]).Minimum;
    }
    else if (valueKey == "TestSigmaPost-") {
        if (valueType == "current")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_CONFRG_MS]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_CONFRG_MS]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->SigmaTeachModeToString(m_interface->StatusData.Cust_Data.cust_qual_range[HEIGHT_CONFRG_MS]).Minimum;
    }
    else if (valueKey == "TestStandardQty") {
        if (valueType == "current")
            ResultStr = variantToString->TeachModeQuantity(m_interface->StatusData.Cust_Data.StandardRunQuantity).Current;
        else if (valueType == "max")
            ResultStr = variantToString->TeachModeQuantity(m_interface->StatusData.Cust_Data.StandardRunQuantity).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->TeachModeQuantity(m_interface->StatusData.Cust_Data.StandardRunQuantity).Minimum;
    }
    else if (valueKey == "TestAutoQty") {
        if (valueType == "current")
            ResultStr = variantToString->TeachModeQuantity(m_interface->StatusData.Cust_Data.AutoRunQuantity).Current;
        else if (valueType == "max")
            ResultStr = variantToString->TeachModeQuantity(m_interface->StatusData.Cust_Data.AutoRunQuantity).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->TeachModeQuantity(m_interface->StatusData.Cust_Data.AutoRunQuantity).Minimum;
    }
    else if (valueKey == "TestSigmaQty") {
        if (valueType == "current")
            ResultStr = variantToString->TeachModeQuantity(m_interface->StatusData.Cust_Data.SigmaRunQuantity).Current;
        else if (valueType == "max")
            ResultStr = variantToString->TeachModeQuantity(m_interface->StatusData.Cust_Data.SigmaRunQuantity).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->TeachModeQuantity(m_interface->StatusData.Cust_Data.SigmaRunQuantity).Minimum;
    }
    else if (valueKey == "TestModel") {
        ResultStr = QString("%1").arg((int)m_interface->StatusData.Soft_Settings.ToolCoverIgnore);
    }
    else if (valueKey == "TestCount") {
        ResultStr = QString("%1").arg((int)m_interface->StatusData.Soft_Settings.RunCount);
    }
    else if (valueKey == "TeachMode") {
        ResultStr = QString("%1").arg((int)m_interface->StatusData.Soft_Settings.Teach_Mode);
    }
    else
        ResultStr = "";
    return ResultStr;
}

void SplicesModel::setTeachModeValue(QString valueKey, QString standValue, QString autoValue, QString sigmaValue)
{
    qDebug() << "setTeachModeValue" << valueKey << standValue << autoValue << sigmaValue
             << sizeof(m_interface->tempStatusData.Cust_Data.cust_qual_range);
    if (valueKey == "TestTime+")
    {
        m_interface->tempStatusData.Cust_Data.cust_qual_range[TIME_PLRG_STD] = stringToVariant->SigmaTeachModeToInt(standValue);
        m_interface->tempStatusData.Cust_Data.cust_qual_range[TIME_PLRG_AUTO] = stringToVariant->SigmaTeachModeToInt(autoValue);
        m_interface->tempStatusData.Cust_Data.cust_qual_range[TIME_CONFRG_PL] = stringToVariant->SigmaTeachModeToInt(sigmaValue);
    }
    else if (valueKey == "TestTime-")
    {
        m_interface->tempStatusData.Cust_Data.cust_qual_range[TIME_MSRG_STD] = stringToVariant->SigmaTeachModeToInt(standValue);
        m_interface->tempStatusData.Cust_Data.cust_qual_range[TIME_MSRG_AUTO] = stringToVariant->SigmaTeachModeToInt(autoValue);
        m_interface->tempStatusData.Cust_Data.cust_qual_range[TIME_CONFRG_MS] = stringToVariant->SigmaTeachModeToInt(sigmaValue);
    }
    else if (valueKey == "TestPower+")
    {
        m_interface->tempStatusData.Cust_Data.cust_qual_range[POWER_PLRG_STD] = stringToVariant->SigmaTeachModeToInt(standValue);
        m_interface->tempStatusData.Cust_Data.cust_qual_range[POWER_PLRG_AUTO] = stringToVariant->SigmaTeachModeToInt(autoValue);
        m_interface->tempStatusData.Cust_Data.cust_qual_range[POWER_CONFRG_PL] = stringToVariant->SigmaTeachModeToInt(sigmaValue);
    }
    else if (valueKey == "TestPower-")
    {
        m_interface->tempStatusData.Cust_Data.cust_qual_range[POWER_MSRG_STD] = stringToVariant->SigmaTeachModeToInt(standValue);
        m_interface->tempStatusData.Cust_Data.cust_qual_range[POWER_MSRG_AUTO] = stringToVariant->SigmaTeachModeToInt(autoValue);
        m_interface->tempStatusData.Cust_Data.cust_qual_range[POWER_CONFRG_MS] = stringToVariant->SigmaTeachModeToInt(sigmaValue);
    }
    else if (valueKey == "TestPre+")
    {
        m_interface->tempStatusData.Cust_Data.cust_qual_range[PRE_HGT_PLRG_STD] = stringToVariant->SigmaTeachModeToInt(standValue);
        m_interface->tempStatusData.Cust_Data.cust_qual_range[PRE_HGT_PLRG_AUTO] = stringToVariant->SigmaTeachModeToInt(autoValue);
        m_interface->tempStatusData.Cust_Data.cust_qual_range[PRE_HGT_CONFRG_PL] = stringToVariant->SigmaTeachModeToInt(sigmaValue);
    }
    else if (valueKey == "TestPre-")
    {
        m_interface->tempStatusData.Cust_Data.cust_qual_range[PRE_HGT_MSRG_STD] = stringToVariant->SigmaTeachModeToInt(standValue);
        m_interface->tempStatusData.Cust_Data.cust_qual_range[PRE_HGT_MSRG_AUTO] = stringToVariant->SigmaTeachModeToInt(autoValue);
        m_interface->tempStatusData.Cust_Data.cust_qual_range[PRE_HGT_CONFRG_MS] = stringToVariant->SigmaTeachModeToInt(sigmaValue);
    }
    else if (valueKey == "TestPost+")
    {
        m_interface->tempStatusData.Cust_Data.cust_qual_range[HEIGHT_PLRG_STD] = stringToVariant->SigmaTeachModeToInt(standValue);
        m_interface->tempStatusData.Cust_Data.cust_qual_range[HEIGHT_PLRG_AUTO] = stringToVariant->SigmaTeachModeToInt(autoValue);
        m_interface->tempStatusData.Cust_Data.cust_qual_range[HEIGHT_CONFRG_PL] = stringToVariant->SigmaTeachModeToInt(sigmaValue);
    }
    else if (valueKey == "TestPost-")
    {
        m_interface->tempStatusData.Cust_Data.cust_qual_range[HEIGHT_MSRG_STD] = stringToVariant->SigmaTeachModeToInt(standValue);
        m_interface->tempStatusData.Cust_Data.cust_qual_range[HEIGHT_MSRG_AUTO] = stringToVariant->SigmaTeachModeToInt(autoValue);
        m_interface->tempStatusData.Cust_Data.cust_qual_range[HEIGHT_CONFRG_MS] = stringToVariant->SigmaTeachModeToInt(sigmaValue);
    }
    else if (valueKey == "TestQty")
    {
        m_interface->tempStatusData.Cust_Data.StandardRunQuantity = stringToVariant->QuantityTeachModeToInt(standValue);
        m_interface->tempStatusData.Cust_Data.AutoRunQuantity = stringToVariant->QuantityTeachModeToInt(autoValue);
        m_interface->tempStatusData.Cust_Data.SigmaRunQuantity = stringToVariant->QuantityTeachModeToInt(sigmaValue);
    }    
    else if (valueKey == "TestModel") {
        if (standValue == "true")
            m_interface->StatusData.Soft_Settings.ToolCoverIgnore = true;
        else if (standValue == "false")
            m_interface->StatusData.Soft_Settings.ToolCoverIgnore = false;
    }
    else if (valueKey == "TestCount") {
        bool ok;
        m_interface->StatusData.Soft_Settings.RunCount = standValue.toInt(&ok,10);
    }
    else if (valueKey == "TeachMode") {
        if (standValue == "0")
            m_interface->StatusData.Soft_Settings.Teach_Mode = TEACHMODESETTING::TEACH_MODE_TYPE::UNDEFINED;
        else if (standValue == "1")
            m_interface->StatusData.Soft_Settings.Teach_Mode = TEACHMODESETTING::TEACH_MODE_TYPE::STANDARD;
        else if (standValue == "2")
            m_interface->StatusData.Soft_Settings.Teach_Mode = TEACHMODESETTING::TEACH_MODE_TYPE::AUTO;
        else if (standValue == "3")
            m_interface->StatusData.Soft_Settings.Teach_Mode = TEACHMODESETTING::TEACH_MODE_TYPE::SIGMA;
    }
}


QString SplicesModel::getStructValue(QString valueKey, QString valueType)
{
    QString ResultStr = "";
    if (valueKey == "Energy") {
        if (valueType == "current")
            ResultStr = variantToString->EnergyToString(presetElement.WeldSettings.BasicSetting.Energy).Current;
        else if (valueType == "max")
            ResultStr = variantToString->EnergyToString(presetElement.WeldSettings.BasicSetting.Energy).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->EnergyToString(presetElement.WeldSettings.BasicSetting.Energy).Minimum;
    }
    else if (valueKey == "Trigger Pressure") {
        if (valueType == "current")
            ResultStr = variantToString->TriggerPressureToString(presetElement.WeldSettings.BasicSetting.TrigPres).Current;
        else if (valueType == "max")
            ResultStr = variantToString->TriggerPressureToString(presetElement.WeldSettings.BasicSetting.TrigPres).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->TriggerPressureToString(presetElement.WeldSettings.BasicSetting.TrigPres).Minimum;
    }
    else if (valueKey == "Amplitude") {
        if (valueType == "current")
            ResultStr = variantToString->AmplitudeToString(presetElement.WeldSettings.BasicSetting.Amplitude).Current;
        else if (valueType == "max")
            ResultStr = variantToString->AmplitudeToString(presetElement.WeldSettings.BasicSetting.Amplitude).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->AmplitudeToString(presetElement.WeldSettings.BasicSetting.Amplitude).Minimum;
    }
    else if (valueKey == "Weld Pressure") {
        if (valueType == "current")
            ResultStr = variantToString->WeldPressureToString(presetElement.WeldSettings.BasicSetting.Pressure).Current;
        else if (valueType == "max")
            ResultStr = variantToString->WeldPressureToString(presetElement.WeldSettings.BasicSetting.Pressure).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->WeldPressureToString(presetElement.WeldSettings.BasicSetting.Pressure).Minimum;
    }
    else if (valueKey == "Width") {
        if (valueType == "current")
            ResultStr = variantToString->WidthToString(presetElement.WeldSettings.BasicSetting.Width).Current;
        else if (valueType == "max")
            ResultStr = variantToString->WidthToString(presetElement.WeldSettings.BasicSetting.Width).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->WidthToString(presetElement.WeldSettings.BasicSetting.Width).Minimum;
    }
    else if (valueKey == "Time-") {
        if (valueType == "current")
            ResultStr = variantToString->TimeMinusToString(presetElement.WeldSettings.QualitySetting.Time.Minus).Current;
        else if (valueType == "max")
            ResultStr = variantToString->TimeMinusToString(presetElement.WeldSettings.QualitySetting.Time.Minus).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->TimeMinusToString(presetElement.WeldSettings.QualitySetting.Time.Minus).Minimum;
    }
    else if (valueKey == "Time+") {
        if (valueType == "current")
            ResultStr = variantToString->TimePlusToString(presetElement.WeldSettings.QualitySetting.Time.Plus).Current;
        else if (valueType == "max")
            ResultStr = variantToString->TimePlusToString(presetElement.WeldSettings.QualitySetting.Time.Plus).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->TimePlusToString(presetElement.WeldSettings.QualitySetting.Time.Plus).Minimum;
    }
    else if (valueKey == "Power-") {
        if (valueType == "current")
        {
            ResultStr = variantToString->PowerMinusToString
                (presetElement.WeldSettings.QualitySetting.Power.Minus).Current;
        }
        else if (valueType == "max")
        {
            ResultStr = variantToString->PowerMinusToString
                (presetElement.WeldSettings.QualitySetting.Power.Minus).Maximum;
        }
        else if (valueType == "min")
        {
            ResultStr = variantToString->PowerMinusToString
                (presetElement.WeldSettings.QualitySetting.Power.Minus).Minimum;
        }
    }
    else if (valueKey == "Power+") {
        if (valueType == "current")
        {
//            if(presetElement.WeldSettings.QualitySetting.Power.Plus == 0)
//            {
//                _Utility->InitializeTextData();
//                presetElement.WeldSettings.QualitySetting.Power.Plus = _Utility->Maxpower;
//            }
            ResultStr = variantToString->PowerPlusToString
                (presetElement.WeldSettings.QualitySetting.Power.Plus).Current;
        }
        else if (valueType == "max")
        {
            ResultStr = variantToString->PowerPlusToString
                (presetElement.WeldSettings.QualitySetting.Power.Plus).Maximum;
        }
        else if (valueType == "min")
        {
            ResultStr = variantToString->PowerPlusToString
                (presetElement.WeldSettings.QualitySetting.Power.Plus).Minimum;
        }
    }
    else if (valueKey == "Pre-Height-") {
        if (valueType == "current")
            ResultStr = variantToString->PreHeightMinusToString(presetElement.WeldSettings.QualitySetting.Preheight.Minus).Current;
        else if (valueType == "max")
            ResultStr = variantToString->PreHeightMinusToString(presetElement.WeldSettings.QualitySetting.Preheight.Minus).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->PreHeightMinusToString(presetElement.WeldSettings.QualitySetting.Preheight.Minus).Minimum;
    }
    else if (valueKey == "Pre-Height+") {
        if (valueType == "current")
            ResultStr = variantToString->PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight.Plus).Current;
        else if (valueType == "max")
            ResultStr = variantToString->PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight.Plus).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->PreHeightPlusToString(presetElement.WeldSettings.QualitySetting.Preheight.Plus).Minimum;
    }
    else if (valueKey == "Post-Height-") {
        if (valueType == "current")
            ResultStr = variantToString->HeightMinusToString(presetElement.WeldSettings.QualitySetting.Height.Minus).Current;
        else if (valueType == "max")
            ResultStr = variantToString->HeightMinusToString(presetElement.WeldSettings.QualitySetting.Height.Minus).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->HeightMinusToString(presetElement.WeldSettings.QualitySetting.Height.Minus).Minimum;
    }
    else if (valueKey == "Post-Height+") {
        if (valueType == "current")
            ResultStr = variantToString->HeightPlusToString(presetElement.WeldSettings.QualitySetting.Height.Plus).Current;
        else if (valueType == "max")
            ResultStr = variantToString->HeightPlusToString(presetElement.WeldSettings.QualitySetting.Height.Plus).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->HeightPlusToString(presetElement.WeldSettings.QualitySetting.Height.Plus).Minimum;
    }
    else if (valueKey == "Step-Energy") {
        if (valueType == "current")
            ResultStr = variantToString->StepEnergyToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StepEnergyToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StepEnergyToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep).Minimum;
    }
    else if (valueKey == "Step-Time") {
        if (valueType == "current")
            ResultStr = variantToString->StepTimeToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.TimeToStep).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StepTimeToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.TimeToStep).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StepTimeToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.TimeToStep).Minimum;
    }
    else if (valueKey == "Step-Power") {
        if (valueType == "current")
            ResultStr = variantToString->StepPowerToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.PowerToStep).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StepPowerToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.PowerToStep).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StepPowerToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.PowerToStep).Minimum;
    }
    else if (valueKey == "Amplitude A") {
        if (valueType == "current")
            ResultStr = variantToString->Amplitude2ToString(presetElement.WeldSettings.BasicSetting.Amplitude).Current;
        else if (valueType == "max")
            ResultStr = variantToString->Amplitude2ToString(presetElement.WeldSettings.BasicSetting.Amplitude).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->Amplitude2ToString(presetElement.WeldSettings.BasicSetting.Amplitude).Minimum;
    }
    else if (valueKey == "Amplitude B") {
        if (valueType == "current")
            ResultStr = variantToString->Amplitude2ToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.Amplitude2).Current;
        else if (valueType == "max")
            ResultStr = variantToString->Amplitude2ToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.Amplitude2).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->Amplitude2ToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.Amplitude2).Minimum;
    }
    else if (valueKey == "Pre Burst") {
        if (valueType == "current")
            ResultStr = variantToString->PreBurstTimeToString(presetElement.WeldSettings.AdvanceSetting.PreBurst).Current;
        else if (valueType == "max")
            ResultStr = variantToString->PreBurstTimeToString(presetElement.WeldSettings.AdvanceSetting.PreBurst).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->PreBurstTimeToString(presetElement.WeldSettings.AdvanceSetting.PreBurst).Minimum;
    }
    else if (valueKey == "Hold Time") {
        if (valueType == "current")
            ResultStr = variantToString->HoldTimeToString(presetElement.WeldSettings.AdvanceSetting.HoldTime).Current;
        else if (valueType == "max")
            ResultStr = variantToString->HoldTimeToString(presetElement.WeldSettings.AdvanceSetting.HoldTime).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->HoldTimeToString(presetElement.WeldSettings.AdvanceSetting.HoldTime).Minimum;
    }
    else if (valueKey == "After Burst") {
        if (valueType == "current")
            ResultStr = variantToString->AfterBurstDuringToString(presetElement.WeldSettings.AdvanceSetting.ABDur).Current;
        else if (valueType == "max")
            ResultStr = variantToString->AfterBurstDuringToString(presetElement.WeldSettings.AdvanceSetting.ABDur).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->AfterBurstDuringToString(presetElement.WeldSettings.AdvanceSetting.ABDur).Minimum;
    }
    else if (valueKey == "Squeeze Time") {
        if (valueType == "current")
            ResultStr = variantToString->SqueezeTimeToString(presetElement.WeldSettings.AdvanceSetting.SqzTime).Current;
        else if (valueType == "max")
            ResultStr = variantToString->SqueezeTimeToString(presetElement.WeldSettings.AdvanceSetting.SqzTime).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->SqueezeTimeToString(presetElement.WeldSettings.AdvanceSetting.SqzTime).Minimum;
    }
    else if (valueKey == "ActualWidth") {
        if (valueType == "current")
            ResultStr =
                    variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.OffsetOption.MeasuredWidth).Current;
        else if (valueType == "max")
            ResultStr =
                    variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.OffsetOption.MeasuredWidth).Maximum;
        else if (valueType == "min")
            ResultStr =
                    variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.OffsetOption.MeasuredWidth).Minimum;
    }
    else if (valueKey == "ActualHeight") {
        if (valueType == "current")
            ResultStr =
                    variantToString->MeasureHeightToString(presetElement.WeldSettings.AdvanceSetting.OffsetOption.MeasuredHeight).Current;
        else if (valueType == "max")
            ResultStr =
                    variantToString->MeasureHeightToString(presetElement.WeldSettings.AdvanceSetting.OffsetOption.MeasuredHeight).Maximum;
        else if (valueType == "min")
            ResultStr =
                    variantToString->MeasureHeightToString(presetElement.WeldSettings.AdvanceSetting.OffsetOption.MeasuredHeight).Minimum;
    }
    else if (valueKey == "DisplayedWidth") {
        if (valueType == "current")
            ResultStr =
                    variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.OffsetOption.DisplayWidth).Current;
        else if (valueType == "max")
            ResultStr =
                    variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.OffsetOption.DisplayWidth).Maximum;
        else if (valueType == "min")
            ResultStr =
                    variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.OffsetOption.DisplayWidth).Minimum;
    }
    else if (valueKey == "DisplayedHeight") {
        if (valueType == "current")
            ResultStr =
                    variantToString->MeasureHeightToString(presetElement.WeldSettings.AdvanceSetting.OffsetOption.DisplayHeight).Current;
        else if (valueType == "max")
            ResultStr =
                    variantToString->MeasureHeightToString(presetElement.WeldSettings.AdvanceSetting.OffsetOption.DisplayHeight).Maximum;
        else if (valueType == "min")
            ResultStr =
                    variantToString->MeasureHeightToString(presetElement.WeldSettings.AdvanceSetting.OffsetOption.DisplayHeight).Minimum;
    }
    else if (valueKey == "Unload Time") {
        if (valueType == "current")
            ResultStr =
                    variantToString->AntiSideSpliceTimeToString(presetElement.WeldSettings.AdvanceSetting.AntiSideOption.AntiSideSpliceTime).Current;
        else if (valueType == "max")
            ResultStr =
                    variantToString->AntiSideSpliceTimeToString(presetElement.WeldSettings.AdvanceSetting.AntiSideOption.AntiSideSpliceTime).Maximum;
        else if (valueType == "min")
            ResultStr =
                    variantToString->AntiSideSpliceTimeToString(presetElement.WeldSettings.AdvanceSetting.AntiSideOption.AntiSideSpliceTime).Minimum;
    }
    else if (valueKey == "Load Time") {
        if (valueType == "current")
            ResultStr =
                    variantToString->CutOffSpliceTimeToString(presetElement.WeldSettings.AdvanceSetting.CutOffOption.CutOffSpliceTime).Current;
        else if (valueType == "max")
            ResultStr =
                    variantToString->CutOffSpliceTimeToString(presetElement.WeldSettings.AdvanceSetting.CutOffOption.CutOffSpliceTime).Maximum;
        else if (valueType == "min")
            ResultStr =
                    variantToString->CutOffSpliceTimeToString(presetElement.WeldSettings.AdvanceSetting.CutOffOption.CutOffSpliceTime).Minimum;
    }
    else if (valueKey == "Anti-Side") {
        if (presetElement.WeldSettings.AdvanceSetting.AntiSideOption.AntiSideMode)
            ResultStr = "left";
        else
            ResultStr = "right";
    }
    else if (valueKey == "Cut Off") {
        if (presetElement.WeldSettings.AdvanceSetting.CutOffOption.CutOff)
            ResultStr = "left";
        else
            ResultStr = "right";
    }
    else if (valueKey == "Insulation") {
        if (presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption)
            ResultStr = "left";
        else
            ResultStr = "right";
    }
    else if (valueKey == "PicPath") {
        if (presetElement.PresetPicNamePath.isEmpty())
            ResultStr = " ";
        ResultStr = presetElement.PresetPicNamePath;
    }
    else if (valueKey == "SpliceName") {
        ResultStr = presetElement.SpliceName;
    }
    else if (valueKey == "SpliceId") {
        ResultStr = QString("%1").arg(presetElement.SpliceID);
    }
    else if (valueKey == "ShrinkId") {
        ResultStr = presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID;
    }
    else if (valueKey == "ShrinkTemp") {
        ResultStr = variantToString->ShrinkTemperatureToString(presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature).Current;
    }
    else if (valueKey == "ShrinkTime") {
        ResultStr = variantToString->ShrinkTimeToString(presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime).Current;
    }
    else if (valueKey == "ShrinkLock") {
        if (presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkMutex)
            ResultStr = "left";
        else
            ResultStr = "right";
    }
    else if (valueKey == "Cross Section") {
        ResultStr = variantToString->CrossSectionToString(presetElement.CrossSection);
    }
    else if (valueKey == "Cross Section") {
        ResultStr = variantToString->CrossSectionToString(presetElement.CrossSection);
    }
    else if (valueKey == "TestStandardTime+") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG_STD]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG_STD]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG_STD]).Minimum;
    }
    else if (valueKey == "TestStandardTime-") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG_STD]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG_STD]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG_STD]).Minimum;
    }
    else if (valueKey == "TestStandardPower+") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG_STD]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG_STD]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG_STD]).Minimum;
    }
    else if (valueKey == "TestStandardPower-") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG_STD]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG_STD]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG_STD]).Minimum;
    }
    else if (valueKey == "TestStandardPre+") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG_STD]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG_STD]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG_STD]).Minimum;
    }
    else if (valueKey == "TestStandardPre-") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG_STD]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG_STD]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG_STD]).Minimum;
    }
    else if (valueKey == "TestStandardPost+") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG_STD]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG_STD]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG_STD]).Minimum;
    }
    else if (valueKey == "TestStandardPost-") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG_STD]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG_STD]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG_STD]).Minimum;
    }
    else if (valueKey == "TestAutoTime+") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG_AUTO]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG_AUTO]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG_AUTO]).Minimum;
    }
    else if (valueKey == "TestAutoTime-") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG_AUTO]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG_AUTO]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG_AUTO]).Minimum;
    }
    else if (valueKey == "TestAutoPower+") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG_AUTO]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG_AUTO]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG_AUTO]).Minimum;
    }
    else if (valueKey == "TestAutoPower-") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG_AUTO]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG_AUTO]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG_AUTO]).Minimum;
    }
    else if (valueKey == "TestAutoPre+") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG_AUTO]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG_AUTO]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG_AUTO]).Minimum;
    }
    else if (valueKey == "TestAutoPre-") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG_AUTO]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG_AUTO]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG_AUTO]).Minimum;
    }
    else if (valueKey == "TestAutoPost+") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG_AUTO]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG_AUTO]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG_AUTO]).Minimum;
    }
    else if (valueKey == "TestAutoPost-") {
        if (valueType == "current")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG_AUTO]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG_AUTO]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG_AUTO]).Minimum;
    }
    else if (valueKey == "TestSigmaTime+") {
        if (valueType == "current")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_PL]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_PL]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_PL]).Minimum;
    }
    else if (valueKey == "TestSigmaTime-") {
        if (valueType == "current")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_MS]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_MS]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_MS]).Minimum;
    }
    else if (valueKey == "TestSigmaPower+") {
        if (valueType == "current")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_PL]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_PL]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_PL]).Minimum;
    }
    else if (valueKey == "TestSigmaPower-") {
        if (valueType == "current")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_MS]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_MS]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_MS]).Minimum;
    }
    else if (valueKey == "TestSigmaPre+") {
        if (valueType == "current")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_PL]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_PL]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_PL]).Minimum;
    }
    else if (valueKey == "TestSigmaPre-") {
        if (valueType == "current")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_MS]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_MS]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_MS]).Minimum;
    }
    else if (valueKey == "TestSigmaPost+") {
        if (valueType == "current")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_PL]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_PL]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_PL]).Minimum;
    }
    else if (valueKey == "TestSigmaPost-") {
        if (valueType == "current")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_MS]).Current;
        else if (valueType == "max")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_MS]).Maximum;
        else if (valueType == "min")
            ResultStr = variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_MS]).Minimum;
    }
    else if (valueKey == "TestModel") {
        ResultStr = QString("%1").arg((int)presetElement.TestSetting.TestMode);
    }
    else if (valueKey == "TestCount") {
        ResultStr = QString("%1").arg(presetElement.TestSetting.BatchSize);
    }
    else if (valueKey == "TeachMode") {
        ResultStr = QString("%1").arg((int)presetElement.TestSetting.TeachModeSetting.TeachModeType);
    }
    else
        ResultStr = "";
    return ResultStr;
}

int SplicesModel::getRawData(QString key)
{
    int iResult = 0;
    if (key == "Time-")        
        iResult = presetElement.WeldSettings.QualitySetting.Time.Minus;
    else if (key == "Time+")
        iResult = presetElement.WeldSettings.QualitySetting.Time.Plus;
    else if (key == "Power-")
        iResult = presetElement.WeldSettings.QualitySetting.Power.Minus;
    else if (key == "Power+")
        iResult = presetElement.WeldSettings.QualitySetting.Power.Plus;
    else if (key == "Pre-Height-")
        iResult = presetElement.WeldSettings.QualitySetting.Preheight.Minus;
    else if (key == "Pre-Height+")
        iResult = presetElement.WeldSettings.QualitySetting.Preheight.Plus;
    else if (key == "Post-Height-")
        iResult = presetElement.WeldSettings.QualitySetting.Height.Minus;
    else if (key == "Post-Height+")
        iResult = presetElement.WeldSettings.QualitySetting.Height.Plus;
    else
        iResult = 0;
    return iResult;
}

void SplicesModel::setStructValue(QString valueKey, QVariant value)
{
    if (valueKey == "Energy") {
        presetElement.WeldSettings.BasicSetting.Energy = stringToVariant->EnergyToInt(value.toString());
    }
    else if (valueKey == "Trigger Pressure") {
        presetElement.WeldSettings.BasicSetting.TrigPres = stringToVariant->TriggerPressureToInt(value.toString());
        qDebug() << "setStructValue" << value<<presetElement.WeldSettings.BasicSetting.TrigPres;
    }
    else if (valueKey == "Amplitude") {
        presetElement.WeldSettings.BasicSetting.Amplitude = stringToVariant->AmplitudeToInt(value.toString());
    }
    else if (valueKey == "Weld Pressure") {
        presetElement.WeldSettings.BasicSetting.Pressure = stringToVariant->WeldPressureToInt(value.toString());
    }
    else if (valueKey == "Width") {
        presetElement.WeldSettings.BasicSetting.Width = stringToVariant->WidthToInt(value.toString());
    }
    else if (valueKey == "Time-") {
        presetElement.WeldSettings.QualitySetting.Time.Minus = stringToVariant->TimeMinusToInt(value.toString());
    }
    else if (valueKey == "Time+") {
        presetElement.WeldSettings.QualitySetting.Time.Plus = stringToVariant->TimePlusToInt(value.toString());
    }
    else if (valueKey == "Power-") {
        presetElement.WeldSettings.QualitySetting.Power.Minus = stringToVariant->PowerMinusToInt(value.toString());
    }
    else if (valueKey == "Power+") {
        presetElement.WeldSettings.QualitySetting.Power.Plus = stringToVariant->PowerPlusToInt(value.toString());
    }
    else if (valueKey == "Pre-Height-") {
        presetElement.WeldSettings.QualitySetting.Preheight.Minus = stringToVariant->PreHeightMinusToInt(value.toString());
    }
    else if (valueKey == "Pre-Height+") {
        presetElement.WeldSettings.QualitySetting.Preheight.Plus = stringToVariant->PreHeightPlusToInt(value.toString());
    }
    else if (valueKey == "Post-Height-") {
        presetElement.WeldSettings.QualitySetting.Height.Minus = stringToVariant->HeightMinusToInt(value.toString());
    }
    else if (valueKey == "Post-Height+") {
        presetElement.WeldSettings.QualitySetting.Height.Plus = stringToVariant->HeightPlusToInt(value.toString());
    }
    else if (valueKey == "Step-Energy") {
        presetElement.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep = stringToVariant->StepEnergyToInt(value.toString());
    }
    else if (valueKey == "Step-Time") {
        presetElement.WeldSettings.AdvanceSetting.StepWeld.TimeToStep = stringToVariant->StepTimeToInt(value.toString());
    }
    else if (valueKey == "Step-Power") {
        presetElement.WeldSettings.AdvanceSetting.StepWeld.PowerToStep = stringToVariant->StepPowerToInt(value.toString());
    }
    else if (valueKey == "Amplitude B") {
        presetElement.WeldSettings.AdvanceSetting.StepWeld.Amplitude2 = stringToVariant->Amplitude2ToInt(value.toString());
    }
    else if (valueKey == "WeldModel") {
        presetElement.WeldSettings.AdvanceSetting.WeldMode = (ADVANCESETTING::WELDMODE)value.toInt();
    }
    else if (valueKey == "StepModel") {
        presetElement.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode = (STEPWELD::STEPWELDMODE)value.toInt();
    }
    else if (valueKey == "Pre Burst") {
        presetElement.WeldSettings.AdvanceSetting.PreBurst = stringToVariant->PreBurstTimeToInt(value.toString());
    }
    else if (valueKey == "Hold Time") {
        presetElement.WeldSettings.AdvanceSetting.HoldTime = stringToVariant->HoldTimeToInt(value.toString());
    }
    else if (valueKey == "After Burst") {
        presetElement.WeldSettings.AdvanceSetting.ABDur = stringToVariant->AfterBurstDuringToInt(value.toString());
    }
    else if (valueKey == "Squeeze Time") {
        presetElement.WeldSettings.AdvanceSetting.SqzTime = stringToVariant->SqueezeTimeToInt(value.toString());
    }
    else if (valueKey == "ActualWidth") {
        presetElement.WeldSettings.AdvanceSetting.OffsetOption.MeasuredWidth =
                stringToVariant->MeasureWidthToInt(value.toString());
    }
    else if (valueKey == "ActualHeight") {
        presetElement.WeldSettings.AdvanceSetting.OffsetOption.MeasuredHeight
                = stringToVariant->MeasureHeightToInt(value.toString());
    }
    else if (valueKey == "DisplayWidth") {
        processPresetElement.WeldSettings.AdvanceSetting.OffsetOption.DisplayWidth
                = stringToVariant->MeasureHeightToInt(value.toString());
    }
    else if (valueKey == "DisplayHeight") {
        processPresetElement.WeldSettings.AdvanceSetting.OffsetOption.DisplayHeight
                = stringToVariant->MeasureHeightToInt(value.toString());
    }
    else if (valueKey == "Unload Time") {
        presetElement.WeldSettings.AdvanceSetting.AntiSideOption.AntiSideSpliceTime =
                stringToVariant->AntiSideSpliceTimeToInt(value.toString());
    }
    else if (valueKey == "Load Time") {
        presetElement.WeldSettings.AdvanceSetting.CutOffOption.CutOffSpliceTime =
                stringToVariant->CutOffSpliceTimeToInt(value.toString());
    }
    else if (valueKey == "Anti-Side") {
        presetElement.WeldSettings.AdvanceSetting.AntiSideOption.AntiSideMode =
                value.toBool();
    }
    else if (valueKey == "Cut Off") {
        presetElement.WeldSettings.AdvanceSetting.CutOffOption.CutOff =
                value.toBool();
    }
    else if (valueKey == "Insulation") {
        presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption =
                value.toBool();
    }
    else if (valueKey == "ShrinkId") {
        presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID =
                value.toString();
    }
    else if (valueKey == "ShrinkTemp") {
        presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature =
                stringToVariant->ShrinkTemperatureToInt(value.toString());
    }
    else if (valueKey == "ShrinkTime") {
        presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime =
                stringToVariant->ShrinkTimeToInt(value.toString());
    }
    else if (valueKey == "ShrinkLock") {
        if (value.toString() == "left")
            presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkMutex = true;
        else
            presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkMutex = false;
    }
    else if (valueKey == "SpliceName") {
        presetElement.SpliceName = value.toString();
    }
    else if (valueKey == "OperatorId") {
        presetElement.OperatorID = value.toInt();
    }
    else if (valueKey == "Total Cross") {
        presetElement.CrossSection =
                stringToVariant->CrossSectionToInt(value.toString());
    }
    else if (valueKey == "WireMap") {
        QStringList list = value.toStringList();
        presetElement.WireIndex.clear();
        int wireId;
        QString temp;
        bool ok;
        WireElement tempWire;
        for (int i = 0; i < list.count(); i++) {
            temp = list[i];
            wireId = temp.toInt(&ok,10);
            if (m_wireAdaptor->QueryOneRecordFromTable(wireId,&tempWire))
                presetElement.WireIndex.insert(wireId,tempWire.WireName);
        }
        presetElement.NoOfWires = list.count();
    }
    else if (valueKey == "PicPath") {
        presetElement.PresetPicNamePath = value.toString();
    }
    else if (valueKey == "TestStandardTime+") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG_STD] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPower+") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG_STD] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPre+") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG_STD] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPost+") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG_STD] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardTime-") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG_STD] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPower-") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG_STD] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPre-") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG_STD] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPost-") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG_STD] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestSigmaTime+") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_PL] = stringToVariant->SigmaTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestSigmaPower+") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_PL] = stringToVariant->SigmaTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestSigmaPre+") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_PL] = stringToVariant->SigmaTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestSigmaPost+") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_PL] = stringToVariant->SigmaTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestSigmaTime-") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_MS] = stringToVariant->SigmaTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestSigmaPower-") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_MS] = stringToVariant->SigmaTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestSigmaPre-") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_MS] = stringToVariant->SigmaTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestSigmaPost-") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_MS] = stringToVariant->SigmaTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestModel") {
        presetElement.TestSetting.TestMode = (TESTSETTING::TESTMODE)value.toInt();
    }
    else if (valueKey == "TestCount") {
        presetElement.TestSetting.BatchSize = value.toInt();
    }
    else if (valueKey == "TeachMode") {
        presetElement.TestSetting.TeachModeSetting.TeachModeType = (TEACHMODESETTING::TEACH_MODE_TYPE)value.toInt();
    }
    else if (valueKey == "CutterTime") {
        presetElement.WeldSettings.AdvanceSetting.CutOffOption.Cutter4TimeAlarm = value.toBool();
    }
    else if (valueKey == "CutterPeakPower") {
        presetElement.WeldSettings.AdvanceSetting.CutOffOption.Cutter4PowerAlarm = value.toBool();
    }
    else if (valueKey == "CutterPreHeight") {
        presetElement.WeldSettings.AdvanceSetting.CutOffOption.Cutter4PreHeightAlarm = value.toBool();
    }
    else if (valueKey == "CutterPostHeight") {
        presetElement.WeldSettings.AdvanceSetting.CutOffOption.Cutter4HeightAlarm = value.toBool();
    }
}

void SplicesModel::setProcessValue(QString valueKey, QVariant value)
{
    qDebug() << "0000000000000000000" << valueKey << value;
    if (valueKey == "Energy") {
        processPresetElement.WeldSettings.BasicSetting.Energy = stringToVariant->EnergyToInt(value.toString());
    }
    else if (valueKey == "Trigger Pressure") {
        processPresetElement.WeldSettings.BasicSetting.TrigPres = stringToVariant->TriggerPressureToInt(value.toString());
    }
    else if (valueKey == "Amplitude") {
        processPresetElement.WeldSettings.BasicSetting.Amplitude = stringToVariant->AmplitudeToInt(value.toString());
    }
    else if (valueKey == "Weld Pressure") {
        processPresetElement.WeldSettings.BasicSetting.Pressure = stringToVariant->WeldPressureToInt(value.toString());
    }
    else if (valueKey == "Width") {
        processPresetElement.WeldSettings.BasicSetting.Width = stringToVariant->WidthToInt(value.toString());
    }
    else if (valueKey == "Time-") {
        processPresetElement.WeldSettings.QualitySetting.Time.Minus = stringToVariant->TimeMinusToInt(value.toString());
    }
    else if (valueKey == "Time+") {
        processPresetElement.WeldSettings.QualitySetting.Time.Plus = stringToVariant->TimePlusToInt(value.toString());
    }
    else if (valueKey == "Power-") {
        processPresetElement.WeldSettings.QualitySetting.Power.Minus = stringToVariant->PowerMinusToInt(value.toString());
    }
    else if (valueKey == "Power+") {
        processPresetElement.WeldSettings.QualitySetting.Power.Plus = stringToVariant->PowerPlusToInt(value.toString());
    }
    else if (valueKey == "Pre-Height-") {
        processPresetElement.WeldSettings.QualitySetting.Preheight.Minus = stringToVariant->PreHeightMinusToInt(value.toString());
    }
    else if (valueKey == "Pre-Height+") {
        processPresetElement.WeldSettings.QualitySetting.Preheight.Plus = stringToVariant->PreHeightPlusToInt(value.toString());
    }
    else if (valueKey == "Post-Height-") {
        processPresetElement.WeldSettings.QualitySetting.Height.Minus = stringToVariant->HeightMinusToInt(value.toString());
    }
    else if (valueKey == "Post-Height+") {
        processPresetElement.WeldSettings.QualitySetting.Height.Plus = stringToVariant->HeightPlusToInt(value.toString());
    }
    else if (valueKey == "Step-Energy") {
        processPresetElement.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep = stringToVariant->StepEnergyToInt(value.toString());
    }
    else if (valueKey == "Step-Time") {
        processPresetElement.WeldSettings.AdvanceSetting.StepWeld.TimeToStep = stringToVariant->StepTimeToInt(value.toString());
    }
    else if (valueKey == "Step-Power") {
        processPresetElement.WeldSettings.AdvanceSetting.StepWeld.PowerToStep = stringToVariant->StepPowerToInt(value.toString());
    }
    else if (valueKey == "Amplitude B") {
        processPresetElement.WeldSettings.AdvanceSetting.StepWeld.Amplitude2 = stringToVariant->Amplitude2ToInt(value.toString());
    }
    else if (valueKey == "WeldModel") {
        processPresetElement.WeldSettings.AdvanceSetting.WeldMode = (ADVANCESETTING::WELDMODE)value.toInt();
    }
    else if (valueKey == "StepModel") {
        processPresetElement.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode = (STEPWELD::STEPWELDMODE)value.toInt();
    }
    else if (valueKey == "Pre Burst") {
        processPresetElement.WeldSettings.AdvanceSetting.PreBurst = stringToVariant->PreBurstTimeToInt(value.toString());
    }
    else if (valueKey == "Hold Time") {
        processPresetElement.WeldSettings.AdvanceSetting.HoldTime = stringToVariant->HoldTimeToInt(value.toString());
    }
    else if (valueKey == "After Burst") {
        processPresetElement.WeldSettings.AdvanceSetting.ABDur = stringToVariant->AfterBurstDuringToInt(value.toString());
    }
    else if (valueKey == "Squeeze Time") {
        processPresetElement.WeldSettings.AdvanceSetting.SqzTime = stringToVariant->SqueezeTimeToInt(value.toString());
    }
    else if (valueKey == "ActualWidth") {
        processPresetElement.WeldSettings.AdvanceSetting.OffsetOption.MeasuredWidth =
                stringToVariant->MeasureWidthToInt(value.toString());
    }
    else if (valueKey == "ActualHeight") {
        processPresetElement.WeldSettings.AdvanceSetting.OffsetOption.MeasuredHeight
                = stringToVariant->MeasureHeightToInt(value.toString());
    }
    else if (valueKey == "DisplayWidth") {
        processPresetElement.WeldSettings.AdvanceSetting.OffsetOption.DisplayWidth
                = stringToVariant->MeasureHeightToInt(value.toString());
    }
    else if (valueKey == "DisplayHeight") {
        processPresetElement.WeldSettings.AdvanceSetting.OffsetOption.DisplayHeight
                = stringToVariant->MeasureHeightToInt(value.toString());
    }
    else if (valueKey == "Unload Time") {
        processPresetElement.WeldSettings.AdvanceSetting.AntiSideOption.AntiSideSpliceTime =
                stringToVariant->AntiSideSpliceTimeToInt(value.toString());
    }
    else if (valueKey == "Load Time") {
        processPresetElement.WeldSettings.AdvanceSetting.CutOffOption.CutOffSpliceTime =
                stringToVariant->CutOffSpliceTimeToInt(value.toString());
    }
    else if (valueKey == "Anti-Side") {
        processPresetElement.WeldSettings.AdvanceSetting.AntiSideOption.AntiSideMode =
                value.toBool();
    }
    else if (valueKey == "Cut Off") {
        processPresetElement.WeldSettings.AdvanceSetting.CutOffOption.CutOff =
                value.toBool();
    }
    else if (valueKey == "Insulation") {
        processPresetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption =
                value.toBool();
    }
    else if (valueKey == "ShrinkId") {
        processPresetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID =
                value.toString();
    }
    else if (valueKey == "ShrinkTemp") {
        processPresetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature =
                stringToVariant->ShrinkTemperatureToInt(value.toString());
    }
    else if (valueKey == "ShrinkTime") {
        processPresetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime =
                stringToVariant->ShrinkTimeToInt(value.toString());
    }
    else if (valueKey == "ShrinkLock") {
        if (value.toString() == "left")
            presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkMutex = true;
        else
            presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkMutex = false;
    }
    else if (valueKey == "SpliceName") {
        processPresetElement.SpliceName = value.toString();
    }
    else if (valueKey == "SpliceId") {
        processPresetElement.SpliceID = value.toInt();
    }
    else if (valueKey == "OperatorId") {
        processPresetElement.OperatorID = value.toInt();
    }
    else if (valueKey == "Total Cross") {
        processPresetElement.CrossSection =
                stringToVariant->CrossSectionToInt(value.toString());
    }
    else if (valueKey == "WireMap") {
        QStringList list = value.toStringList();
        processPresetElement.WireIndex.clear();
        int wireId;
        QString temp;
        bool ok;
        WireElement tempWire;
        for (int i = 0; i < list.count(); i++) {
            temp = list[i];
            wireId = temp.toInt(&ok,10);
            if (m_wireAdaptor->QueryOneRecordFromTable(wireId,&tempWire))
                presetElement.WireIndex.insert(wireId,tempWire.WireName);
        }
        processPresetElement.NoOfWires = list.count();
    }
    else if (valueKey == "PicPath") {
        processPresetElement.PresetPicNamePath = value.toString();
    }
    else if (valueKey == "TestStandardTime+") {
        processPresetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG_STD] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPower+") {
        processPresetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG_STD] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPre+") {
        processPresetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG_STD] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPost+") {
        processPresetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG_STD] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardTime-") {
        processPresetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG_STD] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPower-") {
        processPresetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG_STD] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPre-") {
        processPresetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG_STD] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPost-") {
        processPresetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG_STD] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestSigmaTime+") {
        processPresetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_PL] = stringToVariant->SigmaTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestSigmaPower+") {
        processPresetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_PL] = stringToVariant->SigmaTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestSigmaPre+") {
        processPresetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_PL] = stringToVariant->SigmaTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestSigmaPost+") {
        processPresetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_PL] = stringToVariant->SigmaTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestSigmaTime-") {
        processPresetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_MS] = stringToVariant->SigmaTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestSigmaPower-") {
        processPresetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_MS] = stringToVariant->SigmaTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestSigmaPre-") {
        processPresetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_MS] = stringToVariant->SigmaTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestSigmaPost-") {
        processPresetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_MS] = stringToVariant->SigmaTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestModel") {
        processPresetElement.TestSetting.TestMode = (TESTSETTING::TESTMODE)value.toInt();
    }
    else if (valueKey == "TestCount") {
        processPresetElement.TestSetting.BatchSize = value.toInt();
    }
    else if (valueKey == "TeachMode") {
        processPresetElement.TestSetting.TeachModeSetting.TeachModeType = (TEACHMODESETTING::TEACH_MODE_TYPE)value.toInt();
    }
    else if (valueKey == "CutterTime") {
        processPresetElement.WeldSettings.AdvanceSetting.CutOffOption.Cutter4TimeAlarm = value.toBool();
    }
    else if (valueKey == "CutterPeakPower") {
        processPresetElement.WeldSettings.AdvanceSetting.CutOffOption.Cutter4PowerAlarm = value.toBool();
    }
    else if (valueKey == "CutterPreHeight") {
        processPresetElement.WeldSettings.AdvanceSetting.CutOffOption.Cutter4PreHeightAlarm = value.toBool();
    }
    else if (valueKey == "CutterPostHeight") {
        processPresetElement.WeldSettings.AdvanceSetting.CutOffOption.Cutter4HeightAlarm = value.toBool();
    }





//    spliceModel.setProcessValue("CutterTime",cutterModel.get(0).switchState == "left" ? true : false)
//    spliceModel.setProcessValue("CutterPeakPower",cutterModel.get(1).switchState == "left" ? true : false)
//    spliceModel.setProcessValue("CutterPreHeight",cutterModel.get(2).switchState == "left" ? true : false)
//    spliceModel.setProcessValue("CutterPostHeight",cutterModel.get(3).switchState == "left" ? true : false)
}

int SplicesModel::saveSplice(bool bIsEdit)
{
    int spliceId;
    if (bIsEdit)
    {
        m_spliceAdaptor->UpdateRecordIntoTable(&presetElement);
        setModelList();
        return presetElement.SpliceID;
    }
    else
    {
        spliceId = m_spliceAdaptor->InsertRecordIntoTable(&presetElement);
    }
    setModelList();
    return spliceId;
}

uint SplicesModel::getHashCode()
{
    return presetElement.HashCode;
}

void SplicesModel::createNew()
{
    PresetElement temp;
    presetElement = temp;
}

void SplicesModel::editNew(int spliceId)
{
    m_spliceAdaptor->QueryOneRecordFromTable(spliceId, &presetElement);
}

QString SplicesModel::getString(QString type, int value)
{
    QString ResultStr = "";
    if (type == "CrossSection")
        ResultStr = variantToString->CrossSectionToString(value);
    else
        ResultStr = "";
    return ResultStr;
}

bool SplicesModel::getWeldMode(QString type, int index)
{
    bool bResult = false;
    if (type == "weld")
    {
        if ((int)presetElement.WeldSettings.AdvanceSetting.WeldMode == index)
            bResult = true;
        else
            bResult = false;
    }
    else if (type == "step")
    {
        if ((int)presetElement.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode == index)
            bResult = true;
        else
            bResult = false;
    }
    return bResult;
}

QList<int> SplicesModel::getWireIdList()
{
    QMap<int,QString>::iterator it; //遍历map
    QList<int> list;
    for ( it = presetElement.WireIndex.begin(); it != presetElement.WireIndex.end(); ++it ) {
        list.append(it.key());
    }
    return list;
}

QString SplicesModel::graphTimeToString(int time)
{
    return variantToString->GraphTimeToString(time);
}

QString SplicesModel::graphPowerToString(int power)
{
    return variantToString->GraphPowerToString(power);
}

QString SplicesModel::graphHeightToString(int height)
{
    return variantToString->GraphHeightToString(height);
}

bool SplicesModel::exportData(int spliceId, QString fileUrl)
{
    m_PresetDataObj->ExportData(spliceId, fileUrl);
    return true;
}

int SplicesModel::importData(QString value)
{
    int ret = m_PresetDataObj->ImportData(value);
    setModelList();
    return ret;
}

QString SplicesModel::getSpliceName(int spliceId)
{
    PresetElement  tempSplice;
    if (m_spliceAdaptor->QueryOneRecordFromTable(spliceId,&tempSplice))
        return tempSplice.SpliceName;
    else
        return "";
}

int SplicesModel::searchIndexByName(QString name)
{
    QMap<int,QString>::iterator it; //遍历map
    int i = 0;
    for ( it = splices->begin(); it != splices->end(); ++it ) {
        if (name == it.value())
            return i;
        i++;

    }
    return -1;
}

int SplicesModel::copySplice(int spliceId)
{
    PresetElement  tempSplice;
    bool ok;
    if (m_spliceAdaptor->QueryOneRecordFromTable(spliceId,&tempSplice))
    {
        if (tempSplice.SpliceName.size() > 3) {
            QString str = tempSplice.SpliceName.right(3);
            QString type = str.left(1) + str.right(1);
            if (type == "()")
            {
                str = str.mid(1,1);
                QString name = tempSplice.SpliceName = tempSplice.SpliceName.left(tempSplice.SpliceName.size() - 3);
                QString spliceName = name + QString("(%1)").arg(str.toInt(&ok,10)+1);

                tempSplice.SpliceName = spliceName;

            }
            else
                tempSplice.SpliceName = tempSplice.SpliceName+"(1)";
        }
        else
            tempSplice.SpliceName = tempSplice.SpliceName+"(1)";

        int ret = m_spliceAdaptor->InsertRecordIntoTable(&tempSplice);
        setModelList();
        return ret;

    }
    else
        return -1;

}

QString SplicesModel::timePlusToString(int time)
{
    return variantToString->TimePlusToString(time).Maximum;
}

QString SplicesModel::timeMinusToString(int time)
{
    return variantToString->TimeMinusToString(time).Minimum;
}

QString SplicesModel::actualTimeToString(int ActualTime)
{
    return variantToString->ActualTimeToString(ActualTime);
}

QString SplicesModel::actualPowerToString(int ActualPower)
{
    return variantToString->ActualPowerToString(ActualPower);
}

QString SplicesModel::actualPreHeightToString(int ActualPreHeight)
{
    return variantToString->ActualPreHeightToString(ActualPreHeight);
}

QString SplicesModel::actualHeightToString(int ActualHeight)
{
    return variantToString->ActualHeightToString(ActualHeight);
}

void SplicesModel::updateSplice(PresetElement presetElement)
{
    m_spliceAdaptor->UpdateRecordIntoTable(&presetElement);
}


void SplicesModel::removeValue(int id, QString name)
{
    m_spliceAdaptor->DeleteOneRecordFromTable(id,name);
    setModelList();
}

int SplicesModel::columnCount(const QModelIndex &parent) const
{
    UNUSED(parent);
    return 1;
}

QVariant SplicesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    UNUSED(section);
    UNUSED(orientation);
    UNUSED(role);
    return QVariant();
}

void SplicesModel::setRoles(const QStringList &names)
{
    m_roleNames.clear();
    for(int idx=0; idx<names.count(); idx++)
    {
        m_roleNames[Qt::UserRole + idx + 1] = names[idx].toLocal8Bit();
    }
}

QHash<int, QByteArray> SplicesModel::roleNames() const
{
    return m_roleNames;
}

QVariant SplicesModel::getValue(int index, QString key)
{
//    QMap<int,QString>::iterator it; //遍历map
//    int i = 0;
//    int orderId;
//    for ( it = splices->begin(); it != splices->end(); ++it ) {
//        if (i == index){
//            orderId = it.key();
//            break;
//        }
//        else {
//            i++;
//        }
//    }
//    splices[rowList[index]]
    //        list << "SpliceId" << "SpliceName" << "DateCreated" << "OperatorName" << "CrossSection" << "TotalWires" << "Verified" << "WeldMode" << "Energy" << "Amplitude"
    //             << "Width" << "TriggerPressure" << "WeldPressure" << "Time+" << "Time-" << "Power+" << "Power-" << "Pre-Height+" << "Pre-Height-" << "Height+" << "Height-" << "count";
//    PresetElement mySplice;
//    OperatorElement myOperator;
    if (mySplice.SpliceID != rowList[index])
    {
        m_spliceAdaptor->QueryOneRecordFromTable(rowList[index],splices->value(rowList[index]),&mySplice);
        m_operatorAdaptor->QueryOneRecordFromTable(mySplice.OperatorID,&myOperator);
    }
    QHash<QString, QVariant> SpliceModelHash;
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
    SpliceModelHash.insert("count",mySplice.TestSetting.BatchSize);
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
    m_harnessAdaptor = DBHarnessTable::Instance();
    m_HarnessDataObj = CSVHarnessData::Instance();
    m_operatorAdaptor = DBOperatorTable::Instance();
    parts = new QMap<int, QString>();
    m_Harness = new HarnessElement();
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
        UNUSED(rowId);
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

        HarnessElement myHarness;
        OperatorElement myOperator;
        m_harnessAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myHarness);
        m_operatorAdaptor->QueryOneRecordFromTable(myHarness.OperatorID,&myOperator);
        if (columnIdx == 0)
            value = QVariant::fromValue(myHarness.HarnessID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(myHarness.HarnessName);
        else if (columnIdx == 2)
            value = QVariant::fromValue(QDateTime::fromTime_t(myHarness.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 3)
            value = QVariant::fromValue(myOperator.OperatorName);
        else if (columnIdx == 4)
            value = QVariant::fromValue(myHarness.NoOfSplice);
        else if (columnIdx == 5) {
            QString processModel;
            if (myHarness.HarnessTypeSetting.ProcessMode == BASIC)
                processModel = "BASIC";
            else if (myHarness.HarnessTypeSetting.ProcessMode == ADVANCE)
                processModel = "ADVANCE";
            value = QVariant::fromValue(processModel);
        }
        else if (columnIdx == 6)
            value = QVariant::fromValue(myHarness.HarnessTypeSetting.WorkStations.TotalWorkstation);
        else if (columnIdx == 7)
            value = QVariant::fromValue(myHarness.NoOfSplice);
        else if (columnIdx == 8)
            value = QVariant::fromValue(myHarness.HarnessTypeSetting.BoardLayout.Rows);
        else if (columnIdx == 9)
            value = QVariant::fromValue(myHarness.HarnessTypeSetting.BoardLayout.Columns);
        else if (columnIdx == 10)
            value = QVariant::fromValue(myHarness.HarnessTypeSetting.WorkStations.MaxSplicesPerWorkstation);
    }
    return value;
}



void PartModel::setModelList(unsigned int time_from, unsigned int time_to)
{
    beginResetModel();
    parts->clear();
    if (m_harnessAdaptor->QueryOnlyUseTime(time_from,time_to,parts))
        qDebug( )<< "PartModel " << parts->count();
    endResetModel();
}

void PartModel::setModelList()
{
    beginResetModel();
    parts->clear();
    if (m_harnessAdaptor->QueryEntireTable(parts))
        qDebug( )<< "PartModel" << parts->count();
    endResetModel();
}


int PartModel::rowCount(const QModelIndex & parent) const
{
    UNUSED(parent);
    return parts->count();
}


int PartModel::count()
{
    return parts->count();
}

QVariant PartModel::getStruceValue(QString key)
{
    QVariant varResult = -1;
    if (key == "PartId")
        varResult = m_Harness->HarnessID;
    else if (key == "PartName")
        varResult = m_Harness->HarnessName;
    return varResult;
}

bool PartModel::exportData(int partId, QString fileUrl)
{
    return m_HarnessDataObj->ExportData(partId,fileUrl);
}

int PartModel::importData(QString filePath)
{
    int ret = m_HarnessDataObj->ImportData(filePath);
    setModelList();
    return ret;
}

QString PartModel::getPartName(int partId)
{
    HarnessElement myHarness;
    bool reb;
    reb = m_harnessAdaptor->QueryOneRecordFromTable(partId,&myHarness);
    return myHarness.HarnessName;
}

QList<int> PartModel::getSpliceList()
{
    QMap<int,struct HARNESSATTRIBUTE>::iterator it; //遍历map
    QList<int> list;
    for ( it = m_Harness->SpliceList.begin(); it != m_Harness->SpliceList.end(); ++it ) {
        list.append(it.value().SpliceID);
    }
    return list;
}

int PartModel::searchIndexByName(QString name)
{
    QMap<int,QString>::iterator it; //遍历map
    int i = 0;
    for ( it = parts->begin(); it != parts->end(); ++it ) {
        if (name == it.value())
            return i;
        i++;

    }
    return -1;
}


int PartModel::columnCount(const QModelIndex &parent) const
{
    UNUSED(parent);
    return 1;
}

QVariant PartModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    UNUSED(section);
    UNUSED(orientation);
    UNUSED(role);
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

void PartModel::editNew(int partId)
{
    m_harnessAdaptor->QueryOneRecordFromTable(partId, m_Harness);
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
    UNUSED(orderId);
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
    HarnessElement myHarness;
    OperatorElement myOperator;
    m_harnessAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myHarness);
    m_operatorAdaptor->QueryOneRecordFromTable(myHarness.OperatorID,&myOperator);
    QHash<QString, QVariant> PartModelHash;
    PartModelHash.insert("PartId",myHarness.HarnessID);
    PartModelHash.insert("HarnessName",myHarness.HarnessName);
    PartModelHash.insert("DateCreated",QDateTime::fromTime_t(myHarness.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    PartModelHash.insert("OperatorName",myOperator.OperatorName);
    PartModelHash.insert("TotalSplices",myHarness.NoOfSplice);
    QString processModel;
    if (myHarness.HarnessTypeSetting.ProcessMode == BASIC)
        processModel = "BASIC";
    else if (myHarness.HarnessTypeSetting.ProcessMode == ADVANCE)
        processModel = "ADVANCE";
    PartModelHash.insert("ProcessMode",processModel);
    PartModelHash.insert("ofWorkstation",myHarness.HarnessTypeSetting.WorkStations.TotalWorkstation);
    PartModelHash.insert("#ofSplicesperWorkstation",myHarness.NoOfSplice);
    PartModelHash.insert("Rows",myHarness.HarnessTypeSetting.BoardLayout.Rows);
    PartModelHash.insert("Columns",myHarness.HarnessTypeSetting.BoardLayout.Columns);
    PartModelHash.insert("MaxSplicesPerZone",myHarness.HarnessTypeSetting.WorkStations.MaxSplicesPerWorkstation);
    if (key == "") {
        return PartModelHash;
    } else {
        return PartModelHash.value(key);
    }
}

void PartModel::removeValue(int id, QString name)
{
    m_harnessAdaptor->DeleteOneRecordFromTable(id, name);
    setModelList();
}

void PartModel::getPartInfo(bool bIsEdit, int id, QString name)
{

    if (bIsEdit) {
        m_harnessAdaptor->QueryOneRecordFromTable(id,name,m_Harness);
    } else {
        delete m_Harness;
        m_Harness = NULL;
        m_Harness = new HarnessElement();
    }
}

int PartModel::getWorkStationRows()
{
    return m_Harness->HarnessTypeSetting.BoardLayout.Rows;
}

int PartModel::getWorkStationColumns()
{
    return m_Harness->HarnessTypeSetting.BoardLayout.Columns;
}

int PartModel::getWorkStationMaxSplicePerZone()
{
    return m_Harness->HarnessTypeSetting.BoardLayout.MaxSplicesPerZone;
}

int PartModel::getWorkStationCount()
{
    return m_Harness->HarnessTypeSetting.WorkStations.TotalWorkstation;
}

int PartModel::getWorkStationMaxSplicePerStation()
{
    return m_Harness->HarnessTypeSetting.WorkStations.MaxSplicesPerWorkstation;
}

int PartModel::getCurrentPartSpliceCount()
{
    return m_Harness->SpliceList.count();
}

QList<int> PartModel::getWorkStationCorlor()
{
    QList<int> corlorList;
    for (int i = 0; i < m_Harness->SpliceList.count(); i++) {
        corlorList.append( m_Harness->SpliceList.value( m_Harness->SpliceList.keys().at(i)).CurrentWorkstation);
    }
    return corlorList;
}

QList<int> PartModel::geteWorkStationZone()
{
    QList<int> zoneList;
    for (int i = 0; i < m_Harness->SpliceList.count(); i++) {
        zoneList.append(m_Harness->SpliceList.value(m_Harness->SpliceList.keys().at(i)).CurrentBoardLayoutZone);
    }
    return zoneList;
}

QStringList PartModel::getCurrentPartOfSpliceName()
{
    QStringList list;
    for (int i = 0; i < m_Harness->SpliceList.count(); i++) {
        list.append(m_Harness->SpliceList.value(m_Harness->SpliceList.keys().at(i)).SpliceName);
    }
    return list;
}

QList<int> PartModel::getCurrentPartOfSpliceId()
{
    QList<int> idList;
    for (int i = 0; i < m_Harness->SpliceList.count(); i++) {
        idList.append(m_Harness->SpliceList.value(m_Harness->SpliceList.keys().at(i)).SpliceID);
    }
    return idList;
}

bool PartModel::getPartOnlineOrOffLine()
{
    if (m_Harness->HarnessTypeSetting.ProcessMode == BASIC) {
        return false;
    } else {
        return true;
    }
}

void PartModel::setPartOffLineOrOnLine(bool bIsLine)
{
    if (bIsLine) {
        m_Harness->HarnessTypeSetting.ProcessMode = ADVANCE;
    } else {
        m_Harness->HarnessTypeSetting.ProcessMode = BASIC;
    }
}

void PartModel::setPartName(QString name)
{
   m_Harness->HarnessName =  name;
}

void PartModel::setPartColumns(int columns)
{
    m_Harness->HarnessTypeSetting.BoardLayout.Columns = columns;
}

void PartModel::setPartRows(int rows)
{
   m_Harness->HarnessTypeSetting.BoardLayout.Rows = rows;
}

void PartModel::setPartMaxSplicePerZone(int maxNum)
{
    m_Harness->HarnessTypeSetting.BoardLayout.MaxSplicesPerZone = maxNum;
}

void PartModel::setPartWorkStationNum(int num)
{
    m_Harness->HarnessTypeSetting.WorkStations.TotalWorkstation = num;
}

void PartModel::setPartMaxSplicePerWorkStation(int maxNum)
{
     m_Harness->HarnessTypeSetting.WorkStations.MaxSplicesPerWorkstation = maxNum;
}

void PartModel::setPartSpliceListClear()
{
    m_Harness->SpliceList.clear();
}

void PartModel::setPartSpliceList(QString name, int id, int station, int zone, int index)
{
    m_Harness->SpliceList[index].SpliceID = id;
    m_Harness->SpliceList[index].SpliceName = name;
    m_Harness->SpliceList[index].CurrentWorkstation = station;
    m_Harness->SpliceList[index].CurrentBoardLayoutZone = zone;
}

void PartModel::savePartInfo(bool bIsEdit, int operatorId)
{
    m_Harness->OperatorID = operatorId;
    m_Harness->NoOfSplice = m_Harness->SpliceList.count();
    if (bIsEdit) {
        m_harnessAdaptor->UpdateRecordIntoTable(m_Harness);
    } else {
        int harnessId = m_harnessAdaptor->InsertRecordIntoTable(m_Harness);
        qDebug()<<"savePartInfo insert id: "<< harnessId;
    }
    setModelList();
}

/*******************************OperaTorModel*****************************/
OperatorModel::OperatorModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_operatorAdaptor = DBOperatorTable::Instance();
    operators = new QMap<int, QString>();
    permissionSetting = new PermissionSetting();
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
        UNUSED(rowId);
        QMap<int,QString>::iterator it; //遍历map
        int i = 0;
        OperatorElement myOperator;
        for ( it = operators->begin(); it != operators->end(); ++it ) {
            m_operatorAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myOperator);
            if (myOperator.PermissionLevel == OperatorElement::BRANSON)
            {
                operators->remove(it.key());
                break;
            }
        }
        for ( it = operators->begin(); it != operators->end(); ++it ) {
            if (i == index.row()){
                rowId = it.key();
                break;
            }
            else {
                i++;
            }
        }
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
            permissionSetting->_Recall();
            qDebug() << "(int)myOperator.PermissionLevel" << (int)myOperator.PermissionLevel;
            if ((int)myOperator.PermissionLevel == 0)
                value = "Key";
            else
            {
                switch(myOperator.PermissionLevel)
                {
                case OperatorElement::LEVEL1:
                case OperatorElement::LEVEL2:
                case OperatorElement::LEVEL3:
                case OperatorElement::LEVEL4:
                    value = QVariant::fromValue(permissionSetting->FiveLevelIdentifier.at(myOperator.PermissionLevel-1));
                    break;
                case OperatorElement::INITIAL:
                    value = "Initial";
                    break;
                case OperatorElement::BRANSON:
                    value = "Branson";
                    break;
                default:
                    value = "None";
                    break;
                }
            }
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

void OperatorModel::editNew(int index)
{
    QMap<int,QString>::iterator it; //遍历map
    int i = 0;
    for ( it = operators->begin(); it != operators->end(); ++it ) {
        if (i == index){
            break;
        }
        else {
            i++;
        }
    }
    m_operatorAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&operatorElement);
}

QString OperatorModel::getStruckValue(QString key)
{
    QString ResultStr = "";
    if (key == "OperatorName")
        ResultStr = operatorElement.OperatorName;
    else if (key == "PassWord")
        ResultStr = operatorElement.Password;
    else
        ResultStr = "";
//    else if (key == "Level") {
//        QString level = "";
//        if (operatorElement.PermissionLevel == PASSWORDCONTROL::SUPERUSER)
//            level = "SUPERUSER";
//        else if (operatorElement.PermissionLevel == PASSWORDCONTROL::ADMINISTRATOR)
//            level = "ADMINISTRATOR";
//        else if (operatorElement.PermissionLevel == PASSWORDCONTROL::TECHNICIAN)
//            level = "TECHNICIAN";
//        else if (operatorElement.PermissionLevel == PASSWORDCONTROL::QUALITYCONTROL)
//            level = "QUALITYCONTROL";
//        else if (operatorElement.PermissionLevel == PASSWORDCONTROL::OPEN)
//            level = "OPEN";
//        return level;
//    }
    return ResultStr;
}


int OperatorModel::rowCount(const QModelIndex & parent) const
{
    UNUSED(parent);
    return operators->count();
}


int OperatorModel::count()
{
    return operators->count();
}

void OperatorModel::insertValue(QString name, QString passwd,int level)
{
    qDebug() << "insertValue----------" << name << passwd<<level;
    OperatorElement myOperator;
    myOperator.OperatorName = name;
    myOperator.Password = passwd;
    if (level == 1)
        myOperator.PermissionLevel = OperatorElement::LEVEL1;
    else if (level == 2)
        myOperator.PermissionLevel = OperatorElement::LEVEL2;
    else if (level == 3)
        myOperator.PermissionLevel = OperatorElement::LEVEL3;
    else if (level == 4)
        myOperator.PermissionLevel = OperatorElement::LEVEL4;
    else if (level == 0)
        myOperator.PermissionLevel = OperatorElement::PHYKEY;
    myOperator.CreatedDate = QDateTime::currentDateTime().toTime_t();
    m_operatorAdaptor->InsertRecordIntoTable(&myOperator);
    setModelList();
}

bool OperatorModel::login(QString passwd, OperatorElement *operatot)
{
    QMap<int,QString>::iterator it; //遍历map
    OperatorElement myOperator;
    for ( it = operators->begin(); it != operators->end(); ++it ) {
        m_operatorAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myOperator);
        qDebug() << it.key() << it.value() << myOperator.Password;
        if (myOperator.Password == passwd) {
            operatot->RevCode = myOperator.RevCode;
            operatot->OperatorID = myOperator.OperatorID;
            operatot->OperatorName = myOperator.OperatorName;
            operatot->CreatedDate = myOperator.CreatedDate;
            operatot->Password = myOperator.Password;
            operatot->PermissionLevel = myOperator.PermissionLevel;
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

void OperatorModel::updateOperator(int id, QString name, QString passwd, int level)
{
    OperatorElement myOperator;
    m_operatorAdaptor->QueryOneRecordFromTable(id,&myOperator);
    myOperator.OperatorName = name;
    myOperator.Password = passwd;
    if (level == 1)
        myOperator.PermissionLevel = OperatorElement::LEVEL1;
    else if (level == 2)
        myOperator.PermissionLevel = OperatorElement::LEVEL2;
    else if (level == 3)
        myOperator.PermissionLevel = OperatorElement::LEVEL3;
    else if (level == 4)
        myOperator.PermissionLevel = OperatorElement::LEVEL4;
    else if (level == 0)
        myOperator.PermissionLevel = OperatorElement::PHYKEY;
    m_operatorAdaptor->UpdateRecordIntoTable(&myOperator);
    setModelList();
}

int OperatorModel::columnCount(const QModelIndex &parent) const
{
    UNUSED(parent);
    return 1;
}

QVariant OperatorModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    UNUSED(section);
    UNUSED(orientation);
    UNUSED(role);
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
    UNUSED(orderId);
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
    int level = myOperator.PermissionLevel;
    permissionSetting->_Recall();
    OperatorModelHash.insert("count",(int)myOperator.PermissionLevel);

//    OperatorModelHash.insert("count",permissionSetting->FourLevelIdentifier.at(level-1));//myOperator.PermissionLevel;
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
    m_spliceAdaptor = DBPresetTable::Instance();
    m_weldHistoryAdaptor = DBWeldResultTable::Instance();
    alarms = new QMap<int, QString>();
    variantToString = VariantToString::Instance();
}

QList<int> AlarmModel::getPoint()
{
//    QString pointStr = "0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	20	20	20	40	60	60	60	80	80	100	100	120	120	140	160	160	160	180	180	200	220	220	240	260	280	300	300	320	340	340	380	400	420	440	460	480	480	500	520	520	540	540	560	560	580	580	580	580	580	580	580	580	580	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	580	580	580	580	580	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	600	580	580	580	580	580	580	600	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	600	600	600	600	600	600	600	600	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	600	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	580	560	560	560	560	560	580	580	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	540	540	540	540	540	540	540	540	540	540	540	540	540	540	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	560	540	540	540	540	540	540	540	540	540	540	540	540	540	540	540	540	520	520	520	520	520	520	520	520	520	540	540	540	540	540	540	540	520	520	520	520	520	520	520	540	540	540	540	540	540	540	540	520	520	540	0";
//    char s = '\t';
//    QString temp;
//    bool ok;
//    QStringList list = pointStr.split(s);
//    QList<int> pointList;
//    for (int i = 0; i < list.count(); i++)
//    {
//        temp = list[i];
//        pointList.append(temp.toInt(&ok, 10));
//    }
    QList<int> pointList;
    pointList = weldResultElement.PowerGraph;
    return pointList;
}

QList<int> AlarmModel::getPoint2()
{
    QList<int> pointList;
    pointList = weldResultElement.PostHeightGraph;
    return pointList;
}

QList<int> AlarmModel::getPointList(QString key, QString spliceName, uint hashCode)
{
    QMap<int, QString> *tempMap = new QMap<int, QString>();
    QMap<int,QString>::iterator it; //遍历map

    WeldResultElement  temp;
    bool reb;
    QList<int> list;
    reb = m_weldHistoryAdaptor->QueryBySomeFields(spliceName,hashCode,startTime.toTime_t(),QDateTime::currentDateTime().toTime_t(),tempMap);
    qDebug() << "getPointList" << spliceName << hashCode << startTime.toString("hh:mm:ss") << reb << tempMap->count();
    if (reb)
    {
        if (key == "Time") {
            for ( it = tempMap->begin(); it != tempMap->end(); ++it ) {
                m_weldHistoryAdaptor->QueryOneRecordFromTable(it.key(),&temp);
                list.append(temp.ActualResult.ActualTime);
            }
        }
        else if (key == "Power") {
            for ( it = tempMap->begin(); it != tempMap->end(); ++it ) {
                m_weldHistoryAdaptor->QueryOneRecordFromTable(it.key(),&temp);
                list.append(temp.ActualResult.ActualPeakPower);
            }
        }
        else if (key == "Pre-Height") {
            for ( it = tempMap->begin(); it != tempMap->end(); ++it ) {
                m_weldHistoryAdaptor->QueryOneRecordFromTable(it.key(),&temp);
                list.append(temp.ActualResult.ActualPreheight);
            }
        }
        else if (key == "Post-Height") {
            for ( it = tempMap->begin(); it != tempMap->end(); ++it ) {
                m_weldHistoryAdaptor->QueryOneRecordFromTable(it.key(),&temp);
                list.append(temp.ActualResult.ActualPostheight);
            }
        }
    }
    return list;
}

int AlarmModel::getAxes(QString key)
{
    int iResult = -1;
    if (key == "Time")
        iResult = weldResultElement.ActualResult.ActualTime;
    else if (key == "Power")
        iResult = weldResultElement.ActualResult.ActualPeakPower;
    else if (key == "Pre-Height")
        iResult = weldResultElement.ActualResult.ActualPreheight;
    else if (key == "Post-Height")
        iResult = weldResultElement.ActualResult.ActualPostheight;
    return iResult;
}

QString AlarmModel::getAxes2(QString key)
{
    QString iResult = "";
    if (key == "Time")
        iResult = variantToString->ActualTimeToString(weldResultElement.ActualResult.ActualTime);
    else if (key == "Power")
        iResult = variantToString->ActualPowerToString(weldResultElement.ActualResult.ActualPeakPower);
    else if (key == "Pre-Height")
        iResult = variantToString->ActualPreHeightToString(weldResultElement.ActualResult.ActualPreheight);
    else if (key == "Post-Height")
        iResult = variantToString->ActualHeightToString(weldResultElement.ActualResult.ActualPostheight);

    else if (key == "Energy")
        iResult = variantToString->EnergyToString(weldResultElement.ActualResult.ActualEnergy).Current;
    else if (key == "T.Pressure")
        iResult = variantToString->TriggerPressureToString(weldResultElement.ActualResult.ActualTPressure).Current;
    else if (key == "W.Pressure")
        iResult = variantToString->WeldPressureToString(weldResultElement.ActualResult.ActualPressure).Current;
    else if (key == "Amplitude")
        iResult = variantToString->AmplitudeToString(weldResultElement.ActualResult.ActualAmplitude).Current;
    else if (key == "Width")
        iResult = variantToString->WidthToString(weldResultElement.ActualResult.ActualWidth).Current;

    return iResult;
}

void AlarmModel::setStartTime()
{
    startTime = QDateTime::currentDateTime();
}

void AlarmModel::editNew(int weldId, QString weldName)
{
    bool reb;
    UNUSED(reb);
    if(weldName.isEmpty() == true)
        reb = m_weldHistoryAdaptor->QueryOneRecordWithGraph(weldId, &weldResultElement);
    else
        reb = m_weldHistoryAdaptor->QueryOneRecordWithGraph(weldId,weldName,&weldResultElement);
    qDebug() << "editNew" << weldId << weldName << reb << weldResultElement.PowerGraph;
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
        UNUSED(rowId);
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
        PresetElement splice;

        m_alarmAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myAlarm);
        m_spliceAdaptor->QueryOneRecordFromTable(myAlarm.SpliceID,&splice);
        QString temp;
        if (columnIdx == 0)
            value = QVariant::fromValue(myAlarm.AlarmID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(QDateTime::fromTime_t(myAlarm.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 2) {
            temp = myAlarm.AlarmType;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 3) {
            temp = variantToString->AlarmLevelToString(myAlarm.AlarmType);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 4)
            value = QVariant::fromValue(myAlarm.AlarmMsg);
        else if (columnIdx == 5) {
            value = QVariant::fromValue(splice.SpliceName);
        }
    }
    return value;
}

void AlarmModel::setModelList(QString name, unsigned int time_from, unsigned int time_to)
{
    beginResetModel();
    alarms->clear();
    if (m_alarmAdaptor->QueryUseNameAndTime(name,time_from,time_to,alarms))
        qDebug( )<< "AlarmModel " << alarms->count();
    endResetModel();
    getAlarmbIsShowFlag();
}

void AlarmModel::setModelList(unsigned int time_from, unsigned int time_to)
{
    beginResetModel();
    alarms->clear();
    if (m_alarmAdaptor->QueryOnlyUseTime(time_from,time_to,alarms))
        qDebug( )<< "AlarmModel " << alarms->count();
    endResetModel();
    getAlarmbIsShowFlag();
}

void AlarmModel::setModelList(bool bIsNeedReset)
{
    beginResetModel();
    alarms->clear();
    if (bIsNeedReset) {
        m_alarmAdaptor->QueryOnlyUseField("IsReseted",QVariant(false),alarms);
    } else {
        m_alarmAdaptor->QueryEntireTable(alarms);
    }
    qDebug( )<< "AlarmModel" << alarms->count()<<bIsNeedReset;
    endResetModel();
    getAlarmbIsShowFlag();
}

void AlarmModel::searchAlarmLog(QString name, unsigned int time_from, unsigned int time_to)
{
    if (name == "All") {
        setModelList(time_from,time_to);
    } else {
        setModelList(name,time_from,time_to);
    }
}

int AlarmModel::rowCount(const QModelIndex & parent) const
{
    UNUSED(parent);
    return alarms->count();
}


int AlarmModel::count()
{
    return alarms->count();
}


int AlarmModel::columnCount(const QModelIndex &parent) const
{
    UNUSED(parent);
    return 1;
}

QVariant AlarmModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
    UNUSED(section);
    UNUSED(orientation);
    UNUSED(role);
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
    UNUSED(orderId);
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
    m_spliceAdaptor->QueryOneRecordFromTable(myAlarm.SpliceID,&m_splice);
    QHash<QString, QVariant> AlarmModelHash;
    AlarmModelHash.insert("AlarmId",myAlarm.AlarmID);
    AlarmModelHash.insert("CreatedDate",QDateTime::fromTime_t(myAlarm.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    AlarmModelHash.insert("Alarm/ErrorType",myAlarm.AlarmType);
    AlarmModelHash.insert("Alarm/ErrorLevel",variantToString->AlarmLevelToString(myAlarm.AlarmType));
    AlarmModelHash.insert("Message",myAlarm.AlarmMsg);//myOperator.PermissionLevel;
    AlarmModelHash.insert("SpliceName",m_splice.SpliceName);//myOperator.PermissionLevel;

    if (key == "") {
        return AlarmModelHash;
    } else {
        return AlarmModelHash.value(key);
    }
}

void AlarmModel::removeValue(int id, QString name)
{
    m_alarmAdaptor->DeleteOneRecordFromTable(id,name);
    setModelList(false);
}

void AlarmModel::updateAlarmLog(int id)
{
    AlarmIcon *alarmIcon = AlarmIcon::Instance();
    alarmIcon->ResetAlarmItem(id);
    setModelList(false);
}

void AlarmModel::getAlarmbIsShowFlag()
{
    QMap<int, QString> tempalarms;
    m_alarmAdaptor->QueryOnlyUseField("IsReseted",QVariant(false),&tempalarms);
    if (tempalarms.count()) {
        emit signalShowFlag(true);
    } else {
        emit signalShowFlag(false);
    }
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
        UNUSED(rowId);
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
        qDebug() << "m_weldHistoryAdaptor" << QDateTime::currentDateTime().toTime_t();
        m_weldHistoryAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myHistory);
        PresetElement presetElement;
        m_spliceTable->QueryOneRecordFromTable(myHistory.CurrentSplice.PartID,myHistory.CurrentSplice.PartName,&presetElement);
        qDebug() << "m_spliceTable" << QDateTime::currentDateTime().toTime_t();

//        list << "WeldHistoryId" << "SpliceName" << "SequenceName" << "HarnessName" << "OperatorName" << "DateCreated" << "OperateMode" << "Alarm"
//             << "CrossSection" << "WeldMode" << "Energy" << "TriggerPressure" << "WeldPressure" << "Amplitude" << "Width"
//             << "Time+" << "Timer-" << "Time" << "Power+" << "Power-" << "Power" << "Pre-Height+" << "Pre-Height-"
//             << "Pre-Height" << "Height+" << "Height-" << "Height" << "SampleRatio" <<"GraphData";


        QString temp;
        if (columnIdx == 0)
            value = QVariant::fromValue(myHistory.WeldResultID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(myHistory.CurrentSplice.PartName);
        else if (columnIdx == 2)
            value = QVariant::fromValue(myHistory.CurrentSequence.SequenceName);
        else if (columnIdx == 3)
            value = QVariant::fromValue(myHistory.CurrentHarness.HarnessName);
        else if (columnIdx == 4)
            value = QVariant::fromValue(myHistory.OperatorName);
        else if (columnIdx == 5)
            value = QVariant::fromValue(QDateTime::fromTime_t(myHistory.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 6)
            value = QVariant::fromValue(myHistory.OperateMode);
        else if (columnIdx == 7) {
                    temp = variantToString->AlarmTypeToString((ALARMTYPE)myHistory.ActualResult.ActualAlarmflags);
                    value = QVariant::fromValue(temp);
        }
        else if (columnIdx == 8)
            value = QVariant::fromValue(variantToString->CrossSectionToString(presetElement.CrossSection));
        else if (columnIdx == 9)
            value = QVariant::fromValue(variantToString->WeldModeToString(presetElement.WeldSettings.AdvanceSetting.WeldMode,presetElement.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode));
        else if (columnIdx == 10) {
            temp = variantToString->EnergyToString(myHistory.ActualResult.ActualEnergy).Current;
            value = QVariant::fromValue(temp);
        }
        else if (columnIdx == 11) {
            temp = variantToString->TriggerPressureToString(myHistory.ActualResult.ActualTPressure).Current;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 12) {
            temp = variantToString->WeldPressureToString(myHistory.ActualResult.ActualPressure).Current;
            value = QVariant::fromValue(temp);
        }
        else if (columnIdx == 13) {
            temp = variantToString->AmplitudeToString(myHistory.ActualResult.ActualAmplitude).Current;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 14) {
            temp = variantToString->WidthToString(myHistory.ActualResult.ActualWidth).Current;
            value = QVariant::fromValue(temp);
        }
        else if (columnIdx == 15) {
            temp = variantToString->Time_PlusToString(presetElement.WeldSettings.QualitySetting.Time.Plus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 16) {
            temp = variantToString->Time_MinusToString(presetElement.WeldSettings.QualitySetting.Time.Minus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 17) {
            temp = variantToString->ActualTimeToString(myHistory.ActualResult.ActualTime);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 18) {
            temp = variantToString->Power_PlusToString(presetElement.WeldSettings.QualitySetting.Power.Plus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 19) {
            temp = variantToString->Power_MinusToString(presetElement.WeldSettings.QualitySetting.Power.Minus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 20) {
            temp = variantToString->ActualPowerToString(myHistory.ActualResult.ActualPeakPower);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 21) {
            temp = variantToString->PreHeight_PlusToString(presetElement.WeldSettings.QualitySetting.Preheight.Plus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 22) {
            temp = variantToString->PreHeight_MinusToString(presetElement.WeldSettings.QualitySetting.Preheight.Minus);
            value = QVariant::fromValue(myHistory.ActualResult.ActualPreheight);
        } else if (columnIdx == 23) {
            temp = variantToString->ActualPreHeightToString(myHistory.ActualResult.ActualPreheight);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 24) {
            temp = variantToString->Height_PlusToString(presetElement.WeldSettings.QualitySetting.Height.Plus);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 25) {
            temp = variantToString->Height_MinusToString(presetElement.WeldSettings.QualitySetting.Height.Minus);
            value = QVariant::fromValue(myHistory.ActualResult.ActualPostheight);
        } else if (columnIdx == 26) {
            temp = variantToString->ActualHeightToString(myHistory.ActualResult.ActualPostheight);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 27) {
            temp = variantToString->SampleRatioToString(myHistory.SampleRatio);
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 28) {
            temp = "GraphData";
            value = QVariant::fromValue(temp);
        }
        qDebug() << "m_spliceTable" << QDateTime::currentDateTime().toTime_t();

    }
    return value;
}

void WeldHistoryModel::setModelList(unsigned int time_from, unsigned int time_to)
{
    beginResetModel();
    historys->clear();
    if (m_weldHistoryAdaptor->QueryOnlyUseTime(time_from,time_to,historys))
        qDebug( )<< "WeldHistoryModel 3" << historys->count();
    endResetModel();
}

void WeldHistoryModel::setModelList(QString WorkOrderName, QString PartName, QString SpliceName,
                                    unsigned int time_from, unsigned int time_to,
                                    enum FieldType OrderField, bool Orderby)
{
    beginResetModel();
    historys->clear();
    if (m_weldHistoryAdaptor->QueryBySomeFields(historys,WorkOrderName,PartName,SpliceName,time_from,time_to,OrderField,Orderby))
        qDebug( )<< "WeldHistoryModel 2" << historys->count();
    endResetModel();
}

void WeldHistoryModel::setModelList()
{
    beginResetModel();
    historys->clear();
    if (m_weldHistoryAdaptor->QueryEntireTable(historys))
        qDebug( )<< "WeldHistoryModel 1" << historys->count();
    endResetModel();
}


int WeldHistoryModel::rowCount(const QModelIndex & parent) const
{
    UNUSED(parent);
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
    UNUSED(parent);
    return 1;
}

QVariant WeldHistoryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    UNUSED(section);
    UNUSED(orientation);
    UNUSED(role);
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

void WeldHistoryModel::weldResultSearch(QString WorkOrderName, QString PartName, QString SpliceName, unsigned int time_from, unsigned int time_to, FieldType OrderField, bool Orderby)
{
    QString workOrderName,partName,spliceName;
    if (WorkOrderName != "All")
        workOrderName = WorkOrderName;
    if (PartName != "All")
        partName = PartName;
    if (SpliceName != "All")
        spliceName = SpliceName;
    qDebug()<<"weldResultSearch"<<WorkOrderName<<PartName<<SpliceName;
    setModelList(workOrderName,partName,spliceName,time_from,time_to,OrderField,Orderby);
}

QVariant WeldHistoryModel::getValue(int index, QString key)
{
    int orderId;


    orderId = historys->keys().at(index);
    WeldResultElement myHistory;
    PresetElement presetElement;
    if (!historyList.contains(index)) {
        if(historys->value(orderId).isEmpty() == true)
            m_weldHistoryAdaptor->QueryOneRecordFromTable(orderId, &myHistory);
        else
            m_weldHistoryAdaptor->QueryOneRecordFromTable(orderId,historys->value(orderId),&myHistory);
        historyList.insert(index,myHistory);
    } else {
        myHistory = historyList.value(index);
    }
    if (!presetList.contains(index)) {
        m_spliceTable->QueryOneRecordFromTable(myHistory.CurrentSplice.PartID,myHistory.CurrentSplice.PartName,&presetElement);
        presetList.insert(index,presetElement);
    } else {
        presetElement = presetList.value(index);
    }
    QHash<QString, QVariant> WeldHistoryModelHash;
    WeldHistoryModelHash.insert("WeldHistoryId",myHistory.WeldResultID);
    WeldHistoryModelHash.insert("SpliceName",myHistory.CurrentSplice.PartName);
    WeldHistoryModelHash.insert("SequenceName",myHistory.CurrentSequence.SequenceName);
    WeldHistoryModelHash.insert("HarnessName",myHistory.CurrentHarness.HarnessName);
    WeldHistoryModelHash.insert("OperatorName",myHistory.OperatorName);
    WeldHistoryModelHash.insert("OperateMode",myHistory.OperateMode);
    WeldHistoryModelHash.insert("DateCreated",QDateTime::fromTime_t(myHistory.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    WeldHistoryModelHash.insert("CrossSection",variantToString->CrossSectionToString(presetElement.CrossSection)); //contain in splice
    WeldHistoryModelHash.insert("WeldMode",variantToString->WeldModeToString(presetElement.WeldSettings.AdvanceSetting.WeldMode,presetElement.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode));     //contain in splice
    WeldHistoryModelHash.insert("Energy",variantToString->EnergyToString(myHistory.ActualResult.ActualEnergy).Current);
    WeldHistoryModelHash.insert("Amplitude",variantToString->AmplitudeToString(myHistory.ActualResult.ActualAmplitude).Current);
    WeldHistoryModelHash.insert("Width",variantToString->WidthToString(myHistory.ActualResult.ActualWidth).Current);
    WeldHistoryModelHash.insert("TriggerPressure",variantToString->TriggerPressureToString(myHistory.ActualResult.ActualTPressure).Current);
    WeldHistoryModelHash.insert("Weld Pressure",variantToString->WeldPressureToString(myHistory.ActualResult.ActualPressure).Current);
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
    WeldHistoryModelHash.insert("AlarmType",variantToString->AlarmTypeToString((ALARMTYPE)myHistory.ActualResult.ActualAlarmflags)); //myHistory.ActualResult.ActualAlarmflags
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
    m_WireDataObj = CSVWireData::Instance();
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
        UNUSED(rowId);
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
        else if (columnIdx == 5) {
            if (myWire.Stripe.TypeOfStripe == 0) {
                temp = "Horizontal";
            } else if (myWire.Stripe.TypeOfStripe == 1) {
                temp = "Slash";
            } else if (myWire.Stripe.TypeOfStripe == 2) {
                temp = "Vertical";
            } else {
                temp = "None";
            }
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 6)
            value = QVariant::fromValue(myWire.Stripe.Color);
        else if (columnIdx == 7) {
            temp = variantToString->GaugeToString(myWire.Gauge,myWire.GaugeAWG).Current;
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 8) {
            if (myWire.TypeOfWire == 0) {
                temp = "Copper";
            } else {
                temp = "Aluminum";
            }
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 9) {
            if (myWire.Side == 0) {
                temp = "Left";
            } else {
                temp = "Right";
            }
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 10) {
            if (myWire.VerticalSide == 0) {
                temp = "Basic";
            } else {
                temp = "Advance";
            }
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 11) {
            if (myWire.Position == 0) {
                temp = "Top";
            } else if (myWire.Position == 1) {
                temp = "Middle";
            } else {
                temp = "Bottom";
            }
            value = QVariant::fromValue(temp);
        }

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

void WireModel::setTemplateModelList()
{
    beginResetModel();
    wires->clear();
    if (m_wireAdaptor->QueryOnlyUseField("SpliceID","-1",wires))
        qDebug( )<< "setTemplateModelList " << wires->count();
    endResetModel();
}

QString WireModel::getWireName(int wireId)
{
    WireElement myWire;
    m_wireAdaptor->QueryOneRecordFromTable(wireId,&myWire);
    return myWire.WireName;
}

void WireModel::setModelList()
{
    beginResetModel();
    wires->clear();
    qDebug( )<< "WireModel";
    if (m_wireAdaptor->QueryEntireTable(wires))
        qDebug( )<< "WireModel" << wires->count();
    endResetModel();
}

int WireModel::rowCount(const QModelIndex & parent) const
{
    UNUSED(parent);
    return wires->count();
}

int WireModel::count()
{
    return wires->count();
}

void WireModel::removeValue(int id, QString name)
{
    m_wireAdaptor->DeleteOneRecordFromTable(id,name);
    setTemplateModelList();
}
int WireModel::insertValueToTable(QString type,QString wireName,int wireId,int operatorId,QString color,QString stripeColor,int stripeType,int gauge, int awgGauge,int wireType,int side,int verside,int position,QString moduleType)
{

//    QString WireName;
//    int     WireID;
//    unsigned int CreatedDate;
//    int OperatorID;

//    QString Color;
//    struct STRIPE Stripe;
//    int Gauge;               //Area of Wire in mm*mm/100
//    int GaugeAWG;
//    enum MetalType TypeOfWire;
//    enum HorizontalLocation Side;
//    enum VerticalLocation VerticalSide;
//    enum VerticalPosition Position;
//    int a,b;
    int insertWireId;
    WireElement insertWire;
    insertWire.WireName = wireName;
    insertWire.WireID = wireId;
    insertWire.OperatorID = operatorId;
    insertWire.Color = color;
    insertWire.Stripe.Color = stripeColor;
    insertWire.Stripe.TypeOfStripe = (STRIPE::StripeType)stripeType;
    insertWire.GaugeAWG = awgGauge;
    insertWire.Gauge = gauge;
    insertWire.TypeOfWire = (WireElement::MetalType)wireType;
    insertWire.Side = (WireElement::HorizontalLocation)side;
    insertWire.VerticalSide = (WireElement::VerticalLocation)verside;
    insertWire.Position = (WireElement::VerticalPosition)position;
    insertWire.SpliceID = -1;
    if (moduleType == "n/a")
        insertWire.TypeOfModule = WireElement::ModuleType::NA;
    else if (moduleType == "DIN")
        insertWire.TypeOfModule = WireElement::ModuleType::DIN;
    else if (moduleType == "ISO")
        insertWire.TypeOfModule = WireElement::ModuleType::ISO;
    else if (moduleType == "SAE")
        insertWire.TypeOfModule = WireElement::ModuleType::SAE;
    else if (moduleType == "JIS")
        insertWire.TypeOfModule = WireElement::ModuleType::JIS;

    if (type == "insert"){
        insertWireId = m_wireAdaptor->InsertRecordIntoTable(&insertWire);
        setModelList();
        return insertWireId;
    }
    else if (type == "update") {
        WireElement wireTemp;
        m_wireAdaptor->QueryOneRecordFromTable(wireId,&wireTemp);
        if (wireTemp == insertWire) {
            return wireId;
        }
        else
        {
            insertWire.SpliceID = wireTemp.SpliceID;
            bool reb = m_wireAdaptor->UpdateRecordIntoTable(&insertWire);
            if (reb) {
                setTemplateModelList();
                return wireId;
            }
            return -1;
        }
    }
    return -1;
}

void WireModel::updateSpliceIdToWire(QList<int> wireList, int spliceId)
{
    if (spliceId == -1)
        return;
    WireElement temp;
    for (int i = 0; i < wireList.count(); i++)
    {
        if (m_wireAdaptor->QueryOneRecordFromTable(wireList[i], &temp))
        {
            temp.SpliceID = spliceId;
            m_wireAdaptor->UpdateRecordIntoTable(&temp);
        }
    }
}

void WireModel::createNew()
{
    WireElement temp;
    wireElement = temp;
}

void WireModel::addFromLibrary(int wireId)
{
    WireElement temp;
    m_wireAdaptor->QueryOneRecordFromTable(wireId,&temp);
    wireElement = temp;
}

QVariant WireModel::getStructValue(QString key)
{
    QHash<QString, QVariant> WireModelHash;
    int awg,gauge;
    QString value = variantToString->GaugeToString(wireElement.Gauge, wireElement.GaugeAWG).Current;
    stringToVariant->GaugeToInt(value,awg,gauge);
    WireModelHash.insert("Gauge",gauge);
    WireModelHash.insert("AWG",awg);
    int metalType;
    if (wireElement.TypeOfWire == 0) {
        metalType = 0;
    } else {
        metalType = 1;
    }
    QString moduleString;
    if (wireElement.TypeOfModule == WireElement::NA)
        moduleString = "n/a";
    else if (wireElement.TypeOfModule == WireElement::DIN)
        moduleString = "DIN";
    else if (wireElement.TypeOfModule == WireElement::SAE)
        moduleString = "SAE";
    else if (wireElement.TypeOfModule == WireElement::ISO)
        moduleString = "ISO";
    else if (wireElement.TypeOfModule == WireElement::JIS)
        moduleString = "JIS";
    WireModelHash.insert("WireType",metalType);
    WireModelHash.insert("WireColor",wireElement.Color);
    WireModelHash.insert("WireName",wireElement.WireName);
    WireModelHash.insert("WireDirection",(int)wireElement.Side);
    WireModelHash.insert("WirePosition",(int)wireElement.Position);
    WireModelHash.insert("WireBasic",(int)wireElement.VerticalSide);
    WireModelHash.insert("WireId",wireElement.WireID);
    WireModelHash.insert("ModuleType",moduleString);
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
    QString ResultStr = "";
    if (key == "Gauge"){
        if (type == "current")
            ResultStr = variantToString->GaugeToString(wireElement.Gauge,wireElement.GaugeAWG).Current;
        else if (type == "max")
            ResultStr = variantToString->GaugeToString(wireElement.Gauge,wireElement.GaugeAWG).Maximum;
        else if (type == "min")
            ResultStr = variantToString->GaugeToString(wireElement.Gauge,wireElement.GaugeAWG).Minimum;
    }
    else if (key == "StripeColor") {
        ResultStr = wireElement.Stripe.Color;
    }
    return ResultStr;
}

int WireModel::getStructValue3(QString key, QString value)
{
    int gauge,awg, iResult = -1;
    if (key == "Gauge"){
        stringToVariant->GaugeToInt(value,awg,gauge);
        iResult = gauge;
    }
    else if (key == "awg") {
        stringToVariant->GaugeToInt(value,awg,gauge);
        iResult = awg;
    }
    else if (key == "StripeType")
        iResult = (int)wireElement.Stripe.TypeOfStripe;
    else
        iResult = -1;
    return iResult;
}

QString WireModel::getStructValue4(int gauge, int awg)
{
    return variantToString->GaugeToString(gauge,awg).Current;
}

int WireModel::searchIndexByName(QString name)
{
    QMap<int,QString>::iterator it; //遍历map
    int i = 0;
    for ( it = wires->begin(); it != wires->end(); ++it ) {
        if (name == it.value())
            return i;
        i++;

    }
    return -1;
}

bool WireModel::exportData(int wireId, QString fileUrl)
{
    return m_WireDataObj->ExportData(wireId,fileUrl);
}

int WireModel::importData(QString filePath)
{
    int wireId;
    wireId =  m_WireDataObj->ImportData(filePath);
    setModelList();
    return wireId;
}

int WireModel::columnCount(const QModelIndex &parent) const
{
    UNUSED(parent);
    return 1;
}

QVariant WireModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    UNUSED(section);
    UNUSED(orientation);
    UNUSED(role);
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
//    QMap<int,QString>::iterator it; //遍历map
//    int i = 0;
//    int orderId;
//    UNUSED(orderId);
//    for ( it = wires->begin(); it != wires->end(); ++it ) {
//        if (i == index){
//            orderId = it.key();
//            break;
//        }
//        else {
//            i++;
//        }
//    }

//    WireElement myWire;
//    OperatorElement myOperator;
    QList<int> rowList;
    rowList = wires->keys();
    if (myWire.WireID != rowList[index])
    {
        m_wireAdaptor->QueryOneRecordFromTable(rowList[index],wires->value(rowList[index]),&myWire);
        m_operatorAdaptor->QueryOneRecordFromTable(myWire.OperatorID,&myOperator);
    }
    QString temp;
    //    list <<"WireId" << "WireName" << "DateCreated" << "OperatorName" << "Color" << "StripeType" << "StripeColor" << "Gauge" << "MetalType" << "HorizontalLocation" << "VerticalLocation" << "VerticalPosition";
    QHash<QString, QVariant> WireModelHash;
    WireModelHash.insert("WireId",myWire.WireID);
    WireModelHash.insert("WireName",myWire.WireName);
    WireModelHash.insert("DateCreated",QDateTime::fromTime_t(myWire.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    WireModelHash.insert("OperatorName",myOperator.OperatorName);
    WireModelHash.insert("Color",myWire.Color);
    if (myWire.Stripe.TypeOfStripe == 0) {
        temp = "Horizontal";
    } else if (myWire.Stripe.TypeOfStripe == 1) {
        temp = "Slash";
    } else if (myWire.Stripe.TypeOfStripe == 2) {
        temp = "Vertical";
    } else {
        temp = "None";
    }

    WireModelHash.insert("StripeType",temp);
    WireModelHash.insert("StripeColor",myWire.Stripe.Color);
    WireModelHash.insert("Gauge",myWire.Gauge);
    if (myWire.TypeOfWire == 0) {
        temp = "Copper";
    } else {
        temp = "Aluminum";
    }
    WireModelHash.insert("MetalType",temp);
    if (myWire.Side == 0) {
        temp = "Left";
    } else {
        temp = "Right";
    }
    WireModelHash.insert("HorizontalLocation",temp);
    if (myWire.VerticalSide == 0) {
        temp = "Basic";
    } else {
        temp = "Advance";
    }
    WireModelHash.insert("VerticalLocation",temp);
    if (myWire.Position == 0) {
        temp = "Top";
    } else if (myWire.Position == 1) {
        temp = "Middle";
    } else {
        temp = "Bottom";
    }
    WireModelHash.insert("VerticalPosition",temp);
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
        UNUSED(rowId);
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

void MaintenanceLogModel::setModelList(QString Name, unsigned int time_from, unsigned int time_to)
{
    beginResetModel();
    logs->clear();
    if (m_maintenanceLogAdaptor->QueryUseNameAndTime(Name,time_from,time_to,logs))
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
    UNUSED(parent);
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
    UNUSED(parent);
    return 1;
}

QVariant MaintenanceLogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    UNUSED(section);
    UNUSED(orientation);
    UNUSED(role);
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
    qDebug() << "MaintenanceLogModel" << index << key;
    QMap<int,QString>::iterator it; //遍历map
    int i = 0;
    int orderId;
    UNUSED(orderId);
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
void MaintenanceLogModel::searchMaintenanceLog(QString Name, unsigned int time_from, unsigned int time_to)
{
    if (Name == "All")
        setModelList(time_from,time_to);
    else
        setModelList(Name,time_from,time_to);
}
/********************************** SequenceModel **********************/
SequenceModel::SequenceModel(QObject *parent)
{
    m_operatorAdaptor = DBOperatorTable::Instance();
    m_sequenceAdaptor = DBSequenceTable::Instance();
    sequences = new QMap<int, QString>();
}

void SequenceModel::setModelList(unsigned int time_from, unsigned int time_to)
{
    beginResetModel();
    sequences->clear();
    m_sequenceAdaptor->QueryOnlyUseTime(time_from,time_to,sequences);
    endResetModel();
}

void SequenceModel::setModelList()
{
    beginResetModel();
    sequences->clear();
    if (m_sequenceAdaptor->QueryEntireTable(sequences))
        qDebug( )<< "SequenceModel" << sequences->count();
    endResetModel();
}

int SequenceModel::rowCount(const QModelIndex &parent) const
{
    UNUSED(parent);
    return sequences->count();
}

int SequenceModel::columnCount(const QModelIndex &parent) const
{
    UNUSED(parent);
    return 1;
}

QVariant SequenceModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if(role < Qt::UserRole)
    {
        qDebug() << "SequenceModel::data(const QModelIndex &index, int role) const";
    }
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        int rowId;
        UNUSED(rowId);
        QMap<int,QString>::iterator it; //遍历map
        int i = 0;
        for ( it = sequences->begin(); it != sequences->end(); ++it ) {
            if (i == index.row()){
                rowId = it.key();
                break;
            }
            else {
                i++;
            }
        }

        SequenceElement mySequence;
        m_sequenceAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&mySequence);
        OperatorElement myOperator;
        m_operatorAdaptor->QueryOneRecordFromTable(mySequence.OperatorID,&myOperator);

        if (columnIdx == 0)
            value = QVariant::fromValue(mySequence.SequenceID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(mySequence.SequenceName);
        else if (columnIdx == 2)
            value = QVariant::fromValue(QDateTime::fromTime_t(mySequence.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 3)
            value = QVariant::fromValue(myOperator.OperatorName);
        else if (columnIdx == 4)
            value = QVariant::fromValue(mySequence.NoOfSplice);
        else if (columnIdx == 5) {
            int count;
            count = 0;
            for (int i = 0; i< mySequence.SpliceList.count(); i++)
            {
                count = count + mySequence.SpliceList[i].Quantity;
            }
            value = QVariant::fromValue(count);
        }
    }
    return value;
}

QVariant SequenceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    UNUSED(section);
    UNUSED(orientation);
    UNUSED(role);
    return QVariant();
}

QHash<int, QByteArray> SequenceModel::roleNames() const
{
    return m_roleNames;
}

void SequenceModel::setRoles(const QStringList &names)
{
    m_roleNames.clear();
    for(int idx=0; idx<names.count(); idx++)
    {
        m_roleNames[Qt::UserRole + idx + 1] = names[idx].toLocal8Bit();
    }
}

QVariant SequenceModel::getValue(int index, QString key)
{
    qDebug() << "SequenceModel" << index << key;
    QMap<int,QString>::iterator it; //遍历map
    int i = 0;
    int orderId;
    UNUSED(orderId);
    for ( it = sequences->begin(); it != sequences->end(); ++it ) {
        if (i == index){
            orderId = it.key();
            break;
        }
        else {
            i++;
        }
    }
    SequenceElement mySequence;
    m_sequenceAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&mySequence);

    QHash<QString, QVariant> SequenceModelHash;
    SequenceModelHash.insert("SequenceId",mySequence.SequenceID);
    SequenceModelHash.insert("SequenceName",mySequence.SequenceName);
    SequenceModelHash.insert("DateCreated",QDateTime::fromTime_t(mySequence.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    SequenceModelHash.insert("OperatorName",mySequence.OperatorID);
    SequenceModelHash.insert("TotalSplices",mySequence.SpliceList.count());

    int quantity;
    quantity = 0;
    for (int i = 0;i < mySequence.SpliceList.count();i++)
    {
        quantity = mySequence.SpliceList[i].Quantity + quantity;
    }
    SequenceModelHash.insert("QUANTITY",quantity);

    if (key == "") {
        return SequenceModelHash;
    } else {
        return SequenceModelHash.value(key);
    }
}

void SequenceModel::removeValue(int id, QString name)
{
    m_sequenceAdaptor->DeleteOneRecordFromTable(id,name);
    setModelList();
}

QList<int> SequenceModel::getSpliceList()
{
    QMap<int,struct SEQUENCEATTRIBUTE>::iterator it; //遍历map
    QList<int> list;
    for ( it = sequenceElement.SpliceList.begin(); it != sequenceElement.SpliceList.end(); ++it ) {
        list.append(it.value().SpliceID);
    }
    return list;
}

int SequenceModel::getSpliceQty(int spliceId)
{

    QMap<int,struct SEQUENCEATTRIBUTE>::iterator it; //遍历map
    int qty;
    for ( it = sequenceElement.SpliceList.begin(); it != sequenceElement.SpliceList.end(); ++it ) {
        if (it.value().SpliceID == spliceId)
            qty = it.value().Quantity;
    }
    qDebug() << "getSpliceQty" << spliceId << qty;
    return qty;
}

void SequenceModel::reSetSpliceCount(int spliceId, int qty)
{
    QMap<int,struct SEQUENCEATTRIBUTE>::iterator it; //遍历map
    for ( it = sequenceElement.SpliceList.begin(); it != sequenceElement.SpliceList.end(); ++it ) {
        if (it.value().SpliceID == spliceId)
            it.value().Quantity = qty;
    }
    bool reb = m_sequenceAdaptor->UpdateRecordIntoTable(&sequenceElement);
}

void SequenceModel::editNew(int sequenceId)
{
    m_sequenceAdaptor->QueryOneRecordFromTable(sequenceId, &sequenceElement);
}

QString SequenceModel::getSequenceName(int sequenceId)
{
    SequenceElement mySequence;
    bool reb;
    reb = m_sequenceAdaptor->QueryOneRecordFromTable(sequenceId,&mySequence);
    return mySequence.SequenceName;
}

void SequenceModel::getSequenceInfo(bool bIsEdit, int sequenceId, QString sequenceName)
{
    if (bIsEdit) {
        m_sequenceAdaptor->QueryOneRecordFromTable(sequenceId,sequenceName,&sequenceElement);
    } else {
        SequenceElement temp;
        sequenceElement = temp;
    }
}

QList<int> SequenceModel::getCurrentSequenceOfSpliceId()
{
    QList<int> idList;
    for (int i = 0; i < sequenceElement.SpliceList.count(); i++) {
        idList.append(sequenceElement.SpliceList.value(sequenceElement.SpliceList.keys().at(i)).SpliceID);
    }
    return idList;
}

int SequenceModel::searchIndexByName(QString name)
{
    QMap<int,QString>::iterator it; //遍历map
    int i = 0;
    for ( it = sequences->begin(); it != sequences->end(); ++it ) {
        if (name == it.value())
            return i;
        i++;

    }
    return -1;
}

QList<int> SequenceModel::getCurrentSequenceOfSpliceQty()
{
    QList<int> idList;
    for (int i = 0; i < sequenceElement.SpliceList.count(); i++) {
        idList.append(sequenceElement.SpliceList.value(sequenceElement.SpliceList.keys().at(i)).Quantity);
    }
    return idList;
}

QStringList SequenceModel::getCurrentSequenceOfSpliceName()
{
    QStringList list;
    for (int i = 0; i < sequenceElement.SpliceList.count(); i++) {
        list.append(sequenceElement.SpliceList.value(sequenceElement.SpliceList.keys().at(i)).SpliceName);
    }
    return list;
}

int SequenceModel::count()
{
    return sequences->count();
}

void SequenceModel::sequenceSpliceListClear()
{
    sequenceElement.SpliceList.clear();
}

void SequenceModel::setSpliceData(int index,int spliceId,QString spliceName,int quantity)
{
    sequenceElement.SpliceList[index].SpliceID = spliceId;
    sequenceElement.SpliceList[index].SpliceName = spliceName;
    sequenceElement.SpliceList[index].Quantity = quantity;
}

bool SequenceModel::updateRecordIntoTable(int sequenceId, QString sequenceName,int operatorId)
{
    SequenceElement mySequence;
    m_sequenceAdaptor->QueryOneRecordFromTable(sequenceId,&mySequence);
    mySequence.SequenceName = sequenceName;
    mySequence.OperatorID = operatorId;
    mySequence.NoOfSplice = sequenceElement.SpliceList.count();
    mySequence.SpliceList = sequenceElement.SpliceList;
    bool reb =m_sequenceAdaptor->UpdateRecordIntoTable(&mySequence);

    setModelList();
    return reb;
}

bool SequenceModel::insertRecordIntoTable(QString sequenceName,int operatorId)
{
//    int SequenceID;
//    QString SequenceName;
//    unsigned int CreatedDate;
//    int OperatorID;

//    int NoOfSplice;
//    QMap<int, struct SEQUENCEATTRIBUTE> SpliceList;

    int insertSequenceId = -1;
    sequenceElement.SequenceID = -1;
    sequenceElement.CreatedDate = QDateTime::currentDateTime().toTime_t();
    sequenceElement.SequenceName = sequenceName;
    sequenceElement.OperatorID = operatorId;
    sequenceElement.NoOfSplice = sequenceElement.SpliceList.count();

    insertSequenceId = m_sequenceAdaptor->InsertRecordIntoTable(&sequenceElement);
    qDebug() << "sssssssssssssssssssssssss" << insertSequenceId;

    setModelList();
    return insertSequenceId;
}
