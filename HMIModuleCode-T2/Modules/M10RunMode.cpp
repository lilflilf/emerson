#include "M10runMode.h"
#include "M10INI.h"
#include "M102IA.h"
#include "M2010.h"
#include "Statistics.h"
#include "UtilityClass.h"
#include "MODstart.h"
#include "Interface/interface.h"

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

void M10runMode::InitializeTextData()
{
    //To make a backwards compatible routine
    M2010* ptr_M2010 = M2010::Instance();
    InitTextFromSplice(ptr_M2010->Splice);
}

void M10runMode::InitTextFromSplice(M10Part SpliceData)
{

}

void M10runMode::UpdateMaintenanceData()
{
    int i = 0;
    bool tempflag = false;
    M10INI* ptr_M10INI = M10INI::Instance();
    M102IA* ptr_M102IA = M102IA::Instance();
    InterfaceClass* ptr_InterfaceClass = InterfaceClass::Instance();

    for (i = 0; i< 7;i++)
    {
        if (i <= 3)
        {
            if (MODstart::ApplicationFirstStartFlag == false)
            {
                ptr_M10INI->StatusData.currentMaintenanceLimits[i] =
                        ptr_M10INI->StatusData.currentMaintenanceLimits[i] +
                        ptr_M102IA->IAactual.Energy;
            }
            if (ptr_M10INI->StatusData.MaintenanceLimits[i] != 0)
            {
                if (MODstart::Checkmaintenancelimit_EaWeld == true)
                {
                    if (ptr_M10INI->StatusData.currentMaintenanceLimits[i] >=
                            ptr_M10INI->StatusData.MaintenanceLimits[i])
                     //display warning msg
                        tempflag = true;
                }
            }
        }
        else
        {
            if (MODstart::ApplicationFirstStartFlag == false)
                ptr_M10INI->StatusData.currentMaintenanceLimits[i] =
                    ptr_M10INI->StatusData.currentMaintenanceLimits[i] + 1;
            if (ptr_M10INI->StatusData.MaintenanceLimits[i] != 0)
            {
                if (MODstart::Checkmaintenancelimit_EaWeld == true)
                {
                    if (ptr_M10INI->StatusData.currentMaintenanceLimits[i] >=
                        ptr_M10INI->StatusData.MaintenanceLimits[i])
                        //display warning msg
                        tempflag = true;
                }
            }
        }
    }
    if ((tempflag == true) && (MODstart::Checkmaintenancelimit_EaWeld == true))
        ptr_InterfaceClass->dlgMaintWarning();
    ptr_M10INI->Save_StatusData(false);
}
