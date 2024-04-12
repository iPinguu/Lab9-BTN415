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



#include <iostream>
#include <string>
#include "socket.h"
#include "Email.h"

using namespace sdds;

int main() {
	
	char username[] = {""};
	char response[] = "";
	
	Client_TCP client;
	client.create_socket();
	client.connect_socket("127.0.0.1", 28000);
	
	while(true) {
		
		std::cout << "[Client]: Enter username: ";
		std::cin >> username;

    std::cout << std::endl;
		
		client.send_message(username);
		client.receive_message(response);

		std::cout << "[Client] Your email contents: " << response << std::endl;

	}
	return 0;
}