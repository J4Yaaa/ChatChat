#include "udp_server.h"
#include "data.h"

void* ProductEntry(void* arg)
{
    udp_server* server = (udp_server*)arg;
    while(1)
    {
        std::string str;
        server->RecvData(str);
        std::cout<<str<<std::endl;
    }
    return NULL;
}

void* ConsumeEntry(void* arg)
{
    udp_server* server = (udp_server*)arg;
    while(1)
    {
        server->broadcast();
        /* server->show_online_map(); */
        /* sleep(2); */
    }
    return NULL;
}

int main(int argc,char* argv[])
{
    if(argc != 2)
    {
        std::cout<<"Usage "<<argv[0]<<" [port]"<<std::endl;
        return 1;
    }
    udp_server server(atoi(argv[1]));
    server.InitServer();

    // 利用多线程,客户端发送数据,服务器读取数据并写入到pool中
    // 进入事件循环
    pthread_t p,c;
    pthread_create(&p,NULL,ProductEntry,(void*)&server); // 负责接收数据
    pthread_create(&c,NULL,ConsumeEntry,(void*)&server); // 负责广播数据
    pthread_join(c,NULL);
    pthread_join(p,NULL);
    return 0;
}
