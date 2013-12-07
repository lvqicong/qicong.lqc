/*
 * DeviceTotalAverage.cpp
 *
 *  Created on: 2013Äê11ÔÂ28ÈÕ
 *      Author: lvqicong
 */

#include "DeviceTotalAverage.h"

DeviceTotalAverage::DeviceTotalAverage()
{
    device = NULL;
    deviceNum = 0;
    totalMessage = 0;
}

DeviceTotalAverage::~DeviceTotalAverage()
{
}

bool DeviceTotalAverage::destriMessage()
{
    int average = totalMessage / deviceNum + 1;
    for( int i = 0 ; i < deviceNum ; ++i )
        device[i]->setMessageCount( average );
    return true;
}

