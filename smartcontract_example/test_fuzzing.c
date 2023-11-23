#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Simulated Smart Contract Structure
typedef struct {
    uint32_t functionSelector; // Simulates the function identifier
    uint64_t arg1;             // Simulates the first argument (e.g., an amount)
    uint64_t arg2;             // Simulates the second argument (e.g., a recipient address)
    char extraData[200];       // Additional data field
} SmartContract;

// Vulnerable parsing function
void parse_smart_contract(SmartContract *contract) {
    char buffer[50]; // Small buffer for demonstration

    // Vulnerable memcpy: copying extraData without size check
    memcpy(buffer, contract->extraData, sizeof(contract->extraData)); // Buffer overflow here

    printf("Function Selector: %u\n", contract->functionSelector);
    printf("Arg1: %llu\n", contract->arg1);
    printf("Arg2: %llu\n", contract->arg2);
    printf("Extra Data: %s\n", buffer);
}


int main(int argc, char**argv) {

    // Buffer for the contract
    char *buf[100];
    while (__AFL_LOOP(10000)) {

        // Assuming the work is a SmartContract
        SmartContract *contract = (SmartContract*)buf;

        // Simulate parsing a smart contract
        parse_smart_contract(contract);

    }

    return 0;
}
