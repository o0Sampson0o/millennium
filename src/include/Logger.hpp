#pragma once

#include <iostream>
#include <string>

class Logger
{
public:
    static void info(const std::string &message);
    static void error(const std::string &message);
    static void warn(const std::string &message);
    static void debug(const std::string &message);
};