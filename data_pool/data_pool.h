#ifndef _DATA_POOL_H__
#define _DATA_POOL_H__

#include <iostream>
#include <string>
#include <vector>
#include <semaphore.h>

class data_pool
{
public:
    data_pool(int _cap=256);
    void GetData(std::string& outString); //从数据池中取数据
    void PutData(const std::string& inString); //向数据池中放数据
    ~data_pool();
private:
    sem_t BlankSem; //空格的资源,表示生产者可用资源
    sem_t DataSem;  //数据的资源,表示消费者可用资源
    std::vector<std::string> pool; //用vector维护一个环形队列,存放数据(数据池)
    int BlankStep;  //表示生产者的步数
    int DataStep;   //表示消费者的步数
    int cap;        //可存放数据的总容量
};

#endif// _DATA_POOL_H__
