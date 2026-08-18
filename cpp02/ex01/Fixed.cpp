/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 11:04:52 by mdheen            #+#    #+#             */
/*   Updated: 2025/12/30 11:04:53 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(): fp_value(0)
{
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int input) {
    std::cout << "Int constructor called" << std::endl;
    fp_value = input << fract_bits;
}

Fixed::Fixed(const float input)
{
	std::cout << "Float Constructor called" << std::endl;
	this-> fp_value = roundf(input * (1 << this->fract_bits));
}
 
Fixed::Fixed(const Fixed& copy)
{
    std::cout << "Copy constructor called" << std::endl;
    this->fp_value = copy.fp_value;
}


Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& other)
{
    std::cout << "Copy assignment operator called" << std::endl;

    if (this != &other)
        this->fp_value = other.fp_value;

    return *this;
}

float Fixed::toFloat( void ) const
{
    return static_cast<float>(fp_value) / (1 << fract_bits);
}

int Fixed::toInt( void ) const
{
    return fp_value >> fract_bits;
}

int	Fixed::getRawBits(void)const
{
    std::cout << "getRawBits member function called" << std::endl;
    return (this->fp_value);
}

void	Fixed::setRawBits(int const raw)
{
    std::cout << "setRawBits member function called" << std::endl;
    this->fp_value = raw;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed)
{
    os << fixed.toFloat();
    return os;
}
