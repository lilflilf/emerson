#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "Maintenance.h"
class Calibration : public Maintenance
{
    Q_OBJECT
private:
    void WidthCalibration();
    void HeightCalibration();
    void HornCalibration();
public:
    virtual void _start();
    virtual void _stop();
    virtual void _execute(int funCode);
public:
    explicit Calibration();

signals:

public slots:
};

#endif // CALIBRATION_H
