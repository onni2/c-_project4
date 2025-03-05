#include "weapon_loader.h"

// Function to load weapons from CSV file
std::unordered_map<std::string, Weapon> loadWeapons(const std::string& filename) {
    std::unordered_map<std::string, Weapon> weapons;
    std::ifstream file(filename);
    std::string line;
    
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return weapons;
    }

    std::getline(file, line); // Skip header line

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, damageStr, magic;
        
        std::getline(ss, name, ',');
        std::getline(ss, damageStr, ',');
        std::getline(ss, magic, ',');

        int damage = std::stoi(damageStr);
        if (magic == "null") magic = "None";

        weapons[name] = { name, damage, magic };
    }

    return weapons;
}