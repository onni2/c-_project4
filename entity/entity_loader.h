#ifndef ENTITY_LOADER_H
#define ENTITY_LOADER_H

#include "../extra/includes.h"
#include "../weapons/weapon_loader.h"  // Include weapon_loader.h to access the Weapon structure

// Base class for all entities
class Entity {
public:
    virtual ~Entity() = default;

    // Getter functions
    std::string getName() const { return name; }
    std::string getType() const { return type; }
    int getHealth() const { return health; }
    int getStrength() const { return strength; }
    int getStrengthMax() const { return strengthMax; }
    int getDefense() const { return defense; }
    int getDefenseMax() const { return defenseMax; }
    Weapon getWeapon() const { return weapon; }

    // Setter functions
    void setHealth(int newHealth) { health = newHealth; }
    void setStrength(int newStrength) { strength = newStrength; }
    void setDefense(int newDefense) { defense = newDefense; }

    virtual void print() const = 0;

protected:
    std::string name;
    std::string type;
    int health, strength, strengthMax, defense, defenseMax;
    Weapon weapon;

    Entity(std::string name, std::string type, int health, int strength, int strengthMax, 
           int defense, int defenseMax, Weapon weapon)
        : name(std::move(name)), type(std::move(type)), health(health), strength(strength), 
          strengthMax(strengthMax), defense(defense), defenseMax(defenseMax), weapon(std::move(weapon)) {}
};

// Derived class for Character
// Derived class for Character
class Character : public Entity {
    public:
        // Constructor for Character
        Character(std::string name, int health, int strength, int strengthMax, int defense, 
                  int defenseMax, Weapon weapon)
            : Entity(std::move(name), "Character", health, strength, strengthMax, defense, defenseMax, weapon) {}
    
        // Implement the pure virtual print function
        void print() const override {
            std::cout << "\nCharacter Name: " << name << " (" << type << ")\n"
                      << "Health: " << health << "\n"
                      << "Strength: " << strength << "/" << strengthMax << "\n"
                      << "Defense: " << defense << "/" << defenseMax << "\n"
                      << "Weapon: " << weapon.name << " (Damage: " << weapon.damage 
                      << ", Magic: " << weapon.magic << ")\n"
                      << "----------------------------------------\n";
        }
    };
    
    // Derived class for Enemy
    class Enemy : public Entity {
    public:
        // Constructor for Enemy
        Enemy(std::string name, int health, int strength, int strengthMax, int defense, 
              int defenseMax, Weapon weapon)
            : Entity(std::move(name), "Enemy", health, strength, strengthMax, defense, defenseMax, weapon) {}
    
        // Implement the pure virtual print function
        void print() const override {
            std::cout << "\nEnemy Name: " << name << " (" << type << ")\n"
                      << "Health: " << health << "\n"
                      << "Strength: " << strength << "/" << strengthMax << "\n"
                      << "Defense: " << defense << "/" << defenseMax << "\n"
                      << "Weapon: " << weapon.name << " (Damage: " << weapon.damage 
                      << ", Magic: " << weapon.magic << ")\n"
                      << "----------------------------------------\n";
        }
    };
    
    // Derived class for Mob
    class Mob : public Entity {
    public:
        // Constructor for Mob
        Mob(std::string name, int health, int strength, int strengthMax, int defense, 
            int defenseMax, Weapon weapon)
            : Entity(std::move(name), "Mob", health, strength, strengthMax, defense, defenseMax, weapon) {}
    
        // Implement the pure virtual print function
        void print() const override {
            std::cout << "\nMob Name: " << name << " (" << type << ")\n"
                      << "Health: " << health << "\n"
                      << "Strength: " << strength << "/" << strengthMax << "\n"
                      << "Defense: " << defense << "/" << defenseMax << "\n"
                      << "Weapon: " << weapon.name << " (Damage: " << weapon.damage 
                      << ", Magic: " << weapon.magic << ")\n"
                      << "----------------------------------------\n";
        }
    };
    

// Function declarations
std::vector<Entity*> loadEntities(const std::string& filename, const std::unordered_map<std::string, Weapon>& weapons);
void printEntity(const Entity* entity);

#endif // ENTITY_LOADER_H
