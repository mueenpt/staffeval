/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 11:05:38 by mdheen            #+#    #+#             */
/*   Updated: 2025/12/30 11:05:38 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(): fp_value(0) {}

Fixed::Fixed(const int input)
{
    fp_value = input << fract_bits;
}

Fixed::Fixed(const float input)
{
	this-> fp_value = roundf(input * (1 << this->fract_bits));
}
 
Fixed::Fixed(const Fixed& copy)
{
    this->fp_value = copy.fp_value;
}


Fixed& Fixed::operator=(const Fixed& other)
{
    if (this != &other)
        this->fp_value = other.fp_value;

    return *this;
}

        // Comparison Operators
bool Fixed::operator>(const Fixed& fixed) const
{
    return (this->fp_value > fixed.fp_value);
}

bool Fixed::operator<(const Fixed& fixed) const
{
    return (this->fp_value < fixed.fp_value);
}

bool Fixed::operator>=(const Fixed& fixed) const
{
    return (this->fp_value >= fixed.fp_value);
}

bool Fixed::operator<=(const Fixed& fixed) const
{
    return (this->fp_value <= fixed.fp_value);
}

bool Fixed::operator==(const Fixed& fixed) const
{
    return (this->fp_value == fixed.fp_value);
}

bool Fixed::operator!=(const Fixed& fixed) const
{
    return (this->fp_value != fixed.fp_value);
}

        // arithamatic calculation
Fixed Fixed::operator+(const Fixed& fixed) const
{
    Fixed result;
    result.setRawBits(fp_value + fixed.fp_value);
    return result;
}

Fixed Fixed::operator-(const Fixed& fixed) const
{
    Fixed result;
    result.setRawBits(fp_value - fixed.fp_value);
    return result;
}

Fixed Fixed::operator*(const Fixed& fixed) const
{
    Fixed result;
    result.setRawBits((fp_value * fixed.fp_value) >> fract_bits);
    return result;
}

Fixed Fixed::operator/(const Fixed& fixed) const
{
    Fixed result;
    result.setRawBits((fp_value << fract_bits) / fixed.fp_value);
    return result;
}

        // Pre-increment
Fixed& Fixed::operator++()
{
    this->fp_value++;   // + epsilon (1 / 256)
    return *this;
}

        // Pre-decrement
Fixed& Fixed::operator--()
{
    this->fp_value--;
    return *this;
}

        // Post-increment
Fixed Fixed::operator++(int)
{
    Fixed tmp(*this);    // save old value
    this->fp_value++;
    return tmp;
}

        // Post-decrement
Fixed Fixed::operator--(int)
{
    Fixed tmp(*this);
    this->fp_value--;
    return tmp;
}


Fixed::~Fixed()
{
}

float Fixed::toFloat( void ) const
{
    return static_cast<float>(fp_value) / (1 << fract_bits);
}

int Fixed::toInt( void ) const
{
    return fp_value >> fract_bits;
}

Fixed &Fixed::min(Fixed &first, Fixed &second)
{
    if (first.getRawBits() <= second.getRawBits())
        return first;
    return second;
}

const Fixed &Fixed::min(const Fixed &first, const Fixed &second)
{
    if (first.getRawBits() <= second.getRawBits())
        return first;
    return second;
}

Fixed &Fixed::max(Fixed &first, Fixed &second)
{
    if (first.getRawBits() >= second.getRawBits())
        return first;
    return second;
}

const Fixed &Fixed::max(const Fixed &first, const Fixed &second)
{
    if (first.getRawBits() >= second.getRawBits())
        return first;
    return second;
}

int	Fixed::getRawBits(void)const
{
    return (this->fp_value);
}

void	Fixed::setRawBits(int const raw)
{
    this->fp_value = raw;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed)
{
    os << fixed.toFloat();
    return os;
}
