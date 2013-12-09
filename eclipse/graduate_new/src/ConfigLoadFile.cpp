/*
 * ConfigLoadFile.cpp
 *
 *  Created on: 2013Äê12ÔÂ9ÈÕ
 *      Author: lvqicong
 */

#include "ConfigLoadFile.h"
#include "fstream"

ConfigLoadFile *ConfigLoadFile::single = NULL;
ConfigLoadFile *ConfigLoadFile::getConfig()
{
    if (single == NULL)
        single = new ConfigLoadFile;
    return single;
}

void ConfigLoadFile::genPArray()
{
    ifstream configFile(configFileName.c_str());
    configFile >> totalMessage >> deviceNum;
    for( int i = 0 ; i < deviceNum ; ++i )
    {
        configFile >> pArray[i];
    }
    configFile.close();
    configFile.clear();
}

ConfigLoadFile::ConfigLoadFile()
{
    genPArray();
}

ConfigLoadFile::~ConfigLoadFile()
{
    // TODO Auto-generated destructor stub
}

