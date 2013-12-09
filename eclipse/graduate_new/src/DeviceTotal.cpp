/*
 * DeviceTotalBase.cpp
 *
 *  Created on: 2013Äê11ÔÂ28ÈÕ
 *      Author: lvqicong
 */

#include "DeviceTotal.h"
#include "ConfigBase.h"
#include "iostream"

using namespace std;

DeviceTotal::DeviceTotal()
{
    lastAddr = 0;
    totalMessage = 0;
    device = NULL;
    deviceNum = 0;
}

DeviceTotal::~DeviceTotal()
{
    for (int i = 0; i < deviceNum; ++i)
        delete device[i];
    delete[] device;
    device = NULL;
}

void DeviceTotal::configMessageAbility( double *pArray , int *address , int devNum , int totalMess)
{
    deviceNum = devNum;
    totalMessage = totalMess;

    device = new BaseDevice*[deviceNum];
    for (int i = 0; i < deviceNum; ++i)
    {
        device[i] = new BaseDevice;
        device[i]->setP(pArray[i]);
        device[i]->setAbility(true);
        device[i]->setAddr(address[i]);
    }

    showDevice();
}

int DeviceTotal::generalEventRequest(int frame)
{
    int counter = 0;
    for (int i = 0; i < deviceNum; ++i)
    {
        if (device[i]->isMatchGeneral(frame))
        {
            counter++;
            lastAddr = device[i]->getAddr();
        }
    }
    showDevice();

    if( counter == 0 )
        return 0;
    else if( counter > 1 )
        return 2;
    else
        return 1;

}

int DeviceTotal::groupEventRequest(int frame)
{
    int counter = 0;
    for (int i = 0; i < deviceNum; ++i)
    {
        if (device[i]->isMatchGroupAddr(frame))
        {
            counter++;
            lastAddr = device[i]->getAddr();
        }
    }
    if( counter == 0 )
        return 0;
    else if( counter > 1 )
        return 2;
    else
        return 1;

}

bool DeviceTotal::singleEventRequest(int frame)
{
    int counter = 0;
    for (int i = 0; i < deviceNum; ++i)
    {
        if (device[i]->isMatchDeviceAddr(frame))
            counter++;
    }
    return counter;

}

bool DeviceTotal::eventReadRequest()
{
    int frame = ( 12 << 12 ) + lastAddr;
    int counter = 0;
    for (int i = 0; i < deviceNum; ++i)
    {
        if (device[i]->isMatchDeviceAddr(frame))
            counter++;
    }
    return counter;
}

void DeviceTotal::showDevice()
{
    cout << "Total Device: " << deviceNum << endl;
    cout << "Total Message: " << totalMessage << endl;
    for( int i = 0 ; i < deviceNum ; ++i )
    {
        cout << hex << device[i]->getAddr() << dec << '\t';
        cout << device[i]->getP() << '\t' << device[i]->getPtcp() << endl;
    }
}

