#ifndef _DATA_H_
#define _DATA_H_

#include <iostream>
#include <string>
#include "base_json.h"

class data
{
public:
    // 使用默认的构造函数和析构函数即可
    
    // 序列化: 将value转化为string
    void val_to_str(std::string& outString);
    // 反序列化: 将string转化为value
    void str_to_val(std::string& inString);
public:
    std::string nickname; // 昵称
    std::string school;   // 学校
    std::string msg;      // 所发送的消息
    std::string cmd;      // 预留
};

#endif
