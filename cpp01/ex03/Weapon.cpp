/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:03:08 by mdheen            #+#    #+#             */
/*   Updated: 2025/12/10 15:03:09 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string str)
{
    std::cout << "Weapon Created\n";
    type = str;
}

Weapon::~Weapon()
{
    std::cout << "Weapon Destroyed\n";
}
const std::string& Weapon::getType()
{
    return type;
}

void Weapon::setType(std::string newType)
{
    type = newType;
}