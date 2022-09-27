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
    eng::SparseArray<std::string> arrA;

    arrA.insertAt(0, "Bonjour");
    arrA.insertAt(2, "Comment allez vous?");
    reg.registerComponents(arrA);
    std::cout << "registered component" << std::endl;
    auto fromReg = reg.getComponents<std::string>();
    for (int i = 0; i < 3; i++)
        std::cout << fromReg[i].value_or("empty") << std::endl;
    return (0);
}

int anyTest(void)
{
    eng::SparseArray<std::string> myArray;
    std::any myArrayAny = &myArray;

    myArray.insertAt(0, "Bonjour");
    myArray.insertAt(1, "Comment allez vous?");
    myArray.insertAt(2, {});
    myArray.insertAt(3, "Et vous?");
    myArray[0] = "hello";
    // This println should display "hello" and not "bonjour"
    return(0);
}

int main(void)
{
    registryTest();
    return 0;
}