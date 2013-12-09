/*
 * ConfigLoadFile.h
 *
 *  Created on: 2013Äê12ÔÂ9ÈÕ
 *      Author: lvqicong
 */

#ifndef CONFIGLOADFILE_H_
#define CONFIGLOADFILE_H_

#include "ConfigBase.h"

using namespace std;

class ConfigLoadFile : public ConfigBase
{
public:
    ConfigLoadFile();
    virtual ~ConfigLoadFile();
public:
    static ConfigLoadFile *single;
    static ConfigLoadFile *getConfig();
private:
    void genPArray();
};

#endif /* CONFIGLOADFILE_H_ */
