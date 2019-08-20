#ifdef __cplusplus
extern "C" {
#endif

#include "process.h"

void initializeNode(Node *n, Gates gate, bool analog, unsigned char startVal) {
    n->type = (gate << 1) | analog;
    n->value = startVal;
}

void updateNode(Node *n) {
    if (_AD(n) == 0) {
        switch (_TYPE(n)) {
            case OR:
                n->value = n->input1->value | n->input2->value;
                break;
            case AND:
                n->value = n->input1->value & n->input2->value;
                break;
            case XOR:
                n->value = n->input1->value ^ n->input2->value;
                break;
            case NOT:
                n->value = ~n->input1->value & 1;
                break;
            case LATCH:
                if (n->input1->value > 0) n->value = n->input2->value; 
            default:
                break;
        }
    }
}

Node* nalloc(int size) {
    return (Node*) calloc(size, sizeof(Node));
}

void swap(Node *n1, Node *n2) {
    Node tmp = *n2;
    *n2 = *n1;
    *n1 = tmp;
}

#ifdef __cplusplus
extern "C" {
#endif