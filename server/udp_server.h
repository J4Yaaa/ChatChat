#ifndef _UDP_SERVER_H_
#define _UDP_SERVER_H_

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <map>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <semaphore.h>

#include "data_pool.h"

class udp_server
{
public:
    udp_server(int _port); // 构造函数中不做任何有风险的创建动作
    int InitServer();
    void addrUser(struct sockaddr_in& client);
    void delUser(struct sockaddr_in& client);
    int RecvData(std::string& outString);
    int SendData(const std::string& inString,struct sockaddr_in& peer,const socklen_t& len);
    int broadcast(); // 服务器收到消息以后,转发给所有在线的用户
    ~udp_server(); 
private:
    std::string ip;
    int port;
    int sock;

    std::map<int,struct sockaddr_in> online; // 维护一个用户表
    data_pool pool; // 维护一个存放数据的数据池
};

#endif
