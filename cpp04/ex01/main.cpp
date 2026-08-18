/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:08:04 by mdheen            #+#    #+#             */
/*   Updated: 2026/01/04 16:08:05 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Brain.hpp"
int main()
{
    std::cout << "========== BASIC TEST ==========" << std::endl;

    const Animal* j = new Dog();
    const Animal* i = new Cat();

    delete j;
    delete i;

    std::cout << std::endl;
    std::cout << "========== ARRAY TEST ==========" << std::endl;

    const int size = 5;
    Animal* animals[size];

    for (int k = 0; k < size; k++)
    {
        if (k < size / 2)
            animals[k] = new Dog();
        else
            animals[k] = new Cat();
    }

    std::cout << std::endl;
    std::cout << "========== DELETE ARRAY ==========" << std::endl;

    for (int k = 0; k < size; k++) 
        delete animals[k];

    std::cout << std::endl;
    std::cout << "========== DEEP COPY TEST (DOG) ==========" << std::endl;

    Dog a;
    a.setIdea(0, "Idea A");

    Dog b(a);        // copy constructor
    Dog c;
    c = a;           // assignment operator

    b.setIdea(0, "Idea B");
    c.setIdea(0, "Idea C");

    std::cout << a.getIdea(0) << std::endl;
    std::cout << b.getIdea(0) << std::endl;
    std::cout << c.getIdea(0) << std::endl;

    std::cout << "========== DEEP COPY TEST (CAT) ==========" << std::endl;

    Cat x;
    x.setIdea(0, "Idea X");

    Cat y(x);
    Cat z;
    z = x;

    y.setIdea(0, "Idea Y");
    z.setIdea(0, "Idea Z");

    std::cout << x.getIdea(0) << std::endl;
    std::cout << y.getIdea(0) << std::endl;
    std::cout << z.getIdea(0) << std::endl;


    std::cout << std::endl;
    std::cout << "========== END ==========" << std::endl;

    return 0;
}
