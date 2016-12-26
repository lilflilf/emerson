#include "StatisticalFunction.h"
#include <QtAlgorithms>
#include <QDebug>
StatisticalFunction::StatisticalFunction()
{

}

float StatisticalFunction::Mean(QList<float> & RawSample)
{
    double sum = 0;
    for(int i = 0; i < RawSample.size();i++)
    {
        sum += RawSample.at(i);
    }
    return (float)(sum/RawSample.size());
}

float StatisticalFunction::Median(QList<float> & RawSample, float mean)
{
    float median = 0;
    qSort(RawSample.begin(), RawSample.end());
    int len = RawSample.size();
    if (len == 0)
        return median;
    if((len % 2)== 0)
    {
        float tmp1 = RawSample.at(len/2);
        float tmp2 = RawSample.at(len/2 -1);
        float offset1, offset2;
        if(mean > tmp1)
            offset1 = mean - tmp1;
        else
            offset1 = tmp1 - mean;
        if(mean > tmp2)
            offset2 = mean - tmp2;
        else
            offset2 = tmp2 - mean;
        if(offset1 < offset2)
            median = RawSample.at(len/2);
        else
            median = RawSample.at(len/2 -1);
    }
    else
    {
        median = RawSample.at(int(len/2));
    }
    return median;
}

float StatisticalFunction::StandardDeviation(QList<float> &RawSample, float mean)
{
    double sum = 0;
    int len = RawSample.size();
    for(int i = 0; i< RawSample.size(); i++)
    {
        float tmp = RawSample.at(i);
        sum += pow((tmp - mean), 2);
    }
    return sqrt(sum/(len -1));
}

float StatisticalFunction::CPKProcess(float sigma, float mean, float USL, float LSL)
{
    float CPKu = -1;
    float CPKI = -1;
    float CPK = 0;
    if(USL != -1)
    {
        if(mean < USL)
            CPKu = (USL - mean)/(3 * sigma);
        else
            CPKu = (mean - USL)/(3 * sigma);
    }
    if(LSL != -1)
    {
        if(mean < LSL)
            CPKI = (LSL - mean)/ (3 * sigma);
        else
            CPKI = (mean - LSL)/ (3 * sigma);
    }
    if(CPKu == -1)
        CPK = CPKI;
    else if(CPKI == -1)
        CPK = CPKu;
    else
    {
        if(CPKu < CPKI)
            CPK = CPKu;
        else
            CPK = CPKI;
    }


    return CPK;
}

bool StatisticalFunction::StatisticalFun(int* _size, float* _mean, float* _median,
                    float* _sigma, float* _CPK,
                    QList<float>* _RawSample, float USL, float LSL)
{
    bool bResult = true;
    int len = _RawSample->size();
    QList<float> tmpSample = *_RawSample;
    float tmpMean = Mean(tmpSample);
    float tmpMedian = Median(tmpSample, tmpMean);
    float tmpSigma = StandardDeviation(tmpSample, tmpMean);
    float tmpCPK = CPKProcess(tmpSigma, tmpMean, USL, LSL);
    *_size = len;
    *_mean = tmpMean;
    *_median = tmpMedian;
    *_sigma = tmpSigma;
    *_CPK = tmpCPK;
    return bResult;
}
