#include"RingQueue.hpp"

void *comsumer(void *ring_queue)
{
  RingQueue* rq = (RingQueue*)ring_queue;
  while(1)
  {
    int date = 0;
    rq->Get(date);
    std::cout<< "comsumer done ... #" << date<<std::endl;
  }
}

//让生产者不断的放100-110之间的数
void *productor(void *ring_queue)
{
  RingQueue* rq = (RingQueue*)ring_queue;
  while(1)
  {
    sleep(1);
    //要让他们进行组内的竞争
    int count = 100;  
    rq->Put(count);
    if(count > 110)
    {
      count = 100;
    }
    
    std::cout<<"productor done  ..."<<std::endl;
  }
}

int main()
{
  pthread_t c,p;
  RingQueue* rq = new RingQueue();
  pthread_create(&c,nullptr,comsumer,rq);
  pthread_create(&p,nullptr,productor,rq);


  pthread_join(c,nullptr);
  pthread_join(p,nullptr);

  delete rq;
  return 0;
}
