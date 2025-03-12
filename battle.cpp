#include "battle.h"

void printFightStats(const Entity* player, const Entity* mob) {
    std::cout << "Your character: " << player->getName() << " (Health: " 
              << player->getHealth() << ", Strength: " << player->getStrength() << ")\n";
    std::cout << "Mob: " << mob->getName() << " (Health: " 
              << mob->getHealth() << ", Strength: " << mob->getStrength() << ")\n";
}

void fight(Entity* player, Entity* mob) {
    int damageToMob = player->getStrength();
    int mobHealth = mob->getHealth();
    
    mobHealth -= damageToMob; // Mob takes damage
    mob->setHealth(mobHealth); // Update mob health using setter

    std::cout << mob->getName() << " takes " << damageToMob << " damage! Health left: " 
              << mob->getHealth() << "\n";
}

Entity* pickRandomMob(const std::vector<Entity*>& mobs) {
    srand(time(0)); // Seed random number generator
    int randomIndex = rand() % mobs.size();
    return mobs[randomIndex];
}
