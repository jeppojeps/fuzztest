#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Simulated Smart Contract Structure
typedef struct {
    uint32_t functionSelector; // Simulates the function identifier
    char data[256];            // Simulates data passed to the contract function
} SmartContract;

// Vulnerable parsing function
void parse_smart_contract(SmartContract *contract) {
    char buffer[50]; // Small buffer for demonstration

    // Vulnerable memcpy: copying data without size check
    memcpy(buffer, contract->data, sizeof(contract->data)); // Buffer overflow here

    printf("Function Selector: %u\n", contract->functionSelector);
    printf("Data: %s\n", buffer);
}

// Fuzzing infrastructure (similar to the previous example)...
// startForkserver, getWork, startWork, doneWork functions...

int main() {
    startForkserver();

    // Buffer for the contract
    char workBuffer[1024];
    int workSize;

    while (1) {
        workSize = getWork(workBuffer, sizeof(workBuffer));
        if (workSize == 0) {
            break; // Exit loop if no more work
        }

        startWork();

        // Assuming the work is a SmartContract
        SmartContract *contract = (SmartContract*)workBuffer;

        // Simulate parsing a smart contract
        parse_smart_contract(contract);

        doneWork();
    }

    return 0;
}
