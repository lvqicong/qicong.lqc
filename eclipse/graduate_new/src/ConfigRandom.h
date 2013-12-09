/*
 * ConfigRandom.h
 *
 *  Created on: 2013��12��8��
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
