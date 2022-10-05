/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** Log
*/

#include "Log.hpp"
#include <iostream>
#include <fstream>

eng::Log::Log()
{
}

eng::Log::~Log()
{
}

std::string eng::Log::createPath()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::string path = std::to_string(ltm->tm_mday) + "-" +
    std::to_string(1 + ltm->tm_mon) + "-" + std::to_string(1900 + ltm->tm_year)
    + "_" + std::to_string(5 + ltm->tm_hour) + "h"
    + std::to_string(ltm->tm_min) + "m" + std::to_string(ltm->tm_sec)
    + "s.log";
    
    std::ofstream out(path.c_str());
    out << "Log from this run:\n";
    out.close();
    return path;
}

void eng::Log::setPath(std::string path)
{
    _path = path;
}

std::string eng::Log::getPath()
{
    return _path;
}

void eng::Log::enable()
{
    _debugMode = true;
}

void eng::Log::disable()
{
    _debugMode = false;
}

bool eng::Log::isEnabled()
{
    return _debugMode;
}

void eng::Log::log(std::string msg)
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::string str;
    std::ifstream filein(_path.c_str());
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
    remove(_path.c_str());
    std::rename("tmp.txt", _path.c_str());
    filein.close();
    fileout.close();
}