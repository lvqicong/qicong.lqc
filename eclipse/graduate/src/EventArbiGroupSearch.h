/*
 * EventArbiGroupSearch.h
 *
 *  Created on: 2013Äê12ÔÂ5ÈÕ
 *      Author: lvqicong
 */

#ifndef EVENTARBIGROUPSEARCH_H_
#define EVENTARBIGROUPSEARCH_H_

#include "EventArbiBase.h"

class EventArbiGroupSearch : public EventArbiBase
{
private:
    int messageCounter;
    static const int c_size = 32;
    static const int m_size = 8;
    static const int c_address[32];
    static const int m_address[8];
public:
    EventArbiGroupSearch();
    virtual ~EventArbiGroupSearch();
public:
    void arbiAlgorithm();
private:
    void groupSearch(int,int);
};

#endif /* EVENTARBIGROUPSEARCH_H_ */
