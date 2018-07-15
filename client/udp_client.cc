#include "udp_client.h"

udp_client::udp_client(const std::string _ip,const int _port)
    :sock(-1)
{
    server.sin_family = AF_INET;
    server.sin_port = htons(_port);
    server.sin_addr.s_addr = inet_addr(_ip.c_str());
}

int udp_client::InitClient()
{
    sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0)
    {
        std::cerr<<"socket"<<std::endl;
        return -1;
    }
    return 0;
}

int udp_client::RecvData(std::string& outString)
{
    char buf[1024] = {0};
    struct sockaddr_in peer;
    socklen_t len = sizeof(peer);

    int ret = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);

    if(ret <= 0)
    {
        std::cerr<<"recvfrom"<<std::endl;
        return -1;
    }
    buf[ret] = '\0';
    outString = buf;
    return 0;
}

int udp_client::SendData(std::string& inString)
{
    int ret = sendto(sock,inString.c_str(),inString.size(),0,(struct sockaddr*)&server,sizeof(server));
    if(ret < 0)
    {
        std::cerr<<"sendto"<<std::endl;
        return -1;
    }
    return 0;
}

udp_client::~udp_client()
{
    if(sock >= 0)
    {
        close(sock);
        sock = -1;
    }
}
