#ifndef _UDP_CLIENT_H__
#define _UDP_CLIENT_H__

#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class udp_client
{
public:
    udp_client(const std::string _ip,const int _port);
    int InitClient();
    int RecvData(std::string& outString);
    int SendData(std::string& inString);
    ~udp_client();
private:
    struct sockaddr_in server;
    int sock;
};

#endif// _UDP_CLIENT_H__
