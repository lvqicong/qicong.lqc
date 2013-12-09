//============================================================================
// Name        : graduate.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "CreateScene.h"
#include "EventArbiBase.h"
#include "string"

using namespace std;

int main()
{
    EventArbiBase *test;

    string configSwitch = "loadfile";

    test = CreateScene::createCase("group_search", configSwitch);
    test->runAlgorithm();
    delete test;

    test = CreateScene::createCase("bi_search", configSwitch);
    test->runAlgorithm();
    delete test;

    test = CreateScene::createCase("seq", configSwitch);
    test->runAlgorithm();
    delete test;

    return 0;
}
