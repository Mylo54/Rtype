
# R-TYPE

<a href="https://img.shields.io/badge/MADE%20WITH-SFML-brightgreen" alt="SFML">
        <img src="https://img.shields.io/badge/MADE%20WITH-SFML-brightgreen" /></a>
<a href="https://img.shields.io/badge/MADE%20WITH-C%2B%2B-ff69b4" alt="C++">
        <img src="https://img.shields.io/badge/MADE%20WITH-C%2B%2B-ff69b4" /></a>
<a href="https://img.shields.io/badge/MADE%20WITH-CONAN-blueviolet" alt="Conan">
        <img src="https://img.shields.io/badge/MADE%20WITH-CONAN-blueviolet" /></a>
<a href="https://img.shields.io/badge/MADE%20WITH-CMAKE-red" alt="Cmake">
        <img src="https://img.shields.io/badge/MADE%20WITH-CMAKE-red" /></a>
<a href="https://codedocs.xyz/Mylo54/Rtype.svg" alt="Documentation">
        <img src="https://codedocs.xyz/Mylo54/Rtype.svg" /></a>

[![Linux compile](https://github.com/Mylo54/Rtype/actions/workflows/test_linux_compile.yml/badge.svg?branch=master)](https://github.com/Mylo54/Rtype/actions/workflows/test_linux_compile.yml)
[![Windows compile](https://github.com/Mylo54/Rtype/actions/workflows/test_windows_compile.yml/badge.svg?branch=master)](https://github.com/Mylo54/Rtype/actions/workflows/test_windows_compile.yml)
[![MacOS compile](https://github.com/Mylo54/Rtype/actions/workflows/test_macos_compile.yml/badge.svg?branch=master)](https://github.com/Mylo54/Rtype/actions/workflows/test_macos_compile.yml)
[![Mirroring](https://github.com/Mylo54/Rtype/actions/workflows/push_on_teck.yml/badge.svg?branch=master)](https://github.com/Mylo54/Rtype/actions/workflows/push_on_teck.yml)

A 3rd year Epitech Project.

This project aims to create an online multiplayer R-Type game. We had to implement a multi-threaded server using Asio and a graphical client in SFML.

For the one unfamliar with the R-TYPE genre, [here is a bit about it](http://www.hardcoregaming101.net/r-type/).

## Installation :

1. Install Conan

2. Compile on your os:

**Linux && MacOS :**

``` bash
$ ./comp_linux.sh
```

**Windows:**

``` bash
$ ./comp_windows.sh
```

### Binary Packagin

After having compiled on your OS, you can generate the binary package by executing :

``` bash
$ cmake --build build --target package
```

## Execution :

### Client

``` bash
$ ./build/bin/Server-Rtype
```

### Server

``` bash
$ ./build/bin/Client-Rtype
```

or

``` bash
$ sudo docker build . -t test_v2_dock && sudo docker run --rm -it test_v2_dock
```

## Known issues :

### Alsa-lib 

The audio libraries may have weird installs on some linux distros, if that's the case, then run these lines

``` bash
$ ln -s /usr/lib64/alsa-lib/ ~/.conan/data/libalsa/1.2.7.2/_/_/package/45572951e04977fe87dc4117ce69daf41aa9589c/lib/
$ ln -s /usr/lib64/pkgconfig/ ~/.conan/data/libalsa/1.2.7.2/_/_/package/45572951e04977fe87dc4117ce69daf41aa9589c/lib/
```

and then, every time you open a new terminal:

``` bash
$ export ALSA_CONFIG_DIR=/usr/share/alsa
```

OR, you can just run the `fix_audio.sh` script and add `-first` if its your first time executing it.

### Multiple clients on same system :

When running multiple clients at the same time, if you input something on one window and then unfocus it, it will keep repeating the input.

## Team :
The team is composed of :

* chloe.lere@epitech.eu 

* clovis.schneider@epitech.eu

* vivant.garrigues@epitech.eu

* mylo.jeandat@epitech.eu

* damien.demontis@epitech.eu
