/*
 * DeviceTotalBase.h
 *
 *  Created on: 2013Äê11ÔÂ28ÈÕ
 *      Author: lvqicong
 */

#ifndef DEVICETOTAL_H_
#define DEVICETOTAL_H_

#include "BaseDevice.h"

class DeviceTotal
{
protected:
    BaseDevice **device;
    int deviceNum;
    int totalMessage;
    int lastAddr;
public:
    DeviceTotal();
    virtual ~DeviceTotal();
public:
    void configMessageAbility(double *, int * , int , int );

public:
    int generalEventRequest(int);
    int groupEventRequest(int);
    bool singleEventRequest(int);
    bool eventReadRequest();
    void showDevice();
};

#endif /* DEVICETOTAL_H_ */
