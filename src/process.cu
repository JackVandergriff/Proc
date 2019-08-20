#include <stdio.h>
#include <cuda.h>
#include "process.h"

void cuda_process(Node* nodes_host) {
    // Node* nodes;
    // cudaMemcpy(nodes, nodes_host, sizeof(nodes_host), cudaMemcpyHostToDevice);
    
    printf("Yo GPU time\n");
}

__global__ void kernel_process(void*) {
    printf("things\n");
}