//the threads will run upon wakeup(), and will sleep when its own works done
// the works needs to be balanced, thus the cost of sync will be saved

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <string>
#include <thread>
#include <functional>
#include <mutex>
#include <vector>
#include <condition_variable>

std::condition_variable cv;
std::mutex cv_m;
std::vector<std::thread> threadPool;

void wakeUp(){
     cv.notify_all();
}

void finalize(){
    
}
// int get_numa(void* ptr){
//     get NUMA status  
//     int numa_node = -1;
//     get_mempolicy(&numa_node, NULL, 0, (void*)ptr, MPOL_F_NODE | MPOL_F_ADDR);
//     LOG(INFO)<<numa_node;
//     return numa_node;
// }


//working!!
// std::function<void()> do_work(int i, std::function<void(int)> do){
// return [i](){
//     while(true){
//      std::unique_lock<std::mutex> lk(cv_m);
//      cv.wait(lk);
//      do(i);
//     };
//   };
// }

void init(int num_threads, int NUMA,std::function<void(int)> do){
    //launch the threads
    threadPool = std::vector<std::thread>(num_threads);
    for (int i = 0; i < num_threads; ++i){
    //threadPool[i] = std::thread(do_work(i,do));
    threadPool[i] = std::thread(&do,i);
    //Create a cpu_set_t object representing a set of CPUs. Clear it and mark
    //only CPU i as set.
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(i, &cpuset);
    int rc = pthread_setaffinity_np(threadPool[i].native_handle(),
                                    sizeof(cpu_set_t), &cpuset);
    if (rc != 0) {
      std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
    }
    }
}



