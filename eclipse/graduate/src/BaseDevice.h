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
    int messageCount;
    double prob;
    bool ptcp;
public:
    inline void decMessage()
    {
        messageCount--;
    }
    inline void incMessage()
    {
        messageCount++;
    }
    inline void sendMessage()
    {
        decMessage();
    }
    bool isMatchDeviceAddr(int);
    bool isMatchGeneral(int);
    bool isMatchGroupAddr(int);

    inline void setAddr(int otherAddr)
    {
        addr = otherAddr;
    }
    inline void setability(bool ability)
    {
        messageAbility = ability;
    }
    inline void setMessageCount( int n )
    {
        messageCount = n;
    }
    inline void setP(double p)
    {
        prob = p;
    }
    inline int getAddr()
    {
        return addr;
    }
    inline int getMessageCount()
    {
        return messageCount;
    }
    inline double getP()
    {
        return prob;
    }
    inline bool getPtcp()
    {
        return ptcp;
    }

};

#endif /* BASEDEVICE_H_ */
