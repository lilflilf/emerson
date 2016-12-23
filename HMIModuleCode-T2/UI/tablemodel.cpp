#include "tablemodel.h"
#include <QDebug>
#include <QQmlPropertyMap>

WorkOrderModel::WorkOrderModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_workOrderAdaptor = DBWorkOrderTable::Instance();
    m_partAdaptor = DBPartTable::Instance();
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

int WorkOrderModel::getPartId(int index)
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
    return myWorkOrder.PartIndex.begin().key();
}

QList<int> WorkOrderModel::getSpliceList()
{
    QMap<int,struct PARTATTRIBUTE>::iterator it; //遍历map
    QList<int> list;
    for ( it = partElement.SpliceList.begin(); it != partElement.SpliceList.end(); ++it ) {
        list.append(it.value().SpliceID);
    }
    return list;
}

void WorkOrderModel::editNew(int index)
{
    m_partAdaptor->QueryOneRecordFromTable(index,&partElement);
}

QVariant WorkOrderModel::getStructValue(QString key)
{
    if (key == "WorkOrderId")
        return workOrderElement.WorkOrderID;
    else if (key == "WorkOrderName")
        return workOrderElement.WorkOrderName;
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

SpliceModel::SpliceModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_spliceAdaptor = DBPresetTable::Instance();
    m_operatorAdaptor = DBOperatorTable::Instance();
    m_wireAdaptor = DBWireTable::Instance();
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
            value = QVariant::fromValue(temp);
        } else if (columnIdx == 21) {
            value = QVariant::fromValue(mySplice.TestSetting.Qutanty);
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
        qDebug( )<< "setModelList SpliceModel" << splices->count();
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

void SpliceModel::calculateSpliceData()
{
    presetElement.CalculateSpliceData();
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
            return variantToString->HeightMinusToString(presetElement.WeldSettings.QualitySetting.Height.Minus).Current;
        else if (valueType == "max")
            return variantToString->HeightMinusToString(presetElement.WeldSettings.QualitySetting.Height.Minus).Maximum;
        else if (valueType == "min")
            return variantToString->HeightMinusToString(presetElement.WeldSettings.QualitySetting.Height.Minus).Minimum;
    }
    else if (valueKey == "Post-Height+") {
        if (valueType == "current")
            return variantToString->HeightPlusToString(presetElement.WeldSettings.QualitySetting.Height.Plus).Current;
        else if (valueType == "max")
            return variantToString->HeightPlusToString(presetElement.WeldSettings.QualitySetting.Height.Plus).Maximum;
        else if (valueType == "min")
            return variantToString->HeightPlusToString(presetElement.WeldSettings.QualitySetting.Height.Plus).Minimum;
    }
    else if (valueKey == "Step-Energy") {
        if (valueType == "current")
            return variantToString->StepEnergyToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep).Current;
        else if (valueType == "max")
            return variantToString->StepEnergyToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep).Maximum;
        else if (valueType == "min")
            return variantToString->StepEnergyToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.EnergyToStep).Minimum;
    }
    else if (valueKey == "Step-Time") {
        if (valueType == "current")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.TimeToStep).Current;
        else if (valueType == "max")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.TimeToStep).Maximum;
        else if (valueType == "min")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.TimeToStep).Minimum;
    }
    else if (valueKey == "Step-Power") {
        if (valueType == "current")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.PowerToStep).Current;
        else if (valueType == "max")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.PowerToStep).Maximum;
        else if (valueType == "min")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.PowerToStep).Minimum;
    }
    else if (valueKey == "Amplitude A") {
        if (valueType == "current")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.BasicSetting.Amplitude).Current;
        else if (valueType == "max")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.BasicSetting.Amplitude).Maximum;
        else if (valueType == "min")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.BasicSetting.Amplitude).Minimum;
    }
    else if (valueKey == "Amplitude B") {
        if (valueType == "current")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.Amplitude2).Current;
        else if (valueType == "max")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.Amplitude2).Maximum;
        else if (valueType == "min")
            return variantToString->PreHeightPlusToString(presetElement.WeldSettings.AdvanceSetting.StepWeld.Amplitude2).Minimum;
    }
    else if (valueKey == "Pre Burst") {
        if (valueType == "current")
            return variantToString->PreBurstTimeToString(presetElement.WeldSettings.AdvanceSetting.PreBurst).Current;
        else if (valueType == "max")
            return variantToString->PreBurstTimeToString(presetElement.WeldSettings.AdvanceSetting.PreBurst).Maximum;
        else if (valueType == "min")
            return variantToString->PreBurstTimeToString(presetElement.WeldSettings.AdvanceSetting.PreBurst).Minimum;
    }
    else if (valueKey == "Hold Time") {
        if (valueType == "current")
            return variantToString->HoldTimeToString(presetElement.WeldSettings.AdvanceSetting.HoldTime).Current;
        else if (valueType == "max")
            return variantToString->HoldTimeToString(presetElement.WeldSettings.AdvanceSetting.HoldTime).Maximum;
        else if (valueType == "min")
            return variantToString->HoldTimeToString(presetElement.WeldSettings.AdvanceSetting.HoldTime).Minimum;
    }
    else if (valueKey == "After Burst") {
        if (valueType == "current")
            return variantToString->AfterBurstDuringToString(presetElement.WeldSettings.AdvanceSetting.ABDur).Current;
        else if (valueType == "max")
            return variantToString->AfterBurstDuringToString(presetElement.WeldSettings.AdvanceSetting.ABDur).Maximum;
        else if (valueType == "min")
            return variantToString->AfterBurstDuringToString(presetElement.WeldSettings.AdvanceSetting.ABDur).Minimum;
    }
    else if (valueKey == "Squeeze Time") {
        if (valueType == "current")
            return variantToString->SqueezeTimeToString(presetElement.WeldSettings.AdvanceSetting.SqzTime).Current;
        else if (valueType == "max")
            return variantToString->SqueezeTimeToString(presetElement.WeldSettings.AdvanceSetting.SqzTime).Maximum;
        else if (valueType == "min")
            return variantToString->SqueezeTimeToString(presetElement.WeldSettings.AdvanceSetting.SqzTime).Minimum;
    }
    else if (valueKey == "ActualWidth") {
        if (valueType == "current")
            return variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.MeasuredWidth).Current;
        else if (valueType == "max")
            return variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.MeasuredWidth).Maximum;
        else if (valueType == "min")
            return variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.MeasuredWidth).Minimum;
    }
    else if (valueKey == "ActualHeight") {
        if (valueType == "current")
            return variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.MeasuredHeight).Current;
        else if (valueType == "max")
            return variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.MeasuredHeight).Maximum;
        else if (valueType == "min")
            return variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.MeasuredHeight).Minimum;
    }
    else if (valueKey == "Unload Time") {
        if (valueType == "current")
            return variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.AntiSideSpliceTime).Current;
        else if (valueType == "max")
            return variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.AntiSideSpliceTime).Maximum;
        else if (valueType == "min")
            return variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.AntiSideSpliceTime).Minimum;
    }
    else if (valueKey == "Load Time") {
        if (valueType == "current")
            return variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.CutOffSpliceTime).Current;
        else if (valueType == "max")
            return variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.CutOffSpliceTime).Maximum;
        else if (valueType == "min")
            return variantToString->MeasureWidthToString(presetElement.WeldSettings.AdvanceSetting.CutOffSpliceTime).Minimum;
    }
    else if (valueKey == "Anti-Side") {
        if (presetElement.WeldSettings.AdvanceSetting.AntiSide)
            return "left";
        else
            return "right";
    }
    else if (valueKey == "Cut Off") {
        if (presetElement.WeldSettings.AdvanceSetting.CutOff)
            return "left";
        else
            return "right";
    }
    else if (valueKey == "Insulation") {
        if (presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption)
            return "left";
        else
            return "right";
    }
    else if (valueKey == "PicPath") {
        if (presetElement.PresetPicNamePath.isEmpty())
            return " ";
        return presetElement.PresetPicNamePath;
    }
    else if (valueKey == "SpliceName") {
        return presetElement.SpliceName;
    }
    else if (valueKey == "ShrinkId") {
        return presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID;
    }
    else if (valueKey == "ShrinkTemp") {
        return variantToString->ShrinkTemperatureToString(presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature).Current;
    }
    else if (valueKey == "ShrinkTime") {
        return variantToString->ShrinkTimeToString(presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime).Current;
    }
    else if (valueKey == "Cross Section") {
        return variantToString->CrossSectionToString(presetElement.CrossSection);
    }
    else if (valueKey == "Cross Section") {
        return variantToString->CrossSectionToString(presetElement.CrossSection);
    }
    else if (valueKey == "TestStandardTime+") {
        if (valueType == "current")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG]).Current;
        else if (valueType == "max")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG]).Maximum;
        else if (valueType == "min")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG]).Minimum;
    }
    else if (valueKey == "TestStandardTime-") {
        if (valueType == "current")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG]).Current;
        else if (valueType == "max")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG]).Maximum;
        else if (valueType == "min")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG]).Minimum;
    }
    else if (valueKey == "TestStandardPower+") {
        if (valueType == "current")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG]).Current;
        else if (valueType == "max")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG]).Maximum;
        else if (valueType == "min")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG]).Minimum;
    }
    else if (valueKey == "TestStandardPower-") {
        if (valueType == "current")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG]).Current;
        else if (valueType == "max")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG]).Maximum;
        else if (valueType == "min")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG]).Minimum;
    }
    else if (valueKey == "TestStandardPre+") {
        if (valueType == "current")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG]).Current;
        else if (valueType == "max")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG]).Maximum;
        else if (valueType == "min")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG]).Minimum;
    }
    else if (valueKey == "TestStandardPre-") {
        if (valueType == "current")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG]).Current;
        else if (valueType == "max")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG]).Maximum;
        else if (valueType == "min")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG]).Minimum;
    }
    else if (valueKey == "TestStandardPost+") {
        if (valueType == "current")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG]).Current;
        else if (valueType == "max")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG]).Maximum;
        else if (valueType == "min")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG]).Minimum;
    }
    else if (valueKey == "TestStandardPost-") {
        if (valueType == "current")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG]).Current;
        else if (valueType == "max")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG]).Maximum;
        else if (valueType == "min")
            return variantToString->StandardAutoTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG]).Minimum;
    }
    else if (valueKey == "TestSigmaTime+") {
        if (valueType == "current")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_PL]).Current;
        else if (valueType == "max")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_PL]).Maximum;
        else if (valueType == "min")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_PL]).Minimum;
    }
    else if (valueKey == "TestSigmaTime-") {
        if (valueType == "current")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_MS]).Current;
        else if (valueType == "max")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_MS]).Maximum;
        else if (valueType == "min")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_CONFRG_MS]).Minimum;
    }
    else if (valueKey == "TestSigmaPower+") {
        if (valueType == "current")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_PL]).Current;
        else if (valueType == "max")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_PL]).Maximum;
        else if (valueType == "min")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_PL]).Minimum;
    }
    else if (valueKey == "TestSigmaPower-") {
        if (valueType == "current")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_MS]).Current;
        else if (valueType == "max")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_MS]).Maximum;
        else if (valueType == "min")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_CONFRG_MS]).Minimum;
    }
    else if (valueKey == "TestSigmaPre+") {
        if (valueType == "current")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_PL]).Current;
        else if (valueType == "max")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_PL]).Maximum;
        else if (valueType == "min")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_PL]).Minimum;
    }
    else if (valueKey == "TestSigmaPre-") {
        if (valueType == "current")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_MS]).Current;
        else if (valueType == "max")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_MS]).Maximum;
        else if (valueType == "min")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_CONFRG_MS]).Minimum;
    }
    else if (valueKey == "TestSigmaPost+") {
        if (valueType == "current")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_PL]).Current;
        else if (valueType == "max")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_PL]).Maximum;
        else if (valueType == "min")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_PL]).Minimum;
    }
    else if (valueKey == "TestSigmaPost-") {
        if (valueType == "current")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_MS]).Current;
        else if (valueType == "max")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_MS]).Maximum;
        else if (valueType == "min")
            return variantToString->SigmaTeachModeToString(presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_CONFRG_MS]).Minimum;
    }
    else if (valueKey == "TestModel") {
        return QString("%1").arg((int)presetElement.TestSetting.TestMode);
    }
    else if (valueKey == "TestCount") {
        return QString("%1").arg(presetElement.TestSetting.Qutanty);
    }
    else if (valueKey == "TeachMode") {
        return QString("%1").arg((int)presetElement.TestSetting.TeachModeSetting.TeachModeType);
    }
    else
        return "";
}

int SpliceModel::getRawData(QString key)
{
    if (key == "Time-")
        return presetElement.WeldSettings.QualitySetting.Time.Minus;
    else if (key == "Time+")
        return presetElement.WeldSettings.QualitySetting.Time.Plus;
    else if (key == "Power-")
        return presetElement.WeldSettings.QualitySetting.Power.Minus;
    else if (key == "Power+")
        return presetElement.WeldSettings.QualitySetting.Power.Plus;
    else if (key == "Pre-Height-")
        return presetElement.WeldSettings.QualitySetting.Preheight.Minus;
    else if (key == "Pre-Height+")
        return presetElement.WeldSettings.QualitySetting.Preheight.Plus;
    else if (key == "Post-Height-")
        return presetElement.WeldSettings.QualitySetting.Height.Minus;
    else if (key == "Post-Height+")
        return presetElement.WeldSettings.QualitySetting.Height.Plus;
}

void SpliceModel::setStructValue(QString valueKey, QVariant value)
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
        presetElement.WeldSettings.AdvanceSetting.WeldMode = (WELDMODE)value.toInt();
    }
    else if (valueKey == "StepModel") {
        presetElement.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode = (STEPWELDMODE)value.toInt();
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
        presetElement.WeldSettings.AdvanceSetting.MeasuredWidth = stringToVariant->MeasureWidthToInt(value.toString());
    }
    else if (valueKey == "ActualHeight") {
        presetElement.WeldSettings.AdvanceSetting.MeasuredHeight = stringToVariant->MeasureHeightToInt(value.toString());
    }
    else if (valueKey == "Unload Time") {
        presetElement.WeldSettings.AdvanceSetting.AntiSideSpliceTime = stringToVariant->AntiSideSpliceTimeToInt(value.toString());
    }
    else if (valueKey == "Load Time") {
        presetElement.WeldSettings.AdvanceSetting.CutOffSpliceTime = stringToVariant->CutOffSpliceTimeToInt(value.toString());
    }
    else if (valueKey == "Anti-Side") {
        presetElement.WeldSettings.AdvanceSetting.AntiSide = value.toBool();
    }
    else if (valueKey == "Cut Off") {
        presetElement.WeldSettings.AdvanceSetting.CutOff = value.toBool();
    }
    else if (valueKey == "Insulation") {
        presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkOption = value.toBool();
    }
    else if (valueKey == "ShrinkId") {
        presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTubeID = value.toString();
    }
    else if (valueKey == "ShrinkTemp") {
        presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTemperature = stringToVariant->ShrinkTemperatureToInt(value.toString());
    }
    else if (valueKey == "ShrinkTime") {
        presetElement.WeldSettings.AdvanceSetting.ShrinkTube.ShrinkTime = stringToVariant->ShrinkTimeToInt(value.toString());
    }
    else if (valueKey == "SpliceName") {
        presetElement.SpliceName = value.toString();
    }
    else if (valueKey == "OperatorId") {
        presetElement.OperatorID = value.toInt();
    }
    else if (valueKey == "Total Cross") {
        presetElement.CrossSection = stringToVariant->CrossSectionToInt(value.toString());
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
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_PLRG] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPower+") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_PLRG] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPre+") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_PLRG] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPost+") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_PLRG] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardTime-") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[TIME_MSRG] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPower-") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[POWER_MSRG] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPre-") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[PRE_HGT_MSRG] = stringToVariant->PercentTeachModeToInt(value.toString());
    }
    else if (valueKey == "TestStandardPost-") {
        presetElement.TestSetting.TeachModeSetting.TeachModequal_Window[HEIGHT_MSRG] = stringToVariant->PercentTeachModeToInt(value.toString());
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
        presetElement.TestSetting.TestMode = (TESTMODE)value.toInt();
    }
    else if (valueKey == "TestCount") {
        presetElement.TestSetting.Qutanty = value.toInt();
    }
    else if (valueKey == "TeachMode") {
        presetElement.TestSetting.TeachModeSetting.TeachModeType = (TEACH_MODE_TYPE)value.toInt();
    }
}

int SpliceModel::saveSplice(bool bIsEdit)
{
    int spliceId;
    if (bIsEdit)
    {
        m_spliceAdaptor->UpdateRecordIntoTable(&presetElement);
        return -1;
    }
    else
    {
        spliceId = m_spliceAdaptor->InsertRecordIntoTable(&presetElement);
    }
    setModelList();
    return spliceId;
}

uint SpliceModel::getHashCode()
{
    return presetElement.HashCode;
}

void SpliceModel::createNew()
{
    PresetElement temp;
    presetElement = temp;
}

void SpliceModel::editNew(int spliceId)
{
    m_spliceAdaptor->QueryOneRecordFromTable(spliceId, &presetElement);
}

QString SpliceModel::getString(QString type, int value)
{
    if (type == "CrossSection")
        return variantToString->CrossSectionToString(value);
}

bool SpliceModel::getWeldMode(QString type, int index)
{
    if (type == "weld")
    {
        if ((int)presetElement.WeldSettings.AdvanceSetting.WeldMode == index)
            return true;
        else
            return false;
    }
    else if (type == "step")
    {
        if ((int)presetElement.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode == index)
            return true;
        else
            return false;
    }
}

QList<int> SpliceModel::getWireIdList()
{
    QMap<int,QString>::iterator it; //遍历map
    QList<int> list;
    for ( it = presetElement.WireIndex.begin(); it != presetElement.WireIndex.end(); ++it ) {
        list.append(it.key());
    }
    return list;
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
    SpliceModelHash.insert("count",mySplice.TestSetting.Qutanty);
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
    m_Part = new PartElement();
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

QVariant PartModel::getStruceValue(QString key)
{
    if (key == "PartId")
        return m_Part->PartID;
    else if (key == "PartName")
        return m_Part->PartName;
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

void PartModel::getPartInfo(bool bIsEdit, int id, QString name)
{
    if (bIsEdit) {
        m_partAdaptor->QueryOneRecordFromTable(id,name,m_Part);
    } else {
        m_Part = NULL;
        m_Part = new PartElement();
    }
}

int PartModel::getWorkStationRows()
{
    return m_Part->PartTypeSetting.BoardLayout.Rows;
}

int PartModel::getWorkStationColumns()
{
    return m_Part->PartTypeSetting.BoardLayout.Columns;
}

int PartModel::getWorkStationMaxSplicePerZone()
{
    return m_Part->PartTypeSetting.BoardLayout.MaxSplicesPerZone;
}

int PartModel::getWorkStationCount()
{
    return m_Part->PartTypeSetting.WorkStations.TotalWorkstation;
}

int PartModel::getWorkStationMaxSplicePerStation()
{
    return m_Part->PartTypeSetting.WorkStations.MaxSplicesPerWorkstation;
}

int PartModel::getCurrentPartSpliceCount()
{
    return m_Part->SpliceList.count();
}

QList<int> PartModel::getWorkStationCorlor()
{
    QList<int> corlorList;
    for (int i = 0; i < m_Part->SpliceList.count(); i++) {
        corlorList.append( m_Part->SpliceList.value( m_Part->SpliceList.keys().at(i)).CurrentWorkstation);
    }
    return corlorList;
}

QList<int> PartModel::geteWorkStationZone()
{
    QList<int> zoneList;
    for (int i = 0; i < m_Part->SpliceList.count(); i++) {
        zoneList.append(m_Part->SpliceList.value(m_Part->SpliceList.keys().at(i)).CurrentBoardLayoutZone);
    }
    return zoneList;
}

QStringList PartModel::getCurrentPartOfSpliceName()
{
    QStringList list;
    for (int i = 0; i < m_Part->SpliceList.count(); i++) {
        list.append(m_Part->SpliceList.value(m_Part->SpliceList.keys().at(i)).SpliceName);
    }
    return list;
}

QList<int> PartModel::getCurrentPartOfSpliceId()
{
    QList<int> idList;
    for (int i = 0; i < m_Part->SpliceList.count(); i++) {
        idList.append(m_Part->SpliceList.value(m_Part->SpliceList.keys().at(i)).SpliceID);
    }
    return idList;
}

bool PartModel::getPartOnlineOrOffLine()
{
    if (m_Part->PartTypeSetting.ProcessMode == BASIC) {
        return false;
    } else {
        return true;
    }
}

void PartModel::setPartOffLineOrOnLine(bool bIsLine)
{
    if (bIsLine) {
        m_Part->PartTypeSetting.ProcessMode = ADVANCE;
    } else {
        m_Part->PartTypeSetting.ProcessMode = BASIC;
    }
}

void PartModel::setPartName(QString name)
{
   m_Part->PartName =  name;
}

void PartModel::setPartColumns(int columns)
{
    m_Part->PartTypeSetting.BoardLayout.Columns = columns;
}

void PartModel::setPartRows(int rows)
{
   m_Part->PartTypeSetting.BoardLayout.Rows = rows;
}

void PartModel::setPartMaxSplicePerZone(int maxNum)
{
    m_Part->PartTypeSetting.BoardLayout.MaxSplicesPerZone = maxNum;
}

void PartModel::setPartWorkStationNum(int num)
{
    m_Part->PartTypeSetting.WorkStations.TotalWorkstation = num;
}

void PartModel::setPartMaxSplicePerWorkStation(int maxNum)
{
     m_Part->PartTypeSetting.WorkStations.MaxSplicesPerWorkstation = maxNum;
}

void PartModel::setPartSpliceListClear()
{
    m_Part->SpliceList.clear();
}

void PartModel::setPartSpliceList(QString name, int id, int station, int zone, int index)
{
    m_Part->SpliceList[index].SpliceID = id;
    m_Part->SpliceList[index].SpliceName = name;
    m_Part->SpliceList[index].CurrentWorkstation = station;
    m_Part->SpliceList[index].CurrentBoardLayoutZone = zone;
}

void PartModel::savePartInfo(bool bIsEdit, int operatorId)
{
    m_Part->OperatorID = operatorId;
    m_Part->NoOfSplice = m_Part->SpliceList.count();
    if (bIsEdit) {
        m_partAdaptor->UpdateRecordIntoTable(m_Part);
    } else {
        int partId = m_partAdaptor->InsertRecordIntoTable(m_Part);
        qDebug()<<"savePartInfo insert id: "<< partId;
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
            permissionSetting->_Recall();
            value = QVariant::fromValue(permissionSetting->FourLevelIdentifier.at(myOperator.PermissionLevel));
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
    if (key == "OperatorName")
        return operatorElement.OperatorName;
    else if (key == "PassWord")
        return operatorElement.Password;
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
}


int OperatorModel::rowCount(const QModelIndex & parent) const
{
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
        myOperator.PermissionLevel = PASSWORDCONTROL::ADMINISTRATOR;
    else if (level == 2)
        myOperator.PermissionLevel = PASSWORDCONTROL::TECHNICIAN;
    else if (level == 3)
        myOperator.PermissionLevel = PASSWORDCONTROL::QUALITYCONTROL;
    else if (level == 4)
        myOperator.PermissionLevel = PASSWORDCONTROL::OPEN;
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
        myOperator.PermissionLevel = PASSWORDCONTROL::ADMINISTRATOR;
    else if (level == 2)
        myOperator.PermissionLevel = PASSWORDCONTROL::TECHNICIAN;
    else if (level == 3)
        myOperator.PermissionLevel = PASSWORDCONTROL::QUALITYCONTROL;
    else if (level == 4)
        myOperator.PermissionLevel = PASSWORDCONTROL::OPEN;
    m_operatorAdaptor->UpdateRecordIntoTable(&myOperator);
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
    int level = myOperator.PermissionLevel;
    permissionSetting->_Recall();
    OperatorModelHash.insert("count",permissionSetting->FourLevelIdentifier.at(level));//myOperator.PermissionLevel;
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
    if (key == "Time")
        return weldResultElement.ActualResult.ActualTime;
    else if (key == "Power")
        return weldResultElement.ActualResult.ActualPeakPower;
    else if (key == "Pre-Height")
        return weldResultElement.ActualResult.ActualPreheight;
    else if (key == "Post-Height")
        return weldResultElement.ActualResult.ActualPostheight;
}

void AlarmModel::setStartTime()
{
    startTime = QDateTime::currentDateTime();
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
            temp = myAlarm.AlarmType;
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

void AlarmModel::setModelList(QString name, unsigned int time_from, unsigned int time_to)
{
    beginResetModel();
    alarms->clear();
    if (m_alarmAdaptor->QueryUseNameAndTime(name,time_from,time_to,alarms))
        qDebug( )<< "AlarmModel " << alarms->count();
    endResetModel();
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
    AlarmModelHash.insert("Alarm/ErrorType",myAlarm.AlarmType);
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
    qDebug() << "m_weldHistoryAdaptorcccccccccccccccccccccccc";

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
        qDebug() << "m_weldHistoryAdaptor" << QDateTime::currentDateTime().toTime_t();
        m_weldHistoryAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myHistory);
        PresetElement presetElement;
        m_spliceTable->QueryOneRecordFromTable(myHistory.CurrentSplice.SpliceID,myHistory.CurrentSplice.SpliceName,&presetElement);
        qDebug() << "m_spliceTable" << QDateTime::currentDateTime().toTime_t();

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
            value = QVariant::fromValue(variantToString->CrossSectionToString(presetElement.CrossSection));
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
    m_weldHistoryAdaptor->QueryOneRecordFromTable(orderId,historys->value(orderId),&myHistory);
    PresetElement presetElement;
    m_spliceTable->QueryOneRecordFromTable(myHistory.CurrentSplice.SpliceID,myHistory.CurrentSplice.SpliceName,&presetElement);
    QHash<QString, QVariant> WeldHistoryModelHash;
    WeldHistoryModelHash.insert("WeldHistoryId",myHistory.WeldResultID);
    WeldHistoryModelHash.insert("WorkOrderName",myHistory.CurrentWorkOrder.WorkOrderName);
    WeldHistoryModelHash.insert("PartName",myHistory.CurrentPart.PartName);
    WeldHistoryModelHash.insert("SpliceName",myHistory.CurrentSplice.SpliceName);
    WeldHistoryModelHash.insert("OperatorName",myHistory.OperatorName);
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
        else if (columnIdx == 5) {
            if (myWire.Stripe.TypeOfStripe == 0) {
                temp = "Horizontal";
            } else if (myWire.Stripe.TypeOfStripe == 1) {
                temp = "Slash";
            } else if (myWire.Stripe.TypeOfStripe == 2) {
                temp = "OneVertical";
            } else {
                temp = "TwoVertical";
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

int WireModel::insertValueToTable(QString type,QString wireName,int wireId,int operatorId,QString color,QString stripeColor,int stripeType,QString gauge,int wireType,int side,int verside,int position)
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
    int insertWireId;
    WireElement insertWire;
    insertWire.WireName = wireName;
    insertWire.WireID = wireId;
    insertWire.OperatorID = operatorId;
    insertWire.Color = color;
    insertWire.Stripe.Color = stripeColor;
    insertWire.Stripe.TypeOfStripe = (StripeType)stripeType;
    stringToVariant->GaugeToInt(gauge,insertWire.GaugeAWG,insertWire.Gauge);
    insertWire.TypeOfWire = (MetalType)wireType;
    insertWire.Side = (HorizontalLocation)side;
    insertWire.VerticalSide = (VerticalLocation)verside;
    insertWire.Position = (VerticalPosition)position;
    insertWire.SpliceID = -1;

    if (type == "insert"){
        insertWireId = m_wireAdaptor->InsertRecordIntoTable(&insertWire);
        setModelList();
        return insertWireId;
    }
    else if (type == "update") {
        WireElement wireTemp;
        m_wireAdaptor->QueryOneRecordFromTable(wireId,&wireTemp);
        if (wireTemp == insertWire)
            return wireId;
        else
        {
            if (m_wireAdaptor->UpdateRecordIntoTable(&insertWire))
                return wireId;
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
    WireModelHash.insert("Gauge",wireElement.Gauge);
    WireModelHash.insert("AWG",wireElement.GaugeAWG);
    int metalType;
    if (wireElement.TypeOfWire == 0) {
        metalType = 0;
    } else {
        metalType = 1;
    }
    WireModelHash.insert("WireType",metalType);
    WireModelHash.insert("WireColor",wireElement.Color);
    WireModelHash.insert("WireName",wireElement.WireName);
    WireModelHash.insert("WireDirection",(int)wireElement.Side);
    WireModelHash.insert("WirePosition",wireElement.Position);
    WireModelHash.insert("WireBasic",wireElement.VerticalSide);
    WireModelHash.insert("WireId",wireElement.WireID);

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
        temp = "OneVertical";
    } else {
        temp = "TwoVertical";
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
    qDebug() << "MaintenanceLogModel" << index << key;
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
void MaintenanceLogModel::searchMaintenanceLog(QString Name, unsigned int time_from, unsigned int time_to)
{
    if (Name == "All")
        setModelList();
    else
        setModelList(Name,time_from,time_to);
}
