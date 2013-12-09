/*
 * CreateScene.cpp
 *
 *  Created on: 2013Äê12ÔÂ9ÈÕ
 *      Author: lvqicong
 */

#include "CreateScene.h"

CreateScene::CreateScene()
{

}

CreateScene::~CreateScene()
{

}

EventArbiBase *CreateScene::createCase(string algorithm, string config)
{
    if (algorithm == "group_search")
        return new EventArbiGroupSearch(config);
    else if (algorithm == "bi_search")
        return new EventArbiBiSearch(config);
    else if (algorithm == "seq")
        return new EventArbiSeq(config);
    else
        return NULL;
}

