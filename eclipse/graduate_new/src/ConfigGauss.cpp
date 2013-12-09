/*
 * ConfigGauss.cpp
 *
 *  Created on: 2013年12月8日
 *      Author: lvqicong
 */

#include "ConfigGauss.h"
#include "cmath"
#include "cstdlib"
#include "iostream"

#define PI 3.1415926

ConfigGauss *ConfigGauss::single = NULL;
ConfigGauss *ConfigGauss::getConfig()
{
    if (single == NULL)
        single = new ConfigGauss;
    return single;
}

double randP()
{
    return double(rand()) / RAND_MAX;
}

double randLimit(double max)
{
    return double(rand() % int(max * 10000)) / 10000;
}

double normalF(double x, double miu, double sigma)
{
    return 1.0 / sqrt(2 * PI * sigma) * exp(-1 * (x - miu) * (x - miu) / (2 * sigma * sigma));
}

double ConfigGauss::randDouble()
{
    double x, y;
    double yRand;
    do
    {
        x = randP();
        y = normalF(x, u, sigma);
        yRand = randLimit(max);
    } while (yRand > y);

    /*
     * 四舍五入保留一位小数
     */
//    x += 0.05;
//    int tmp = x * 10;
//    if( tmp == 0 )
//        return 0.1;
//    x = double(tmp) / 10;
    return x;
}

void ConfigGauss::genPArray()
{
    u = 0.5;
    sigma = 0.18;
    max = normalF(u, u, sigma);

    for( int i = 0 ; i < deviceNum ; ++i )
    {
        pArray[i] = randDouble();
    }

    for( int i = 0 ; i < deviceNum ; ++i )
    {
        cout << pArray[i] << endl;
    }
}

ConfigGauss::ConfigGauss()
{
    genPArray();
}

ConfigGauss::~ConfigGauss()
{
}

