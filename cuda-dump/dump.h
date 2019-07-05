/**
 * @brief dump from a cuda mem
 */

#include <stdio.h>
#include <stdlib.h>
//#include <assert.h>//seems not working with cpp


bool _dump_binary_graph(char* filename,void* graph,size_t size){
        FILE *out = fopen(filename, "w");
        if(!out){
            puts("open failed!");
        }
        if(graph != NULL)
        {
            size_t to_go = size;
            //while(to_go > 0)
            {
                const size_t wrote = fwrite(graph, to_go, 1, out);
                //if(wrote == 0)
                //    break;
               // to_go -= wrote;//why this is wrong??????
            }
            puts("write finished");
            fclose(out);
            return true;
        }
    return false;
}

bool dump_cuda_mem(char * name,void* device,size_t size){
    void* hMem=malloc(size);
    //assert(hMem);
    cudaMemcpy(hMem,device, size, cudaMemcpyDeviceToHost);
    bool result=_dump_binary_graph(name,hMem,size);
    free(hMem);
    return result;
}
bool dump_ram(char * name,void* hMem,size_t size){
    //assert(hMem);
    printf("the size %d\n",size);
    bool result=_dump_binary_graph(name,hMem,size);
    if(!result){
       puts("dump failed! graph==NULL");
    }
    return result;
}
