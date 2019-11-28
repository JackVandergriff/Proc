#ifdef __cplusplus
extern "C" {
#endif

#include "process.h"

char getRoll(int8_t mask) { // Example mask 0b1111
    char i=0;
    while (mask >> i > 0) { // if i=4, mask >> i = 0
        i++;
    }
    return i;
}

void makeEntry(Sector* block, int8_t inputs, int8_t outputs) {
    block[1 + block[0].header.buffers + inputs/8].page.entries[inputs % 8] = outputs;
}

Sector* createBlock(int8_t inputs, int8_t outputs, int8_t registers, int8_t buffers) {
    int sectors = (1 << (inputs + registers))/8; // if 4 inputs/registers, then 16 entries (1 << 4), so 2 pages 
    Sector* block = malloc(sizeof(Sector) * (sectors + buffers + 2));
    block[0].header.buffers = buffers;
    block[0].header.input_mask = (1 << inputs) - 1;
    block[0].header.register_mask = (1 << registers) - 1;
    block[0].header.output_mask = ((1 << (registers + outputs)) - 1) ^ ((1 << registers) - 1);
    block[0].header.register_roll = inputs; 
    // imagine 3 inputs, one register, to get register then inputs need to roll left past input mask
    return block;
}

int8_t __always_inline lookup(Sector* block, int8_t inputs) {
    Header header = block[0].header;
    int8_t entry_num = ((header.current & header.register_mask) << header.register_roll) | inputs;
    return (block[1 + header.buffers + entry_num/8].page.entries[entry_num % 8]);
}

int main() {
    char line[100];
    int8_t input;
    int8_t cur;
    Sector* block = createBlock(2, 2, 1, 0);
    makeEntry(block, 0x00, 0x01);
    makeEntry(block, 0x01, 0x02);
    makeEntry(block, 0x02, 0x04);
    makeEntry(block, 0x03, 0x06);
    makeEntry(block, 0x04, 0x00);
    makeEntry(block, 0x05, 0x05);
    makeEntry(block, 0x06, 0x03);
    makeEntry(block, 0x07, 0x01);
    // hexdump("Block", block, 2 * sizeof(Sector));
    while (true) {
        fgets(line, sizeof line, stdin);
        sscanf(line, "%x", &input);
        cur = lookup(block, input);
        block[0].header.current = cur;
        printf("%x\n", cur);
    }
    return 0;
}

#ifdef __cplusplus
}
#endif