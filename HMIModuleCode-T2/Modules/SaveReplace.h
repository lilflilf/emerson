#ifndef SAVEREPLACE_H
#define SAVEREPLACE_H
#include <iostream>
#include <QString>
//#include <string>
//#include "stdlib.h"
//#include "stdio.h"
#include "M10definitions.h"
#include "Interface/definition.h"
using namespace std;

const int MINWIREINDEX = 0;
const int MAXWIREINDEX = 19;
const int MAXNOOFWIRES = 20;
const int MAXNOOFFILES = 500;
const int TEACH_AUTO_THRESHOLD = 5;

struct CommonFile
{
    string CommonFileList[MAXNOOFFILES];
    int CommonFileListCount;
};

//the enum variable comes in use in file manager screen
enum FILE_MANAGER_SELECT_SIDE
{
    No_Side,
    Browse_Side,
    Application_Side,
};

class SaveReplace
{
private:
    int index;
public:
    int ReplaceFlag;
    int DeleteFlag;
    int CopyFromFlag;
    int MoveFromFlag;
    int MoveFlag;
    bool Failed_To_Find_Seq_File; //flag indicates whether seq file could be found on load of Operator
                                  // or Setup screen

    TEACH_MODE_TYPE Teach_Mode;
    string AuxName[AuxEND];
    FILE_MANAGER_SELECT_SIDE FM_SelectSide;
//    Public ProjectBitmaps As ImageList
//    Public demo As TextBox
public:
    void CalculateSpliceData();
    void Change_Teach_To_Setup();
    bool CheckPartFilesInSeqExist(QString sSeqName, bool bFailedLoad);
    void CheckIfSeqFileExist(QString SeqNameToCheck);
    void Load_EditSequence_Structure(string Sel_Seq);
    void Load_Seq_File_Structure(string Sel_Seq);
    void CopySequencerevTwo(Sequence_StructrevTwo SequencervTwo);
    void CopyEditSequencerevTwo(Sequence_StructrevTwo SequencervTwo);
    void Update_Setup_Screen_with_Weld_result();
    void Update_Operator_Screen_with_Weld_Result();
    void GetLimitsAfterWeld();





public:
    static SaveReplace* Instance();
protected:
    SaveReplace();
private:
    static SaveReplace* _instance;
public:
    ~SaveReplace(){} //do-nothing destructor
};

#endif // SAVEREPLACE_H
