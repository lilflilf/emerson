#include "M10runMode.h"
#include "M10INI.h"
#include "M102IA.h"
#include "M2010.h"
#include "Statistics.h"
#include "UtilityClass.h"
#include "MODstart.h"
#include "Interface/Interface.h"
#include "AlarmMessage.h"
#include <QDateTime>

M10runMode* M10runMode::_instance = 0;
M10runMode* M10runMode::Instance()
{
    if(_instance == 0){
        _instance = new M10runMode();
    }
    return _instance;
}

M10runMode::M10runMode()
{

}

/*It gets the value of Splice_Stat structure from temporary/permanent Stat file*/
/*depending on whether the user is working on a current or saved preset        */
void M10runMode::init_m20_data_events(PresetElement *_Splice)
{
    QString StatFileFound;
    M2010* _M2010 = M2010::Instance();
    M10INI* _M10INI = M10INI::Instance();
    Statistics* _Statistics = Statistics::Instance();
    UtilityClass* _Utility = UtilityClass::Instance();

    tempStatFile = _Splice->SpliceName;
    StatFileFound = _M10INI->ConfigFilesPath + tempStatFile + ".ini";

    _Statistics->Splice_Stat.ReadQSettingToSpliceStat(StatFileFound, _Splice);
}
void M10runMode::Save_Data_Events()
{
    QString StatFileFound;
    M10INI* _M10INI = M10INI::Instance();
    Statistics* _Statistics = Statistics::Instance();
    StatFileFound = _M10INI->ConfigFilesPath;
    _Statistics->Splice_Stat.WriteSpliceStatToQSetting(StatFileFound);
}

void M10runMode::UpdateMaintenanceData()
{
    M10INI *_M10INI = M10INI::Instance();
    InterfaceClass* _Interface = InterfaceClass::Instance();
    QDateTime TimeLabel = QDateTime::currentDateTime();
    for(int i = 0; i < 8; i++)
    {
        if(_Interface->StatusData.CurrentMaintenanceLimits[i] == 0)
        {
            _Interface->StatusData.MaintenanceDateStarted[i] = TimeLabel.toTime_t();
        }
        _Interface->StatusData.CurrentMaintenanceLimits[i]++;
    }
    _M10INI->Save_StatusData(false);
}

bool M10runMode::CheckForOverLoad(bool ShowAlarm)
{
    M102IA *_M102IA = M102IA::Instance();
    M2010  *_M2010  = M2010::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    AlarmMessage *_AlarmMsg = AlarmMessage::Instance();
    bool bResult = false;
    if((_M102IA->IAactual.Alarmflags & 0x01) == 0x01)
    {
        _M2010->M10Run.Alarm_found = true;
        if((_Interface->FirstScreenComesUp == true) && (ShowAlarm == true))
            _AlarmMsg->Initialization(WeldResultID);
        bResult = true;
    }
    return bResult;
}

void M10runMode::Update_Counter()
{
    //Enter the Data and update the counters if no errors are found during weld
    //This section must be editted, note that the part counter is updated AFTER the data is saved
    Statistics *_Statistics = Statistics::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    _Statistics->EnterM20DataEvent();
    Save_Data_Events();
}

bool M10runMode::CheckWeldData(int weldresult)
{
    //This routine must control all of the data checks including alarm checks.
    bool Invalidweld = false;
    WeldResultID = weldresult;
    M2010 *_M2010 = M2010::Instance();
    M10INI *_M10INI = M10INI::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    M102IA* _M102IA = M102IA::Instance();
    AlarmMessage* _AlarmMsg = AlarmMessage::Instance();
    Statistics* _Statistics = Statistics::Instance();
    _M2010->M10Run.Pre_Hght_Error = false;
    _M10INI->ValidWeldData = false;
    WidthError = false;
    //If width encoder is checked
    if((_Interface->StatusData.Machineflags.Word[0] & 0x4000) != 0x4000)
    {
        if((_M102IA->IAactual.Alarmflags & 0x800) == 0x800)
        {
            _M2010->M10Run.Alarm_found = true;
            if(_Interface->FirstScreenComesUp == true)
                _AlarmMsg->Initialization(WeldResultID);
            CheckForOverLoad(false);
            return true;
        }
    }

    if((_M102IA->IAactual.Alarmflags & 0x02) == 0x02)
    {
        if(_Interface->FirstScreenComesUp == true)
        {
            _M2010->M10Run.Alarm_found = true;
            _AlarmMsg->Initialization(WeldResultID);
        }
        CheckForOverLoad(false);
        return true;
    }

    //Check Overload Alarm
    if (CheckForOverLoad(true) == true) return true;

    //Safety Alarm Check
    if((_M102IA->IAactual.Alarmflags & 0x400) == 0x400)
    {
        if(_Interface->FirstScreenComesUp == true)
        {
            _M2010->M10Run.SafetyFailed = true;
            _AlarmMsg->Initialization(WeldResultID);
        }
        return true;
    }

    //Weld Abort
    if((_M102IA->IAactual.Alarmflags & 0x10) == 0x10) return true;

    //Foot Paddle Abort
    if((_M102IA->IAactual.Alarmflags & 0x200) == 0x200) return true;

    /***************** PREHEIGHT **************************/
    //Check for pre-height alarm indicated by bit 2
    if((_Interface->StatusData.Machineflags.Word[0] & 0x8000) == 0x8000)
    {
        if((_M102IA->IAactual.Alarmflags & 0x04) == 0x04) //IF FLAG SET
        {
            Invalidweld = true; //Do not increment Maintenance counters
            _M2010->M10Run.Pre_Hght_Error = true;
            _M2010->M10Run.Alarm_found = true;
            //Display PreHeight Error
            //need some warning message
            _AlarmMsg->Initialization(WeldResultID);
            return true;
        }
    }

    //Sense 24V
    if((_M102IA->IAactual.Alarmflags & 0x10000) == 0x10000)
        _M2010->M10Run.Alarm_found = true;

    //Cutter alarm for new splicer
    if((_M102IA->IAactual.Alarmflags & 0x20000) == 0x20000)
        _M2010->M10Run.Alarm_found = true;

    //Lock Key alarm for new splicer
    if((_M102IA->IAactual.Alarmflags & 0x40000) == 0x40000)
        _M2010->M10Run.Alarm_found = true;

    //ID Chip alarm for new splicer
    if((_M102IA->IAactual.Alarmflags & 0x80000) == 0x80000)
        _M2010->M10Run.Alarm_found = true;

    // BBR & RAM alarm for new splicer
    if((_M102IA->IAactual.Alarmflags & 0x100000) == 0x100000)
        _M2010->M10Run.Alarm_found = true;

    //Check if this is the current weld data. (WeldDone Flag)
    if((_M102IA->IAactual.Alarmflags & 0x4000) != 0x4000)
    {
        if(_M2010->M10Run.Alarm_found == true)
            _AlarmMsg->Initialization(WeldResultID);
        return true;
    }
    if(WeldResultID == -1) return true;
        // PREHEIGHT CHECK FINISH

    //TIME CHECK BEGINS
    //Watch for time error: Special condition because of units change
    //Bit 5 is the time error flag
    if((_M102IA->IAactual.Alarmflags & 0x20) == 0x20)
    {
        //if time is too low system will handle is properly, if time is too high
        //the system clips the data
        if (_M102IA->IAactual.Time >= _M102IA->IAsetup.Time.min)
            _M102IA->IAactual.Time = _M102IA->IAsetup.Time.max + 1;
        _M2010->M10Run.Alarm_found = true;
    }
    //POWER CHECK START
    if((_M102IA->IAactual.Alarmflags & 0x40) == 0x40)
    {
        _M2010->M10Run.Alarm_found = true;
    }
    // POWER CHECK FINISH
    // HEIGHT
    if((_Interface->StatusData.Machineflags.Word[0] & 0x8000) == 0x8000)
    {
        if ((_M102IA->IAactual.Alarmflags & 0x80) == 0x80)
            _M2010->M10Run.Alarm_found = true;
    }
    // HEIGHT CHECK FINISH
    //check: is there some error due to parameters going out of bound
    if(_M2010->M10Run.Alarm_found == false)
    {
        PreviousWeldValid = true;
        if(_Interface->ApplicationFirstStartFlag == false)
        {
            Update_Counter();
            _M10INI->ValidWeldData = true;
            _Statistics->UpdateSoftLimitData();
        }
    }else
    {
        PreviousWeldValid = false;
        _AlarmMsg->Initialization(WeldResultID);
    }

    return Invalidweld;
}

void M10runMode::CalculateTeachMode(PresetElement *_Splice)
{
    M2010 *_M2010 = M2010::Instance();
    Statistics* _Statistics = Statistics::Instance();
    if(_M2010->M10Run.Alarm_found == false)
    {
        _Statistics->CalcConfLimits(_Splice);
    }
}

void M10runMode::TeachModeFinished(PresetElement *_Splice)
{
    Statistics* _Statistics = Statistics::Instance();
    if(_Splice->WeldSettings.AdvanceSetting.WeldMode != TIME)
    {
        _Splice->WeldSettings.QualitySetting.Time.Minus =
                (int)_Statistics->time_lower_limit;
        _Splice->WeldSettings.QualitySetting.Time.Plus =
                (int)_Statistics->time_upper_limit;
    }
    _Splice->WeldSettings.QualitySetting.Power.Minus =
            (int)_Statistics->power_lower_limit;
    _Splice->WeldSettings.QualitySetting.Power.Plus =
            (int)_Statistics->power_upper_limit;
    _Splice->WeldSettings.QualitySetting.Preheight.Minus =
            (int)_Statistics->pre_hght_lower_limit;
    _Splice->WeldSettings.QualitySetting.Preheight.Plus =
            (int)_Statistics->pre_hght_upper_limit;
    if((_Splice->WeldSettings.AdvanceSetting.WeldMode !=  HEIGHT) &&
            (_Splice->WeldSettings.AdvanceSetting.WeldMode != ENERGYWITHHEIGHT))
    {
        _Splice->WeldSettings.QualitySetting.Height.Minus =
                (int)_Statistics->height_lower_limit;
        _Splice->WeldSettings.QualitySetting.Height.Plus =
                (int)_Statistics->height_upper_limit;
    }
}
