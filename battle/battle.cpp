#include "battle.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

#define RESET_COLOR "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define LINE_BREAK "\n============================\n"

void printFightStats(const Entity* player, const Entity* mob) {
    std::cout << "Your character: " << player->getName()
              << " (Health: " << player->getHealth()
              << ", Strength: " << player->getStrength()
              << ", Defense: " << player->getDefense() << ")\n";
    std::cout << "Mob: " << mob->getName()
              << " (Health: " << mob->getHealth()
              << ", Strength: " << mob->getStrength()
              << ", Defense: " << mob->getDefense() << ")\n";
}

bool attackHits(int defenderDefense, bool& isCritical) {
    std::string input;
    int roll;
    std::cout << "Press 'r' to roll a d20: ";
    std::cin >> input;

    if (input == "r" || input.empty()) {
        roll = (rand() % 20) + 1;
        std::cout << "You rolled: " << roll << "\n";
    }

    if (roll == 20) {
        isCritical = true;
        return true;
    }

    isCritical = false;
    return roll > defenderDefense;
}

void playerTurn(Entity* player, Entity* mob) {
    std::cout << "Choose your action:\n";
    std::cout << "1. Attack\n";
    std::cout << "2. Heal\n";
    if (player->getWeapon().magic != "None") {
        std::cout << "3. Use " << player->getWeapon().magic << " magic attack\n";
    }

    int choice;
    std::cin >> choice;

    if (choice == 2) {
        int healAmount = rand() % 5 + 1;
        player->setHealth(player->getHealth() + healAmount);
        std::cout << BLUE << player->getName() << " heals for " << healAmount << " HP!" << RESET_COLOR << "\n";
    } 
    else if (choice == 3 && player->getWeapon().magic != "null") {
        std::string magicType = player->getWeapon().magic;
        int magicDamage = player->getStrength() + 5; // Magic does extra damage
        
        mob->setHealth(mob->getHealth() - magicDamage);
        std::cout << RED << player->getName() << " casts " << magicType 
                  << " magic attack! Deals " << magicDamage << " damage!" 
                  << RESET_COLOR << "\n";
    } 
    else {
        bool isCritical = false;
        if (attackHits(mob->getDefense(), isCritical)) {
            int damage = player->getStrength();
            if (isCritical) {
                damage *= 2;
                std::cout << RED << "CRITICAL HIT! DOUBLE DAMAGE!" << RESET_COLOR << "\n";
            }
            mob->setHealth(mob->getHealth() - damage);
            std::cout << GREEN << player->getName() << " hits " << mob->getName()
                      << " for " << damage << " damage! (" << mob->getHealth() << " HP left)" 
                      << RESET_COLOR << "\n";
        } else {
            std::cout << RED << player->getName() << " missed the attack!" << RESET_COLOR << "\n";
        }
    }
}


void mobTurn(Entity* mob, Entity* player) {
    int action = rand() % 3; // 0 = attack, 1 = heal, 2 = use weapon magic

    if (action == 1 && mob->getHealth() < 10) { 
        int healAmount = rand() % 5 + 1;
        mob->setHealth(mob->getHealth() + healAmount);
        std::cout << BLUE << mob->getName() << " heals for " << healAmount << " HP!" << RESET_COLOR << "\n";
    } 
    else if (action == 2 && mob->getWeapon().magic != "null") { 
        // Magic attack if weapon has an ability
        std::string magicType = mob->getWeapon().magic;
        int magicDamage = mob->getStrength() + 5; // Magic attacks are stronger
        
        player->setHealth(player->getHealth() - magicDamage);
        std::cout << RED << mob->getName() << " uses " << magicType 
                  << " magic attack! Deals " << magicDamage << " damage!" 
                  << RESET_COLOR << "\n";
    } 
    else {
        // Normal attack
        if ((rand() % 20) + 1 > player->getDefense()) {
            int damage = mob->getStrength();
            player->setHealth(player->getHealth() - damage);
            std::cout << GREEN << mob->getName() << " hits " << player->getName()
                      << " for " << damage << " damage! (" << player->getHealth() 
                      << " HP left)" << RESET_COLOR << "\n";
        } else {
            std::cout << RED << mob->getName() << " missed the attack!" << RESET_COLOR << "\n";
        }
    }
}



void fight(Entity* player, Entity* mob) {
    static int mobsDefeated = 0;  // Static variable to track defeated mobs

    std::cout << LINE_BREAK;
    std::cout << BLUE << "A fight begins between " << player->getName() << " and " << mob->getName() << "!" << RESET_COLOR << "\n";
    std::cout << LINE_BREAK;

    while (player->getHealth() > 0 && mob->getHealth() > 0) {
        std::cout << YELLOW << player->getName() << "'s turn!" << RESET_COLOR << "\n";
        playerTurn(player, mob);
        
        if (mob->getHealth() <= 0) {
            std::cout << GREEN << mob->getName() << " has been defeated!" << RESET_COLOR << "\n";
            mobsDefeated++;  // Increment defeated mob count
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        std::cout << LINE_BREAK;
        std::cout << BLUE << mob->getName() << "'s turn!" << RESET_COLOR << "\n";
        mobTurn(mob, player);

        if (player->getHealth() <= 0) {
            std::cout << RED << player->getName() << " has been defeated! Game over." << RESET_COLOR << "\n";
            break;
        }
        
        std::cout << LINE_BREAK;
        std::cout << "---- Next round ----\n";
        std::cout << LINE_BREAK;
    }
    if (mobsDefeated > 2) {
    Character* character = dynamic_cast<Character*>(player);
        if (character) {
            levelUp(character);  // Safely call levelUp if the cast was successful
        } else {
            std::cerr << "Error: Player is not a Character, cannot level up.\n";
        }
        mobsDefeated = 0;
    }
}


Entity* pickRandomMob(const std::vector<Entity*>& mobs) {
    srand(time(0));
    std::vector<Entity*> aliveMobs;
    Entity* orc = nullptr;
    Entity* dragon = nullptr;

    // Separate Orc and Dragon from other mobs and add other mobs to aliveMobs
    for (Entity* mob : mobs) {
        if (mob->getHealth() > 0) {
            if (mob->getName() == "Orc") {
                orc = mob;
            } else if (mob->getName() == "Dragon") {
                dragon = mob;
            } else {
                aliveMobs.push_back(mob);
            }
        }
    }
 
    // If there are alive mobs other than Orc and Dragon, pick one of them
    if (!aliveMobs.empty()) {
        int randomIndex = rand() % aliveMobs.size();
        return aliveMobs[randomIndex];
    }

    // If the Orc is alive and no other mobs are alive, pick the Orc
    if (orc != nullptr) {
        return orc;
    }

    // If the Dragon is alive and Orc is dead, pick the Dragon
    if (dragon != nullptr) {
        return dragon;
    }

    // If no mobs are alive
    std::cout << "All mobs are dead! No more enemies left.\n";
    return nullptr;
}

