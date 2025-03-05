#ifndef CHARACTER_LOADER_H
#define CHARACTER_LOADER_H



// Structure to store character data
struct Character {
    std::string name;
    std::string type;
    int health;
    int strength;
    int strengthMax;
    int defense;
    int defenseMax;
    Weapon weapon;
};

// Function declarations
Character loadCharacter(const std::string& filename, const std::unordered_map<std::string, Weapon>& weapons);

#endif // CHARACTER_LOADER_H
