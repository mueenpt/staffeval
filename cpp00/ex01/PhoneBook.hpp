/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:09:26 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/11 12:09:32 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
class PhoneBook
{
  private:
	Contact contacts[8];
	int total;
	int nextIndex;

  public:
	PhoneBook();
	void addContact();
	void searchContact() const;
};

#endif
