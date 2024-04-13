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
#include <vector>
#include "socket.h"
#include "Email.h"

using namespace sdds;

int main() {
	std::string message = "";
	Server_TCP server("127.0.0.1", 28000);

	std::vector<Email> emails;
			
	emails.push_back(Email("JobsS", EmailDetails("Bill","Jobs","Finance Presentation","Looking forward to our meeting onfinance")));
	emails.push_back(Email("BillG", EmailDetails("Warren", "Bill", "Dinner", "It was lovely meeting you over dinner meeting")));
	emails.push_back(Email("WarrenB", EmailDetails("Elon", "Warren", "SpaceX", "Hows new SpaceX project going?")));
	emails.push_back(Email("JobsS", EmailDetails("Elon", "Jobs", "Twitter", "How is it going at Twitter?")));
		
	

	server.create_socket();
	server.bind_socket();
	
	while(true) {

		bool found = false;
		packet messagePacket;

		server.listen_for_connections();
		std::cout << "Waiting for Conenctions. " << std::endl;
		server.accept_connection();
		std::cout << "Connection accepted. " << std::endl;
		
		std::string message;
		std::string msgOnly, recvCheckSum;
		server.receive_message(message);
		
		msgOnly = message.substr(0, message.size() - 2);
		recvCheckSum = message.substr(message.size() - 2);

		std::cout << msgOnly << std::endl;
		std::cout << recvCheckSum << std::endl;

		unsigned char checkSum = 0;
		for(const char& chars : msgOnly) {
			checkSum += sum_bits(static_cast<int>(chars));
		}

		if(recvCheckSum == std::to_string(checkSum)) {
			
			std::cout << "Checksum matches \n";
			
			for(const auto& email : emails) {
				
				if(email.getUserName() == msgOnly) {

					messagePacket = create_packet(email);
					server.send_packet(messagePacket);
					found = true;
					break;
				}
			}

			if(!found) {
				messagePacket = create_packet("User not found\n");
				std::cerr << "User not found\n";
				server.send_packet(messagePacket);
			}
		
		} else {
			std::cerr << "[SERVER] Checksum failed\n";
			messagePacket = create_packet("Error, checksum does not match!");
			server.send_packet(messagePacket);
		}
	}

	return 0;
}
