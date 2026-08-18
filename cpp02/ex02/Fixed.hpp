/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 11:05:44 by mdheen            #+#    #+#             */
/*   Updated: 2025/12/30 11:05:44 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
private:
    int fp_value;
    static const int fract_bits = 8;

public:
    // Constructors / Destructor
    Fixed();
    Fixed(const int input);
    Fixed(const float input);
    Fixed(const Fixed& copy);
    ~Fixed();

    // Assignment
    Fixed& operator=(const Fixed& other);

    // Comparison operators
    bool operator>(const Fixed& fixed) const;
    bool operator<(const Fixed& fixed) const;
    bool operator>=(const Fixed& fixed) const;
    bool operator<=(const Fixed& fixed) const;
    bool operator==(const Fixed& fixed) const;
    bool operator!=(const Fixed& fixed) const;

    // Arithmetic operators
    Fixed operator+(const Fixed& fixed) const;
    Fixed operator-(const Fixed& fixed) const;
    Fixed operator*(const Fixed& fixed) const;
    Fixed operator/(const Fixed& fixed) const;

    // Increment / Decrement
    Fixed& operator++();     // pre
    Fixed& operator--();
    Fixed operator++(int);   // post
    Fixed operator--(int);

    // Conversion
    float toFloat(void) const;
    int toInt(void) const;

    // Raw bits
    int getRawBits(void) const;
    void setRawBits(int const raw);

    // Min / Max
    static Fixed& min(Fixed& a, Fixed& b);
    static const Fixed& min(const Fixed& a, const Fixed& b);
    static Fixed& max(Fixed& a, Fixed& b);
    static const Fixed& max(const Fixed& a, const Fixed& b);
};

// Stream operator
std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif
