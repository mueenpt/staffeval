/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 14:47:39 by mdheen            #+#    #+#             */
/*   Updated: 2025/12/31 14:47:40 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main()
{
    ClapTrap a("Fighter");

    a.attack("Enemy");
    a.takeDamage(3);
    a.beRepaired(5);
    // std::cout << "Energy: " << a.getenergy() << std::endl;

    return 0;
}
