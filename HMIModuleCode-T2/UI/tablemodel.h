#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QHash>
#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include "DataBase/DBWorkOrderTable.h"
#include "DataBase/DBPresetTable.h"
#include "DataBase/DBPartTable.h"
#include "DataBase/DBOperatorTable.h"
#include "DataBase/DBAlarmLogTable.h"
#include "DataBase/DBWeldResultTable.h"
#include "DataBase/DBWireTable.h"
//#include "Interface/Definition.h"
#include "Interface/WireElement.h"
#include "Interface/PresetElement.h"
#include "Interface/PartElement.h"
#include "Interface/WorkOrderElement.h"
#include "Interface/AlarmElement.h"
#include "Interface/WeldResultElement.h"
#include "Interface/Settings/OperatorLibrary.h"
#include "DataBase/DBMaintenanceLogTable.h"
#include "Interface/Maintenance/MaintenanceLog.h"
#include "Interface/variantToString.h"
#include "Interface/StringToVariant.h"
#include "Interface/Settings/PermissionSetting.h"
#include "Interface/UpperRightIcon/AlarmIcon.h"

class WorkOrderModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit WorkOrderModel(QObject *parent = 0);
    void setModelList(unsigned int time_from, unsigned int time_to);

    void setModelList();

    QStringList m_idList;
    DBWorkOrderTable *m_workOrderAdaptor;
    DBPartTable *m_partAdaptor;
    QMap<int, QString> *workOrders;
    PartElement partElement;
    WorkOrderElement workOrderElement;

protected:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QHash<int, QByteArray> roleNames() const;

signals:


public slots:
    void setRoles(const QStringList &names);
    Q_INVOKABLE QVariant getValue(int index, QString key);
    Q_INVOKABLE void removeValue(int id, QString name);
    Q_INVOKABLE int getPartId(int index);
    Q_INVOKABLE QList<int> getSpliceList();
    Q_INVOKABLE void editNew(int index);
    Q_INVOKABLE QVariant getStructValue(QString key);

    //    QString getContacterName(QString contacterId);
    Q_INVOKABLE int count();
    //    void removeContacter(QString info,int rows);
    int getCurrentIndex(QString info);
    //    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Q_INVOKABLE bool updateRecordIntoTable(int workId, QString oldWorkName, QString workName, int partId, QString partName, int count);
    Q_INVOKABLE bool insertRecordIntoTable(QString workName, int partId, QString partName, int count);

private:
    QHash<int, QByteArray> m_roleNames;
};


class SplicesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SplicesModel(QObject *parent = 0);
    void setModelList(unsigned int time_from, unsigned int time_to);
    void setModelList();

    QStringList m_idList;
    DBPresetTable *m_spliceAdaptor;
    DBWireTable * m_wireAdaptor;
    DBOperatorTable *m_operatorAdaptor;
    QMap<int, QString> *splices;

 protected:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QHash<int, QByteArray> roleNames() const;

    PresetElement presetElement;
    VariantToString *variantToString;
    StringToVariant *stringToVariant;
signals:


public slots:
    void setRoles(const QStringList &names);
    Q_INVOKABLE QVariant getValue(int index, QString key); // table
    Q_INVOKABLE void removeValue(int id, QString name);
    Q_INVOKABLE int count();
    Q_INVOKABLE void calculateSpliceData();

    Q_INVOKABLE QString getStructValue(QString valueKey, QString valueType); // create wire
    Q_INVOKABLE int getRawData(QString key);
    Q_INVOKABLE void setStructValue(QString valueKey, QVariant value);
    Q_INVOKABLE int saveSplice(bool bIsEdit);
    Q_INVOKABLE uint getHashCode();

    Q_INVOKABLE void createNew();
    Q_INVOKABLE void editNew(int spliceId);
    Q_INVOKABLE QString getString(QString type, int value);
    Q_INVOKABLE bool getWeldMode(QString type,int index);
    Q_INVOKABLE QList<int> getWireIdList();
    Q_INVOKABLE QString graphTimeToString(int time);
    Q_INVOKABLE QString graphPowerToString(int power);
    Q_INVOKABLE QString graphHeightToString(int height);

    QString timePlusToString(int time);
    QString timeMinusToString(int time);
    QString actualTimeToString(int ActualTime);
    QString actualPowerToString(int ActualPower);
    QString actualPreHeightToString(int ActualPreHeight);
    QString actualHeightToString(int ActualHeight);

    void updateSplice(PresetElement presetElement);
private:
    QHash<int, QByteArray> m_roleNames;
};


class PartModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit PartModel(QObject *parent = 0);
    void setModelList(unsigned int time_from, unsigned int time_to);

    void setModelList();

    QStringList m_idList;
    DBPartTable *m_partAdaptor;
    DBOperatorTable *m_operatorAdaptor;
    QMap<int, QString> *parts;
    PartElement *m_Part;

protected:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QHash<int, QByteArray> roleNames() const;

signals:

public slots:
    void setRoles(const QStringList &names);
    Q_INVOKABLE QVariant getValue(int index, QString key);
    Q_INVOKABLE void getPartInfo(bool bIsEdit, int id, QString name);
    Q_INVOKABLE void removeValue(int id, QString name);
    Q_INVOKABLE int getWorkStationRows();
    Q_INVOKABLE int getWorkStationColumns();
    Q_INVOKABLE int getWorkStationMaxSplicePerZone();
    Q_INVOKABLE int getWorkStationCount();
    Q_INVOKABLE int getWorkStationMaxSplicePerStation();
    Q_INVOKABLE int getCurrentPartSpliceCount();
    Q_INVOKABLE QList<int> getWorkStationCorlor();
    Q_INVOKABLE QList<int> geteWorkStationZone();
    Q_INVOKABLE bool getPartOnlineOrOffLine();
    Q_INVOKABLE QStringList getCurrentPartOfSpliceName();
    Q_INVOKABLE QList<int> getCurrentPartOfSpliceId();
    Q_INVOKABLE void setPartOffLineOrOnLine(bool bIsLine);
    Q_INVOKABLE void setPartName(QString name);
    Q_INVOKABLE void setPartColumns(int columns);
    Q_INVOKABLE void setPartRows(int rows);
    Q_INVOKABLE void setPartMaxSplicePerWorkStation(int maxNum);
    Q_INVOKABLE void setPartMaxSplicePerZone(int maxNum);
    Q_INVOKABLE void setPartWorkStationNum(int num);
    Q_INVOKABLE void setPartSpliceListClear();
    Q_INVOKABLE void setPartSpliceList(QString name, int id, int station, int zone, int index);
    Q_INVOKABLE void savePartInfo(bool bIsEdit, int operatorId);
    Q_INVOKABLE int count();
    Q_INVOKABLE QVariant getStruceValue(QString key);
   // int getCurrentIndex(QString info);

//    Q_INVOKABLE bool updateRecordIntoTable(int workId, QString oldWorkName, QString workName, int partId, QString partName, int count);
//    Q_INVOKABLE bool insertRecordIntoTable(QString workName, int partId, QString partName, int count);

private:
    QHash<int, QByteArray> m_roleNames;
};


class OperatorModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit OperatorModel(QObject *parent = 0);
    void setModelList(unsigned int time_from, unsigned int time_to);
    void setModelList();

    QStringList m_idList;
    DBOperatorTable *m_operatorAdaptor;
    QMap<int, QString> *operators;
    OperatorElement operatorElement;
    Q_INVOKABLE void editNew(int index);
    Q_INVOKABLE QString getStruckValue(QString key);
    PermissionSetting *permissionSetting;

protected:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QHash<int, QByteArray> roleNames() const;

//signals:


public slots:
    void setRoles(const QStringList &names);
    Q_INVOKABLE QVariant getOperatorValue(int index, QString key);
    Q_INVOKABLE int count();
    Q_INVOKABLE void insertValue(QString name, QString passwd, int level);
    Q_INVOKABLE bool login(QString passwd, OperatorElement *operatot);
    Q_INVOKABLE void removeValue(int id, QString name);
    Q_INVOKABLE void updateOperator(int id, QString name, QString passwd, int level);

private:
    QHash<int, QByteArray> m_roleNames;
};

class AlarmModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit AlarmModel(QObject *parent = 0);
    void setModelList(QString name, unsigned int time_from, unsigned int time_to);
    void setModelList(unsigned int time_from, unsigned int time_to);
    void setModelList(bool bIsNeedReset);

    QStringList m_idList;
    DBAlarmLogTable *m_alarmAdaptor;
    DBPresetTable *m_spliceAdaptor;
    QMap<int, QString> *alarms;
    DBWeldResultTable *m_weldHistoryAdaptor;
    PresetElement m_splice;

    WeldResultElement weldResultElement;
    QDateTime startTime;

protected:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QHash<int, QByteArray> roleNames() const;

//signals:


public slots:
    void setRoles(const QStringList &names);
    Q_INVOKABLE QVariant getAlarmValue(int index, QString key);
    Q_INVOKABLE void removeValue(int id, QString name);
    Q_INVOKABLE void searchAlarmLog(QString name, unsigned int time_from, unsigned int time_to);
    Q_INVOKABLE int count();
    Q_INVOKABLE QList<int> getPoint();
    Q_INVOKABLE QList<int> getPoint2();
    Q_INVOKABLE QList<int> getPointList(QString key, QString spliceName, uint hashCode);
    Q_INVOKABLE int getAxes(QString key);
    Q_INVOKABLE void setStartTime();
    Q_INVOKABLE void updateAlarmLog(int id);

    Q_INVOKABLE void editNew(int weldId, QString weldName);

private:
    QHash<int, QByteArray> m_roleNames;
    VariantToString *variantToString;
};


class WeldHistoryModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit WeldHistoryModel(QObject *parent = 0);
    void setModelList(QString WorkOrderName, QString PartName, QString SpliceName,
                      unsigned int time_from, unsigned int time_to,
                      enum FieldType OrderField = CreatedDateType, bool Orderby = true);
    void setModelList(unsigned int time_from, unsigned int time_to);
    void setModelList();

    QStringList m_idList;
    DBWeldResultTable *m_weldHistoryAdaptor;
    QMap<int, QString> *historys;

protected:
    DBPresetTable *m_spliceTable;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QHash<int, QByteArray> roleNames() const;
    QMap<int, WeldResultElement> historyList;
    QMap<int, PresetElement> presetList;
signals:


public slots:
    void setRoles(const QStringList &names);
    Q_INVOKABLE QVariant getValue(int index, QString key);
    Q_INVOKABLE void weldResultSearch(QString WorkOrderName, QString PartName, QString SpliceName,
                                 unsigned int time_from, unsigned int time_to,
                                 enum FieldType OrderField = CreatedDateType, bool Orderby = true);
    Q_INVOKABLE int count();
    Q_INVOKABLE void removeValue(int id, QString name);

private:
    QHash<int, QByteArray> m_roleNames;
    VariantToString *variantToString;
};


class WireModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit WireModel(QObject *parent = 0);
    void setModelList(unsigned int time_from, unsigned int time_to);

    QStringList m_idList;
    DBWireTable *m_wireAdaptor;
    DBOperatorTable *m_operatorAdaptor;
    QMap<int, QString> *wires;

protected:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QHash<int, QByteArray> roleNames() const;
    WireElement wireElement;
    VariantToString *variantToString;
    StringToVariant *stringToVariant;
//signals:


public slots:
    void setRoles(const QStringList &names);
    Q_INVOKABLE void setModelList();
    Q_INVOKABLE void setTemplateModelList();


    Q_INVOKABLE QVariant getValue(int index, QString key);
    Q_INVOKABLE int count();
    Q_INVOKABLE void removeValue(int id, QString name);
    Q_INVOKABLE int insertValueToTable(QString type, QString wireName, int wireId, int operatorId, QString color, QString stripeColor, int stripeType, int gauge, int awgGauge, int wireType, int side, int verside, int position);
    Q_INVOKABLE void updateSpliceIdToWire(QList<int> wireList, int spliceId);

    Q_INVOKABLE void createNew();
    Q_INVOKABLE void addFromLibrary(int wireId);
    Q_INVOKABLE QVariant getStructValue(QString key);
    Q_INVOKABLE QString getStructValue2(QString key, QString type);
    Q_INVOKABLE int getStructValue3(QString key, QString value);
    Q_INVOKABLE QString getStructValue4(int gauge, int awg);


private:
    QHash<int, QByteArray> m_roleNames;
};


class MaintenanceLogModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MaintenanceLogModel(QObject *parent = 0);
    void setModelList(unsigned int time_from, unsigned int time_to);
    void setModelList(QString Name, unsigned int time_from,unsigned int time_to);
    void setModelList();

    QStringList m_idList;
    DBMaintenanceLogTable *m_maintenanceLogAdaptor;
    QMap<int, QString> *logs;

protected:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QHash<int, QByteArray> roleNames() const;

//signals:


public slots:
    void setRoles(const QStringList &names);
    Q_INVOKABLE QVariant getValue(int index, QString key);
    Q_INVOKABLE int count();
    Q_INVOKABLE void removeValue(int id, QString name);
    Q_INVOKABLE void searchMaintenanceLog(QString Name, unsigned int time_from,unsigned int time_to);

private:
    QHash<int, QByteArray> m_roleNames;
};


#endif // TABLEMODEL_H
