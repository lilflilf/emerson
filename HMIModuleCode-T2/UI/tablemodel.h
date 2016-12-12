#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QHash>
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

class WorkOrderModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit WorkOrderModel(QObject *parent = 0);
    void setModelList(unsigned int time_from, unsigned int time_to);

    void setModelList();

    QStringList m_idList;
    DBWorkOrderTable *m_workOrderAdaptor;
    QMap<int, QString> *workOrders;

protected:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QHash<int, QByteArray> roleNames() const;

signals:


public slots:
    void setRoles(const QStringList &names);
    Q_INVOKABLE QVariant getWorkOrderValue(int index, QString key);
    Q_INVOKABLE void removeValue(int id, QString name);
    Q_INVOKABLE int getPartId(int index);

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


class SpliceModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SpliceModel(QObject *parent = 0);
    void setModelList(unsigned int time_from, unsigned int time_to);
    void setModelList();

    QStringList m_idList;
    DBPresetTable *m_spliceAdaptor;
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
signals:


public slots:
    void setRoles(const QStringList &names);
    Q_INVOKABLE QVariant getValue(int index, QString key); // table
    Q_INVOKABLE void removeValue(int id, QString name);
    Q_INVOKABLE int count();
    Q_INVOKABLE void calculateSpliceData();

    Q_INVOKABLE QString getStructValue(QString valueKey, QString valueType); // create wire
    Q_INVOKABLE void createNew();
    Q_INVOKABLE QString getString(QString type, int value);
    Q_INVOKABLE bool getWeldMode(QString type,int index);
//    Q_INVOKABLE void setNewValue();

private:
    QHash<int, QByteArray> m_roleNames;
    VariantToString *m_variant;
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
    Q_INVOKABLE int getWorkStationRows(int id, QString name);
    Q_INVOKABLE int getWorkStationColumns(int id, QString name);
    Q_INVOKABLE int getWorkStationMaxSplicePerZone(int id, QString name);
    Q_INVOKABLE int getWorkStationCount(int id, QString name);
    Q_INVOKABLE int getWorkStationMaxSplicePerStation(int id, QString name);
    Q_INVOKABLE QList<int> getWorkStationCorlor(int id, QString name);
    Q_INVOKABLE QList<int> geteWorkStationZone(int id, QString name);
    Q_INVOKABLE bool getPartOnlineOrOffLine(int id, QString name);
    Q_INVOKABLE QStringList getCurrentPartOfSpliceName(int id, QString name);
    Q_INVOKABLE QList<int> getCurrentPartOfSpliceId(int id, QString name);
    Q_INVOKABLE int count();
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
    Q_INVOKABLE void insertValue(QString name, QString passwd);
    Q_INVOKABLE bool login(QString passwd, OperatorElement *operatot);
    Q_INVOKABLE void removeValue(int id, QString name);

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
    void setModelList();

    QStringList m_idList;
    DBAlarmLogTable *m_alarmAdaptor;
    QMap<int, QString> *alarms;
    DBWeldResultTable *m_weldHistoryAdaptor;

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

    Q_INVOKABLE QVariant getValue(int index, QString key);
    Q_INVOKABLE int count();
    Q_INVOKABLE void removeValue(int id, QString name);
    Q_INVOKABLE int insertValueToTable(QString type, QString wireName, int wireId, int operatorId, QString color, QString stripeColor, int stripeType, QString gauge, int wireType, int side, int verside, int position);

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

private:
    QHash<int, QByteArray> m_roleNames;
};


#endif // TABLEMODEL_H
