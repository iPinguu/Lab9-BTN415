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

	std::string Email::returnDetails() const {
		
		std::string output;

		output += "To: " + this->details.to + "\n" += "From: " + this->details.from + "\n" += "Subject: " + this->details.subject + "\n" += "Body: " + this->details.body + "\n";

		return output;
	}

	EmailDetails Email::getDetails() const {
		return details;
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

	EmailDetails EmailDetails::operator=(const EmailDetails& src) {
		if(this != &src) {
			this->to = src.to;
			this->from = src.from;
			this->subject = src.subject;
			this->body = src.body;
		}

		return *this;
	}
}




