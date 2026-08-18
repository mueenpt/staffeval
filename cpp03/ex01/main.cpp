/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 14:50:47 by mdheen            #+#    #+#             */
/*   Updated: 2025/12/31 14:50:48 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int main()
{
    ScavTrap a("Fighter");

    a.attack("Enemy");
    a.takeDamage(30);
    a.beRepaired(20);
    // std::cout << "Energy: " << a.getenergy() << std::endl;
    
    return 0;
}
