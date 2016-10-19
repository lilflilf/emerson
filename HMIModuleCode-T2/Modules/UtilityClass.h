#ifndef UTILITY_H
#define UTILITY_H
#include <QString>

class UtilityClass
{  
public:
    bool ReadFromBinaryFile(QString SourcDirectory, void* DestStruct);
    bool WriteToBinaryFile(void* SourceStruct, QString DestDirectory);



public:
    static UtilityClass* Instance();
protected:
    UtilityClass();
private:
    static UtilityClass* _instance;
public:
    ~UtilityClass(){} //do-nothing destructor
};

#endif // UTILITY_H
