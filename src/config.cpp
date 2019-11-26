#include "config.hpp"

Config::Config() {
    load();
    std::cout << getProperty<int>("Sprites[1].name") << "\n";
}

Config::~Config() {
    save();
}

template <class T> T Config::getProperty(string path) {
    YAML::Node current = properties;
    for (auto sector : Utility::split_str(path, '.')) {
        if (sector.find('[') != string::npos) {
            auto subs = Utility::split_str(sector, '[');
            current = current[subs[0]][std::stoi(subs[1].substr(0, subs[1].size()-1))];
        } else {
            current = current[sector];
        }
    }
    return current.as<T>();
}

void Config::load() {
    properties = YAML::LoadFile(filename);
}

void Config::save() {
    // Do nothing for now, assuming changes not being made
}