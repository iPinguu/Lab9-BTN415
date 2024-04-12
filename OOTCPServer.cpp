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

		server.listen_for_connections();
		std::cout << "Waiting for Conenctions. " << std::endl;
		server.accept_connection();
		std::cout << "Connection accepted. " << std::endl;
		
		char* theUser;
		std::string stringUser = {theUser};
		server.receive_message(theUser);
		
		std::cout << "Before the For loop: \n";
		
		for(const auto& email : emails) {
			
			std::cout << "Inside the For loop looking for: \n" << stringUser << std::endl;
			
			if(email.getUserName() == stringUser) {
				
				std::cout << "Found match: \n";
				char* result = email.returnDetails();

				std::cout << result;
				
				// server.send_message(email.returnDetails());		
				

				
				break;
			}
		}
		
		// std::cout << "Message Received: " << message << std::endl;
		// server.send_message("Got your message!");
	}


	return 0;
}
