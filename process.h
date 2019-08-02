#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

#define DEBUG

#define AD(x) ((x) >> 7)
#define AT(x) (((x) & 0b01110000) >> 4)
#define DT(x) (((x) & 0b01111110) >> 1)
#define AV(x) ((x) & 0b00001111)
#define DV(x) ((x) & 0b00000001)
#define SDV(x, y) x = ((x) & 0b10000000) | (y)


typedef struct node {
    struct node *input1;
    struct node *input2;
    unsigned char typeval;
    unsigned char typevalnew;
} Node;

void updateNode(Node *n) {
    if (AD(n->typeval) == 0) {
        switch (DT(n->typeval)) {
            case 0b1:
                SDV(n->typevalnew, DV(n->input1->typeval) | DV(n->input2->typeval));
                break;
            case 0b10:
                SDV(n->typevalnew, DV(n->input1->typeval) & DV(n->input2->typeval));
                break;
            case 0b11:
                SDV(n->typevalnew, DV(n->input1->typeval) ^ DV(n->input2->typeval));
                break;
            case 0b100:
                SDV(n->typevalnew, ~DV(n->input1->typeval));
                break;
            default:
                break;
        }
    }
}

Node* nalloc() {
    return (Node*) calloc(1, sizeof(Node));
}

#ifdef DEBUG

void bin(unsigned char n) { 
    unsigned char i; 
    for (i = 1 << 7; i > 0; i = i / 2) 
        (n & i)? printf("1"): printf("0"); 
} 

int main() {
    Node* n1 = nalloc();
    n1->typeval = 0b00000001;
    Node* n2 = nalloc();
    n1->typeval = 0b00000000;
    Node* n3 = nalloc();
    n3->input1 = n1;
    n3->input2 = n2;
    n3->typeval = 0b00000010;

    updateNode(n3);
    bin(n3->typevalnew);
    printf("\n");

    return 0;
}

#endif


#undef AD
#undef AT
#undef DT
#undef AV
#undef DV

#ifdef __cplusplus
}
#endif