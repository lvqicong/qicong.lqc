/*
 * DeviceTotalAverage.h
 *
 *  Created on: 2013��11��28��
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
