/*
 * DeviceTotalBase.h
 *
 *  Created on: 2013��11��28��
 *      Author: lvqicong
 */

#ifndef DEVICETOTALBASE_H_
#define DEVICETOTALBASE_H_

#include "BaseDevice.h"

class DeviceTotalBase
{
protected:
    BaseDevice **device;
    int deviceNum;
    int totalMessage;
    int lastAddr;
public:
    DeviceTotalBase();
    virtual ~DeviceTotalBase();
public:
    void configMessageAbility(double *, int * , int , int );

protected:

    virtual bool destriMessage()=0;
public:
    int generalEventRequest(int);
    int groupEventRequest(int);
    bool singleEventRequest(int);
    bool eventReadRequest();
    void showDevice();
};

#endif /* DEVICETOTALBASE_H_ */
