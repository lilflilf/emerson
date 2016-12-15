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
void M10runMode::init_m20_data_events()
{
    QString StatFileFound;
    M2010* ptr_M2010 = M2010::Instance();
    M10INI* ptr_M10INI = M10INI::Instance();
    Statistics* ptr_Statistics = Statistics::Instance();
    UtilityClass* ptr_Utility = UtilityClass::Instance();

    if ((ptr_M2010->PresetChanged == true) && (ptr_M2010->UseTempStsFile == true))
    {
        //Reworked to use part name as file name
        //M10Run.Run_Splice_Stat =
        tempStatFile = ptr_M2010->Splice.PartNo.trimmed() + ".tempsts";
        StatFileFound = ptr_M10INI->ConfigFilesPath + tempStatFile;
        if(ptr_Utility->ReadFromBinaryFile(StatFileFound,&ptr_Statistics->Splice_Stat) == false)
        {
            //M10Run.Run_Splice_Stat =
            tempStatFile = ptr_M2010->Splice.PartNo.trimmed() + ".tempsbk";
            StatFileFound = ptr_M10INI->ConfigFilesPath + tempStatFile;
            if(ptr_Utility->ReadFromBinaryFile(StatFileFound,&ptr_Statistics->Splice_Stat) == true)
                tempStatFile = ptr_M2010->Splice.PartNo.trimmed() + ".tempsts";
            else
                ptr_Statistics->ZeroM20DataEvents();
        }
    }
    else
    {
        //Reworked to use part name as file name
        tempStatFile = "";
        ptr_M2010->M10Run.Run_Splice_Stat = ptr_M2010->Splice.PartNo.trimmed() + ".sts";

        StatFileFound = ptr_M10INI->ConfigFilesPath + ptr_M2010->M10Run.Run_Splice_Stat;
        if(ptr_Utility->ReadFromBinaryFile(StatFileFound,&ptr_Statistics->Splice_Stat) == false)
        {
            ptr_M2010->M10Run.Run_Splice_Stat = ptr_M2010->Splice.PartNo + ".sbk";
            StatFileFound = ptr_M10INI->ConfigFilesPath + ptr_M2010->M10Run.Run_Splice_Stat;
            if(ptr_Utility->ReadFromBinaryFile(StatFileFound,&ptr_Statistics->Splice_Stat) == true)
                ptr_M2010->M10Run.Run_Splice_Stat = ptr_M2010->Splice.PartNo + ".sts";
            else
                ptr_Statistics->ZeroM20DataEvents();
        }
    }
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
            _AlarmMsg->Initialization();


    }
}

void M10runMode::CheckWeldData()
{
    //This routine must control all of the data checks including alarm checks.
    bool Done, tmpAlarmFound, Invalidweld = false;
    int i;
    M2010 *_M2010 = M2010::Instance();
    M10INI *_M10INI = M10INI::Instance();
    InterfaceClass *_Interface = InterfaceClass::Instance();
    M102IA* _M102IA = M102IA::Instance();
    AlarmMessage* _AlarmMsg = AlarmMessage::Instance();
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
                _AlarmMsg->Initialization();
        }

    }



}
