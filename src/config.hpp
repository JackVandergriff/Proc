#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <fstream>
#include <string>

#include "utility.hpp"

using boost::property_tree::ptree;
using boost::property_tree::xml_parser::read_xml;
using boost::property_tree::xml_parser::write_xml;

class Config {
    private:
        ptree properties;
        string filename = ROOT_PATH + "etc/config.xml";
        void load() {
            read_xml(filename, properties);
            // printf(properties.get<string>("collision.item.rect.<xmlattr>.width", "0").c_str());
        }
        void save() {
            write_xml(filename, properties);
        }
    public:
        Config() {load();};
        virtual ~Config(){save();};
};