//============================================================================
// Name        : graduate.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "EventArbiBiSearch.h"
#include "EventArbiBase.h"
#include "EventArbiGroupSearch.h"
using namespace std;

int main() {
//	EventArbiBase *test = new EventArbiGroupSearch;
//	test->runAlgorithm();

	EventArbiBase *test2 = new EventArbiBiSearch;
	test2->runAlgorithm();
	return 0;
}
