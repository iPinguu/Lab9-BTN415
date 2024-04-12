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
#include <string.h>
#include "Email.h"

using namespace sdds;

namespace sdds
{
	Email::Email() {
		Email::userName = "";
		Email::details;
	}

	Email::Email(std::string userName, EmailDetails details) {
		Email::userName = userName;
		Email::details = details;

	}

	std::string Email::getUserName() const {
		return userName;
	}

	std::string Email::display() const {
		return Email::details.body;
	}

	char* Email::returnDetails() const {
		
		// Serialize this ig, so it works? ¯\_(ツ)_/¯

		char* output;

		strcpy(output, details.from.c_str());
		strcpy(output, details.to.c_str());
		strcpy(output, details.subject.c_str());
		strcpy(output, details. body.c_str());

		std::cout << "in returnDetails() " << output;

		return output;
	}

	// -------------------------------------------------------------------- //

	EmailDetails::EmailDetails() {
		from = "";
		to = "";
		subject = "";
		body = "";
	}

	EmailDetails::EmailDetails(std::string from, std::string to, std::string subject, std::string body) {
		this->from = from;
		this->to = to;
		this->subject = subject;
		this->body = body;
	}

	EmailDetails::EmailDetails(const EmailDetails &src) {
		from = src.from;
		to = src.to;
		subject = src.subject;
		body = src.body;
	}
}




