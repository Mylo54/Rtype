/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-clovis.schneider
** File description:
** Registry
*/

#include "Registry.hpp"

extern std::string logPath;

eng::Registry::Registry()
{
}

eng::Registry::~Registry()
{
}

void eng::Registry::setDebugMode(bool isEnable)
{
    _debugMode = isEnable;
}

bool eng::Registry::getDebugMode()
{
    return _debugMode;
}

void eng::Registry::log(std::string msg)
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::string str;
    std::ifstream filein(logPath.c_str());
    std::ofstream fileout("tmp.txt");

    if(!filein || !fileout) return;
    while(getline(filein, str)) fileout << str << std::endl;
    fileout << ltm->tm_mday << "/";
    fileout << 1 + ltm->tm_mon << "/";
    fileout << 1900 + ltm->tm_year << " | " ;
    fileout<< ltm->tm_hour << ":";
    fileout << ltm->tm_min << ":";
    fileout << ltm->tm_sec << " | " ;
    fileout << msg << std::endl;
    remove(logPath.c_str());
    std::rename("tmp.txt", logPath.c_str());
    filein.close();
    fileout.close();
}

void eng::Registry::setName(std::string name)
{
    _name = name;
}

std::string eng::Registry::getName()
{
    return _name;
}