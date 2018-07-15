#include "base_json.h"

void serialize(Json::Value& val,std::string& outString)
{
    /* Json::FastWriter w; */
    Json::StyledWriter w;
    outString = w.write(val);
}

void deserialize(std::string& inString,Json::Value& val)
{
    Json::Reader r;
    r.parse(inString,val,false);
}
