#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define TARGET_IP "10.0.0.1"  // Replace with the actual IP of your target
#define TARGET_PORT 12345      // Replace with the actual port of your target
#define PACKET_SIZE 1024
#define PACKET_RATE 10
#define DURATION 30

int main() {
    int sockfd;
    struct sockaddr_in target_addr;
    char packet[PACKET_SIZE];
    int sent_packets = 0;
    struct timeval start_time, end_time;
    double transfer_bytes = 0.0;

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    // Configure target address
    memset(&target_addr, 0, sizeof(target_addr));
    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(TARGET_PORT);
    target_addr.sin_addr.s_addr = inet_addr(TARGET_IP);

    // Generate data for the packet (you can customize this part)
    memset(packet, 'x', PACKET_SIZE);

    // Start sending traffic
    gettimeofday(&start_time, NULL);
    gettimeofday(&end_time, NULL);

    while (1) {
        sendto(sockfd, packet, PACKET_SIZE, 0, (struct sockaddr *)&target_addr, sizeof(target_addr));
        sent_packets++;
        transfer_bytes += PACKET_SIZE;
        usleep(1000000 / PACKET_RATE);

        gettimeofday(&end_time, NULL); // Update end_time within the loop

        if (end_time.tv_sec - start_time.tv_sec >= DURATION) {
            break;
        }
    }

    close(sockfd);

    // Calculate bandwidth
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    double bandwidth_Mbps = (transfer_bytes * 8) / (elapsed_time * 1024 * 1024);

    printf("Sent %d packets in %.2f seconds.\n", sent_packets, elapsed_time);
    printf("Transfer: %.2f bits\n", transfer_bytes);
    printf("Bandwidth: %.2f Mbps\n", bandwidth_Mbps);

    return 0;
}
