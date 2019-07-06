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

// Macro to catch CUDA errors in kernel launches
#define CHECK_LAUNCH_ERROR()                                          \
    do {                                                                  \
        /* Check synchronous errors, i.e. pre-launch */                   \
        cudaError_t err = cudaGetLastError();                             \
        if (cudaSuccess != err) {                                         \
            fprintf (stderr, "Cuda error in file '%s' in line %i : %s.\n",\
                     __FILE__, __LINE__, cudaGetErrorString(err) );       \
            exit(EXIT_FAILURE);                                           \
        }                                                                 \
        /* Check asynchronous errors, i.e. kernel failed (ULF) */         \
        err = cudaDeviceSynchronize();                                    \
        if (cudaSuccess != err) {                                         \
            fprintf (stderr, "Cuda error in file '%s' in line %i : %s!\n",\
                     __FILE__, __LINE__, cudaGetErrorString( err) );      \
            exit(EXIT_FAILURE);                                           \
        }                                                                 \
    } while (0)

// Macro to catch CUDA errors in CUDA runtime calls
#define CUDA_CHECK(call)                                              \
    do {                                                                  \
        cudaError_t err = call;                                           \
        if (cudaSuccess != err) {                                         \
            fprintf (stderr, "Cuda error in file '%s' in line %i : %s.\n",\
                     __FILE__, __LINE__, cudaGetErrorString(err) );       \
            exit(EXIT_FAILURE);                                           \
        }                                                                 \
    } while (0)


