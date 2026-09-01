#ifndef DOTS_H
#define DOTS_H

#include "Player.h"

typedef enum DotType
{
    // Points
    CCCiC_DOT_TYPE_TINY_POINT    = 0b10000000,                  // A tiny point Dot that contains 10 points
    CCCiC_DOT_TYPE_MED_POINT     = 0b10001000,                  // A medium point Dot that contains 25 points
    CCCiC_DOT_TYPE_BIG_POINT     = 0b10000100,                  // A big point Dot that contains 40 points
    CCCiC_DOT_TYPE_LARGE_POINT   = 0b10001100,                  // A large point Dot that contains 65 points
    CCCiC_DOT_TYPE_XLARGE_POINT  = 0b10000010,                  // An extra large Dot that contais 80 points
    CCCiC_DOT_TYPE_XXLARGE_POINT = 0b10001010,                  // A double extra large Dot that contains 125 points
    
    // Upgrades
    CCCiC_DOT_TYPE_DOUB_SPEED    = 0b01000000,                  // An upgrade Dot that contains a double speed, stackable (2 > 3 [max is 3])
    CCCiC_DOT_TYPE_DOUB_POINTS   = 0b01001000,                  // An upgrade Dot that contains a double point, stackable (2 > 3 > 4 > 5 > inc up to 10, which is max)
    CCCiC_DOT_TYPE_DOUB_DAMAGE   = 0b01000100,                  // An upgrade Dot that contains a double damage, stackable (2 > 3 > 4 > 5 > inc up to 15, which is max)
    CCCiC_DOT_TYPE_DOUB_DEFENSE  = 0b01001100,                  // An upgrade Dot that contains a double defense, stackable (2 > 3 > 4 > 5 > inc up to 15, which is max)
    CCCiC_DOT_TYPE_DOUB_HEALTH   = 0b01000010,                  // An upgrade Dot that contains a double health, stackable (2 > 3 > 4 > 5 > inc up to 35, which is max)
    CCCiC_DOT_TYPE_DOUB_DISCOUNT = 0b01001010,                  // An upgrade Dot that contains a shop discount, unstackable

    // Deprecated, they are standalone
    // Enemies
    // CCCiC_DOT_TYPE_ENEMY_CHASER     = 0b00100000,               // An enemy Dot that chases the player (-1 dmg, 5 hp)
    // CCCiC_DOT_TYPE_ENEMY_CHASFAST   = 0b00101000,               // An enemy Dot that chases the player fast (-5 dmg, 5 hp)
    // CCCiC_DOT_TYPE_ENEMY_SHORTRANGE = 0b00100100,               // An enemy Dot that has a short-ranged weapon that chases the player (-15 dmg, 10 hp)
    // CCCiC_DOT_TYPE_ENEMY_LONGRANGE  = 0b00101100,               // An enemy Dot that has a long-ranged weapong that chases the player (-20 dmg, 15 hp)
    // CCCiC_DOT_TYPE_ENEMY_SHOOTER_1  = 0b00100010,               // An enemy Dot that can shoot the player (-25 dmg, 25 hp)
    // CCCiC_DOT_TYPE_ENEMY_SHOOTER_2  = 0b00101010,               // An enemy Dot that can shoot the player, but smarter (-30 dmg, 30 hp)
    // CCCiC_DOT_TYPE_ENEMY_THIEVE_1   = 0b00100110,               // An enemy Dot that can steal points, and point Dots from you (-30 points, -3 dmg, 2 hp)
    // CCCiC_DOT_TYPE_ENEMY_THIEVE_2   = 0b00101110,               // An enemy Dot that can steal points, point Dots, and upgrade Dots (without benefit) from you, fast and smart (-65 points, -6 dmg, 4 hp)
    // CCCiC_DOT_TYPE_ENEMY_THIEVE_3   = 0b00100001,               // An enemy Dot that can steal points, point Dots, and upgrade Dots (with benefit) from you, fast and smart (-120 points, -12 dmg, 6 hp)
    
    // Bosses
    // CCCiC_DOT_TYPE_BOSS_CHASER_1    = 0b00010000,               // A boss Dot that chases the player. Attacks: can dash at the player, spawn enemies, has 10 hp
    // CCCiC_DOT_TYPE_BOSS_CHASER_2    = 0b00011000,               // A boss Dot that chases the player, faster. Attacks: can dash, spawn enemies, has 15 hp
    // CCCiC_DOT_TYPE_BOSS_SHORTRANGE  = 0b00010100,               // A boss Dot that has a short-range weapon that chases the player. Attacks: lung, dash, spawn enemies, has 30 hp
    // CCCiC_DOT_TYPE_BOSS_LONGRANGE   = 0b00011100,               // A boss Dot that has a long-range weapon that chases the player. Attacks: throw weapon, lung, dash, spawn enemies, has 40 hp
    // CCCiC_DOT_TYPE_BOSS_SHOOTER_1   = 0b00010010,               // A boss Dot that can shoot the player. Attacks: shoot, dash, spawn enemies, has 50 hp
    // CCCiC_DOT_TYPE_BOSS_SHOOTER_2   = 0b00011010,               // A boss Dot that can shoot the player. Attacks: doubled, throw primary weapon (blunt), dash and counter dash, spawn enemies, has 75 hp
    // CCCiC_DOT_TYPE_BOSS_THIEVE_1    = 0b00010110,               // A boss Dot that's the boss of thieves. Attacks: stealing, shoot revolver (once with cd), dash & steal, hide, spawn thieves, has 65 hp
    // CCCiC_DOT_TYPE_BOSS_THIEVE_2    = 0b00011110,               // A boss Dot that's the boss of the boss of thieves. Attacks: secret stealing, shoot revolver (twice with cd, smart), dash & steal, hide, spawn thieves, 70
    // CCCiC_DOT_TYPE_BOSS_THIEVE_3    = 0b00010001,               // A boss Dot that's the boss of all thieves. Attacks: hard lung, stun, bodyguarding, shoot strong weapons (twice with cd, smarter), throw hard objects at player (stun), dash away, hide, spawn the previous bosses, has 120 hp
    // CCCiC_DOT_TYPE_BOSS_STRONG_1    = 0b00011001,               // A boss Dot that's strong enough to crush you. Attacks: unknown and inevitable (still working on it), has 175 hp
} DotType;

typedef struct Dot
{
    Entity ent;                                                 // Dot entity
    uint16_t pointgain;                                         // How much points does the Dot have
    uint8_t type;                                               // Dot type
    // unsigned int hp;                                            // Dot health (for enemies and bosses)
    float duration;                                             // Dot duration (for upgrades)
    Color color;                                                // Dot color
    float radius;                                               // Dot radius
    const char* text;                                           // Dot text
    // Vector2 dfp;                                                // Distance From Player (Deprecated hence it was made for enemy AI)
} Dot;

typedef struct DotSpawnEntry
{
    uint8_t type;                                               // Dot Entry type
    int weight;                                                 // Dot Entry spawn weights. The higher, the commoner.
} DotSpawnEntry;

void InitDots(const Vector2 wind_size, Dot* dot, unsigned int amount);                                      // Initalize Dots
void GenDots(const Vector2 wind_Size, Dot* dot);                                                            // (Re)Generate Dots
void UpdateDotsBasedOnPlayer(const Vector2 wind_szie, Player* player, Dot* dot, unsigned int amount);       // Update Dots (Based on player ACTIONS and applying CONSIQUENCE)
void DrawDots(Dot* dot, unsigned int amount);                                                               // Drawing Dots (duh)
DotType SpawnFromTable(DotSpawnEntry* table, unsigned int size);                                            // RNG for generating Dot types

#endif
