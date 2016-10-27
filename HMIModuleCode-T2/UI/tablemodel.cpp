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
    qDebug() << "data";
    QVariant value;
    if(role < Qt::UserRole)
    {
        qDebug() << "WorkOrderModel::data(const QModelIndex &index, int role) const";
    }
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        //QString rowId = m_idList.at(index.row());
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
            value = QVariant::fromValue(myWorkOrder.WorkOrderName);
        else if (columnIdx == 1)
            value = QVariant::fromValue(myWorkOrder.CreatedDate);
        else if (columnIdx == 2)
            value = QVariant::fromValue(myWorkOrder.OperatorID);
        else
            value = QVariant::fromValue(myWorkOrder.Quantity);
        qDebug() << "WorkOrderModel data " << value;
    }
    return value;
}



//void WorkOrderModel::setModelList(const int &netType, const int &contacterType, const QString& searchText, QStringList memberList)
//{
//    beginResetModel();
//    if (netType != 0) {
//        if (searchText == "") {
//            m_idList  = m_contacterAdaptor->getContactersExcept(1, netType, memberList);
//        } else {
//            m_idList  = m_contacterAdaptor->searchContactorsExcept(1, netType, searchText, memberList);
//        }
//    } else {
//        m_idList = m_contacterAdaptor->searchContactors(contacterType, searchText);
//    }
//    qDebug()<<"setModelList"<<m_idList.count();
//    endResetModel();
//}

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

//QVariant WorkOrderModel::getContacterValue(int index, QString key)
//{
//    Contacter contacter;
//    QHash<QString, QVariant> ContacterModelHash;
//    contacter = m_contacterAdaptor->getContacter(m_idList.at(index));
//    ContacterModelHash.insert("id",contacter.id);
//    ContacterModelHash.insert("name",contacter.surname + " " + contacter.name);
//    ContacterModelHash.insert("position",getTitleStringFromEnum(contacter.title));
//    ContacterModelHash.insert("size",contacter.namePinyin);
//    ContacterModelHash.insert("type",QString("%1").arg(contacter.type));
//    if (key == "") {
//        return ContacterModelHash;
//    } else {
//        return ContacterModelHash.value(key);
//    }
//}

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

/*
void CallHistoryModel::setRoles(const QStringList &names)
{
    m_roleNames.clear();
    for(int idx=0; idx<names.count(); idx++)
    {
        m_roleNames[Qt::UserRole + idx + 1] = names[idx].toLocal8Bit();
    }
}
QVariant CallHistoryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}
int CallHistoryModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}
int CallHistoryModel::count()
{
    return m_idList.count();
}
int CallHistoryModel::rowCount(const QModelIndex & parent) const
{
    return m_idList.count();
}
void CallHistoryModel::setModelList(int type,const QString& searchText)
{
    m_idList.clear();
    beginResetModel();
    QStringList historylist;
    historylist= m_historyAdaptor->searchCallHistory(searchText,type);
    for (int j = 0; j < historylist.count(); j++) {
        m_idList.append(oneList(0,historylist[j]));
    }
    if (searchText != "") {
        QStringList contacterlist = m_contacterAdaptor->searchContactors(3,searchText);
        for (int i = 0; i < contacterlist.count(); i++) {
            Contacter contacter = m_contacterAdaptor->getContacter(contacterlist[i]);
            for (int j = 0; j < contacter.numbers.count(); j++) {
                m_idList.append(oneList(contacter.numbers[j].netType,contacter.id));
            }
        }
    }
    endResetModel();
}
QHash<int, QByteArray> CallHistoryModel::roleNames() const
{
    return m_roleNames;
}

QVariant CallHistoryModel::getCallHistoryValue(int index, QString key)
{
    Contacter contacter;
    QHash<QString, QVariant> callHistoryModelHash;

    QString time,networkInfo;
    CallHistory callHistory = m_historyAdaptor->getCallHistory(m_idList[index].second);
    callHistoryModelHash.insert("id",callHistory.dialHistoryId);
    callHistoryModelHash.insert("iconValue",callHistory.dialType);
    if (callHistory.dialTarget.count() != 0) {
        contacter = m_contacterAdaptor->getContacter(callHistory.dialTarget[0]);
        callHistoryModelHash.insert("serialnum",contacter.id);
        callHistoryModelHash.insert("theName",contacter.surname + " " + contacter.name);
        callHistoryModelHash.insert("info",getTitleStringFromEnum(contacter.title));
    } else {
        callHistoryModelHash.insert("serialnum","null");
        callHistoryModelHash.insert("theName","");
        callHistoryModelHash.insert("info","");
    }
    switch (callHistory.dialNetworkType) {
    case LTE_NETWORK_VOICE_DIAL:
    case LTE_NETWORK_VIDEO_DIAL:
    case LTE_NETWORK_METTING_DIAL:
        networkInfo = "LTE";
        break;
    case CS_NETWORK_VOICE_DIAL:
    case CS_NETWORK_VOICE_MUL_DIAL:
    case CS_NETWORK_VIDEO_DIAL:
        networkInfo = "天通网";
        break;
    case ADC_NETWORK_VIDEO_DIAL:
    case ADC_NETWORK_VOICE_DIAL:
    case ADC_NETWORK_METTING_DIAL:
        networkInfo = "自组网";
        break;
    case WIFI_NETWORK_VOICE_DIAL:
    case WIFI_NETWORK_VIDEO_DIAL:
    case WIFI_NETWORK_METTING_DIAL:
        networkInfo = "WIFI";
        break;
    default:
        break;
    }
    QDateTime nowtime = QDateTime::currentDateTime();
    int timediff = callHistory.dialDateStart.daysTo(nowtime);
    if (timediff == 0) {
        time = callHistory.dialDateStart.toString("hh:mm:ss");
    } else if ((timediff <= 7) && (timediff >= 1)) {
        time = callHistory.dialDateStart.toString("dddd hh:mm");
    } else {
        time = callHistory.dialDateStart.toString("yyyy年M月d日 hh:mm");
    }
    callHistoryModelHash.insert("num",callHistory.dialTargetNumber.at(0));
    callHistoryModelHash.insert("timeinfo",time);
    callHistoryModelHash.insert("netinfo",networkInfo);
    if (key == "") {
        return callHistoryModelHash;
    } else {
        return callHistoryModelHash.value(key);
    }
}

void CallHistoryModel::getMeetingTime(QString historyId)
{
    CallHistory callHistory = m_historyAdaptor->getCallHistory(historyId);
    if (callHistory.dialType == 4)
    {
        QString time;
        QDateTime nowtime = QDateTime::currentDateTime();
        int timediff = callHistory.dialDateStart.daysTo(nowtime);
        if (timediff == 0) {
            time = callHistory.dialDateStart.toString("hh:mm:ss");
        } else if ((timediff <= 7) && (timediff >= 1)) {
            time = callHistory.dialDateStart.toString("dddd hh:mm");
        } else {
            time = callHistory.dialDateStart.toString("yyyy年M月d日 hh:mm");
        }
        emit signalMeetingStart(time);
        timediff = callHistory.dialDateStart.daysTo(nowtime);
        if (timediff == 0) {
            time = callHistory.dialDateStart.toString("hh:mm:ss");
        } else if ((timediff <= 7) && (timediff >= 1)) {
            time = callHistory.dialDateStart.toString("dddd hh:mm");
        } else {
            time = callHistory.dialDateStart.toString("yyyy年M月d日 hh:mm");
        }
        emit signalMeetingEnd(time);

        for (int i = 0; i < callHistory.dialTarget.count(); i++)
        {
            emit signalMeetingMember(callHistory.dialTarget.at(i));
        }
    }

}


CallHistoryModel::CallHistoryModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_contacterAdaptor = ContacterInterfaceAdaptor::getInstance();
    m_historyAdaptor = CallHistoryInterfaceAdaptor::getInstance();
}

QVariant CallHistoryModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if(role < Qt::UserRole)
    {
        qDebug() << "CallHistoryModel::data(const QModelIndex &index, int role) const";
    }
    else
    {

        int columnIdx = role - Qt::UserRole - 1;
        QString rowId = m_idList[index.row()].second;
        int firstcount = m_idList[index.row()].first;
        QString name,titleName,networkInfo,time,titleId,phoneNum;
        Contacter contacter;
        CallHistory callHistory;
        bool bIsHistory = false;
        if (firstcount == 0) {
            bIsHistory = true;
        } else {
            bIsHistory = false;
        }
        if (bIsHistory) {
            callHistory  = m_historyAdaptor->getCallHistory(rowId);
            if (callHistory.dialTarget.count() != 0) {
                contacter = m_contacterAdaptor->getContacter(callHistory.dialTarget[0]);
                titleId = contacter.id;
                name = contacter.surname + " " + contacter.name;
                switch (contacter.title) {
                case BATTLION:
                    titleName = "营长";
                    break;
                case COMPANY:
                    titleName = "连长";
                    break;
                case PLATOON:
                    titleName = "排长";
                    break;
                case SQUAD:
                    titleName = "班长";
                    break;
                case SOLIDER:
                    titleName = "战士";
                    break;
                default:
                    titleName = "";
                    break;
                }
            } else {
                name = "";
                titleName = "";
                titleId = "null";
            }
            switch (callHistory.dialNetworkType) {
            case LTE_NETWORK_VOICE_DIAL:
            case LTE_NETWORK_VIDEO_DIAL:
            case LTE_NETWORK_METTING_DIAL:
                networkInfo = "LTE";
                break;
            case CS_NETWORK_VOICE_DIAL:
            case CS_NETWORK_VOICE_MUL_DIAL:
            case CS_NETWORK_VIDEO_DIAL:
                networkInfo = "天通网";
                break;
            case ADC_NETWORK_VIDEO_DIAL:
            case ADC_NETWORK_VOICE_DIAL:
            case ADC_NETWORK_METTING_DIAL:
                networkInfo = "自组网";
                break;
            case WIFI_NETWORK_METTING_DIAL:
            case WIFI_NETWORK_VIDEO_DIAL:
            case WIFI_NETWORK_VOICE_DIAL:
                networkInfo = "WIFI";
                break;
//            case bat:
//            case WIFI_NETWORK_VIDEO_DIAL:
//            case WIFI_NETWORK_VOICE_DIAL:
//                networkInfo = "WIFI";
//                break;
            default:
                break;
            }

            QDateTime nowtime = QDateTime::currentDateTime();
            int timediff = callHistory.dialDateStart.daysTo(nowtime);
            if (timediff == 0) {
                time = callHistory.dialDateStart.toString("hh:mm:ss");
            } else if ((timediff <= 7) && (timediff >= 1)) {
                time = callHistory.dialDateStart.toString("dddd hh:mm");
            } else {
                time = callHistory.dialDateStart.toString("yyyy年M月d日 hh:mm");
            }
            phoneNum = callHistory.dialTargetNumber.at(0);
        } else {
            contacter = m_contacterAdaptor->getContacter(rowId);
            name = contacter.surname + " " + contacter.name;
            titleId = contacter.id;
            time = "";
            switch (contacter.title) {
            case BATTLION:
                titleName = "营长";
                break;
            case COMPANY:
                titleName = "连长";
                break;
            case PLATOON:
                titleName = "排长";
                break;
            case SQUAD:
                titleName = "班长";
                break;
            case SOLIDER:
                titleName = "战士";
                break;
            default:
                titleName = "";
                break;
            }
            for (int i = 0; i < contacter.numbers.count(); i++) {
                if (contacter.numbers[i].netType == firstcount) {
                    phoneNum = contacter.numbers[i].number;
                    break;
                }
            }
            switch (firstcount) {
            case LTE_NETWORK:
                networkInfo = "LTE";
                break;
            case AD_HOC_NETWORK:
                networkInfo = "自组网";
                break;
            case SATELLITE_NETWORK:
                networkInfo = "天通网";
                break;
            case DIGITAL_WALKIE_TALKIE_NETWORK:
                networkInfo = "模块数字对讲";
                break;
            case BATTLE_NETWORK:
                networkInfo = "战互网";
                break;
            case WIFI_NETWORK:
                networkInfo = "WIFI";
            default:
                break;
            }
        }
        if (columnIdx == 0) {
            if (bIsHistory) {
                value = QVariant::fromValue(callHistory.dialHistoryId);
            } else {
                value = QVariant::fromValue(0);
            }
        } else if (columnIdx == 1) {
            value = QVariant::fromValue(titleId);
        } else if (columnIdx == 2) {
            qDebug() << "bIsHistory xxxxxxxxxxxxxxxxxxxxxxx " << bIsHistory << callHistory.dialType;
            if (bIsHistory) {
                value = QVariant::fromValue(callHistory.dialType);
            } else {
                value = QVariant::fromValue(0);
            }
        } else if (columnIdx == 3) {
            value = QVariant::fromValue(name);
        } else if (columnIdx == 4) {
            value = QVariant::fromValue(titleName);
        } else if (columnIdx == 5) {
            value = QVariant::fromValue(phoneNum);
        } else if (columnIdx == 6) {
            value = QVariant::fromValue(time);
        } else if (columnIdx == 7) {
            value = QVariant::fromValue(networkInfo);
        }
    }
    return value;
}

void CallHistoryModel::removeTheCallHistory(QString info, int rows)
{
    int temp = 0;
    bool bIsFind = false;
    for (int i = 0; i < rows; i++) {
        if (m_idList[i].second == info) {
            bIsFind = true;
            temp = i;
            break;
        }
    }
    if (bIsFind) {
        beginRemoveRows(QModelIndex(),temp,temp);
        m_idList.removeAt(temp);
        endRemoveRows();
    }
}

MessageModel::MessageModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_messageAdaptor = MessageManagerAdaptor::getInstance();
    m_contacterAdaptor = ContacterInterfaceAdaptor::getInstance();
    messages = new QMap<QString ,Message>;
}

void MessageModel::setModelList(QString groupId)
{

    m_groupID = groupId;
    beginResetModel();
    messages->clear();
    m_idList = m_messageAdaptor->getMessageList(groupId);
    endResetModel();
    emit signalFreshEnd();
}

int MessageModel::rowCount(const QModelIndex &parent) const
{
    return m_idList.count();
}

int MessageModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant MessageModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    QString data;
    if(role < Qt::UserRole)
    {
        qDebug() << "MessageModel::data(const QModelIndex &index, int role) const";
    }
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        QString rowId = m_idList.at(index.row());
        Message msg;// = m_messageAdaptor->getMessage(rowId , m_groupID);
        if(!messages->contains(rowId))
        {
            msg = m_messageAdaptor->getMessage(rowId , m_groupID);
            messages->insert(rowId, msg);
        }
        msg = messages->value(rowId);

        int messageType = 0;
        if (msg.common.type == 1){
            data = msg.content.data();
            messageType = 1;
        }
        else if (msg.common.type == 2)
        {
            data = msg.contentName;
            messageType = 2;
        }
        else if (msg.common.type == 4)
        {
            data = msg.contentName;
            messageType = 4;
        }
        else if (msg.common.type == 5)
        {
            data = msg.contentName;
            messageType = 5;
        }
        else if (msg.common.type == 3)
        {
            data = msg.contentName;
            messageType = 3;
        }
        else if (msg.common.type == 6)
        {
            data = msg.common.showMsg;
            messageType = 6;
        }
        else if (msg.common.type == 7)
        {
            data = msg.contentName;
            messageType = 7;
        }
        else if (msg.common.type == 8)
        {
            data = msg.contentName;
            messageType = 8;
        }
        else if (msg.common.type == 10)
        {
            data = msg.contentName;
            messageType = 10;
        }
        QString userId,flag,messageState,fileName,text,direction,messId,photoPath;
        direction = "left";
        if (msg.common.userId == m_contacterAdaptor->getLocalInfo().id){
            direction = "right";
            photoPath = m_contacterAdaptor->getLocalInfo().photoPath;
        }else {
            //photoPath = m_contacterAdaptor->getLocalInfo().photoPath;
            photoPath = m_contacterAdaptor->getContacter(msg.common.userId).photoPath;
        }
        if (columnIdx == 0) {
            value = QVariant::fromValue(msg.common.userId);
        } else if (columnIdx == 1) {
            value = QVariant::fromValue(messageType);
        } else if (columnIdx == 2) {
            value = QVariant::fromValue(msg.common.state);
        } else if (columnIdx == 3) {
            value = QVariant::fromValue(msg.senderRealName);
        } else if (columnIdx == 4) {
            value = QVariant::fromValue(data);
        } else if (columnIdx == 5) {
            value = QVariant::fromValue(direction);
        }else if (columnIdx == 6) {
            value = QVariant::fromValue(msg.common.id);
        }else if (columnIdx == 7) {
            value = QVariant::fromValue(photoPath);
        }else if (columnIdx == 8) {
            value = QVariant::fromValue(msg.common.isRead);
        }
        else if (columnIdx == 9) {
            value = QVariant::fromValue(msg.common.date);
        }
        else if (columnIdx == 10) {
            value = QVariant::fromValue(index.row());
        }
    }
    return value;
}

QVariant MessageModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

QHash<int, QByteArray> MessageModel::roleNames() const
{
    return m_roleNames;
}

void MessageModel::setRoles(const QStringList &names)
{
    m_roleNames.clear();
    for(int idx=0; idx<names.count(); idx++)
    {
        m_roleNames[Qt::UserRole + idx + 1] = names[idx].toLocal8Bit();
    }
}

QVariant MessageModel::getMessageValue(int index, QString key)
{
    if (index < 0)
        index = 0;
    Message msg;
    QString text;
    QHash<QString, QVariant> MessageModelHash;
    msg = m_messageAdaptor->getMessage(m_idList.at(index), m_groupID);
    if (msg.common.state == 1)
        text = msg.content.data();
    else
        text = msg.contentName;
    MessageModelHash.insert("userId",msg.common.userId);
    MessageModelHash.insert("messageState",msg.common.state);
    MessageModelHash.insert("fileName",msg.senderRealName);
    MessageModelHash.insert("text",text);
    MessageModelHash.insert("messId",msg.common.id);
    MessageModelHash.insert("time",msg.common.date);
    if (key == "") {
        return MessageModelHash;
    } else {
        return MessageModelHash.value(key);
    }
}

void MessageModel::removeMessage(QString info, int rows)
{

}

void MessageModel::getImageList()
{
    QStringList list = m_idList;
    Message msg;
    for (int i = 0; i < list.count(); i++)
    {
        msg = m_messageAdaptor->getMessage(list.at(i), m_groupID);
        if (msg.common.type == 2 && QFile::exists(msg.contentName.section("/",2,-1))){
            emit signalFindImage(msg.contentName);
        }
    }

}

int MessageModel::getCount()
{
    return m_idList.count();
}
*/
