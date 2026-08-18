/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 11:04:58 by mdheen            #+#    #+#             */
/*   Updated: 2025/12/30 11:04:59 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>
#include <iostream>
class Fixed
{
    private:
        int fp_value;
        static const int fract_bits = 8;

    public:
        Fixed();

        Fixed( const int input);
        Fixed(const float input);

        Fixed(const Fixed& copy);

        Fixed& operator=(const Fixed& other);

        ~Fixed();

        float toFloat( void ) const;
        int toInt( void ) const;

        int getRawBits(void)const;
        void setRawBits(int const raw);
};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif