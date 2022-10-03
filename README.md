
# R-TYPE

A 3rd year Epitech Project.

This project aims to create an online multiplayer R-Type game. We had to implement a multi-threaded server using Asio and a graphical client in SFML.

For the one unfamliar with the R-TYPE genre, [here is a bit about it](http://www.hardcoregaming101.net/r-type/).

## Installation :
First of all, you need to install Conan.

Then...

**Linux:**
```
mkdir build
cd build && conan install .. --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True && cmake .. -G "Unix Makefiles"  && cmake --build .
```
**Windows:**
```
mkdir build
cd build && conan install .. --build=missing && cmake .. -G "Visual Studio 17"  -A x64 && cmake --build .
```
**MacOS:**
```
mkdir build
cd build && conan install .. --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True && cmake .. -G "Unix Makefiles"  && cmake --build .
```

## Team :
The team is composed of :

* chloe.lere@epitech.eu 

* clovis.schneider@epitech.eu

* vivant.garrigues@epitech.eu

* mylo.jeandat@epitech.eu

* damien.demontis@epitech.eu