/*
 * DeviceTotalRandom.h
 *
 *  Created on: 2013��12��5��
 *      Author: lvqicong
 */

#ifndef DEVICETOTALRANDOM_H_
#define DEVICETOTALRANDOM_H_

#include "DeviceTotalBase.h"

class DeviceTotalRandom : public DeviceTotalBase
{
public:
    DeviceTotalRandom();
    virtual ~DeviceTotalRandom();
private:
    bool destriMessage();
};

#endif /* DEVICETOTALRANDOM_H_ */
