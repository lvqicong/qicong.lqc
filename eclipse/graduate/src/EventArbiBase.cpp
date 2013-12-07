/*
 * EventArbiBase.cpp
 *
 *  Created on: 2013Äê11ÔÂ28ÈÕ
 *      Author: lvqicong
 */

#include "EventArbiBase.h"
#include "cstddef"
#include "iostream"
#include "DeviceTotalAverage.h"
#include "DeviceTotalRandom.h"

using namespace std;

EventArbiBase::EventArbiBase()
{
    engine = NULL;
    reqCount = 0;
    totalMessage = 0;
    configer = NULL;
}

EventArbiBase::~EventArbiBase()
{

}

void EventArbiBase::runAlgorithm()
{
    int reqTmp[3];
    engine = new DeviceTotalAverage;
    configDevice();
    reqCount = 0;
    arbiAlgorithm();
    reqTmp[0] = reqCount;
    delete engine;

//    engine = new DeviceTotalRandom;
//    configDevice();
//    reqCount = 0;
//    arbiAlgorithm();
//    reqTmp[1] = reqCount;
//    delete engine;

    cout << "Average reqCount: " << reqTmp[0] << endl;
    cout << "Random repCount: " << reqTmp[1] << endl;

}

int EventArbiBase::send_general_request()
{
    reqCount++;
    return engine->generalEventRequest( 12 << 12 );
}

int Mtable[13] = { 0 , 0 , 0x800, 0xC00, 0XE00, 0XF00, 0XF80, 0XFC0, 0XFE0, 0XFF0, 0XFF8, 0XFFC, 0XFFE};
int EventArbiBase::send_group_request(int M , int C)
{
    reqCount++;
    return engine->groupEventRequest(Mtable[M] + C );
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
