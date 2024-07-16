#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>

#define LISTEN_PORT 12345  // Port to listen on
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in listen_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    int received_packets = 0;
    int received_bytes = 0;
    struct timeval start_time, end_time;
    double transfer_bytes = 0.0;

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    // Configure listening address
    memset(&listen_addr, 0, sizeof(listen_addr));
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_port = htons(LISTEN_PORT);
    listen_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the listening address
    if (bind(sockfd, (struct sockaddr *)&listen_addr, sizeof(listen_addr)) == -1) {
        perror("bind");
        close(sockfd);

        exit(1);
    }

    printf("Listening on port %d...\n", LISTEN_PORT);

    gettimeofday(&start_time, NULL);
    gettimeofday(&end_time, NULL);

    while (end_time.tv_sec < start_time.tv_sec + 30) {
        ssize_t received_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (received_len == -1) {
            perror("recvfrom");
            close(sockfd);
            exit(1);
        }

        received_packets++;
        received_bytes += received_len;
        transfer_bytes += received_len;

        // Convert the sender's IP address to a human-readable format
        char sender_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_addr.sin_addr), sender_ip, INET_ADDRSTRLEN);

        printf("Received packet from %s\n", sender_ip);
    }

    close(sockfd);

    // Calculate bandwidth
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    double bandwidth_Mbps = (transfer_bytes * 8) / (elapsed_time * 1024 * 1024);

    printf("Received %d packets in %.2f seconds.\n", received_packets, elapsed_time);
    printf("Transfer: %.2f bytes\n", transfer_bytes);
    printf("Bandwidth: %.2f Mbps\n", bandwidth_Mbps);

    return 0;
}
