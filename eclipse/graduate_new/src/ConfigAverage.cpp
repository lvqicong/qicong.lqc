/*
 * ConfigAverage.cpp
 *
 *  Created on: 2013Äê12ÔÂ7ÈÕ
 *      Author: lvqicong
 */

#include "ConfigAverage.h"
#include "iostream"

using namespace std;

ConfigAverage *ConfigAverage::single = NULL;
ConfigAverage *ConfigAverage::getConfig()
{
    if (single == NULL)
        single = new ConfigAverage;
    return single;
}

void ConfigAverage::genPArray()
{
    int eachNum = deviceNum / 10;
    int index = 0 ;
    for( int i = 1 ; i <= 10 ; ++i )
    {
        double p = double(i) / 10;
        for( int j = 0 ; j < eachNum ; ++j )
        {
            pArray[index++] = p;
        }
    }
    for( int i = 1 ; i <= ( deviceNum - eachNum * 10 ) ; ++i )
    {
        double p = double(i) / 10;
        pArray[index++] = p;
    }
}

ConfigAverage::ConfigAverage()
{
    genPArray();
}

ConfigAverage::~ConfigAverage()
{
}

