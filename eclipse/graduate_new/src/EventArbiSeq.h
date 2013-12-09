/*
 * EventArbiSeq.h
 *
 *  Created on: 2013Äê12ÔÂ9ÈÕ
 *      Author: lvqicong
 */

#ifndef EVENTARBISEQ_H_
#define EVENTARBISEQ_H_

#include "EventArbiBase.h"

class EventArbiSeq: public EventArbiBase
{
private:
    int messageCounter;
    int lower_addr;
    int upper_addr;
public:
    EventArbiSeq(string);
    virtual ~EventArbiSeq();
public:
    void arbiAlgorithm();
    void configDevice();
};

#endif /* EVENTARBISEQ_H_ */
