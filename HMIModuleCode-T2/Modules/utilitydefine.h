#ifndef UTILITYDEFINE_H
#define UTILITYDEFINE_H

#include <QString>

#define DEFAULTPRESSURE  200
#define DEFAULTAMPLITUDE 1
#define MINENERGY        1
#define MINWIDTH         1
#define MINWELDPRESSURE  10
#define MINAMPLITUDE     1
#define MINTIME          0
#define MINPOWER         0
#define MINPREHEIGHT     0
#define MINHEIGHT        0
#define MINTRIGPRESSURE  MINWELDPRESSURE
#define MINABDELAY       0
#define MINABDURATION    0
#define MINPARTCOUNT     0
#define MINSTOPCOUNT     0
#define MINSQUEEZETIME   0
#define MINHOLDTIME      0
#define MINANTISIDETIME  100
#define MINCUTOFFTIME    100
#define MINPREBURST      0
#define MINFORCE         0
#define MINCOOLDUR       100
#define MAXCOOLDUR       6000
#define MINCOOLDEL       0
#define MAXCOOLDEL       500
#define MAXENERGY        10000              //Joules
#define MAXWIDTH         800                //mm * 100
#define MAXWIDTH2032     980                //mm * 100
#define MAXWELDPRESSURE  800                //PSI * 10
#define MAXAMPLITUDE     150                //microns
#define MAXTIME          1000               //Seconds * 200
#define MAXSTEPTIME      5000               //Seconds * 1000
#define MINSTEPENERGY    0                  //Joules

#define MAXPREHEIGHT     1500               //mm * 100
#define MAXHEIGHT        1500               //mm * 100
#define MAXTRIGPRESSURE  500                //PSI * 10
#define MAXABDELAY       50                 //Seconds * 100
#define MAXABDURATION    200                //Seconds * 100
#define MAXPARTCOUNT     30000              //Pieces
#define MAXSTOPCOUNT     1000               //Pieces
#define MAXSQUEEZETIME   200                //Seconds * 100
#define MAXHOLDTIME      200                //Seconds * 100
#define MAXANTISIDETIME  1000               //Secs * 200
#define MAXCUTOFFTIME    1000               //Secs * 200
#define MAXPREBURST      50                 //Seconds * 1000
#define MAXFORCE         (1.2 * MAXWELDPRESSURE)  //PSI * 10
#define MINWIREAREA      10
#define MAXWIREAREA      4000                 //* 100
#define MINWIREAREA_AWG  1
#define MAXWIREAREA_AWG  37
#define MINWIREREF       0.1
#define MAXWIREREF       40
#define DEFWIREAREA      10
#define MINEDITWIRE      10
#define MAXEDITWIRE      2000
#define MINFORMULAAREA   0
#define MAXFORMULAAREA   40
#define MINSTEPAMPLITUDE 2                  //Min value of Amplitude2
#define DEFAULTSTEP      0                  //Default values of all Steps
#define ZEROHEIGHTPRESSURE 256              //PSI * 10
#define DEFAULTUNLOADTIME  300              //secs * 200
#define MAXHORNLIMIT     200000
#define MINHORNLIMIT     1
#define MAXANVILTIPLIMIT 400000
#define MINANVILTIPLIMIT 1
#define MAXGATHERLIMIT   400000
#define MINGATHERLIMIT   1
#define MAXANVILGUIDELIMIT    400000
#define MINANVILGUIDELIMIT    1
#define MAXCONVERTERLIMIT     400000
#define MINCONVERTERLIMIT     1
#define MAXPERCENTTEACHMODE   100
#define MINPERCENTTEACHMODE   1
#define MAXSIGMATEACHMODE     9
#define MINSIGMATEACHMODE     1
#define MINTESTQUANTITY       1
#define MAXTESTQUANTITY       50

//Used by the program to consistently change from PSI to BAR
#define PRESS2BARFACTOR  (0.1 / 14.5)
#define PRESS2KPAFACTOR  (0.1 / 0.145)
#define PSItoBARfactor   (1 / 14.5)
#define PSItoKPAfactor   (1 / 0.145)

enum ScreenShowDataType{
// Data Index Numbers
    DINZero,
    DINGauge,
    DINGaugeAWG,
    DINCrossSection,
    DINEnergy,
    DINWidth,
    DINPressure,
    DINAmplitude,
    DINActTime,
    DINTimePl,
    DINTimeMs,
    DINActPower,
    DINPowerPl,
    DINPowerMs,
    DINActPreHgt,
    DINPre_HgtPl,
    DINPre_HgtMs,
    DINActHgt,
    DINHeightPl,
    DINHeightMs,
    DINForcePl,
    DINForceMs,

    //Used by IA detailed settings
    DINTriggerPressure,
    DINABDelay,
    DINABDuration,
    DINPartCounter,
    DINStopCounter,
    DINSqueezeTime,
    DINHoldTime,
    DINAntiSpliceTime,
    DINCutOffTime,
    DINCoolDur,
    DINCoolDel,
    DINFlagBits,
    DINHeightCalibration,
    DINWidthCalibration,
    DINPreBurst,

    //Reference to FlagBits
    DINWeldMode,
    //Used for Amplitude Step Settings
    //DINAmpStepMode
    DINAmplitude2,
    DINEnergy2Step,
    DINTime2Step,
    DINPower2Step,
    DINFormulaArea,
    DINFormulaEnergyOffset,
    DINFormulaWidthOffset,
    DINFormulaPressureOffset,
    DINFormulaAmplitudeOffset,
    DINFormulaEnergyMult,
    DINFormulaWidthMult,
    DINFormulaPressureMult,
    DINFormulaAmplitudeMult,
    DINShrinkTubeTemperature,
    DINShrinkTubeTime,
    DINServerPortNumber,
    DINHornLimit,
    DINAnvilTipLimit,
    DINGatherLimit,
    DINAnvilGuideLimit,
    DINConverterLimit,
    DINPercentTeachMode,
    DINSigmaTeachMode,
    DINGraphTimeMS,
    DINGraphPower,
    DINGraphHeight,
    DINTestQuantity,
    DIN_end,
};

struct DataShownStructure{
    long Data;                 //members
    long TempData;
    long min;
    long max;
    long Incrementor;
    float Factor;
    QString Format;
};


#endif // UTILITYDEFINE_H


