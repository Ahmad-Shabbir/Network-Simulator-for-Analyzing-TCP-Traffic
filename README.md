
# C-based Network Simulator for Analyzing TCP Traffic

## Introduction

This project involves the development of a simple C-based network simulator designed to analyze TCP traffic. The simulator listens to incoming packets at the Ethernet port, extracts headers and data from the incoming packets, and logs the traffic information. The project is implemented using C and TCP/IP-based libraries.

## Features

- **Packet Capture:** Listens to incoming packets at the Ethernet port.
- **Header and Data Extraction:** Extracts header and data from the incoming packets.
- **Traffic Analysis:** Logs the traffic information including the number of packets, transfer rate, and bandwidth.
- **Bandwidth Calculation:** Calculates and logs the bandwidth in Mbps.

## Prerequisites

- Linux-based operating system (Ubuntu recommended)
- GCC compiler
- Basic knowledge of TCP/IP protocols

## Usage

1. **Set Up Virtual Environment:**
   - It is recommended to use a virtual machine or an SDN hub for running this project. Tools like VirtualBox or VMware can be used to set up a virtual machine.
   - Alternatively, you can use Mininet to create a virtual network environment.

2. **Install Required Tools:**
   - Install GCC if not already installed:
     ```bash
     sudo apt-get update
     sudo apt-get install gcc
     ```

3. **Compile the Code:**
   - Navigate to the directory containing the source code and compile the receiver and sender programs:
     ```bash
     gcc -o receiver receiver.c
     gcc -o sender sender.c
     ```

4. **Run the Receiver:**
   - Start the receiver program on the machine that will act as the server (listening for incoming packets):
     ```bash
     ./receiver
     ```

5. **Run the Sender:**
   - Start the sender program on the machine that will act as the client (sending packets to the server):
     ```bash
     ./sender
     ```
 ## Additional Information

- **Duration:** The receiver will listen for incoming packets for 30 seconds.
- **Logging:** The traffic information, including the number of packets, transfer rate, and bandwidth, will be logged to `logfile.txt`.
- **Bandwidth Calculation:** The bandwidth is calculated in Mbps and logged for analysis.
  






