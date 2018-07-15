#ifndef _BASE_JSON_H_
#define _BASE_JSON_H_

#include <iostream>
#include <json/json.h>

// 序列化: Value -> string
void serialize(Json::Value& val,std::string& outString);

// 反序列化: string -> Value
void deserialize(std::string& inString,Json::Value& val);

#endif //_BASE_JSON_H_
