/*
 * BaseDevice.cpp
 *
 *  Created on: 2013Äê11ÔÂ27ÈÕ
 *      Author: lvqicong
 */

#include "BaseDevice.h"
#include "cstdlib"
#include "ctime"

#include "iostream"
using namespace std;


const int BaseDevice::MMASK[12] =
{ 0x0800, 0x0400, 0x0200, 0x0100, 0x0080, 0x0040, 0x0020, 0x0010, 0x0008, 0x0004, 0x0002, 0x0001 };
const int BaseDevice::CMASK[12] =
{ 0X0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200, 0x0400, 0x0800 };


BaseDevice::BaseDevice()
{
    srand(time(NULL));
    addr = 0;
    messageCount = 0;
    messageAbility = false;
    prob = 0.0L;
    ptcp = false;
}

BaseDevice::~BaseDevice()
{
}

bool BaseDevice::isMatchDeviceAddr(int frame)
{
    if( (addr == (frame & ADDRMASK)) && messageCount > 0 && ptcp )
    {
        messageCount--;
        ptcp = false;
        return true;
    }
    return false;
}

bool BaseDevice::isMatchGeneral(int frame)
{
    if( messageCount > 0 )
        ptcp = double(rand()) / RAND_MAX < prob?true:false;
    else
        ptcp = false;
    return ptcp;
}

bool BaseDevice::isMatchGroupAddr(int frame)
{
    int otherAddr = (frame & ADDRMASK);
    int i = 0;
    for (i = 0; i < 12; ++i)
    {
        if ((otherAddr & MMASK[i]) == 0)
            break;
    }
    int M = i + 1;
    int C = 0;
    int thisC = 0;
    for (int j = 0; j < 12 - M; ++j)
    {
        C += otherAddr & CMASK[j];
        thisC += addr & CMASK[j];
    }
    return C == thisC && messageCount > 0 && ptcp;
}

