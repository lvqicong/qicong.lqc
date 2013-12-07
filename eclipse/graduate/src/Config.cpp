/*
 * Config.cpp
 *
 *  Created on: 2013Äê11ÔÂ28ÈÕ
 *      Author: lvqicong
 */

#include "Config.h"
#include "cstddef"
#include "fstream"

using namespace std;

const string Config::configFileName = "./data/config";

Config *Config::single = NULL;
Config *Config::getConfig()
{
    if (single == NULL)
        single = new Config;
    return single;
}

Config::Config()
{
    totalMessage = 0;
    deviceNum = 0;

    ifstream configFile(configFileName.c_str());
    configFile >> totalMessage >> deviceNum;
    pArray = new double[deviceNum];
    for (int i = 0; i < deviceNum; ++i)
    {
        configFile >> pArray[i];
    }
    configFile.close();
    configFile.clear();
}

Config::~Config()
{
    delete[] pArray;
}

