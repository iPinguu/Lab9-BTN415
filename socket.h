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


#ifndef SDDS_SOCKET_H
#define SDDS_SOCKET_H

#pragma once
#include <string>
#include <iostream>
#include <winsock2.h>

#define MAX_BUFFER_SIZE 512

namespace sdds {
	
	class Node {
	protected:
		static bool dlls_started;
		static int num_nodes;
		std::string ip;
		std::string role;
		std::string protocol;
		int port;
		SOCKET active_socket;
	public:
		Node();
		Node(std::string ip, int port);
		~Node();
		void start_dlls();
		bool create_socket();
		void display_info() const;
	};

	class Server_TCP : public Node {
	private:
		SOCKET client_socket;
	public:
		Server_TCP();
		Server_TCP(std::string ip, int port);
		~Server_TCP();
		bool bind_socket();
		bool listen_for_connections();
		bool accept_connection();
		int send_message(char* message);
		int receive_message(char* message);
		void close_connection();
	};

	class Client_TCP : public Node {	
	public:
		Client_TCP();
		bool connect_socket(std::string ip, int port);
		int send_message(char* message);
		int receive_message(char* message);
	};
}

#endif