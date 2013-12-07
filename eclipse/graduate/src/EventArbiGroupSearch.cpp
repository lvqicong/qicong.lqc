/*
 * EventArbiGroupSearch.cpp
 *
 *  Created on: 2013��12��5��
 *      Author: lvqicong
 */

#include "EventArbiGroupSearch.h"
#include "iostream"
#include "vector"

using namespace std;

EventArbiGroupSearch::EventArbiGroupSearch()
{
    messageCounter = 0;
}

EventArbiGroupSearch::~EventArbiGroupSearch()
{
}

struct bucket_node
{
    int n;
    vector<double> node;
    struct bucket_node *next;
    bucket_node()
    {
        n = 0;
        node.clear();
        next = NULL;
    }
};

int hashF(double p)
{
    return (p + 0.01) * 10;
}

//const int max_device[11] =
//{ 0, 8, 4, 4, 2, 2, 2, 2, 1, 1, 1 };
const int max_device[11] =
{ 0, 16,  16, 16, 16, 16, 16, 16, 16, 16, 1 };

const int MAX_GROUP_NUM = 255;
const int GROUP_BITS = 8;
const int M = 4;
void EventArbiGroupSearch::hash_bucket_config()
{
    double *pArray = configer->getPArray();
    bucket_node *bucket = new bucket_node[11];
    bucket_node *head = NULL, *next;
    for (int i = 0; i < deviceNum; ++i)
    {
        head = bucket + hashF(pArray[i]);
        if (head->next == NULL)
        {
            next = new bucket_node;
            head->next = next;
            head->n++;
            bucket[0].n++;
        }
        else
        {
            next = head->next;
        }
        if (next->n == max_device[hashF(pArray[i])])
        {
            bucket_node *tmp = new bucket_node;
            tmp->next = next;
            next = tmp;
            head->next = next;
            head->n++;
            bucket[0].n++;
        }
        next->n++;
        next->node.push_back(pArray[i]);
    }
    while (bucket[0].n > MAX_GROUP_NUM)
    {
        //resize the bucket;
    }

    int groupCounter = 1;
    int index = 0;
    group_lowerbound = groupCounter;
    //encode
    for (int i = 1; i < 11; ++i)
    {
        bucket_node *tmp = bucket[i].next;
        while (tmp != NULL)
        {
            for (int j = 0; j < tmp->n; ++j)
            {
                pResult[index] = tmp->node[j];
                addrResult[index] = groupCounter + (j << GROUP_BITS);
                index++;
            }
            groupCounter++;
            tmp = tmp->next;
        }

    }
    group_upperbound = groupCounter;

}

void EventArbiGroupSearch::configDevice()
{
    configer = Config::getConfig();
    deviceNum = configer->getDeviceNum();
    totalMessage = configer->getTotalMessage();

    pResult = new double[deviceNum];
    addrResult = new int[deviceNum];

    //config device address
    hash_bucket_config();
//    continus_config();
//    interval_config();

//show encode
    for (int i = 0; i < deviceNum; ++i)
    {
        cout << hex << addrResult[i] << "\t" << dec << pResult[i] << endl;
    }

    engine->configMessageAbility(pResult, addrResult, deviceNum, totalMessage);

    delete[] pResult;
    delete[] addrResult;
    pResult = NULL;
    addrResult = NULL;

}

void EventArbiGroupSearch::arbitration_algorithm(int M, int C)
{
    int M_pre = M; //��һ���Mֵ
    int M_now = M_pre - 1; //��ǰ��Mֵ
    int C_now = C; //��ǰ��Cֵ
    int C_gain; //C����ʱ�����ĸ���
    int return_buff; //��¼����ֵ

    //�����һ���MֵΪ0��������Ҫ����Single_Event_Request��������Group_Event_Request
    //ͬʱ��C_now��Ϊ�豸��ַ
    if (M_now == 0)
    {
        return_buff = send_single_request(C_now);
        if (return_buff)
            messageCounter++;

        C_now += (1 << 11);
        return_buff = send_single_request(C_now);
        if (return_buff)
            messageCounter++;
    }
    else
    {
        /*
         * �Ե�һ����֧�ٲ�
         */
        //����Group_Event_Request��֡
        return_buff = send_group_request(M_now, C_now);
        switch (return_buff)
        {
            case 2:
                arbitration_algorithm(M_now, C_now);
                break;
            case 1:
                if (event_read_request())
                    messageCounter++;
                break;
            default:
                break;
        }
        /*
         * ����һ����֧�ٲ�
         */
        //���������֧��Mֵ��Cֵ��Ҳ�������ַ��
        C_gain = 1 << (12 - M_pre);
        C_now += C_gain;
        return_buff = send_group_request(M_now, C_now);
        switch (return_buff)
        {
            case 2:
                arbitration_algorithm(M_now, C_now);
                break;
            case 1:
                if (event_read_request())
                    messageCounter++;
                break;
            default:
                break;
        }
    }
}
void EventArbiGroupSearch::arbiAlgorithm()
{
    int return_buff;

    while (messageCounter < totalMessage)
    {
        cout << "messageCounter:" << messageCounter << endl;
        return_buff = send_general_request();
        if( return_buff > 1)
        {
            for (int i = group_lowerbound; i <= group_upperbound; ++i)
            {
                return_buff = send_group_request(M, i);
                if (return_buff > 1)
                {
                    arbitration_algorithm(M, i);
                }
                else if (return_buff == 1)
                {
                    engine->eventReadRequest();
                    messageCounter++;
                }
            }
        }
        else if (return_buff == 1)
        {
            engine->eventReadRequest();
            messageCounter++;
        }
    }
    messageCounter = 0;

}

