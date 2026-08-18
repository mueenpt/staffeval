/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 14:47:30 by mdheen            #+#    #+#             */
/*   Updated: 2025/12/31 14:47:31 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(std::string name)
{
    this->name = name;
    this->hitPoints = 10;
    this->energyPoints = 10;
    this->attackDamage = 0;

    std::cout << "ClapTrap " << this->name << " constructed" << std::endl;
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap " << this->name << " destroyed" << std::endl;
}

void ClapTrap::attack(std::string const & target)
{
    if (this->hitPoints <= 0)
    {
        std::cout << "ClapTrap " << this->name << " is dead and cannot attack" << std::endl;
        return;
    }
    if (this->energyPoints <= 0)
    {
        std::cout << "ClapTrap " << this->name << " has no energy to attack" << std::endl;
        return;
    }

    this->energyPoints--;
    std::cout << "ClapTrap " << this->name << " attacks " << target << ", causing " << this->attackDamage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (this->hitPoints <= 0)
    {
        std::cout << "ClapTrap " << this->name << " is already dead" << std::endl;
        return;
    }

    this->hitPoints -= amount;
    if (this->hitPoints < 0)
        this->hitPoints = 0;

    std::cout << "ClapTrap " << this->name << " takes " << amount << " points of damage!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->hitPoints <= 0)
    {
        std::cout << "ClapTrap " << this->name << " is dead and cannot be repaired" << std::endl;
        return;
    }
    if (this->energyPoints <= 0)
    {
        std::cout << "ClapTrap " << this->name << " has no energy to repair" << std::endl;
        return;
    }

    this->energyPoints--;
    this->hitPoints += amount;

    std::cout << "ClapTrap " << this->name << " repairs itself for " << amount << " hit points!" << std::endl;
}

// int ClapTrap::getenergy() const{
//     return energyPoints;
// }