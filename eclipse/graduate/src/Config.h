/*
 * Config.h
 *
 *  Created on: 2013Äê11ÔÂ28ÈÕ
 *      Author: lvqicong
 */

#ifndef CONFIG_H_
#define CONFIG_H_
#include "string"

using namespace std;

class Config
{
private:
    int deviceNum;
    double *pArray;
    int totalMessage;
public:
    Config();
    virtual ~Config();
    static Config *single;
    static const string configFileName;
public:
    static Config *getConfig();
    inline int getDeviceNum()
    {
        return deviceNum;
    }
    inline double * getPArray()
    {
        return pArray;
    }
    inline int getTotalMessage()
    {
        return totalMessage;
    }

};

#endif /* CONFIG_H_ */
