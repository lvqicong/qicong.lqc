/*
 * DeviceTotalRandom.cpp
 *
 *  Created on: 2013��12��5��
 *      Author: lvqicong
 */

#include "DeviceTotalRandom.h"
#include "cstdlib"

DeviceTotalRandom::DeviceTotalRandom()
{
    device = NULL;
    deviceNum = 0;
    totalMessage = 0;
}

DeviceTotalRandom::~DeviceTotalRandom()
{
    // TODO Auto-generated destructor stub
}

bool DeviceTotalRandom::destriMessage()
{
    for( int i = 0 ; i < totalMessage ; ++i )
    {
        device[rand()%deviceNum]->incMessage();
    }
    return true;
}

