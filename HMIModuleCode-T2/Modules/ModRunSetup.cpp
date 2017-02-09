#include "ModRunSetup.h"
#include "M102IA.h"
#include "M2010.h"
#include "M10INI.h"
#include "typedef.h"
#include <QCoreApplication>
#include <QDateTime>
#include <QString>
#include "MDefine.h"
#include "SaveReplace.h"
#include <QDir>
#include <QDataStream>

ModRunSetup* ModRunSetup::_instance = 0;
ModRunSetup* ModRunSetup::Instance()
{
    if(_instance == 0){
        _instance = new ModRunSetup();
    }
    return _instance;
}
ModRunSetup::ModRunSetup()
{
    OfflineModeEnabled = false;
    GlobalOfflineModeEnabled = false;
}

void ModRunSetup::DeleteStatTempFiles()
{
    QString sFileName;

}

void ModRunSetup::M10initiate(bool bLoadFail)
{
    //Initialize system
    bool SearchResult;
    UNUSED(bLoadFail);
    M2010  *ptr_M2010  = M2010::Instance();
//    MDefine *ptr_MDefine = MDefine::Instance();
    SaveReplace *ptr_SaveReplace = SaveReplace::Instance();

    ptr_M2010->M10Run.Sequence_Done = false;
    ptr_M2010->M10Run.Pre_Hght_Error = false;
    //M10Run.Alarm_found = False
    ptr_M2010->M10Run.Save_Data = true;
    ptr_M2010->M10Run.SafetyFailed = false;
    //IACommand IAComSetM10Mode
    ptr_M2010->SequenceData.sPartName = new string[50];
    ptr_M2010->GetLastRunRecord();          //this reads from run_file.dat
    QString tmp_QStr = ptr_M2010->RunFileRecord.Last_file;
    tmp_QStr = tmp_QStr.trimmed();
    switch(ptr_M2010->RunFileRecord.LastMade)
    {
        case None_Made:
            ptr_M2010->file_mode = no_file;
            ptr_M2010->M10Run.Run_Splice = "";
        break;
        case Splice_Made:
            ptr_M2010->file_mode = Splice_FILE;
            ptr_M2010->M10Run.Run_Splice = tmp_QStr;
        break;

        case Sequence_Made:
            ptr_M2010->file_mode = Sequence_FILE;

            if (ptr_M2010->PreviousScreen_Prog_mode == No_SCREEN) Seqchanged = true;
            if (Seqchanged == true)
            {
//                if((ptr_MDefine->FlagModularProduction != true) &&
//                    ((ptr_M2010->PreviousScreen_Prog_mode == Operator_SCREEN) ||
//                    (ptr_M2010->PreviousScreen_Prog_mode == Setup_SCREEN) ||
//                    (ptr_M2010->PreviousScreen_Prog_mode == Stats_SCREEN)))
//                    return;
                ptr_SaveReplace->CheckIfSeqFileExist(tmp_QStr);
                // if Sequence file was not found then load some default splice and exit
                if (ptr_SaveReplace->Failed_To_Find_Seq_File == true)
                {
                    ptr_SaveReplace->Failed_To_Find_Seq_File = false;
                    ptr_M2010->file_mode = Splice_FILE;
                    ptr_M2010->PutLastRunRecord(Splice_Made, ptr_M2010->Splice.PartNo.trimmed());
                    ptr_M2010->M10Run.Run_Splice = "";
                    return;
                }

                QDir dir;
                if (dir.exists("c:\\AmtData\\Aseq\\" + ptr_M2010->RunFileRecord.Last_file.trimmed() + ".seq") == true)
                {
                    QFile file("c:\\AmtData\\Aseq\\" + ptr_M2010->RunFileRecord.Last_file.trimmed() + ".seq");
                    file.open(QIODevice::ReadOnly);
                    QDataStream in(&file);    // read the data serialized from the file
                    char* buffer = (char*)&ptr_M2010->Seq_FilerevTwo;
                    in >> buffer;
                    file.close();
                    ptr_SaveReplace->CopySequencerevTwo(ptr_M2010->Seq_FilerevTwo);
                    QFile file1("c:\\AmtData\\Aseq\\" + ptr_M2010->RunFileRecord.Last_file.trimmed() + ".seq");
                    file1.open(QIODevice::ReadWrite);
                    QDataStream Out(&file1);
                    buffer = (char*)&ptr_M2010->Seq_File;
                    Out << buffer;
                    file.close();
                }
                else{
                    QFile file("c:\\AmtData\\Aseq\\" + ptr_M2010->RunFileRecord.Last_file.trimmed() + ".seq");
                    file.open(QIODevice::ReadOnly);
                    QDataStream in(&file);
                    char* buffer = (char*)&ptr_M2010->Seq_File;
                    in >> buffer;
                    file.close();
                }
                SearchResult = ptr_SaveReplace->CheckPartFilesInSeqExist(ptr_M2010->Seq_File.SequenceName.trimmed(), false);
                if (SearchResult == true)
                {
                    ptr_M2010->file_mode = no_file;
                    ptr_M2010->M10Run.Run_Splice = "";
                    ptr_M2010->PutLastRunRecord(None_Made, "");

                    return;
                }
        //--Place First Record in Sequence in Run_Splice String
                ptr_M2010->M10Run.Run_Splice = ptr_M2010->Seq_File.record[ptr_M2010->M10Run.Sequence_Line].FileName.trimmed(); //PartName)
                Seqchanged = false;
            }
        break;
    }
}

//void ModRunSetup::Start_Run(int ModeLabel, int Onlycolorchange)
//{

//}
