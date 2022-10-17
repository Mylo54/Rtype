#!/bin/bash


if [ $1 ];
then
	ln -s /usr/lib64/alsa-lib/ ~/.conan/data/libalsa/1.2.7.2/_/_/package/45572951e04977fe87dc4117ce69daf41aa9589c/lib/
	ln -s /usr/lib64/pkgconfig/ ~/.conan/data/libalsa/1.2.7.2/_/_/package/45572951e04977fe87dc4117ce69daf41aa9589c/lib/
fi

export ALSA_CONFIG_DIR=/usr/share/alsa
