#ifndef WIREELEMENT_H
#define WIREELEMENT_H
#include "Definition.h"

class WireElement
{
public:
    QString WireName;
    int     WireID;
    unsigned int CreatedDate;
    int OperatorID;
    int SpliceID;

    QString Color;
    struct STRIPE Stripe;
    int Gauge;               //Area of Wire in mm*mm/100
    int GaugeAWG;
    enum MetalType TypeOfWire;
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
