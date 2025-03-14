#ifndef BATTLE_H
#define BATTLE_H

#include "../extra/includes.h"
#include "../entity/entity_loader.h"

// Function declarations
bool attackHits(int defenderDefense);
void printFightStats(const Entity* player, const Entity* mob);
void fight(Entity* player, Entity* mob);
Entity* pickRandomMob(const std::vector<Entity*>& mobs);
int calculateDamage(int attackerStrength, int defenderDefense, bool isCritical);

#endif // BATTLE_H
