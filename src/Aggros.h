#ifndef AGGROS_H
#define AGGROS_H

#include "Player.h"

typedef enum EnmType
{
    // Enemies
    CCCiC_ENEMY_CHASER_1    = 0b00000000,                       // An enemy that chases the player. Slow, has 4 HP and deals 2 dmg
    CCCiC_ENEMY_CHASER_2    = 0b00000001,                       // An enemy that chases the player. Fast, has 8 HP and deals 5 dmg
    CCCiC_ENEMY_SHORT_RANGE = 0b00000010,                       // An enemy that attacks the player with a short melee. Short range, has 8 HP and deals 6 dmg
    CCCiC_ENEMY_LONG_RANGE  = 0b00000011,                       // An enemy that attacks the player with a long melee. Long range, has 14 HP and deals 12 dmg
    CCCiC_ENEMY_SHOOTER_1   = 0b00000100,                       // An enemy that shoots the player. Slow firerate, has 15 HP and deals 5 dmg/bullet
    CCCiC_ENEMY_SHOOTER_2   = 0b00000101,                       // An enemy that shoots the player. Fast firerate, has 20 HP and deals 8 dmg/bullet
    CCCiC_ENEMY_SHOOTER_3   = 0b00000110,                       // An enemy that shoots the player. Faster firerate, has 26 HP and deals 11 dmg/bullet
    CCCiC_ENEMY_THIEVE_1    = 0b00000111,                       // An enemy that steals the most valuable point dots from the player. Slow, has 6 HP and each shot/attack makes them drop points
    CCCiC_ENEMY_THIEVE_2    = 0b00001000,                       // An enemy that steals the most valuable dots from the player. Fast, has 8 HP and each shot/attack makes them drop dots
    CCCiC_ENEMY_THIEVE_3    = 0b00001001,                       // An enemy that steals the most valuable dots from the player and benefits from them. Fast, has 12 HP and won't drop anything

    // Bosses
} EnmType;

typedef struct AggroEnt
{
    Entity ent;                                                 // Enemy Entity
    float radius;                                               // Enemy radius
    float rotation;                                             // Enemy weapon rotation
    float speed;                                                // Enemy speed
    unsigned int health;                                        // Enemy health
    unsigned int maxhealth;                                     // Enemy max health
    Color color;                                                // Enemy color
    uint8_t type;                                               // Enemy type
    bool brainless;                                             // Enemy AI activation. If it's true (1), it's off
} AggroEnt;

// Functions
void InitEnemy(AggroEnt* enm, const Vector2 wind_size, unsigned int amount);                                            // Initialize enemy
void UpdateEnemy(AggroEnt* enm, const Player* player, Dot* dots, const Vector2 wind_size, const float dt, unsigned int amount); // Updates enemy
void DrawEnemy(AggroEnt* enm, unsigned int amount);                                                                     // Draws enemy

#endif
