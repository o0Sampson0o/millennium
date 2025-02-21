#include "Logger.hpp"
#include <iostream>

// only active for debug builds, detect debug build by checking if NDEBUG is not defined
#ifndef NDEBUG
#define DEBUG
#endif

// ANSI color codes
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

void Logger::info(const std::string &message)
{
    std::cout << BLUE << "INFO: " << message.c_str() << RESET << std::endl;
}

void Logger::error(const std::string &message)
{
    std::cerr << RED << "ERROR: " << message.c_str() << RESET << std::endl;
}

void Logger::warn(const std::string &message)
{
    std::cout << YELLOW << "WARNING: " << message.c_str() << RESET << std::endl;
}

void Logger::debug(const std::string &message)
{
#ifdef DEBUG
    std::cout << GREEN << "DEBUG: " << message.c_str() << RESET << std::endl;
#endif
}