#include "StatisticalTrend.h"
#include "DataBase/DBPresetTable.h"
#include "DataBase/DBWeldResultTable.h"
#include "Interface/WeldResultElement.h"
//#include "Interface/Definition.h"
#include "Modules/UtilityClass.h"
#include "StatisticalFunction.h"
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
    DataList[QUALITYPOWER].clear();
    DataList[QUALITYPREHEIGHT].clear();
    DataList[QUALITYPOSTHEIGHT].clear();
    struct WeldActualParameter CurrentWeldActual;
    QMap<int, QString>::const_iterator i = ResultIndex->constBegin();
    while (i != ResultIndex->constEnd()) {
        bResult =_DBWeldResult->QueryOneRecordFromTable(i.key(), i.value(), &CurrentWeldResultRecord);
        if(bResult == true)
        {
            float time = _Utility->FormatedDataToFloat(DINActTime,
                        CurrentWeldResultRecord.ActualResult.ActualTime);
            float peakpower = _Utility->FormatedDataToFloat(DINActPower,
                        CurrentWeldResultRecord.ActualResult.ActualPeakPower);
            float preheight = _Utility->FormatedDataToFloat(DINActPreHgt,
                        CurrentWeldResultRecord.ActualResult.ActualPreheight);
            float postheight = _Utility->FormatedDataToFloat(DINActHgt,
                        CurrentWeldResultRecord.ActualResult.ActualPostheight);
            CurrentWeldActual.Amplitude = _Utility->FormatedDataToString(DINAmplitude,
                        CurrentWeldResultRecord.ActualResult.ActualAmplitude);
            CurrentWeldActual.CrossSection = _Utility->FormatedDataToString(DINCrossSection,
                        CurrentPreset.CrossSection);
            CurrentWeldActual.DateCreated  = CurrentWeldActual.DateCreated;
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
            DataList[QUALITYPOWER].push_back(peakpower);
            DataList[QUALITYPREHEIGHT].push_back(preheight);
            DataList[QUALITYPOSTHEIGHT].push_back(postheight);
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
    float USL, LSL;
    int tmp = 0;
    for(int i = QUALITYTIME; i <= QUALITYPOSTHEIGHT; i++)
    {
        switch (i)
        {
        case QUALITYTIME:
            tmp = CurrentPreset.WeldSettings.QualitySetting.Time.Plus;
            USL = _Utility->FormatedDataToFloat(DINTimePl, tmp);
            tmp = CurrentPreset.WeldSettings.QualitySetting.Time.Minus;
            LSL = _Utility->FormatedDataToFloat(DINTimeMs, tmp);
            break;
        case QUALITYPOWER:
            tmp = CurrentPreset.WeldSettings.QualitySetting.Power.Plus;
            USL = _Utility->FormatedDataToFloat(DINPowerPl, tmp);
            tmp = CurrentPreset.WeldSettings.QualitySetting.Power.Minus;
            LSL = _Utility->FormatedDataToFloat(DINPowerMs, tmp);
            break;
        case QUALITYPREHEIGHT:
            tmp = CurrentPreset.WeldSettings.QualitySetting.Preheight.Plus;
            USL = _Utility->FormatedDataToFloat(DINPre_HgtPl, tmp);
            tmp = CurrentPreset.WeldSettings.QualitySetting.Preheight.Minus;
            LSL = _Utility->FormatedDataToFloat(DINPre_HgtMs, tmp);
            break;
        case QUALITYPOSTHEIGHT:
            tmp = CurrentPreset.WeldSettings.QualitySetting.Height.Plus;
            USL = _Utility->FormatedDataToFloat(DINHeightPl, tmp);
            tmp = CurrentPreset.WeldSettings.QualitySetting.Height.Minus;
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
    }
    return bResult;
}

void StatisticalTrend::_apply(int SpliceID, QString SpliceName,
                              unsigned int time_from, unsigned int time_to)
{
    bool bResult = GetCurrentPresetFromLibrary(SpliceID, SpliceName);
    if(bResult == true)
        bResult = GetCurrentWeldResultList(CurrentPreset.SpliceName,
                CurrentPreset.HashCode, time_from, time_to);
    if(bResult == true)
        bResult = GetCurrentWeldResultOneByOne(&RetrievedWeldResultIndexList);
//    if(bResult == true)
//        if(DataList[QUALITYTIME].size() < 20)
//            bResult = false;
    if(bResult == true)
         GetStatisticsParameter();
    emit _ProcessFinished(bResult);
}
