#ifndef WEAPON_LOADER_H
#define WEAPON_LOADER_H


#include "../extra/includes.h"
// Structure to store weapon data
struct Weapon {
    std::string name;
    int damage;
    std::string magic;
};
std::unordered_map<std::string, Weapon> loadWeapons(const std::string& filename);
std::string toLowerCase(const std::string& str);
#endif