#ifndef STATISTICALTREND_H
#define STATISTICALTREND_H

#include <QObject>
#include "Interface/PresetElement.h"

struct WeldActualParameter
{
    QString CrossSection;
    QString Energy;
    QString TriggerPressure;
    QString WeldPressure;
    QString Amplitude;
    QString Width;
    QString Time;
    QString PeakPower;
    QString PreHeight;
    QString PostHeight;
    QString WorkOrderName;
    QString PartName;
    QString DateCreated;
};
struct StatisticsParameter
{
    QString SampleSize;
    QString Mean;
    QString Median;
    QString Sigma;
    QString Cpk;
};
enum QUALITYTYPE
{
    QUALITYTIME,
    QUALITYPOWER,
    QUALITYPREHEIGHT,
    QUALITYPOSTHEIGHT,
};

class StatisticalTrend : public QObject
{
    Q_OBJECT
private:
    PresetElement CurrentPreset;
    QMap<int, QString> RetrievedWeldResultIndexList;
    QList<float> DataList[4];
private:
    bool GetCurrentPresetFromLibrary(int SpliceID, QString SpliceName);
    bool GetCurrentWeldResultList(QString SpliceName, unsigned int HashCode,
                                  unsigned int time_from, unsigned int time_to);
    bool GetCurrentWeldResultOneByOne(QMap<int, QString>* ResultIndex);
    bool GetStatisticsParameter();
public:
    QList<struct WeldActualParameter> CurrentWeldParameterList;
    struct StatisticsParameter CurrentStatisticsParameter[4];
public:
    void _apply(int, QString, unsigned int time_from, unsigned int time_to);
public:
    explicit StatisticalTrend(QObject *parent = 0);

signals:
    void _ProcessFinished(const bool &_Result);
public slots:
};

#endif // STATISTICALTREND_H
