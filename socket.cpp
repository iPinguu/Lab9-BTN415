// ****************************************************************************
//                        	Lab - #9
// Full Name: Franz Luiz Sy
// Student ID#: 116322223
// Email: fsy1@myseneca.ca
// Section: NBB
// Date Of Completion: 04/11/2024

// Authenticity Declaration:

// I declare that this submittion is the reslt of my own work and has not been
// shared to any other student or any 3rd party content distributer/provider.
// This submitted piece of work is entirely of my creation.

// ****************************************************************************


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "socket.h"
#include "Email.h"
#include <string>
#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#pragma comment(lib, "Ws2_32.lib")

using namespace sdds;

namespace sdds
{
    bool Node::dlls_started = false;
    int Node::num_nodes = 0;

    Node::Node() {
        start_dlls();
        num_nodes++;
        this->active_socket = INVALID_SOCKET;
        this->protocol = "tcp";
        this->ip = "127.0.0.1";
        this->port = 27000;
    }

    Node::Node(std::string ip, int port) {
        start_dlls();
        num_nodes++;
        this->active_socket = INVALID_SOCKET;
        this->ip = ip;
        this->port = port;
    }

    Node::~Node() {
        closesocket(this->active_socket);
        std::cout << "Closing socket" << std::endl;
        num_nodes--;
        if (num_nodes == 0) {
            WSACleanup();
        }
    }

    void Node::start_dlls() {
        if (!dlls_started) {
            WSADATA wsaData;
            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
                std::cout << "Could not start DLLs" << std::endl;
                exit(EXIT_FAILURE);
            }
            else {
                dlls_started = true;
            }
        }
    }

    bool Node::create_socket() {
        if (this->protocol == "tcp") {
            this->active_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        }
        else {
            this->active_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        }

        if (this->active_socket == INVALID_SOCKET) {
            std::cout << "Could not create socket" << std::endl;
            return false;
        }
        else {
            return true;
        }
    }

    void Node::display_info() const {
        std::cout << "IP: " << this->ip << std::endl;
        std::cout << "port: " << this->port << std::endl;
        std::cout << "protocol: " << this->protocol << std::endl;
        std::cout << "dlls: " << dlls_started << std::endl;
    }

    Server_TCP::Server_TCP() : Node() {
        this->role = "server";
        this->client_socket = INVALID_SOCKET;
    }

    Server_TCP::Server_TCP(std::string ip, int port) : Node(ip, port) {
        this->protocol = "tcp";
        this->role = "server";
        this->client_socket = INVALID_SOCKET;
    }

    Server_TCP::~Server_TCP() {
        closesocket(this->client_socket);
        std::cout << "Closing client socket" << std::endl;
    }

    bool Server_TCP::bind_socket() {
        struct sockaddr_in SvrAddr;
        SvrAddr.sin_family = AF_INET;
        SvrAddr.sin_addr.s_addr = inet_addr(this->ip.c_str());
        SvrAddr.sin_port = htons(this->port);
        if (bind(this->active_socket, (struct sockaddr*)&SvrAddr,
            sizeof(SvrAddr)) == SOCKET_ERROR) {
            std::cout << "Could not bind socket to address" << std::endl;
            return false;
        }
        else {
            return true;
        }
    }

    bool Server_TCP::listen_for_connections() {
        if (listen(this->active_socket, 1) == SOCKET_ERROR) {
            std::cout << "Could not start to listen" << std::endl;
            return false;
        }
        else {
            return true;
        }
    }

    bool Server_TCP::accept_connection() {
        this->client_socket = accept(this->active_socket, NULL, NULL);
        if (this->client_socket == INVALID_SOCKET) {
            std::cout << "Failed to accept connection" << std::endl;
            return false;
        }
        else {
            return true;
        }
    }

    int Server_TCP::send_message(std::string message) {
        return send(this->client_socket, message.c_str(), sizeof(message), 0);
    }

    int Server_TCP::send_packet(packet message) {
        struct serialized_packet serialized = packet_serializer(message);
        return send(this->client_socket, serialized.data, serialized.length, 0);
    }

    int Server_TCP::receive_message(std::string& message) {
        char RxBuffer[MAX_BUFFER_SIZE] = {};
        memset(RxBuffer, 0, MAX_BUFFER_SIZE);

        int num_bytes = recv(this->client_socket, RxBuffer, MAX_BUFFER_SIZE, 0);
        message = RxBuffer;
        return num_bytes;
    }

    int Server_TCP::receive_packet(packet& my_packet) {
        char RxBuffer[MAX_BUFFER_SIZE] = {};
        memset(RxBuffer, 0, MAX_BUFFER_SIZE);
        int num_bytes = recv(this->client_socket, RxBuffer, MAX_BUFFER_SIZE, 0);
        my_packet = packet_deserializer(RxBuffer);
        return num_bytes;
    }

    void Server_TCP::close_connection() {
        closesocket(this->client_socket);
    }

    Client_TCP::Client_TCP() : Node() {
        this->protocol = "tcp";
        this->role = "client";
    }

    bool Client_TCP::connect_socket(std::string ip, int port) {
        struct sockaddr_in SvrAddr;
        SvrAddr.sin_family = AF_INET;
        SvrAddr.sin_port = htons(port);
        SvrAddr.sin_addr.s_addr = inet_addr(ip.c_str());
        if ((connect(this->active_socket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
            std::cout << "Failed to connect to server" << std::endl;
            return false;
        }
        else {
            return true;
        }
    }

    int Client_TCP::send_message(std::string message) {        
        return send(this->active_socket, message.c_str(), sizeof(message), 0);
    }

    int Client_TCP::send_packet(packet message) {
        struct serialized_packet serialized = packet_serializer(message);
        return send(this->active_socket, serialized.data, serialized.length, 0);
    }

    int Client_TCP::receive_message(std::string& message) {
        char RxBuffer[MAX_BUFFER_SIZE] = {};
        memset(RxBuffer, 0, MAX_BUFFER_SIZE);
        int num_bytes = recv(this->active_socket, RxBuffer, MAX_BUFFER_SIZE, 0);
        message = RxBuffer;
        return num_bytes;
    }

    int Client_TCP::receive_packet(packet& my_packet) {
        char RxBuffer[MAX_BUFFER_SIZE] = {};
        memset(RxBuffer, 0, MAX_BUFFER_SIZE);
        int num_bytes = recv(this->active_socket, RxBuffer, MAX_BUFFER_SIZE, 0);
        my_packet = packet_deserializer(RxBuffer);
        return num_bytes;
    }

    unsigned char sum_bits(unsigned char bitregister) {
        unsigned char sum_bits = 0;
        for (int i = 0; i < 8; i++) {
            sum_bits += bitregister & 0x01;
            bitregister = bitregister >> 1;
        }
     
        return sum_bits;
    }
    
    void CRC(unsigned char input, unsigned char& state) {
        unsigned char feedback;
        feedback = ((state & 0x80) >> 7) ^ ((state & 0x20) >> 5) ^ input;
        state = (state << 1) + feedback;
    }


    packet create_packet(const Email& email){
		packet my_packet;

		strcpy(my_packet.name, email.getUserName().c_str());
        my_packet.size = 150; // magic number for debugging
		my_packet.letters = new char[my_packet.size];

		memset(my_packet.letters, 0, my_packet.size);
		snprintf(my_packet.letters, my_packet.size, email.returnDetails().c_str());

		return my_packet;
	}

    packet create_packet(std::string msg){
		packet my_packet;

		strcpy(my_packet.name, msg.c_str());
        my_packet.size = sizeof(msg);
		my_packet.letters = new char[my_packet.size];

		memset(my_packet.letters, 0, my_packet.size);
		snprintf(my_packet.letters, my_packet.size, msg.c_str());

		return my_packet;
	}
	
	struct serialized_packet packet_serializer(packet my_packet) {
		//beware of Windows completing groups of four bytes
		int letters_size = my_packet.size;
		char* serialized_packet = new char[1 * sizeof(int) + letters_size];
		char* auxptr = serialized_packet;

		memcpy(auxptr, &my_packet.size, 1 * sizeof(int));

		auxptr += 1 * sizeof(int);

		memcpy(auxptr, my_packet.letters, letters_size);
		struct serialized_packet output;

		output.data = serialized_packet;

		output.length = 1 * sizeof(int) + 1 * sizeof(int) + letters_size * sizeof(char);

		return output;
	}
	packet packet_deserializer(char* serialized_packet) {
		packet deserialized_packet;

		char* auxptr = serialized_packet;

		memcpy(&deserialized_packet.size, auxptr, 1 * sizeof(int));

		auxptr += 1 * sizeof(int);
		deserialized_packet.letters = new char[deserialized_packet.size];

		memcpy(deserialized_packet.letters, auxptr, deserialized_packet.size * sizeof(char));
		return deserialized_packet;
	}
}