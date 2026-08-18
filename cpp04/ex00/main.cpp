/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:06:49 by mdheen            #+#    #+#             */
/*   Updated: 2026/01/04 16:06:50 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
    std::cout << "========== CORRECT POLYMORPHISM ==========" << std::endl;

    const Animal* meta = new Animal();
    const Animal* dog  = new Dog();
    const Animal* cat  = new Cat();

    std::cout << "Type: " << meta->getType() << std::endl;
    std::cout << "Type: " << dog->getType() << std::endl;
    std::cout << "Type: " << cat->getType() << std::endl;

    meta->makeSound();
    dog->makeSound();
    cat->makeSound();

    delete meta;
    delete dog;
    delete cat;

    std::cout << "========== WRONG POLYMORPHISM ==========" << std::endl;


    const WrongAnimal* wrong = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();

    std::cout << "Type: " << wrong->getType() << std::endl;
    std::cout << "Type: " << wrongCat->getType() << std::endl;

    wrong->makeSound();
    wrongCat->makeSound();


    delete wrong;
    delete wrongCat;

    std::cout << "========== STACK OBJECT TEST ==========" << std::endl;


    Dog stackDog;
    Cat stackCat;

    stackDog.makeSound();
    stackCat.makeSound();

    return 0;
}
