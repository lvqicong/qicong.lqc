/*
 * ConfigAverage.h
 *
 *  Created on: 2013Äê12ÔÂ7ÈÕ
 *      Author: lvqicong
 */

#ifndef CONFIGAVERAGE_H_
#define CONFIGAVERAGE_H_

#include "ConfigBase.h"

class ConfigAverage : public ConfigBase
{
public:
    ConfigAverage();
    virtual ~ConfigAverage();
public:
    static ConfigAverage *single;
    static ConfigAverage *getConfig();
private:
    void genPArray();


};

#endif /* CONFIGAVERAGE_H_ */
