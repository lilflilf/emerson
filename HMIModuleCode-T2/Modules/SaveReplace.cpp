#include "SaveReplace.h"
#include "M2010.h"
#include "M10definitions.h"

SaveReplace* SaveReplace::_instance = 0;
SaveReplace* SaveReplace::Instance()
{
    if(_instance == 0){
        _instance = new SaveReplace();
    }
    return _instance;
}
SaveReplace::SaveReplace()
{

}

void SaveReplace::CalculateSpliceData()
{

}

void SaveReplace::Change_Teach_To_Setup()
{

}

bool SaveReplace::CheckPartFilesInSeqExist(QString sSeqName, bool bFailedLoad)
{
    // sSeqName  has name of sequence without extension
   string sTmpName, sTmpLine;
   int iLen, CharPos;
   ErrMsgStruct *ErrMsgData;
   int PartFileIndex, iErrCnt;
   bool lbQualifiedOn;
   iErrCnt = 0;
   PartFileIndex = 0;

   return true;
}

void SaveReplace::CheckIfSeqFileExist(QString SeqNameToCheck)
{
    QString sTmpName;
    int sTmpLine, iLen, CharPos;
    sTmpName = SeqNameToCheck.trimmed().toUpper(); //convert to upper case
    // Check for that NULL character  in the name and remove it
    CharPos = sTmpName.indexOf('0');
    if (CharPos > 0) sTmpName = sTmpName.left(CharPos - 1);
    // Is it a file name? if yes then remove the extension
//    if(sTmpName.endsWith(".SEQ"))
    CharPos = sTmpName.indexOf(".SEQ");
    if (CharPos > 0)
    {
        sTmpName = sTmpName.left(CharPos - 1);
        //here we just need the sequence name at the end
        while (CharPos > 0)
        {
            CharPos = sTmpName.indexOf("'\'");
            if(CharPos > 0)
            {
                iLen = sTmpName.length();
                sTmpName = sTmpName.right(iLen - CharPos);

            }
        }
    }
    //sTmpName is now a pure sequence name without extension or path

}

void SaveReplace::Load_EditSequence_Structure(string Sel_Seq)
{

}

void SaveReplace::Load_Seq_File_Structure(string Sel_Seq)
{

}

void SaveReplace::CopySequencerevTwo(Sequence_StructrevTwo SequencervTwo)
{
    M2010* ptr_M2010 = M2010::Instance();
    ptr_M2010->Seq_File.RevCode = DEFINEDREVCODE;
    ptr_M2010->Seq_File.SequenceName = SequencervTwo.SequenceName;
    ptr_M2010->Seq_File.FileName = SequencervTwo.FileName;
    ptr_M2010->Seq_File.NoOfParts = SequencervTwo.NoOfParts;
    for(int i = 0; i< SEQ_MAX_SPLICES;i++)
    {
        ptr_M2010->Seq_File.record[i].PartName = SequencervTwo.record[i].PartName;
        ptr_M2010->Seq_File.record[i].FileName = SequencervTwo.record[i].FileName;
        ptr_M2010->Seq_File.record[i].Quantity = SequencervTwo.record[i].Quantity;
    }

}

void SaveReplace::CopyEditSequencerevTwo(Sequence_StructrevTwo SequencervTwo)
{

}
