/*
 * EventArbiBase.cpp
 *
 *  Created on: 2013Äê11ÔÂ28ÈÕ
 *      Author: lvqicong
 */

#include "EventArbiBase.h"
#include "cstddef"
#include "iostream"
#include "ConfigAverage.h"
#include "ConfigGauss.h"
#include "ConfigRandom.h"
#include "configLoadFile.h"
#include "cstdlib"
using namespace std;

EventArbiBase::EventArbiBase(string configSwitch)
{
    engine = NULL;
    reqCount = 0;
    deviceNum = 0;
    addrResult = NULL;
    pResult = NULL;
    totalMessage = 0;

    if (configSwitch == "average")
        configer = ConfigAverage::getConfig();
    else if (configSwitch == "gauss")
        configer = ConfigGauss::getConfig();
    else if (configSwitch == "random")
        configer = ConfigRandom::getConfig();
    else if (configSwitch == "loadfile")
        configer = ConfigLoadFile::getConfig();
    else
        configer = NULL;
    if (configer == NULL)
    {
        cerr << "no valid config specified!" << endl;
        exit(1);
    }
}

EventArbiBase::~EventArbiBase()
{
}

void EventArbiBase::runAlgorithm()
{
    engine = new DeviceTotal;
    configDevice();
    reqCount = 0;
    arbiAlgorithm();
    delete engine;

    cout << "reqCount: " << reqCount << endl;

}

int EventArbiBase::send_general_request()
{
    reqCount++;
    return engine->generalEventRequest(12 << 12);
}

int Mtable[13] =
{ 0, 0, 0x800, 0xC00, 0XE00, 0XF00, 0XF80, 0XFC0, 0XFE0, 0XFF0, 0XFF8, 0XFFC, 0XFFE };
int EventArbiBase::send_group_request(int M, int C)
{
    reqCount++;
    return engine->groupEventRequest(Mtable[M] + C);
}

bool EventArbiBase::send_single_request(int C)
{
    reqCount++;
    return engine->singleEventRequest(C);
}

bool EventArbiBase::event_read_request()
{
    reqCount++;
    return engine->eventReadRequest();
}
