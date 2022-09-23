/*
** EPITECH PROJECT, 2022
** src
** File description:
** main
*/

#include "SparseArray.hpp"
#include <iostream>
#include <optional>
#include <vector>


int sparseTest(void)
{
    eng::SparseArray<std::string> myArray;
    std::string a = "bonjour";

    myArray.insertAt(0, a);
    std::cout << "destr" << std::endl;
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
    myVector.erase(myVector.begin() + 1);
    for (auto it = myVector.begin(); it != myVector.end(); it++) {
        std::cout << "myVector: " << it->value_or("nothing") << std::endl;
    }
    return 0;
}

int main(void)
{
    sparseTest();
    return 0;
}