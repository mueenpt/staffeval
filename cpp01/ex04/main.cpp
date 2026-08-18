/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:43:30 by mdheen            #+#    #+#             */
/*   Updated: 2025/12/10 14:43:31 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header.hpp"

int main(int ac, char **av)
{
    if (ac != 4)
    {
        std::cerr << "invalid number of arguments" << std::endl;
        return 1;
    }
    

    std::string filename = av[1];
    std::string s1 = av[2];
    std::string s2 = av[3];

    if (s1.empty())
    {
        std::cerr << "s1 cannot be empty" << std::endl;
        return 1;
    }

    std::ifstream inFile(filename.c_str());
    if (!inFile)
    {
        std::cerr << "cannot open input file" << std::endl;
        return 1;
    }

    std::ofstream outFile((filename + ".replace").c_str());
    if (!outFile)
    {
        std::cerr << "cannot create output file" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inFile, line))
        outFile << replaceStr(line, s1, s2) << std::endl;

    return 0;
}