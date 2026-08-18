/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:44:44 by mdheen            #+#    #+#             */
/*   Updated: 2025/12/10 14:44:45 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void Harl::debug(void)
{
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
}

void Harl::info(void)
{
    std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}

void Harl::warning(void)
{
    std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years, whereas you started working here just last month." << std::endl;
}

void Harl::error(void)
{
    std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain(std::string level)
{
    if (level == "DEBUG")
        this->debug();
    else if (level == "INFO")
        this->info();
    else if (level == "WARNING")
        this->warning();
    else if (level == "ERROR")
        this->error();
    else
        std::cout << "Invalid complaint level." << std::endl;
}


Harl::Harl()
{
    std::cout << "Created Harl" << std::endl;
}

Harl::~Harl()
{
    std::cout << "Destroyed Harl" << std::endl;
}
