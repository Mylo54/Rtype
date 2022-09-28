/*
** EPITECH PROJECT, 2022
** src
** File description:
** PlayerPrefs
*/

#include "PlayerPrefs.hpp"
#include <fstream>

eng::PlayerPrefs::PlayerPrefs()
{
}

eng::PlayerPrefs::~PlayerPrefs()
{
}

void eng::PlayerPrefs::loadPrefs()
{
    
}

void eng::PlayerPrefs::setPref(std::string key, std::string value)
{
    this->_strmap[key] = value;
}

void eng::PlayerPrefs::setPref(std::string key, int value)
{
    // this->_intmap[key] = value;
}

void eng::PlayerPrefs::setPref(std::string key, float value)
{
    // this->_floatmap[key] = value;
}

std::string eng::PlayerPrefs::getPref(std::string key)
{
    std::ifstream saveFile;

    saveFile.open("PlayerPreferences.txt");
    // get the string with the key associated
    return "";
}