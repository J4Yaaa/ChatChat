#include "data_pool.h"

data_pool::data_pool(int _cap)
    :pool(_cap),BlankStep(0),DataStep(0),cap(_cap)
{
    // 初始化信号量
    sem_init(&BlankSem,0,_cap);
    sem_init(&DataSem,0,_cap);
}

void data_pool::GetData(std::string& outString)
{
    sem_wait(&BlankSem);
    outString = pool[BlankStep]; // 这里可以赋值是因为string中重载过
    ++BlankStep; //拿走一个数据以后,空格多了一个
    if(BlankStep >= 256)
    {
        BlankStep = 0;
    }
    sem_post(&DataSem);
}
void data_pool::PutData(const std::string& inString)
{
    sem_wait(&DataSem);
    pool[DataStep] = inString;
    ++DataStep;
    if(DataStep >= 256)
    {
        DataStep = 0;
    }
    sem_post(&BlankSem);
}

data_pool::~data_pool()
{
    sem_destroy(&BlankSem);
    sem_destroy(&DataSem);
}
