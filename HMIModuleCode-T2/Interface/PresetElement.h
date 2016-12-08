#ifndef PRESETELEMENT_H
#define PRESETELEMENT_H
#include "Definition.h"

class PresetElement
{
public:
    int RevCode;              //Amtech Revision Code for possible future use
    int SpliceID;
    QString SpliceName;       //Customer's Part Number
    unsigned int CreatedDate; //Date of last rev, seconds from Jan 1, 1980
    int OperatorID;

    int CrossSection;         //Area of part in mm*mm/100
    QString PresetPicNamePath;
    bool Verified;

    struct WELDSETTING WeldSettings;
    unsigned int HashCode;
    int NoOfWires;            //Number of wires in this splice
    /*WireEl(1 To MAX_WIRE_ELEMENTS) As WireElement*/
    QMap<int,QString> WireIndex;   //Store data for individual wires

    struct TESTSETTING TestSetting;
public:
    PresetElement operator=(const PresetElement &PresetObject);
    bool CalculateSpliceData();
public:
    PresetElement();
    ~PresetElement();
};

#endif // PRESETELEMENT_H
