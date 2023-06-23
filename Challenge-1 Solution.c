#include <stdio.h>
#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

// CRC-16 implementation (using CCITT polynomial 0x1021)
uint16_t calculateCRC(uint8_t *data, uint8_t length) {
    uint16_t crc = 0xFFFF;
    
    for (uint8_t i = 0; i < length; ++i) {
        crc ^= (uint16_t)data[i] << 8;
        for (uint8_t j = 0; j < 8; ++j) {
            if (crc & 0x8000)
                crc = (crc << 1) ^ 0x1021;
            else
                crc = crc << 1;
        }
    }
    
    return crc;
}

int isPacketCorrupted(data_packet_t *packet) {
    uint16_t calculatedCRC = calculateCRC((uint8_t *)packet, sizeof(data_packet_t) - sizeof(uint16_t));
    
    return (calculatedCRC != packet->crc);
}

int main() {
    // Example usage
    data_packet_t received_packet; // Define the received_packet variable
    
    // Assuming you have received the packet and populated its values
    received_packet.id = 1;
    received_packet.data_length = 5;
    received_packet.data[0] = 0x11;
    received_packet.data[1] = 0x22;
    received_packet.data[2] = 0x33;
    received_packet.data[3] = 0x44;
    received_packet.data[4] = 0x55;
    received_packet.crc = calculateCRC((uint8_t *)&received_packet, sizeof(data_packet_t) - sizeof(uint16_t)); // Assuming the received CRC value
    
    if (isPacketCorrupted(&received_packet)) {
        // Packet is corrupted
        printf("Received packet is corrupted and will be discarded.\n");
    } else {
        // Packet is intact
        printf("Received packet is intact and will be processed.\n");
    }
    
    return 0;
}

