#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 16  
void xorBlocks(uint8_t *out, uint8_t *in1, uint8_t *in2, size_t length) {
    for (size_t i = 0; i < length; i++) {
        out[i] = in1[i] ^ in2[i];
    }
}
void CBC_MAC(uint8_t *key, uint8_t *message, uint8_t *mac, size_t length) {
    xorBlocks(mac, key, message, length);  
}
void printBlock(uint8_t *block, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02x", block[i]);
    }
    printf("\n");
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x00};    
    uint8_t message[BLOCK_SIZE] = {0x10}; 
    uint8_t mac[BLOCK_SIZE];              
    CBC_MAC(key, message, mac, BLOCK_SIZE);
    printf("CBC-MAC for one-block message X: ");
    printBlock(mac, BLOCK_SIZE);
    uint8_t messageXorMac[BLOCK_SIZE];
    xorBlocks(messageXorMac, message, mac, BLOCK_SIZE);  
    uint8_t twoBlockMessage[2 * BLOCK_SIZE];
    memcpy(twoBlockMessage, message, BLOCK_SIZE);          
    memcpy(twoBlockMessage + BLOCK_SIZE, messageXorMac, BLOCK_SIZE);  
    CBC_MAC(key, twoBlockMessage, mac, 2 * BLOCK_SIZE);
    printf("CBC-MAC for two-block message X || (X XOR T): ");
    printBlock(mac, BLOCK_SIZE);

    return 0;
}
