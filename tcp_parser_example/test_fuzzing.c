#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

// TCP Header structure
typedef struct {
    uint16_t source_port;
    uint16_t dest_port;
    uint32_t seq_number;
    uint32_t ack_number;
    uint8_t data_offset;
    uint8_t flags;
    uint16_t window;
    uint16_t checksum;
    uint16_t urgent_pointer;
} TCPHeader;

// Wrapper function for memset
void custom_memset(void *dest, int val, size_t len) {
    memset(dest, val, len);
}


void receive_tcp_packet(TCPHeader *tcp_header, char *payload, size_t payload_size) {
    char buffer[50]; // Small buffer for demonstration
    memcpy(buffer, payload, payload_size); // Buffer overflow here

    printf("Source Port: %d, Destination Port: %d\n", ntohs(tcp_header->source_port), ntohs(tcp_header->dest_port));
    printf("Sequence Number: %u\n", ntohl(tcp_header->seq_number));
    printf("Ack Number: %u\n", ntohl(tcp_header->ack_number));
    printf("Payload: %s\n", buffer);
}

int main() {
    // Buffer for the payload
    char workBuffer[1024];
    int workSize;

    while (__AFL_LOOP(10000)) {
        if (workSize == 0) {
            break; // Exit loop if no more work
        }


        // Assuming the first part of the work is the TCP header
        TCPHeader *tcp_header = (TCPHeader*)workBuffer;

        // The rest of the work is considered the payload
        char *payload = workBuffer + sizeof(TCPHeader);
        int payloadSize = workSize - sizeof(TCPHeader);

        // Simulate receiving a TCP packet
        receive_tcp_packet(tcp_header, payload, payloadSize);

    }

    return 0;
}

