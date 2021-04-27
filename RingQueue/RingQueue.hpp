#pragma once 

#include<iostream>
#include<vector>
#include<unistd.h>
#include<semaphore.h>

#define NUM 10

class RingQueue 
{
  private:
    std::vector<int> v;
    int max_cap;
    sem_t sem_blank;//生产者
    sem_t sem_date; //消费者
    int c_index;//消费者的索引
    int p_index;//生产者的索引
  
  private:
    void P(sem_t& s)
    {
      sem_wait(&s);
    }
    void V(sem_t& s)
    {
      sem_post(&s);
    }
  public:
    RingQueue(int _cap = NUM)
      :max_cap(_cap)
      ,v(_cap) 
    {
      sem_init(&sem_blank,0,max_cap);//要初始化哪一个信号量，0表示线程，非0表示进程，要初始化的个数
      sem_init(&sem_date,0,0);
      c_index = 0;
      p_index = 0;
    }

    ~RingQueue()
    {
      sem_destroy(&sem_blank);
      sem_destroy(&sem_date);
      c_index = 0;
      p_index = 0;
    }
    
    //谁来拿，当然是消费者
    void Get(int& out)
    {
      P(sem_date);//--
      //消费
      out = v[c_index];
      c_index++;
      c_index %= max_cap;
      V(sem_blank);//++
    }

    void Put(const int& in)
    {
      P(sem_blank);//相当于预约
      //生产
      v[p_index] = in;
      p_index++;
      p_index %= max_cap;
      V(sem_date);
    }
};
