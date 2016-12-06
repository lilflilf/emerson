#include "WireElement.h"

WireElement::WireElement()
{
    WireName.clear();
    WireID = -1;
    CreatedDate = 0;
    OperatorID = -1;
    Color = "pink";
    Stripe.Color = "pink";
    Stripe.TypeOfStripe = Horizontal;
    Gauge = 10;
    GaugeAWG = 37;
    TypeOfWire = Copper;
    Side = Right;
    VerticalSide = Basic;
    Position = Middle;
}

WireElement WireElement::operator=(const WireElement &WireObject)
{
    if(this == &WireObject)
        return *this;
    this->WireName = WireObject.WireName;
    this->WireID = WireObject.WireID;
    this->CreatedDate = WireObject.CreatedDate;
    this->OperatorID = WireObject.OperatorID;
    this->Color = WireObject.Color;
    this->Stripe.Color = WireObject.Stripe.Color;
    this->Stripe.TypeOfStripe = WireObject.Stripe.TypeOfStripe;
    this->Gauge = WireObject.Gauge;
    this->GaugeAWG = WireObject.GaugeAWG;
    this->TypeOfWire = WireObject.TypeOfWire;
    this->Side = WireObject.Side;
    this->VerticalSide = WireObject.VerticalSide;
    this->Position = WireObject.Position;
    return *this;
}

bool WireElement::operator==(const WireElement &WireObject)
{
    bool bResult = false;
//        if(this->WireName != WireObject.WireName)
//            return bResult;
//        if(this->WireID != WireObject.WireID)
//            return bResult;
//        if(this->CreatedDate != WireObject.CreatedDate)
//            return bResult;
    if(this->OperatorID != WireObject.OperatorID)
        return bResult;
    if(this->Color != WireObject.Color)
        return bResult;
    if(this->Stripe.Color != WireObject.Stripe.Color)
        return bResult;
    if(this->Stripe.TypeOfStripe != WireObject.Stripe.TypeOfStripe)
        return bResult;
    if(this->Gauge != WireObject.Gauge)
        return bResult;
    if(this->GaugeAWG != WireObject.GaugeAWG)
        return bResult;
    if(this->TypeOfWire != WireObject.TypeOfWire)
        return bResult;
    if(this->Side != WireObject.Side)
        return bResult;
    if(this->VerticalSide != WireObject.VerticalSide)
        return bResult;
    if(this->Position != WireObject.Position)
        return bResult;
    bResult = true;
    return bResult;
}
