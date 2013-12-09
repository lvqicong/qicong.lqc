/*
 * ConfigRandom.h
 *
 *  Created on: 2013Äê12ÔÂ8ÈÕ
 *      Author: lvqicong
 */

#ifndef CONFIGRANDOM_H_
#define CONFIGRANDOM_H_

#include "ConfigBase.h"

class ConfigRandom : public ConfigBase
{
public:
    ConfigRandom();
    virtual ~ConfigRandom();
public:
    static ConfigRandom *single;
    static ConfigRandom *getConfig();
private:
    void genPArray();
};

#endif /* CONFIGRANDOM_H_ */
