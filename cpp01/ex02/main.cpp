/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:41:09 by mdheen            #+#    #+#             */
/*   Updated: 2025/12/10 14:41:10 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main()
{
    std::string var = "HI THIS IS BRAIN";
    std::string* stringPTR = &var;
    std::string& stringREF = *stringPTR;

    std::cout << "address of string variable: " << &var << std::endl;
    std::cout << "address held by stringPTR: " << &stringPTR << std::endl;
    std::cout << "address held by stringREF: " << &stringREF << std::endl;
    std::cout << std::endl;
    std::cout << "value of the string variable: " << var << std::endl;
    std::cout << "value pointed to by stringPTR: " << stringPTR << std::endl;
    std::cout << "value pointed to by stringREF: " << stringREF << std::endl;


}