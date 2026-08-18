/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:36:59 by mdheen            #+#    #+#             */
/*   Updated: 2025/12/10 14:37:00 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
    Zombie zombie1("SCREAMER");
    zombie1.announce();

    randomChump("SHADOW");

    Zombie* zombiePtr = newZombie("BOOMER");
    zombiePtr->announce();
    delete zombiePtr;

    return 0;
}
