#include "StatisticalTrend.h"
#include "DataBase/DBPresetTable.h"
#include "DataBase/DBWeldResultTable.h"
#include "Interface/WeldResultElement.h"
//#include "Interface/Definition.h"
#include "Modules/UtilityClass.h"
#include "Modules/StatisticalFunction.h"
#include "Modules/Statistics.h"
#include "Modules/typedef.h"
#include <QDateTime>
#include <QDebug>
StatisticalTrend::StatisticalTrend(QObject *parent) : QObject(parent)
{

}

bool StatisticalTrend::GetCurrentPresetFromLibrary(int SpliceID, QString SpliceName)
{

    DBPresetTable* _DBPreset = DBPresetTable::Instance();
    bool bResult = _DBPreset->QueryOneRecordFromTable(SpliceID, SpliceName, &CurrentPreset);
    return bResult;
}

bool StatisticalTrend::GetCurrentWeldResultList(QString SpliceName, unsigned int HashCode,
                                                unsigned int time_from, unsigned int time_to)
{
    DBWeldResultTable* _DBWeldResult = DBWeldResultTable::Instance();
    bool bResult = _DBWeldResult->QueryBySomeFields(SpliceName, HashCode,
                time_from, time_to, &RetrievedWeldResultIndexList);
    return bResult;
}

bool StatisticalTrend::GetCurrentWeldResultOneByOne(QMap<int, QString>* ResultIndex)
{
    DBWeldResultTable* _DBWeldResult = DBWeldResultTable::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();
    Statistics* _Statistics = Statistics::Instance();
    WeldResultElement CurrentWeldResultRecord;
    bool bResult = false;
    DataList[QUALITYTIME].clear();
    RawQualityWindowList[QUALITYTIME].clear();
    DataList[QUALITYPOWER].clear();
    RawQualityWindowList[QUALITYPOWER].clear();
    DataList[QUALITYPREHEIGHT].clear();
    RawQualityWindowList[QUALITYPREHEIGHT].clear();
    DataList[QUALITYPOSTHEIGHT].clear();
    RawQualityWindowList[QUALITYPOSTHEIGHT].clear();
    struct WeldActualParameter CurrentWeldActual;
    if(ResultIndex->isEmpty() == true)
        return false;
    QMap<int, QString>::const_iterator iterator = ResultIndex->constBegin();
    while (iterator != ResultIndex->constEnd()) {
        bResult =_DBWeldResult->QueryOneRecordFromTable(iterator.key(),
                iterator.value(), &CurrentWeldResultRecord);
        if(bResult == true)
        {
            float time = _Utility->FormatedDataToFloat(DINActTime,
                        CurrentWeldResultRecord.ActualResult.ActualTime);
            float peakpower = _Utility->FormatedDataToInteger(DINActPower,
                        CurrentWeldResultRecord.ActualResult.ActualPeakPower);
            float preheight = _Utility->FormatedDataToFloat(DINActPreHgt,
                        CurrentWeldResultRecord.ActualResult.ActualPreheight);
            float postheight = _Utility->FormatedDataToFloat(DINActHgt,
                        CurrentWeldResultRecord.ActualResult.ActualPostheight);
            if(CurrentPreset.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode == STEPWELD::STEPDISABLE)
                CurrentWeldActual.Amplitude = _Utility->FormatedDataToString(DINAmplitude,
                        CurrentWeldResultRecord.ActualResult.ActualAmplitude);
            else
                CurrentWeldActual.Amplitude = _Utility->FormatedDataToString(DINAmplitude,
                        CurrentWeldResultRecord.ActualResult.ActualAmplitude) + "/" +
                        _Utility->FormatedDataToString(DINAmplitude2,
                        CurrentWeldResultRecord.ActualResult.ActualAmplitude2);
            CurrentWeldActual.CrossSection = _Utility->FormatedDataToString(DINCrossSection,
                        CurrentPreset.CrossSection);
            QDateTime TimeLabel = QDateTime::fromTime_t(CurrentWeldResultRecord.CreatedDate);
            CurrentWeldActual.DateCreated  = TimeLabel.toString("MM/dd/yyyy hh:mm:ss");
            CurrentWeldActual.Energy = _Utility->FormatedDataToString(DINEnergy,
                        CurrentWeldResultRecord.ActualResult.ActualEnergy);
            CurrentWeldActual.SequenceName = CurrentWeldResultRecord.CurrentSequence.SequenceName;
            CurrentWeldActual.HarnessName = CurrentWeldResultRecord.CurrentHarness.HarnessName;
            CurrentWeldActual.PeakPower = _Utility->FormatedDataToString(DINActPower,
                        CurrentWeldResultRecord.ActualResult.ActualPeakPower);
            CurrentWeldActual.PostHeight = _Utility->FormatedDataToString(DINActHgt,
                        CurrentWeldResultRecord.ActualResult.ActualPostheight);
            CurrentWeldActual.PreHeight = _Utility->FormatedDataToString(DINActPreHgt,
                        CurrentWeldResultRecord.ActualResult.ActualPreheight);
            CurrentWeldActual.Time = _Utility->FormatedDataToString(DINActTime,
                        CurrentWeldResultRecord.ActualResult.ActualTime);
            CurrentWeldActual.TriggerPressure = _Utility->FormatedDataToString(DINTriggerPressure,
                        CurrentWeldResultRecord.ActualResult.ActualTPressure);
            CurrentWeldActual.WeldPressure = _Utility->FormatedDataToString(DINPressure,
                        CurrentWeldResultRecord.ActualResult.ActualPressure);
            CurrentWeldActual.Width = _Utility->FormatedDataToString(DINWidth,
                        CurrentWeldResultRecord.ActualResult.ActualWidth);
            CurrentWeldParameterList.push_back(CurrentWeldActual);
            DataList[QUALITYTIME].push_back(time);
            RawQualityWindowList[QUALITYTIME].push_back(CurrentWeldResultRecord.ActualResult.ActualTime);
            DataList[QUALITYPOWER].push_back(peakpower);
            RawQualityWindowList[QUALITYPOWER].push_back(CurrentWeldResultRecord.ActualResult.ActualPeakPower);
            DataList[QUALITYPREHEIGHT].push_back(preheight);
            RawQualityWindowList[QUALITYPREHEIGHT].push_back(CurrentWeldResultRecord.ActualResult.ActualPreheight);
            DataList[QUALITYPOSTHEIGHT].push_back(postheight);
            RawQualityWindowList[QUALITYPOSTHEIGHT].push_back(CurrentWeldResultRecord.ActualResult.ActualPostheight);
            RetrievedWeldResultList.push_back(_Statistics->HistoryEvent(&CurrentWeldResultRecord, &CurrentPreset));
        }
        ++iterator;
    }
    return true;
}

bool StatisticalTrend::GetStatisticsParameter()
{
    bool bResult = false;
    UtilityClass* _Utility = UtilityClass::Instance();
    int size;
    float mean, median, sigma, CPK;
    float USL, LSL, UCL, LCL;
    int tmp = 0;
    for(int i = QUALITYTIME; i <= QUALITYPOSTHEIGHT; i++)
    {
        switch (i)
        {
        case QUALITYTIME:
            tmp = CurrentPreset.WeldSettings.QualitySetting.Time.Plus;
            CurrentStatisticsParameter[i].UpperSpecLimit = tmp;
            USL = _Utility->FormatedDataToFloat(DINTimePl, tmp);
            tmp = CurrentPreset.WeldSettings.QualitySetting.Time.Minus;
            CurrentStatisticsParameter[i].LowerSpecLimit = tmp;
            LSL = _Utility->FormatedDataToFloat(DINTimeMs, tmp);
            break;
        case QUALITYPOWER:
            tmp = CurrentPreset.WeldSettings.QualitySetting.Power.Plus;
            CurrentStatisticsParameter[i].UpperSpecLimit = tmp;
            USL = _Utility->FormatedDataToFloat(DINPowerPl, tmp);
            tmp = CurrentPreset.WeldSettings.QualitySetting.Power.Minus;
            CurrentStatisticsParameter[i].LowerSpecLimit = tmp;
            LSL = _Utility->FormatedDataToFloat(DINPowerMs, tmp);
            break;
        case QUALITYPREHEIGHT:
            tmp = CurrentPreset.WeldSettings.QualitySetting.Preheight.Plus;
            CurrentStatisticsParameter[i].UpperSpecLimit = tmp;
            USL = _Utility->FormatedDataToFloat(DINPre_HgtPl, tmp);
            tmp = CurrentPreset.WeldSettings.QualitySetting.Preheight.Minus;
            CurrentStatisticsParameter[i].LowerSpecLimit = tmp;
            LSL = _Utility->FormatedDataToFloat(DINPre_HgtMs, tmp);
            break;
        case QUALITYPOSTHEIGHT:
            tmp = CurrentPreset.WeldSettings.QualitySetting.Height.Plus;
            CurrentStatisticsParameter[i].UpperSpecLimit = tmp;
            USL = _Utility->FormatedDataToFloat(DINHeightPl, tmp);
            tmp = CurrentPreset.WeldSettings.QualitySetting.Height.Minus;
            CurrentStatisticsParameter[i].LowerSpecLimit = tmp;
            LSL = _Utility->FormatedDataToFloat(DINHeightMs, tmp);
            break;
        default:
            break;
        }
        StatisticalFunction::StatisticalFun(&size, &mean, &median, &sigma, &CPK,
                &DataList[i], USL, LSL);

        switch(i)
        {
        case QUALITYTIME:
            CurrentStatisticsParameter[i].Mean.sprintf("%.4fs", mean);
            CurrentStatisticsParameter[i].Median.sprintf("%.2fs", median);
            break;
        case QUALITYPOWER:
            CurrentStatisticsParameter[i].Mean.sprintf("%.4fw", mean);
            CurrentStatisticsParameter[i].Median.sprintf("%dw", (int)median);
            break;
        case QUALITYPREHEIGHT:
            CurrentStatisticsParameter[i].Mean.sprintf("%.4fmm", mean);
            CurrentStatisticsParameter[i].Median.sprintf("%.2fmm", median);
            break;
        case QUALITYPOSTHEIGHT:
            CurrentStatisticsParameter[i].Mean.sprintf("%.4fmm", mean);
            CurrentStatisticsParameter[i].Median.sprintf("%.2fmm", median);
            break;
        }
        CurrentStatisticsParameter[i].Sigma.sprintf("%.4f", sigma);
        CurrentStatisticsParameter[i].Cpk.sprintf("%.4f", CPK);
        CurrentStatisticsParameter[i].SampleSize = QString::number(size, DECIMALISM);

        UCL = mean + 6 * sigma;
        LCL = mean - 6 * sigma;

        switch(i)
        {
        case QUALITYTIME:
            CurrentStatisticsParameter[i].UpperControlLimit =
                    UCL / _Utility->txtData[DINActTime].Factor;
            CurrentStatisticsParameter[i].LowerControlLimit =
                    LCL / _Utility->txtData[DINActTime].Factor;
            CurrentStatisticsParameter[i].WhiteMean =
                    mean / _Utility->txtData[DINActTime].Factor;
            break;
        case QUALITYPOWER:
            CurrentStatisticsParameter[i].UpperControlLimit =
                    UCL / _Utility->txtData[DINActPower].Factor;
            CurrentStatisticsParameter[i].LowerControlLimit =
                    LCL / _Utility->txtData[DINActPower].Factor;
            CurrentStatisticsParameter[i].WhiteMean =
                    mean / _Utility->txtData[DINActPower].Factor;
            break;
        case QUALITYPREHEIGHT:
            CurrentStatisticsParameter[i].UpperControlLimit =
                    UCL / _Utility->txtData[DINActPreHgt].Factor;
            CurrentStatisticsParameter[i].LowerControlLimit =
                    LCL / _Utility->txtData[DINActPreHgt].Factor;
            CurrentStatisticsParameter[i].WhiteMean =
                    mean / _Utility->txtData[DINActPreHgt].Factor;
            break;
        case QUALITYPOSTHEIGHT:
            CurrentStatisticsParameter[i].UpperControlLimit =
                    UCL / _Utility->txtData[DINActHgt].Factor;
            CurrentStatisticsParameter[i].LowerControlLimit =
                    LCL / _Utility->txtData[DINActHgt].Factor;
            CurrentStatisticsParameter[i].WhiteMean =
                    mean / _Utility->txtData[DINActHgt].Factor;
            break;
        }
    }
    return bResult;
}

void StatisticalTrend::Initialization()
{
    CurrentWeldParameterList.clear();
    RetrievedWeldResultList.clear();
    for(int i = QUALITYTIME; i <= QUALITYPOSTHEIGHT; i++)
    {
        CurrentStatisticsParameter[i].Cpk.clear();
        CurrentStatisticsParameter[i].LowerControlLimit = 0;
        CurrentStatisticsParameter[i].LowerSpecLimit = 0;
        CurrentStatisticsParameter[i].Mean.clear();
        CurrentStatisticsParameter[i].Median.clear();
        CurrentStatisticsParameter[i].SampleSize.clear();
        CurrentStatisticsParameter[i].Sigma.clear();
        CurrentStatisticsParameter[i].UpperControlLimit = 0;
        CurrentStatisticsParameter[i].UpperSpecLimit = 0;
        CurrentStatisticsParameter[i].WhiteMean = 0;
        RawQualityWindowList[i].clear();
    }
}

void StatisticalTrend::_apply(int SpliceID, QString SpliceName,
                              unsigned int time_from, unsigned int time_to)
{
    Initialization();
    bool bResult = GetCurrentPresetFromLibrary(SpliceID, SpliceName);
    if(bResult == false)
        return;
    bResult = GetCurrentWeldResultList(CurrentPreset.SpliceName,
                CurrentPreset.HashCode, time_from, time_to);
    if(bResult == false)
        return;
    bResult = GetCurrentWeldResultOneByOne(&RetrievedWeldResultIndexList);
    if(bResult == false)
        return;
    GetStatisticsParameter();
    emit _ProcessFinished(bResult);
}

QString StatisticalTrend::StatisticsHeaderString(QUALITYTYPE QualityItem)
{
    QString TempStr = "\t" + QObject::tr("SampleSize") + "\t" +
            QObject::tr("Mean") + "\t" + QObject::tr("Median") + "\t" +
            QObject::tr("Sigma") + "\t" + QObject::tr("CPK");
    QString HeaderStr;
    switch(QualityItem)
    {
    case QUALITYTIME:
        HeaderStr = QObject::tr("Statistics Time") + TempStr;
        break;
    case QUALITYPOWER:
        HeaderStr = QObject::tr("Statistics Peak Power") + TempStr;
        break;
    case QUALITYPREHEIGHT:
        HeaderStr = QObject::tr("Statistics Pre-Height") + TempStr;
        break;
    case QUALITYPOSTHEIGHT:
        HeaderStr = QObject::tr("Statistics Post Height") + TempStr;
        break;
    default:
        HeaderStr.clear();
        break;
    }
    return HeaderStr;
}

QString StatisticalTrend::StatisticsRecordString(StatisticsParameter StatisticsStruct)
{
    QString RecordStr = "\t" + StatisticsStruct.SampleSize + "\t" +
            StatisticsStruct.Mean + "\t" + StatisticsStruct.Median + "\t" +
            StatisticsStruct.Sigma + "\t" + StatisticsStruct.Cpk;
    return RecordStr;
}

bool StatisticalTrend::ExportData(QString fileUrl)
{
    Statistics* _Statistics = Statistics::Instance();
    QString fileSource;
    bool bResult = false;
    int i = 0;
    fileSource = fileUrl;
    bResult = fileSource.contains("file:///");
    if(bResult == false)
        return bResult;
    fileSource = fileSource.mid(8);
    QFile csvFile(fileSource);
    bResult = csvFile.open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Truncate);
    if(bResult == false)
        return bResult;
    QDateTime TimeLabel = QDateTime::currentDateTime();
    QString TimeStr = TimeLabel.toString("yyyy/MM/dd hh:mm:ss");
    QString TitleStr = "Weld Data Statistical Analysis " + TimeStr;
    QString HeaderStr = _Statistics->HeaderString();
    if(RetrievedWeldResultList.isEmpty() == true)
        return false;
    QTextStream out(&csvFile);
    out << TitleStr << '\n'
        << HeaderStr << '\n';
    for(i = 0; i < RetrievedWeldResultList.size(); i++)
    {
        out << RetrievedWeldResultList[i] << '\n';
    }
    for(i = QUALITYTIME; i <= QUALITYPOSTHEIGHT; i++)
    {
        out << StatisticsHeaderString((QUALITYTYPE)i) << '\n'
            << StatisticsRecordString(CurrentStatisticsParameter[i]) << '\n';
    }
    csvFile.close();
    return true;
}
