/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 14:51:14 by mdheen            #+#    #+#             */
/*   Updated: 2025/12/31 14:51:15 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
    this->hitPoints = 100;
    this->energyPoints = 50;
    this->attackDamage = 20;

    std::cout << "ScavTrap " << this->name << " constructed" << std::endl;
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap " << this->name << " destroyed" << std::endl;
}

void ScavTrap::attack(std::string const & target)
{
    if (this->hitPoints <= 0)
    {
        std::cout << "ScavTrap " << this->name << " is dead and cannot attack" << std::endl;
        return;
    }
    if (this->energyPoints <= 0)
    {
        std::cout << "ScavTrap " << this->name << " has no energy to attack" << std::endl;
        return;
    }

    this->energyPoints--;
    std::cout << "ScavTrap " << this->name << " attacks " << target << ", causing " << this-> attackDamage << " points of damage!" << std::endl;
}

void ScavTrap::guardGate()
{
    std::cout << "ScavTrap " << this->name << " has entered Gate keeper mode!" << std::endl;
}
