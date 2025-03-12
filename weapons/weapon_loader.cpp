#include "weapon_loader.h"


// Convert a string to lowercase
std::string toLowerCase(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        c = std::tolower(c);  // Convert each character to lowercase
    }
    return result;
}

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

        weapons[toLowerCase(name)] = { name, damage, magic }; // Store weapon name in lowercase
    }

    return weapons;
}
