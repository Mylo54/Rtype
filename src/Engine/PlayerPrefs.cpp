/*
** EPITECH PROJECT, 2022
** src
** File description:
** PlayerPrefs
*/

#include "PlayerPrefs.hpp"
#include <fstream>
#include <regex>

eng::PlayerPrefs::PlayerPrefs()
{
}

eng::PlayerPrefs::~PlayerPrefs()
{
}

void eng::PlayerPrefs::loadPref(const std::string str)
{
    std::regex keyRgx("(\\w+) .*");
    std::regex valueRgx(".*\\[(\\w+)\\].*");
    std::smatch match;
    std::string key = "";
    std::string value = "";

    if (std::regex_search(str.begin(), str.end(), match, keyRgx))
        key = match[1];
    if (std::regex_search(str.begin(), str.end(), match, valueRgx))
        value = match[1];

    _strmap.insert(std::pair<std::string, std::string>(key, value));
}

void eng::PlayerPrefs::loadPrefs()
{
    std::ifstream file;
    std::string str;

    file.open(_path);
    while (std::getline(file, str)) {
        // std::cout << str << std::endl;
        loadPref(str);
    }
    file.close();
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
    if (_strmap.count(key) > 0)
        return _strmap[key];
        // return "azs";
    return "Key not found";
}

void eng::PlayerPrefs::setPath(std::string path)
{
    _path = path;
}

std::string eng::PlayerPrefs::getPath()
{
    return _path;
}