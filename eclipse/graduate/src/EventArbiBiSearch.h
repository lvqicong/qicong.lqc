/*
 * EventArbiBiSearch.h
 *
 *  Created on: 2013Äê11ÔÂ28ÈÕ
 *      Author: lvqicong
 */

#ifndef EVENTARBIBISEARCH_H_
#define EVENTARBIBISEARCH_H_

#include "EventArbiBase.h"

struct huff_node;
struct cmp;

class EventArbiBiSearch : public EventArbiBase
{
private:
    int messageCounter;
public:
    EventArbiBiSearch();
    virtual ~EventArbiBiSearch();
public:
    void arbiAlgorithm();
    void configDevice();
private:
    void arbitration_algorithm(int, int);
    void huffman_config();
    void continus_config();
    void generate_huff_code( huff_node *root , int value , int layer );
};

#endif /* EVENTARBIBISEARCH_H_ */
