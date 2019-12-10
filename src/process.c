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

void makeEntry_raw(Sector* block, int8_t inputs, int8_t outputs) {
    block[1 + block[0].header.buffers + inputs/8].page.entries[inputs % 8] = outputs;
}

void makeEntry(Sector* block, int8_t inputs, int8_t input_registers, int8_t outputs, int8_t output_registers) {
    Header header = block[0].header;
    makeEntry_raw(
        block, 
        inputs | (input_registers << header.register_roll),             // roll registers above inputs
        output_registers | (outputs << getRoll(header.register_mask))   // roll outputs above registers
    );
}

Sector* createBlock(int8_t inputs, int8_t outputs, int8_t registers, int8_t buffers) {
    int sectors = (1 << (inputs + registers))/8;                        // if 4 inputs/registers, then 16 entries (1 << 4), so 2 pages 
    Sector* block = malloc(sizeof(Sector) * (sectors + buffers + 2));   // Header, footer, buffers, and pages
    block[0].header.buffers = buffers;                                  // block[0] will always be header
    block[0].header.input_mask = (1 << inputs) - 1;                     // fill in ex. 0b0111 with ones by 0b1000 - 1
    block[0].header.register_mask = (1 << registers) - 1;               // Same for registers
    block[0].header.output_mask =                                       // Output mask sits left of register mask, so
        ((1 << (registers + outputs)) - 1) ^ ((1 << registers) - 1);    // grab full mask and remove register portion
    block[0].header.register_roll = inputs;                             // To roll register past inputs, must go left by inputs
    return block;
}

int8_t __always_inline lookup(Sector* block, int8_t inputs) {
    Header header = block[0].header;
    int8_t entry_num = ((header.current & header.register_mask)         // Grab register portion of current data
        << header.register_roll) | inputs;                              // Roll left past inputs and add input data in
    return (block[1 + header.buffers                                    // Skip header and buffers to find start of table
        + entry_num/8].page.entries[entry_num % 8]);                    // 8 entries per sector, so grab floor and use remainder as index
}

int8_t __always_inline lookup_and_buffer(Sector* block, int8_t inputs) {
    Header* header = ((Header*) block);
    header->current = lookup(block, inputs);
    block[1 + header->buffer_index/8].buffer_page.entries[header->buffer_index % 8] = header->current;
    header->buffer_index++;
    return header->current;
}

int main() {
    char line[100];
    int8_t input;
    int8_t cur;
    Sector* block = createBlock(2, 2, 1, 2);
    printf("%i\n", getRoll(block[0].header.input_mask));
    // Inputs: J K, outputs: Q ~Q, register Q
    makeEntry(block, 0b00, 0b0, 0b01, 0b0);
    makeEntry(block, 0b01, 0b0, 0b01, 0b0);
    makeEntry(block, 0b10, 0b0, 0b10, 0b1);
    makeEntry(block, 0b11, 0b0, 0b10, 0b1);
    makeEntry(block, 0b00, 0b1, 0b10, 0b1);
    makeEntry(block, 0b01, 0b1, 0b01, 0b0);
    makeEntry(block, 0b10, 0b1, 0b10, 0b1);
    makeEntry(block, 0b11, 0b1, 0b01, 0b0);
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