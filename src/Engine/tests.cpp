/*
** EPITECH PROJECT, 2022
** Engine
** File description:
** tests
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

template<typename T>
int add(int a, int b)
{
    typeid(T);
    return (a + b);
}

template<typename T>
int sub(int a, int b)
{
    typeid(T);
    return (a - b);
}

class FunTest
{
    public:
        FunTest() {}
        ~FunTest() {}

        template<typename T>
        void addFunc() {
            _myFuncs.push_back([](int a, int b) -> int {
                if (typeid(int) == typeid(T))
                    std::cout << "this functions was templated with an int" << std::endl;
                return (a + b);
            });
        }

        void playsFuncs() {
            for (int i = 0; i < _myFuncs.size(); i++) {
                std::cout << i << " + 2 = " << _myFuncs[i](i, 2) << std::endl;
            }
        }
    private:
        std::vector<std::function<int(int, int)>> _myFuncs;
};

int functionsTest(void)
{
    std::vector<std::function<int (int, int)>> myFunctions;

    myFunctions.push_back(add<std::string>);
    myFunctions.push_back(sub<int>);

    std::cout << myFunctions.begin()->operator()(54, 54) << std::endl;
    return (0);
}

int registryTest(void)
{
    eng::Registry reg;
    eng::SparseArray<std::string> arrA;
    eng::SparseArray<int> arrB;
    int intA = 5;
    int intB = 666;

    arrA.insertAt(0, "Bonjour");
    arrA.insertAt(2, "Comment allez vous?");
    reg.registerComponents<std::string>(arrA);
    reg.registerComponents<int>(arrB);

    // weird
    reg.addComponent<std::string>(reg.entityFromIndex(1), "addComponent");
    reg.addComponent<int>(reg.entityFromIndex(1), 5);
    reg.addComponent<int>(reg.entityFromIndex(2), std::forward<int>(intB));
    for (int i = 0; i < reg.getComponents<std::string>().size(); i++) {
        std::cout << reg.getComponents<std::string>()[i].value_or("empty") << std::endl;
        std::cout << reg.getComponents<int>()[i].value_or(-1) << std::endl;
    }
    std::cout << "baba" << std::endl;
    reg.killEntity(eng::Entity(0));
    reg.killEntity(eng::Entity(2));
    for (int i = 0; i < reg.getComponents<std::string>().size(); i++) {
        std::cout << reg.getComponents<std::string>()[i].value_or("empty") << std::endl;
        std::cout << reg.getComponents<int>()[i].value_or(-1) << std::endl;
    }
    return (0);
}
