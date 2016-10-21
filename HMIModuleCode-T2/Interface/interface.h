#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"
#include <QObject>
#include "definition.h"

using namespace std;
enum TipsScreenMode{
    OKOnly   = 0, //only show Okay button 2^0
    OKCancel = 1, //show Okay and cancel buttons 2^1 0x01 0000 0001
    Critical = 16,//show Error sign 0x10 0001 0000
    Exclamation = 32,//show Warning sign 0x20 0010 0000
    Information = 64,//show Information sign 0x40 0100 0000
};
struct BransonMessageBox{
    QString MsgTitle;
    QString MsgPrompt;
    int TipsMode;
    void (*func_ptr)(void*);
};


class InterfaceClass:public QObject
{
         Q_OBJECT
public:

public:
public:
    static InterfaceClass* Instance();
    //Following for the screen showing using signal
public:
    void cMsgBox(struct BransonMessageBox* MsgBox);
    void dlgMaintWarning();
    //Recall for Screen
    void DatabaseOperating(int OperatingType, void*);

    //Following for the screen recall


    bool SQLQuery(enum TABLENAME table, QMap<int, QString>* _EntireTableInfo);
    bool SQLQuery(enum TABLENAME table, int ID, QString Name, void* _DataStructure);

    bool SQLInsert(enum TABLENAME table, void* _DataStructure);

    bool SQLUpdate(enum TABLENAME table, void* _DataStructure);

    bool SQLDelete(enum TABLENAME table, QMap<int, QString>* _TableInfo);
    bool SQLDelete(enum TABLENAME table, int ID, QString Name);
private:



protected:
    InterfaceClass(QObject *parent = 0);
private:
    static InterfaceClass* _instance;
public:
    ~InterfaceClass();
};

#endif // INTERFACE_H
