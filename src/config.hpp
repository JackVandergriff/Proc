#pragma once

#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include <string>

#include "utility.hpp"

class Config {
    private:
        YAML::Node properties;
        string filename = ROOT_PATH + "etc/config.yaml";
        void load();
        void save();
    public:
        Config();
        virtual ~Config();
        template<class T> T getProperty(string);
};