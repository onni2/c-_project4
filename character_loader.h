#ifndef CHARACTER_LOADER_H
#define CHARACTER_LOADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string> 
#include "weapon_loader.h"  // Include weapon_loader.h to access the Weapon structure

// Structure to store character data
struct Character {
    std::string name;
    std::string type;
    int health;
    int strength;
    int strengthMax;
    int defense;
    int defenseMax;
    Weapon weapon;  // Weapon now recognized since we included weapon_loader.h
};

// Function declarations
std::vector<Character> loadCharacters(const std::string& filename, const std::unordered_map<std::string, Weapon>& weapons);
void printCharacter(const Character& character);

#endif // CHARACTER_LOADER_H
