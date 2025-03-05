#ifndef WEAPON_LOADER_H
#define WEAPON_LOADER_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>

// Structure to store weapon data
struct Weapon {
    std::string name;
    int damage;
    std::string magic;
};
std::unordered_map<std::string, Weapon> loadWeapons(const std::string& filename);

#endif