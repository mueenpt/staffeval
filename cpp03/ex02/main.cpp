/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 14:51:09 by mdheen            #+#    #+#             */
/*   Updated: 2025/12/31 14:51:10 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int main()
{
    FragTrap a("Fighter");

    a.attack("Enemy");
    a.takeDamage(30);
    a.beRepaired(20);
    // std::cout << "Energy: " << a.getenergy() << std::endl;
    a.highFivesGuys();
    return 0;
}
