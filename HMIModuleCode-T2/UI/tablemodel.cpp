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
        PresetElement mySplice;
        m_spliceAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&mySplice);
        if (columnIdx == 0)
            value = QVariant::fromValue(mySplice.SpliceID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(mySplice.SpliceName);
        else if (columnIdx == 2)
            value = QVariant::fromValue(QDateTime::fromTime_t(mySplice.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 3)
            value = QVariant::fromValue(mySplice.NoOfWires);
        else if (columnIdx == 4)
            value = QVariant::fromValue(mySplice.CrossSection);
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


QVariant SpliceModel::getSpliceValue(int index, QString key)
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
    PresetElement mySplice;
    m_spliceAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&mySplice);
    QHash<QString, QVariant> SpliceModelHash;
    SpliceModelHash.insert("name",mySplice.SpliceName);
    SpliceModelHash.insert("date",QDateTime::fromTime_t(mySplice.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    SpliceModelHash.insert("middle",mySplice.NoOfWires);
    SpliceModelHash.insert("count",mySplice.CrossSection);
    //list << "name" << "date" << "middle" << "count";
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
        PartElement myPart;
        m_partAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myPart);
        if (columnIdx == 0)
            value = QVariant::fromValue(myPart.PartID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(myPart.PartName);
        else if (columnIdx == 2)
            value = QVariant::fromValue(QDateTime::fromTime_t(myPart.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 3)
            value = QVariant::fromValue(myPart.NoOfSplice);
        else if (columnIdx == 4)
            value = QVariant::fromValue(myPart.OperatorID);
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


QVariant PartModel::getPartValue(int index, QString key)
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
    PartElement myPart;
    m_partAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myPart);
    QHash<QString, QVariant> PartModelHash;
    PartModelHash.insert("partId",myPart.PartID);
    PartModelHash.insert("name",myPart.PartName);
    PartModelHash.insert("date",QDateTime::fromTime_t(myPart.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    PartModelHash.insert("middle",myPart.NoOfSplice);
    PartModelHash.insert("type","YES");
    //list << "name" << "date" << "middle" << "count";
    if (key == "") {
        return PartModelHash;
    } else {
        return PartModelHash.value(key);
    }
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
        AlarmElement myAlarm;
        m_alarmAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myAlarm);
        if (columnIdx == 0)
            value = QVariant::fromValue(myAlarm.AlarmID);
        else if (columnIdx == 1)
            value = QVariant::fromValue(myAlarm.AlarmMsg);
        else if (columnIdx == 2)
            value = QVariant::fromValue(QDateTime::fromTime_t(myAlarm.CreatedDate).toString("MM/dd/yyyy hh:mm"));
        else if (columnIdx == 3)
            value = QVariant::fromValue(myAlarm.AlarmType);
        else if (columnIdx == 4) {
            value = QVariant::fromValue(myAlarm.WeldResultID);
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
    AlarmElement myAlarm;
    m_alarmAdaptor->QueryOneRecordFromTable(it.key(),it.value(),&myAlarm);
    QHash<QString, QVariant> AlarmModelHash;
    AlarmModelHash.insert("alarmId",myAlarm.AlarmID);
    AlarmModelHash.insert("message",myAlarm.AlarmMsg);
    AlarmModelHash.insert("date",QDateTime::fromTime_t(myAlarm.CreatedDate).toString("MM/dd/yyyy hh:mm"));
    AlarmModelHash.insert("type",myAlarm.AlarmType);
    AlarmModelHash.insert("splice",myAlarm.WeldResultID);//myOperator.PermissionLevel;
    if (key == "") {
        return AlarmModelHash;
    } else {
        return AlarmModelHash.value(key);
    }
}

