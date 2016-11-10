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
    QMap<int, QString> *splices;

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
    Q_INVOKABLE int count();

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
private:
    QHash<int, QByteArray> m_roleNames;
};

class AlarmModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit AlarmModel(QObject *parent = 0);
    void setModelList(unsigned int time_from, unsigned int time_to);
    void setModelList();

    QStringList m_idList;
    DBAlarmLogTable *m_alarmAdaptor;
    QMap<int, QString> *alarms;

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
    Q_INVOKABLE int count();
private:
    QHash<int, QByteArray> m_roleNames;
};


class WeldHistoryModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit WeldHistoryModel(QObject *parent = 0);
    void setModelList(unsigned int time_from, unsigned int time_to);
    void setModelList();

    QStringList m_idList;
    DBWeldResultTable *m_weldHistoryAdaptor;
    QMap<int, QString> *historys;

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
    Q_INVOKABLE int count();
private:
    QHash<int, QByteArray> m_roleNames;
};



class WireModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit WireModel(QObject *parent = 0);
    void setModelList(unsigned int time_from, unsigned int time_to);
    void setModelList();

    QStringList m_idList;
    DBWireTable *m_wireAdaptor;
    QMap<int, QString> *wires;

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
private:
    QHash<int, QByteArray> m_roleNames;
};


#endif // TABLEMODEL_H
