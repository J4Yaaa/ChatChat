#include "udp_server.h"
#include <data.h>

udp_server::udp_server(int _port)
    :port(_port),sock(-1),pool(256)
{}

int udp_server::InitServer()
{
    sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0)
    {
        std::cerr<<"socket "<<std::endl;
        return -1;
    }
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
    {
        std::cerr<<"bind "<<std::endl;
        return -2;
    }
    return 0;
}

void udp_server::addrUser(struct sockaddr_in &client)
{
    online.insert(std::pair<int,struct sockaddr_in>(client.sin_addr.s_addr,client));
}

void udp_server::delUser(struct sockaddr_in& client)
{
    std::map<int,struct sockaddr_in>::iterator it = online.find(client.sin_addr.s_addr);
    if(it != online.end())
    {
        online.erase(it);
    }
}

int udp_server::RecvData(std::string& outString)
{
    char buf[1024] = {0};
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    int ret = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);
    
    // 只有接收数据成功了以后,我们才需要对数据进行处理
    if(ret > 0)
    {
        buf[ret] = '\0';
        outString = buf;
        pool.PutData(outString);
        data d;
        d.str_to_val(outString);
        if(d.cmd == "QUIT")
        {
            delUser(client);
        }
        else
        {
            addrUser(client);
        }
        return 0;
    }
    return -1;
}

int udp_server::SendData(const std::string& inString,struct sockaddr_in& peer,const socklen_t& len)
{
    int ret = sendto(sock,inString.c_str(),inString.size(),0,(struct sockaddr*)&peer,len);

    if(ret < 0)
    {
        std::cerr<<"sendto "<<std::endl;
    }
    return 0;
}

int udp_server::broadcast()
{
    std::string data;
    pool.GetData(data);
    std::map<int,struct sockaddr_in>::iterator it = online.begin();
    for(;it != online.end(); ++it)
    {
       SendData(data,it->second,sizeof(it->second)); 
    }
    return 0;
}

udp_server::~udp_server() 
{
    if(sock >= 0)
    {
        close(sock);
        sock = -1;
    }
}
