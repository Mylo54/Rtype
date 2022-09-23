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

void eng::PlayerPrefs::setString(std::string key, std::string value)
{
    this->_strmap[key] = value;
}

void eng::PlayerPrefs::setInt(std::string key, int value)
{
    this->_intmap[key] = value;
}

void eng::PlayerPrefs::setFloat(std::string key, float value)
{
    this->_floatmap[key] = value;
}

std::string eng::PlayerPrefs::getString(std::string key)
{
    std::ifstream saveFile;

    saveFile.open("PlayerPreferences.txt");
    // get the string with the key associated
    return "";
}

float eng::PlayerPrefs::getFloat(std::string key)
{
    // Same as getString
}

int eng::PlayerPrefs::getInt(std::string key)
{
    // Same as getString
}

bool eng::PlayerPrefs::save()
{
    std::ofstream saveFile;
    std::map<std::string, int>::iterator intIt;

    saveFile.open("PlayerPreferences.txt");
    saveFile << "[IntMap]" << std::endl;
    for (intIt = this->_intmap.begin(); intIt != this->_intmap.end(); intIt++) {
        saveFile << intIt->first << " = " << intIt->second << std::endl;
    }
}