/*
 * Config.cpp
 *
 *  Created on: 2013Äê11ÔÂ28ÈÕ
 *      Author: lvqicong
 */

#include "ConfigBase.h"
#include "cstddef"
#include "fstream"

using namespace std;

const string ConfigBase::configFileName = "./data/config";

ConfigBase::ConfigBase()
{
    totalMessage = 0;
    deviceNum = 0;

    ifstream configFile(configFileName.c_str());
    configFile >> totalMessage >> deviceNum;
    pArray = new double[deviceNum];

    configFile.close();
    configFile.clear();
}

ConfigBase::~ConfigBase()
{
    delete[] pArray;
}

