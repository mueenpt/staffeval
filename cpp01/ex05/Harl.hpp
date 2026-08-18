/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:44:41 by mdheen            #+#    #+#             */
/*   Updated: 2025/12/10 14:44:42 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
#define HARL_HPP

#include <string>
#include <iostream>
class Harl
{
private:
    void debug();
    void info();
    void warning();
    void error();

public:
    Harl();
    ~Harl();
    void complain(std::string level); // public function to call complaints
};

#endif
