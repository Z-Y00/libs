this code was intended to let only first thread to call init
And others spin wait


```
#include <atomic>
// #include <stdatomic.h>

// https://stackoverflow.com/a/10146102/8428146
// https://stackoverflow.com/a/7281770/8428146
// https://stackoverflow.com/questions/44165049/cache-align-elements-of-array
struct OutputAccessOrInitLock{
  //when enter this struct, we do an atomic read-modify-write 
  //we will get the # of seq we enter it.
  //only the 1st one will init it
  //the rest will spin wait and check for init flag to be true.
  std::atomic<int> entered_threads = 0;
  uint64_t padding[16] = {0};
  volatile bool init_flag = false;//just do simple read from memory   

}

 if(!p_ort_value->IsAllocated()){// if not init, enter this critical section
    int my_thread_seq = (++entered_threads);
    if(my_thread_seq==1){
      //we are the first thread!
      //we shall do the init
      init_flag = true;
      printf("init, only one thread shall call this %p\n",this);
    }else{
      //wait for first thread to finish
      while (!init_flag)
      {
        ;//spin!
      }
      printf("spin wait this %p\n",this);
    }
  }else{//if already init, just get it without worry of racing
      printf("no wait this %p\n",this);
  }
```

# only one thread using the resouces
If it is only one thread shall use the resouces, simple spin lock would works fine.
# spinlock vs mutex
https://www.realworldtech.com/forum/?threadid=189711&curpostid=189723

https://rigtorp.se/spinlock/

https://probablydance.com/2019/12/30/measuring-mutexes-spinlocks-and-how-bad-the-linux-scheduler-really-is/
