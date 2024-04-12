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


#ifndef SDDS_EMAIL_H
#define SDDS_EMAIL_H

#pragma once

#include <iostream>
#include <string>

namespace sdds {
	
	struct EmailDetails
	{
		std::string from;
		std::string to;
		std::string subject;
		std::string body;

	public:
		EmailDetails();
		EmailDetails(std::string from, std::string to, std::string subject, std::string body);
		EmailDetails(const EmailDetails &src);
	};
	
	class Email
	{
	private:
		std::string userName;
		struct EmailDetails details;
	public:
		Email();
		Email(std::string userName, EmailDetails details);
		std::string getUserName() const;
		std::string display() const;
		char* returnDetails() const;

	};
}

#endif