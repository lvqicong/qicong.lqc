/*
 * EventArbiBiSearch.cpp
 *
 *  Created on: 2013��11��28��
 *      Author: lvqicong
 */

#include "EventArbiBiSearch.h"
#include "iostream"
#include "queue"

using namespace std;


EventArbiBiSearch::EventArbiBiSearch()
{
    messageCounter = 0;
}

EventArbiBiSearch::~EventArbiBiSearch()
{
}

struct huff_node
{
    double p;
    huff_node *left;
    huff_node *right;
    huff_node(){ p = 0.0L , left = right = NULL;}
    huff_node(double p) {
        this->p = p;
        left = right = NULL;
    }
};

struct cmp
{
    bool operator()( huff_node *left , huff_node *right )
    {
        return left->p > right->p;
    }
};

int index = 0 ;
void EventArbiBiSearch::generate_huff_code( huff_node *root , int value , int layer )
{
    if( root->left == NULL && root->right == NULL )
    {
        pResult[index] = root->p;
        addrResult[index] = value;
        index++;
    }
    if( root->left != NULL )
        generate_huff_code( root->left , value + ( 1 << layer ) , layer + 1);
    if( root->right != NULL )
        generate_huff_code( root->right , value , layer + 1 );
}

void EventArbiBiSearch::huffman_config()
{
    double *pArray = configer->getPArray();

    priority_queue<huff_node *, vector<huff_node*> , cmp > tmp;
    for( int i = 0 ; i < deviceNum ; ++i )
    {
        tmp.push( new huff_node(pArray[i]) );
    }

    //show priority data
//    for( int i = 0 ; i < deviceNum ; ++i )
//    {
//        cout << tmp.top()->p << endl;
//        tmp.pop();
//    }
    huff_node *root;
    huff_node *leftChild , *rightChild ;
    while( tmp.size() > 1 )
    {
        leftChild = tmp.top();
        tmp.pop();
        rightChild =  tmp.top();
        tmp.pop();
        root = new huff_node( leftChild->p + rightChild->p );
        root->left = leftChild;
        root->right = rightChild;
        tmp.push(root);
    }
    root = tmp.top();
    tmp.pop();

    index = 0 ;
    generate_huff_code( root , 0 , 0 );
}

void EventArbiBiSearch::continus_config()
{
    double *pArray = configer->getPArray();
    for( int i = 0 ; i < deviceNum ; ++i )
    {
        pResult[i] = pArray[i];
        addrResult[i] = i+1;
    }
}

void EventArbiBiSearch::configDevice()
{
    configer = Config::getConfig();
    deviceNum = configer->getDeviceNum();
    totalMessage = configer->getTotalMessage();

    pResult = new double[deviceNum];
    addrResult = new int[deviceNum];

    //config device address
    huffman_config();
//    continus_config();

    //show encode
    for( int i = 0 ; i < deviceNum ; ++i )
    {
        cout << hex << addrResult[i] << "\t" << dec << pResult[i] << endl;
    }

    engine->configMessageAbility(pResult , addrResult , deviceNum , totalMessage );

    delete[] pResult;
    delete[] addrResult;
    pResult = NULL;
    addrResult = NULL;
//    int interval = TOTALDEVICE / deviceNum - 1;
//    int lastAddr = 1;
//    for (int i = 0; i < deviceNum; ++i)
//    {
//        device[i]->setAddr(lastAddr);
//        device[i]->setability(true);
//        lastAddr += interval;
//        device[i]->setP(pArray[i]);
//    }

//    for( int i = 0 ; i < deviceNum ; ++i )
//    {
//        device[i]->setAddr(i+1);
//        device[i]->setability(true);
//        device[i]->setP(pArray[i]);
//    }

}
void EventArbiBiSearch::arbitration_algorithm(int M, int C)
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
        switch(return_buff)
        {
            case 2:
                arbitration_algorithm(M_now, C_now);
                break;
            case 1:
                if( event_read_request() )
                    messageCounter++;
                break;
            default:
                break;
        }
        /*
         * ����һ����֧�ٲ�
         */
        //���������֧��Mֵ��Cֵ��Ҳ�������ַ��
        C_gain = 1 << ( 12 - M_pre );
        C_now += C_gain;
        return_buff = send_group_request(M_now, C_now);
        switch(return_buff)
        {
            case 2:
                arbitration_algorithm(M_now, C_now);
                break;
            case 1:
                if( event_read_request() )
                    messageCounter++;
                break;
            default:
                break;
        }
    }
}

void EventArbiBiSearch::arbiAlgorithm()
{
    int return_buff;

    while (messageCounter != totalMessage)
    {
        return_buff = send_general_request();

        if (return_buff > 1)
        {
            arbitration_algorithm(12, 0);
        }
        else if( return_buff == 1 )
        {
            engine->eventReadRequest();
            messageCounter++;
        }
    }
    messageCounter = 0;
}

