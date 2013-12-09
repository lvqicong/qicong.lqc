/*
 * ConfigRandom.cpp
 *
 *  Created on: 2013Äê12ÔÂ8ÈÕ
 *      Author: lvqicong
 */

#include "ConfigRandom.h"
#include "iostream"
#include "cstdlib"

using namespace std;

ConfigRandom *ConfigRandom::single = NULL;
ConfigRandom *ConfigRandom::getConfig()
{
    if (single == NULL)
        single = new ConfigRandom;
    return single;
}

void ConfigRandom::genPArray()
{
    int index = 0 ;
    for( int i = 0 ; i < deviceNum ; ++i )
    {
        double p = double ( rand() % 10 + 1 ) / 10;
        pArray[index++] = p;
    }
}

ConfigRandom::ConfigRandom()
{
    genPArray();
}

ConfigRandom::~ConfigRandom()
{
}
