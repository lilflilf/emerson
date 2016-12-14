#ifndef STATISTICALFUNCTION_H
#define STATISTICALFUNCTION_H

#include <QList>
class StatisticalFunction
{
private:
    static float Mean(QList<float>&);
    static float Median(QList<float> & RawSample, float mean);
    static float StandardDeviation(QList<float>& RawSample, float mean);
    static float CPKProcess(float sigma, float mean, float USL, float LSL);
public:
    StatisticalFunction();
public:
    static bool StatisticalFun(int* _size, float* _mean, float* _median, float* _sigma, float* _CPK,
                               QList<float>* _RawSample, float USL, float LSL);
};

#endif // STATISTICALFUNCTION_H
