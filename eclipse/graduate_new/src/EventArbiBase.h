/*
 * EventArbiBase.h
 *
 *  Created on: 2013Äê11ÔÂ28ÈÕ
 *      Author: lvqicong
 */

#ifndef EVENTARBIBASE_H_
#define EVENTARBIBASE_H_

#include "ConfigBase.h"
#include "DeviceTotal.h"
#include "string"

using namespace std;

class EventArbiBase
{
protected:
    int reqCount;
    DeviceTotal *engine;

    //for config the device
    ConfigBase *configer;
    static const int TOTALDEVICE = 4096;
    int totalMessage;
    int deviceNum;

    double *pResult;
    int *addrResult;

public:
    EventArbiBase(string);
    virtual ~EventArbiBase();

public:
    virtual void arbiAlgorithm()=0;
    virtual void runAlgorithm();
    virtual void configDevice()=0;

protected:
    int send_general_request();
    int send_group_request(int M , int C);
    bool send_single_request( int C );
    bool event_read_request();
};

#endif /* EVENTARBIBASE_H_ */
