#ifndef WIREELEMENT_H
#define WIREELEMENT_H
#include "Definition.h"

class WireElement
{
public:
    //Wire Structure
    enum MetalType
    {
        Copper,
        Aluminum,
    };
    enum HorizontalLocation
    {
        Left,
        Right
    };
    enum VerticalLocation
    {
        Basic,
        Advance,
    };
    enum VerticalPosition
    {
        Top,
        Middle,
        Bottom,
    };
    enum ModuleType
    {
        NA,
        DIN,
        ISO,
        SAE,
        JIS
    };

    QString WireName;
    int     WireID;
    unsigned int CreatedDate;
    int OperatorID;
    int SpliceID;
    QString Color;
    STRIPE Stripe;
    int Gauge;               //Area of Wire in mm*mm/100
    int GaugeAWG;
    enum MetalType TypeOfWire;
    enum ModuleType TypeOfModule;
    enum HorizontalLocation Side;
    enum VerticalLocation VerticalSide;
    enum VerticalPosition Position;
public:
    WireElement operator=(const WireElement &WireObject);
    bool operator==(const WireElement &WireObject);
public:
    WireElement();
};

#endif // WIREELEMENT_H
