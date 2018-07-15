#include "data.h"
#include "base_json.h"

void data::val_to_str(std::string& outString)
{
    Json::Value v;
    v["nickname"] = nickname;
    v["school"] = school;
    v["msg"] = msg;
    v["cmd"] = cmd;
    serialize(v,outString);
}

void data::str_to_val(std::string& inString)
{
    Json::Value v;
    deserialize(inString,v);
    nickname = v["nickname"].asString();
    school = v["school"].asString();
    msg = v["msg"].asString();
    cmd = v["cmd"].asString();
}

#if 0
int main()
{
    data d;
    d.nickname = "zhangsan";
    d.school = "sust";
    d.msg = "hello";

    std::string s;
    d.val_to_str(s);
    std::cout<<s<<std::endl;
}

#endif
