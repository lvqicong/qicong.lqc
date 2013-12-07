/*
 * EventArbiGroupSearch.cpp
 *
 *  Created on: 2013Äê12ÔÂ5ÈÕ
 *      Author: lvqicong
 */

#include "EventArbiGroupSearch.h"
#include "iostream"

using namespace std;

const int EventArbiGroupSearch::c_address[32] =
{
1
};
const int EventArbiGroupSearch::m_address[8] =
{
    0x000 , 0x200 , 0x400 , 0x600 , 0x800 , 0xA00 , 0xC00 , 0xE00
};

EventArbiGroupSearch::EventArbiGroupSearch()
{
    configer = Config::getConfig();
    totalMessage = configer->getTotalMessage();
    messageCounter = 0;
}

EventArbiGroupSearch::~EventArbiGroupSearch()
{
}

void EventArbiGroupSearch::arbiAlgorithm()
{
    int return_buff;
    while (messageCounter != totalMessage)
    {
        cout << "messageCounter : " << messageCounter << endl;
        return_buff = send_general_request();

        if (return_buff > 1)
        {
            groupSearch(0, 0);
        }
        else if (return_buff == 1)
        {
            engine->eventReadRequest();
            messageCounter++;
        }
    }
    messageCounter = 0;
}

void EventArbiGroupSearch::groupSearch(int m_index, int c_index)
{
    m_index = 0;
    c_index = 0;
    int return_buff;
    int inner_arbi;
    int c_now;
    for (c_index = 0; c_index < c_size; ++c_index)
    {
        return_buff = send_group_request(3, c_address[c_index]);
        switch (return_buff)
        {
            case 2:
                inner_arbi = 1;
                break;
            case 1:
                inner_arbi = 0;
                if (event_read_request())
                    messageCounter++;
                break;
            default:
                break;
        }
        if (inner_arbi == 1)
        {
            for (m_index = 0; m_index < m_size; ++m_index)
            {
                c_now = m_address[m_index] + c_address[c_index];
                return_buff = send_single_request(c_now);
                if (return_buff)
                    messageCounter++;
            }
        }
    }
}

