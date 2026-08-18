/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:08:44 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/11 12:08:50 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact() {}

bool Contact::isEmpty() const {
	return firstName.empty();
}

static std::string format(const std::string &str) {
	if (str.length() > 10)
		return str.substr(0, 9) + ".";
	return str;
}

void Contact::setContact() {
    do {
        std::cout << "Enter First Name: ";
        std::getline(std::cin, firstName);
        if (firstName.empty())
            std::cout << "First Name cannot be empty!" << std::endl;
    } while (firstName.empty());

    do {
        std::cout << "Enter Last Name: ";
        std::getline(std::cin, lastName);
        if (lastName.empty())
            std::cout << "Last Name cannot be empty!" << std::endl;
    } while (lastName.empty());

    do {
        std::cout << "Enter Nickname: ";
        std::getline(std::cin, nickname);
        if (nickname.empty())
            std::cout << "Nickname cannot be empty!" << std::endl;
    } while (nickname.empty());

    do {
        std::cout << "Enter Phone Number: ";
        std::getline(std::cin, phoneNumber);
        if (phoneNumber.empty())
            std::cout << "Phone Number cannot be empty!" << std::endl;
    } while (phoneNumber.empty());

    do {
        std::cout << "Enter Darkest Secret: ";
        std::getline(std::cin, darkestSecret);
        if (darkestSecret.empty())
            std::cout << "Darkest Secret cannot be empty!" << std::endl;
    } while (darkestSecret.empty());

}


void Contact::displaySummary(int index) const {
	std::cout << std::setw(10) << index << "|"
			  << std::setw(10) << format(firstName) << "|"
			  << std::setw(10) << format(lastName) << "|"
			  << std::setw(10) << format(nickname) << std::endl;
}

void Contact::displayFull() const {
	std::cout << "First Name: " << firstName << std::endl;
	std::cout << "Last Name: " << lastName << std::endl;
	std::cout << "Nickname: " << nickname << std::endl;
	std::cout << "Phone Number: " << phoneNumber << std::endl;
	std::cout << "Darkest Secret: " << darkestSecret << std::endl;
}
