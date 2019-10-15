#include "threadsPool.h"

int main(){
    init(1, 0,[](int i){std::cout<<i<<std::endl;});
    wakeUp();
    return 0;
}
