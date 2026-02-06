#include "utils/logger.h"
#include <iostream>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::initialize(const std::string& filename) {}

void Logger::log(LogLevel level, const std::string& message) {
    std::cout << message << std::endl;
}
