/*
** EPITECH PROJECT, 2022
** src
** File description:
** main
*/

#include "SparseArray.hpp"
#include "Registry.hpp"
#include <iostream>
#include <optional>
#include <vector>
#include <typeindex>


int sparseTest(void)
{
    eng::SparseArray<std::string> myArray;
    std::string a = "bonjour";

    myArray.insertAt(15, a);
    std::cout << myArray[14].value_or("coucou") << std::endl;
    return 0;
}

int optionnalVectorTest(void)
{
    std::vector<std::optional<std::string>> myVector;

    myVector.push_back("first");
    myVector.push_back({});
    myVector.push_back({});
    myVector.push_back("a value");
    myVector.push_back({});
    myVector.push_back({});
    myVector.push_back({});

    for (auto it = myVector.begin(); it != myVector.end(); it++) {
        std::cout << "myVector: " << it->value_or("nothing") << std::endl;
    }
    std::cout << "DEBUG" << std::endl;
    myVector.at(0).reset();
    for (auto it = myVector.begin(); it != myVector.end(); it++) {
        std::cout << "myVector: " << it->value_or("nothing") << std::endl;
    }
    return 0;
}

int registryTest(void)
{
    eng::Registry reg;
    eng::SparseArray<int> arrA;

    reg.registerComponents(arrA);
    return (0);
}

int anyTest(void)
{
    std::any myAny;
    int myInt = 5;

    myAny = myInt;
    if (typeid(myInt) == myAny.type())
        std::cout << "yes" << std::endl;
    return(0);
}

int main(void)
{
    anyTest();
    return 0;
}