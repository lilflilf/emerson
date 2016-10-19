#ifndef MDEFINE_H
#define MDEFINE_H
#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include "m10definitions.h"
using namespace std;

// Bar Code One Data
const int MINRunQ = 1;
const int MAXRunQ = 1000;
const int RowMax = 10000;
const int ColomnMax = 2000;
const int BarCodeMax = 9;
const int PartNameLength = 32;


const int LB_SETHORIZONTALEXTENT = 0x0194;

//Public Sub SetListboxScrollbar(ByVal lst As listbox)
//Dim i As Integer
//Dim new_len As Long
//Dim max_len As Long
//max_len = 470
//   For i = 0 To lst.ListCount - 1
//        new_len = 10 + lst.Parent.ScaleX( _
//            lst.Parent.TextWidth(lst.List(i)), _
//            lst.Parent.ScaleMode, vbPixels)
//        If max_len < new_len Then max_len = new_len
//    Next i

//    SendMessage lst.hWnd, _
//        LB_SETHORIZONTALEXTENT, _
//        max_len, 0
//End Sub
struct MSGFLAG{
    bool DataGraphComplete;
    bool EmergencyStopMessage;

};


class MDefine
{
public:
//    int TableWireNameFontSize[9][PartNameLength];
    int TempPrtCount;
    string Barcode;
    string FamilyName;
    string ModuleVersion;
    string ProjectName;
    string PrevFamilyName;
    string PrevModuleVersion;
    string PrevProjectName;
    string CarSerialNum;
    string Mypath;
    string MyName;
    int nCols;

    int SpliceNameIndex;
    int PartNameIndex;
    int InsulationIndex;
    int TotalCSAIndex;
    int CommentIndex;
    int LSWName1Index;
    int LSWComment1Index;
    int LSWCSA1Index;
    int LSWColor1Index;
    int LSWSpec1Index;
    int RSWName1Index;
    int RSWComment1Index;
    int RSWCSA1Index;
    int RSWColor1Index;
    int RSWSpec1Index;
    int LSWName2Index;
    int CalCSAIndex;

    int TempIndex;
    int PartIndex;
    int ColOffset;                               // Column Offset to reach Modular
    int WireDataOffset;
    int ErrorNum;
    bool ShowCancelFlag;
    bool ModeChangeFlag;
    bool WriteHistoryFlag;

//    string Table1[RowMax][ColomnMax];
//    string Table6[RowMax][ColomnMax];
//    string Barcodeid[BarCodeMax];
    string SelProject;
    int RunQuantity;
    int Index;
    long RowCount;
    long PrtCount;
    bool FlagModularProduction;
    bool ModularSequenceDone;
    bool ErrorFlag;
    string sData;
    bool ScanFlag;
//    string DirNames[RowMax];
    int DirCount;
    string hProgramName;
    string hPartName;
    int EndCount;
public:
    MSGFLAG MessageFlag;
public:
    static MDefine* Instance();
protected:
    MDefine();
private:
    static MDefine* _instance;
public:
    ~MDefine(){} //do-nothing destructor
};

#endif // MDEFINE_H
