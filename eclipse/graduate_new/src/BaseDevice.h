/*
 * BaseDevice.h
 *
 *  Created on: 2013Äê11ÔÂ27ÈÕ
 *      Author: lvqicong
 */

#ifndef BASEDEVICE_H_
#define BASEDEVICE_H_
#include "iostream"
using namespace std;

class BaseDevice
{
public:
    BaseDevice();
    virtual ~BaseDevice();
private:
    static const int ADDRMASK = 0x0FFF;
    static const int FCODEMASK = 0XF000;
    static const int MMASK[12];
    static const int CMASK[12];

    int addr;
    bool messageAbility;
    int messageCounter;
    double prob;
    bool ptcp;
public:
    bool isMatchDeviceAddr(int);
    bool isMatchGeneral(int);
    bool isMatchGroupAddr(int);

    inline void setAddr(int otherAddr)
    {
        addr = otherAddr;
    }
    inline void setAbility(bool ability)
    {
        messageAbility = ability;
    }
    inline void setP(double p)
    {
        prob = p;
    }
    inline int getAddr()
    {
        return addr;
    }
    inline double getP()
    {
        return prob;
    }
    inline bool getPtcp()
    {
        return ptcp;
    }
    inline int getMessageCounter()
    {
        return messageCounter;
    }

};

#endif /* BASEDEVICE_H_ */
