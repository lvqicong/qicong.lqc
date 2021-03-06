/*
 * EventArbiGroupSearch.h
 *
 *  Created on: 2013��12��5��
 *      Author: lvqicong
 */

#ifndef EVENTARBIGROUPSEARCH_H_
#define EVENTARBIGROUPSEARCH_H_

#include "EventArbiBase.h"

struct bucket_node;
class EventArbiGroupSearch : public EventArbiBase
{
private:
    int messageCounter;
    int group_lowerbound;
    int group_upperbound;
public:
    EventArbiGroupSearch(string);
    virtual ~EventArbiGroupSearch();
public:
    void arbiAlgorithm();
    void configDevice();
private:
    void hash_bucket_config();
    void bisearch_algorithm(int M, int C);

};

#endif /* EVENTARBIGROUPSEARCH_H_ */
