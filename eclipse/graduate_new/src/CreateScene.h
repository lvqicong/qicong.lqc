/*
 * CreateScene.h
 *
 *  Created on: 2013Äê12ÔÂ9ÈÕ
 *      Author: lvqicong
 */

#ifndef CREATESCENE_H_
#define CREATESCENE_H_

#include "string"
#include "EventArbiBase.h"
#include "EventArbiBiSearch.h"
#include "EventArbiGroupSearch.h"
#include "EventArbiSeq.h"

using namespace std;

class CreateScene
{
public:
    CreateScene();
    virtual ~CreateScene();
public:
    static EventArbiBase *createCase(string, string );
};

#endif /* CREATESCENE_H_ */
