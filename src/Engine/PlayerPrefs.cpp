/*
** EPITECH PROJECT, 2022
** src
** File description:
** PlayerPrefs
*/

#include "PlayerPrefs.hpp"
#include <fstream>
#include <regex>
#include <cstdio>

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
        loadPref(str);
    }
    file.close();
}

bool eng::PlayerPrefs::prefLineMatch(const std::string str, std::string key)
{
    std::regex keyRgx(key + ".*");
    std::smatch match;

    if (std::regex_search(str.begin(), str.end(), match, keyRgx)) return true;
    return false;
} 

void eng::PlayerPrefs::savePref(std::string key, std::string value)
{
    std::ifstream filein(_path);
    std::ofstream fileout("tmp.txt");
    std::string str;

    if(!filein || !fileout) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }

    while(getline(filein, str))
    {
        if (prefLineMatch(str, key))
            str = key + "\t\t[" + value + "]";
        str += "\n";
        fileout << str;
    }
    filein.close();
    fileout.close();
    remove(_path.c_str());
    std::rename("tmp.txt", _path.c_str());
}

void eng::PlayerPrefs::setPref(std::string key, std::string value, bool saved)
{
    this->_strmap[key] = value;
    if (saved) savePref(key, value);
}

void eng::PlayerPrefs::setPref(std::string key, int value, bool saved)
{
    // this->_intmap[key] = value;
}

void eng::PlayerPrefs::setPref(std::string key, float value, bool saved)
{
    // this->_floatmap[key] = value;
}

std::string eng::PlayerPrefs::getPref(std::string key)
{
    if (_strmap.count(key) > 0)
        return _strmap[key];
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