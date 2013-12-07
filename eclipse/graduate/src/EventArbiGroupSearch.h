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
    int group_lowerbound;
    int group_upperbound;
public:
    EventArbiGroupSearch();
    virtual ~EventArbiGroupSearch();
public:
    void arbiAlgorithm();
    void configDevice();
private:
    void hash_bucket_config();
    void arbitration_algorithm(int M, int C);

};

#endif /* EVENTARBIGROUPSEARCH_H_ */
