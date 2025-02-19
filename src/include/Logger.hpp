#include <iostream>

class Logger
{
public:
    static void info(const char *message);
    static void error(const char *message);
    static void warn(const char *message);
    static void debug(const char *message);
};