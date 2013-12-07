/*
 * DeviceTotalAverage.h
 *
 *  Created on: 2013Äê11ÔÂ28ÈÕ
 *      Author: lvqicong
 */

#ifndef DEVICETOTALAVERAGE_H_
#define DEVICETOTALAVERAGE_H_

#include "DeviceTotalBase.h"

class DeviceTotalAverage : public DeviceTotalBase
{
public:
    DeviceTotalAverage();
    virtual ~DeviceTotalAverage();
private:
    bool destriMessage();
};

#endif /* DEVICETOTALAVERAGE_H_ */
