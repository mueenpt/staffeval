/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 14:51:03 by mdheen            #+#    #+#             */
/*   Updated: 2025/12/31 14:51:04 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
    this->hitPoints = 100;
    this->energyPoints = 100;
    this->attackDamage = 30;

    std::cout << "FragTrap " << this->name << " constructed" << std::endl;
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap " << this->name << " destroyed" << std::endl;
}

void FragTrap::attack(std::string const & target)
{
    if (this->hitPoints <= 0)
    {
        std::cout << "FragTrap " << this->name << " is dead and cannot attack" << std::endl;
        return;
    }
    if (this->energyPoints <= 0)
    {
        std::cout << "FragTrap " << this->name << " has no energy to attack" << std::endl;
        return;
    }

    this->energyPoints--;
    std::cout << "FragTrap " << this->name << " attacks " << target << ", causing " << this-> attackDamage << " points of damage!" << std::endl;
}

void FragTrap::highFivesGuys(void)
{
    std::cout << "FragTrap " << name << " requests a positive high five ✋" << std::endl;
}
