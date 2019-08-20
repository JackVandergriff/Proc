#ifdef __cplusplus
extern "C" {
#endif

#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// #define DEBUG

#define _AD(x) ((x->type) & 1)
#define _TYPE(x) ((x->type) >> 1)

typedef struct node {
    struct node *input1;
    struct node *input2;
    unsigned char type; // what sort of gate it is
    unsigned char value; // what value it holds
    unsigned char proc_type; // special info for the update function
} Node;

typedef enum gates{
    NONE, OR, AND, XOR, NOT, NAND, NOR, LATCH
} Gates;

#ifdef DEBUG
const char* gatestring[] = {"NONE", "OR", "AND", "XOR", "NOT", "NAND", "NOR", "LATCH"};
#endif

void initializeNode(Node*, Gates, bool, unsigned char);
void updateNode(Node*);
Node* nalloc(int);
void swap(Node*, Node*);

#ifdef DEBUG

void bin(unsigned char n) { 
    unsigned char i; 
    for (i = 1 << 7; i > 0; i = i / 2) 
        (n & i)? printf("1"): printf("0"); 
} 

void bin_node(Node *n) {
    printf("[*] Node at address %X\n", n);
    printf("[*] Type:           %s\n", gatestring[n->type >> 1]);
    printf("[*] Value:          "); bin(n->value); printf("\n");
    printf("[*] Input 1 at:     %X\n", n->input1);
    printf("[*] Input 2 at:     %X\n", n->input2);
    printf("\n");
}

int main() {
    Node* nodes = nalloc(3);
    initializeNode(nodes, NONE, false, 1);
    initializeNode(nodes+1, NONE, false, 0);
    initializeNode(nodes+2, LATCH, false, 1);
    nodes[2].input1 = nodes;
    nodes[2].input2 = nodes+1;

    bin_node(nodes);
    swap(nodes, nodes+1);
    bin_node(nodes);
    bin_node(nodes+2);

    updateNode(nodes+2);
    bin(nodes[2].value);
    printf("\n");

    return 0;
}

#endif
#endif

#ifdef __cplusplus
}
#endif