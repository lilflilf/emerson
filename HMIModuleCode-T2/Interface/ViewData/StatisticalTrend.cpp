#include "StatisticalTrend.h"
#include "DataBase/DBPresetTable.h"
#include "DataBase/DBWeldResultTable.h"
#include "Interface/Definition.h"
#include "Modules/UtilityClass.h"
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
                time_from, time_to, &RetrievedWeldResultIndex);
    return bResult;
}

bool StatisticalTrend::GetCurrentWeldResultOneByOne(QMap<int, QString>* ResultIndex)
{
    DBWeldResultTable* _DBWeldResult = DBWeldResultTable::Instance();
    WeldResultElement CurrentWeldResultRecord;
    bool bResult = false;
    DataList[QUALITYTIME].clear();
    DataList[QUALITYPOWER].clear();
    DataList[QUALITYPREHEIGHT].clear();
    DataList[QUALITYPOSTHEIGHT].clear();
    QMap<int, QString>::const_iterator i = ResultIndex->constBegin();
    while (i != ResultIndex->constEnd()) {
        bResult =_DBWeldResult->QueryOneRecordFromTable(i.key(), i.value(), &CurrentWeldResultRecord);
        if(bResult == true)
        {
            DataList[QUALITYTIME].push_back(CurrentWeldResultRecord.ActualResult.ActualTime);
            DataList[QUALITYPOWER].push_back(CurrentWeldResultRecord.ActualResult.ActualPeakPower);
            DataList[QUALITYPREHEIGHT].push_back(CurrentWeldResultRecord.ActualResult.ActualPreheight);
            DataList[QUALITYPOSTHEIGHT].push_back(CurrentWeldResultRecord.ActualResult.ActualPostheight);
        }
        ++i;
    }
    return true;
}

bool StatisticalTrend::GetStatisticsParameter()
{
    bool bResult = false;
//    UtilityClass* _Utility = UtilityClass::Instance();
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
        bResult = GetCurrentWeldResultOneByOne(&RetrievedWeldResultIndex);
    if(bResult == true)
        if(DataList[QUALITYTIME].size() < 20)
            bResult = false;
    if(bResult == true)
         GetStatisticsParameter();
    _ProcessFinished(bResult);
}
