//
//  DataBase64.h
//  changeableball
//
//  Created by huge on 5/4/15.
//
//

#ifndef __changeableball__DataBase64__
#define __changeableball__DataBase64__

#include <stdio.h>

#include <string>

#include "cocos2d.h"
using namespace cocos2d;

std::string SaveData(unsigned char const* , unsigned int len);
std::string ParseData(std::string const& s);


static int getIntegerForKey(const char* pKey)
{
    std::string key = pKey;
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()), key.length());
    std::string data = CCUserDefault::sharedUserDefault()->getStringForKey(key.c_str());
    //std::string data = CCUserDefault::sharedUserDefault()->getStringForKey(pKey);//注释后，使用键值加密，开启，注释上句使用值加密
    data = ParseData(data);
    CCString *str = CCString::create(data);
    return str->intValue();
}

static void setIntegerForKey(const char* pKey, int value)
{
    char buffer[50];
    sprintf(buffer,"%d",value);
    std::string data = buffer;
    std::string key = pKey;
    data = SaveData(reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()),key.length());
    CCUserDefault::sharedUserDefault()->setStringForKey(key.c_str(), data);
    //CCUserDefault::sharedUserDefault()->setStringForKey(pKey, data);//注释后，使用键值加密，开启，注释上句使用值加密
    CCUserDefault::sharedUserDefault()->flush();
}

static void setStringForKey(const char* pKey,const char* value)
{
    std::string data = value;
    std::string key = pKey;
    data = SaveData(reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()),key.length());
    CCUserDefault::sharedUserDefault()->setStringForKey(key.c_str(), data);
    //CCUserDefault::sharedUserDefault()->setStringForKey(pKey, data);//注释后，使用键值加密，开启，注释上句使用值加密
    CCUserDefault::sharedUserDefault()->flush();
}
static std::string getStringForKey(const char* pKey)
{
    std::string key = pKey;
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()), key.length());
    std::string data = CCUserDefault::sharedUserDefault()->getStringForKey(key.c_str());
    //std::string data = CCUserDefault::sharedUserDefault()->getStringForKey(pKey);//注释后，使用键值加密，开启，注释上句使用值加密
    data = ParseData(data);
    CCString *str = CCString::create(data);
    return str->getCString();
}
#endif /* defined(__changeableball__DataBase64__) */
