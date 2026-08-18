/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:09:18 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/11 12:09:19 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

#include <iostream>
#include <limits>
#include <iomanip>

PhoneBook::PhoneBook() : total(0), nextIndex(0) {}

void PhoneBook::addContact() {
	Contact newContact;
	newContact.setContact();

	contacts[nextIndex] = newContact;
	nextIndex = (nextIndex + 1) % 8;
	if (total < 8)
		total++;
	std::cout << "Contact added successfully!" << std::endl;
}

void PhoneBook::searchContact() const {
	if (total == 0) {
		std::cout << "No contacts available." << std::endl;
		return;
	}

	std::cout << std::setw(10) << "Index" << "|"
			  << std::setw(10) << "First Name" << "|"
			  << std::setw(10) << "Last Name" << "|"
			  << std::setw(10) << "Nickname" << std::endl;

	for (int i = 0; i < total; ++i)
		contacts[i].displaySummary(i);

	std::cout << "Enter index to view details: ";
	int index;
	if (!(std::cin >> index) || index < 0 || index >= total) {
		std::cout << "Invalid index!" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	contacts[index].displayFull();
}
