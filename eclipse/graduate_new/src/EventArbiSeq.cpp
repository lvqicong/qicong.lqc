/*
 * EventArbiSeq.cpp
 *
 *  Created on: 2013Äê12ÔÂ9ÈÕ
 *      Author: lvqicong
 */

#include "EventArbiSeq.h"

EventArbiSeq::EventArbiSeq(string configSwitch) :
        EventArbiBase(configSwitch)
{
    messageCounter = lower_addr = upper_addr = 0;
}

EventArbiSeq::~EventArbiSeq()
{
}

void EventArbiSeq::arbiAlgorithm()
{
    int return_buff;

    while (messageCounter < totalMessage)
    {
        return_buff = send_general_request();

        if (return_buff > 1)
        {
            for (int i = lower_addr; i < upper_addr; ++i)
            {
                if (send_single_request(i))
                    messageCounter++;
            }
        }
        else if (return_buff == 1)
        {
            event_read_request();
            messageCounter++;
        }
    }
    messageCounter = 0;
}

void EventArbiSeq::configDevice()
{
    deviceNum = configer->getDeviceNum();
    totalMessage = configer->getTotalMessage();

    pResult = new double[deviceNum];
    addrResult = new int[deviceNum];

    double *pArray = configer->getPArray();
    for (int i = 0; i < deviceNum; ++i)
    {
        pResult[i] = pArray[i];
        addrResult[i] = i + 1;
    }

    lower_addr = 1;
    upper_addr = deviceNum;

    //show encode
    for (int i = 0; i < deviceNum; ++i)
    {
        cout << hex << addrResult[i] << "\t" << dec << pResult[i] << endl;
    }

    engine->configMessageAbility(pResult, addrResult, deviceNum, totalMessage);

    delete[] pResult;
    delete[] addrResult;
    addrResult = NULL;
    pResult = NULL;
}
