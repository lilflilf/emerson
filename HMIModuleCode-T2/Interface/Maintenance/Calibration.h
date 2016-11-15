#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "Maintenance.h"
#define SAFETYOPEN 0x02
enum CALIBRATE
{
    WIDTH_CALIBRATE,
    HEIGHT_CALIBRATE,
    AMPLITUDE_CALIBRATE_PRESS,
    AMPLITUDE_CALIBRATE_UPPRESS,
};

class Calibration : public Maintenance
{
    Q_OBJECT
private:
    bool CalStarted;
    int CalbCount;
private:
    void RunSonicsPressed();
    void RunSonicsUnPressed();
    void RunSonics100Pressed();
    void RunSonics100UnPressed();
    void WidthCalibration();
    void HeightCalibration();
    void HornCalibrationStart();
    void HornCalibrationStop();
public:
    virtual bool _start();
    virtual bool _stop();
    virtual bool _execute(int funCode);
public:
    explicit Calibration();

signals:
    void WidthCalibrationFinish(const bool &_Result);
    void HeightCalibrationFinish(const bool &_Result);
public slots:
};

#endif // CALIBRATION_H
