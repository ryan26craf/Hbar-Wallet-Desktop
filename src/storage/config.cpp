#include "storage/config.h"

Config& Config::getInstance() {
    static Config instance;
    return instance;
}

void Config::load() {}
void Config::save() {}
