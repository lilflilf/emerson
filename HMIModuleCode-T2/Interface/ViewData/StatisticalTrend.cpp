#include "StatisticalTrend.h"
#include "DataBase/DBPresetTable.h"
#include "DataBase/DBWeldResultTable.h"
#include "Interface/WeldResultElement.h"
//#include "Interface/Definition.h"
#include "Modules/UtilityClass.h"
#include "Modules/StatisticalFunction.h"
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
    QMap<int, QString>::const_iterator i = ResultIndex->constBegin();
    while (i != ResultIndex->constEnd()) {
        bResult =_DBWeldResult->QueryOneRecordFromTable(i.key(), i.value(), &CurrentWeldResultRecord);
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
            if(CurrentPreset.WeldSettings.AdvanceSetting.StepWeld.StepWeldMode == STEPDISABLE)
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
            CurrentWeldActual.PartName = CurrentWeldResultRecord.CurrentPart.PartName;
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
            CurrentWeldActual.WorkOrderName = CurrentWeldResultRecord.CurrentWorkOrder.WorkOrderName;
            CurrentWeldParameterList.push_back(CurrentWeldActual);
            DataList[QUALITYTIME].push_back(time);
            RawQualityWindowList[QUALITYTIME].push_back(CurrentWeldResultRecord.ActualResult.ActualTime);
            DataList[QUALITYPOWER].push_back(peakpower);
            RawQualityWindowList[QUALITYPOWER].push_back(CurrentWeldResultRecord.ActualResult.ActualPeakPower);
            DataList[QUALITYPREHEIGHT].push_back(preheight);
            RawQualityWindowList[QUALITYPREHEIGHT].push_back(CurrentWeldResultRecord.ActualResult.ActualPreheight);
            DataList[QUALITYPOSTHEIGHT].push_back(postheight);
            RawQualityWindowList[QUALITYPOSTHEIGHT].push_back(CurrentWeldResultRecord.ActualResult.ActualPostheight);
        }
        ++i;
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
        CurrentStatisticsParameter[i].SampleSize = QString::number(size, 10);
        float CentralValue = (USL + LSL)/ 2;
        if(USL > (3 * sigma))
            UCL = USL - 3 * sigma;
        else
            UCL = USL;
        if(UCL < CentralValue)
            UCL = CentralValue;
        LCL = LSL + 3 * sigma;
        if(LCL > CentralValue)
            LCL = CentralValue;
        switch(i)
        {
        case QUALITYTIME:
            CurrentStatisticsParameter[i].UpperControlLimit =
                    UCL / _Utility->txtData[DINActTime].Factor;
            CurrentStatisticsParameter[i].LowerControlLimit =
                    LCL / _Utility->txtData[DINActTime].Factor;
            break;
        case QUALITYPOWER:
            CurrentStatisticsParameter[i].UpperControlLimit =
                    UCL / _Utility->txtData[DINActPower].Factor;
            CurrentStatisticsParameter[i].LowerControlLimit =
                    LCL / _Utility->txtData[DINActPower].Factor;
            break;
        case QUALITYPREHEIGHT:
            CurrentStatisticsParameter[i].UpperControlLimit =
                    UCL / _Utility->txtData[DINActPreHgt].Factor;
            CurrentStatisticsParameter[i].LowerControlLimit =
                    LCL / _Utility->txtData[DINActPreHgt].Factor;
            break;
        case QUALITYPOSTHEIGHT:
            CurrentStatisticsParameter[i].UpperControlLimit =
                    UCL / _Utility->txtData[DINActHgt].Factor;
            CurrentStatisticsParameter[i].LowerControlLimit =
                    LCL / _Utility->txtData[DINActHgt].Factor;
            break;
        }
    }
    return bResult;
}

void StatisticalTrend::Initialization()
{
    CurrentWeldParameterList.clear();
    for(int i = 0; i< 4; i++)
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
        RawQualityWindowList[i].clear();
    }
}

void StatisticalTrend::_apply(int SpliceID, QString SpliceName,
                              unsigned int time_from, unsigned int time_to)
{
    Initialization();
    bool bResult = GetCurrentPresetFromLibrary(SpliceID, SpliceName);
    if(bResult == true)
        bResult = GetCurrentWeldResultList(CurrentPreset.SpliceName,
                CurrentPreset.HashCode, time_from, time_to);
    if(bResult == true)
        bResult = GetCurrentWeldResultOneByOne(&RetrievedWeldResultIndexList);
    if(bResult == true) {
         GetStatisticsParameter();
    }
    emit _ProcessFinished(bResult);
}
