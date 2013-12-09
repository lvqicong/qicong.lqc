/*
 * ConfigGauss.h
 *
 *  Created on: 2013��12��8��
 *      Author: lvqicong
 */

#ifndef CONFIGGAUSS_H_
#define CONFIGGAUSS_H_

#include "ConfigBase.h"

class ConfigGauss : public ConfigBase
{
private:
    double u;
    double sigma;
    double max;
public:
    ConfigGauss();
    virtual ~ConfigGauss();
public:
    static ConfigGauss *single;
    static ConfigGauss *getConfig();
private:
    void genPArray();
    double randDouble();
};

#endif /* CONFIGGAUSS_H_ */
