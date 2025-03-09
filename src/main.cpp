/* HDMI-CEC to Wake-on-LAN (WoL) Implementation
 * Description: Listens for HDMI-CEC power-on signals and sends a Wake-on-LAN packet.
 */

#include <iostream>
#include <libcec/cec.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BROADCAST_IP "255.255.255.255"
#define WOL_PORT 9

using namespace std;

// Function to send Wake-on-LAN packet
void sendWOL(const string& macAddress) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        cerr << "Failed to create socket" << endl;
        return;
    }

    int optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(WOL_PORT);
    addr.sin_addr.s_addr = inet_addr(BROADCAST_IP);

    unsigned char packet[102];
    memset(packet, 0xFF, 6);
    unsigned char mac[6];
    sscanf(macAddress.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", 
           &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);
    
    for (int i = 0; i < 16; i++) {
        memcpy(&packet[6 + i * 6], mac, 6);
    }

    sendto(sock, packet, sizeof(packet), 0, (struct sockaddr*)&addr, sizeof(addr));
    close(sock);
    cout << "WOL packet sent to " << macAddress << endl;
}

// Callback for HDMI-CEC power events
int cec_callback(void* param, const CEC::cec_command* command) {
    if (command->opcode == CEC::CEC_OPCODE_IMAGE_VIEW_ON || command->opcode == CEC::CEC_OPCODE_POWER_ON) {
        cout << "TV powered on! Sending Wake-on-LAN." << endl;
        sendWOL("AA:BB:CC:DD:EE:FF"); // Replace with actual MAC address
    }
    return 1;
}

int main() {
    CEC::ICECAdapter* cec_adapter = CECInitialise();
    if (!cec_adapter) {
        cerr << "CEC initialization failed!" << endl;
        return 1;
    }
    
    cec_adapter->SetCommandCallback(&cec_callback, nullptr);
    cec_adapter->Open("Raspberry Pi HDMI");
    
    cout << "Listening for HDMI-CEC events..." << endl;
    while (true) {
        sleep(10);
    }
    
    cec_adapter->Close();
    return 0;
}
