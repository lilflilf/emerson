#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "Maintenance.h"
#define SAFETYOPEN 0x02
enum CALIBRATE
{
    WIDTH_CALIBRATE,
    HEIGHT_CALIBRATE,
    AMPLITUDE_CALIBRATE,
};

class Calibration : public Maintenance
{
    Q_OBJECT
private:
    void WidthCalibration();
    void HeightCalibration();
    void HornCalibration();
public:
    virtual bool _start();
    virtual bool _stop();
    virtual bool _execute(int funCode);
public:
    explicit Calibration();

signals:

public slots:
};

#endif // CALIBRATION_H
