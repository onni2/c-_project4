#include "battle.h"
// For color output (for supported terminals)
#define RESET_COLOR "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

// For line break and formatting
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

    // Prompt the player for input
    std::cout << "Press 'r' to roll a d20: ";
    std::cin >> input;

    // If the player pressed 'r' or just pressed Enter (empty input)
    if (input == "r" || input.empty()) {
        roll = (rand() % 20) + 1; // Roll a d20 (1-20)
        std::cout << "You rolled: " << roll << "\n";
    }

    if (roll == 20) { 
        isCritical = true;
        return true; // Always hits
    }

    isCritical = false;
    return roll > defenderDefense; // Normal hit check
}


void fight(Entity* player, Entity* mob) {
    std::cout << LINE_BREAK;
    std::cout << BLUE << "A fight begins between " << player->getName() << " and " << mob->getName() << "!" << RESET_COLOR << "\n";
    std::cout << LINE_BREAK;

    while (player->getHealth() > 0 && mob->getHealth() > 0) {
        // Player's turn
        std::cout << YELLOW << player->getName() << "'s turn!" << RESET_COLOR << "\n";
        
        bool isCritical = false;
        if (attackHits(mob->getDefense(), isCritical)) {
            int damageToMob = player->getStrength();
            if (isCritical) {
                damageToMob *= 2;
                std::cout << RED << "CRITICAL HIT! DOUBLE DAMAGE!" << RESET_COLOR << "\n";
            }
            mob->setHealth(mob->getHealth() - damageToMob);
            std::cout << GREEN << player->getName() << " hits " << mob->getName() 
                      << " for " << damageToMob << " damage! (" 
                      << mob->getHealth() << " HP left)" << RESET_COLOR << "\n";
        } else {
            std::cout << RED << player->getName() << " missed the attack!" << RESET_COLOR << "\n";
        }

        // Check if mob is dead
        if (mob->getHealth() <= 0) {
            std::cout << GREEN << mob->getName() << " has been defeated!" << RESET_COLOR << "\n";
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));  // Delay for 2 seconds

        // Mob's turn
        std::cout << LINE_BREAK;
        std::cout << BLUE << mob->getName() << "'s turn!" << RESET_COLOR << "\n";
        
        if ((rand() % 20) + 1 > player->getDefense()) {
            int damageToPlayer = mob->getStrength();
            player->setHealth(player->getHealth() - damageToPlayer);
            std::cout << GREEN << mob->getName() << " hits " << player->getName() 
                      << " for " << damageToPlayer << " damage! (" 
                      << player->getHealth() << " HP left)" << RESET_COLOR << "\n";
        } else {
            std::cout << RED << mob->getName() << " missed the attack!" << RESET_COLOR << "\n";
        }

        if (player->getHealth() <= 0) {
            std::cout << RED << player->getName() << " has been defeated! Game over." << RESET_COLOR << "\n";
            break;
        }

        std::cout << LINE_BREAK;
        std::cout << "---- Next round ----\n";
        std::cout << LINE_BREAK;
    }
}

Entity* pickRandomMob(const std::vector<Entity*>& mobs) {
    srand(time(0)); // Seed random number generator

    std::vector<Entity*> aliveMobs;

    // Filter only mobs that are still alive
    for (Entity* mob : mobs) {
        if (mob->getHealth() > 0) {
            aliveMobs.push_back(mob);
        }
    }

    if (aliveMobs.empty()) {
        std::cout << "All mobs are dead! No more enemies left.\n";
        return nullptr;
    }

    int randomIndex = rand() % aliveMobs.size();
    return aliveMobs[randomIndex];
}

