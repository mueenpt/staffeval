/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replaceStr.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:43:39 by mdheen            #+#    #+#             */
/*   Updated: 2025/12/10 14:43:40 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header.hpp"

std::string replaceStr(const std::string &str, const std::string &s1, const std::string &s2)
{
    std::string result;
    size_t pos = 0;
    size_t found;

    while ((found = str.find(s1, pos)) != std::string::npos)
    {
        result.append(str, pos, found - pos);
        result.append(s2);
        pos = found + s1.length();            // move past s1
    }

    result.append(str, pos, str.length() - pos);
    return result;
}
