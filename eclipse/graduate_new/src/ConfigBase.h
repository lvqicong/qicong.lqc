/*
 * Config.h
 *
 *  Created on: 2013Äê11ÔÂ28ÈÕ
 *      Author: lvqicong
 */

#ifndef CONFIGBASE_H_
#define CONFIGBASE_H_
#include "string"

using namespace std;

class ConfigBase
{
protected:
    int deviceNum;
    double *pArray;
    int totalMessage;
public:
    ConfigBase();
    virtual ~ConfigBase();
    static const string configFileName;
protected:
    virtual void genPArray()=0;
public:
    inline int getDeviceNum()
    {
        return deviceNum;
    }
    inline double *getPArray()
    {
        return pArray;
    }
    inline int getTotalMessage()
    {
        return totalMessage;
    }

};

#endif /* CONFIG_H_ */
