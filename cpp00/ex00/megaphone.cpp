/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:08:25 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/11 12:08:26 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

char	*str_upper(char *str)
{
	for (int i = 0; str[i]; i++)
		str[i] = std::toupper(str[i]);
	return (str);
}

void	megaphone(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
		std::cout << str_upper(argv[i]);
	std::cout << std::endl;
}

int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		megaphone(argc, argv);
		return (0);
	}
	std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	return (0);
}
