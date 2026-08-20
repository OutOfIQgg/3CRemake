#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <stdint.h>
#include <raymath.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "State.h"

typedef struct Entity {
    Vector2 pos;                                                // Entity position
    Vector2 vel;                                                // Entity velocity
} Entity;

typedef struct Player {
    // Attributes
    Entity ent;                                                 // Player entity
    float radius;                                               // Player radius (hence you're a circle, silly. And because we also need it for math)
    float rotation;                                             // Player rotation (for shooting)
    float speed;                                                // Player speed
    uint64_t points;                                            // Player points
    int controls[5];                                            // Player controls
    // controls[0] = up
    // controls[1] = left
    // controls[2] = down
    // controls[3] = right
    // controls[4] = shoot
    Color color;                                                // Player color
    uint16_t health;                                            // Player health

    // Upgrades
    int spdbst;                                                 // Speed Boost,     maximum is 5
    int pntbst;                                                 // Point Boost,     maximum is 10
    int dmgbst;                                                 // Damage Boost,    maximum is 15
    int dfnsbst;                                                // Defense Boost,   maximum is 15
    int hpboost;                                                // Double health,   maximum is 35
    bool discount;                                              // Store discount,  unstackable
    float uduration[6];                                         // Upgrade durations (the duration rotation is respective to the list above)
} Player;

typedef struct Bullet
{
    // Attributes
    Entity ent;                                                 // Bullet entity
    float spd;                                                  // Bullet speed
    bool active;                                                // Is the bullet active (i.e. was it hit or OOB)
} Bullet;

#include "Dots.h"

// Functions
// Player
void UpdatePlayer(Player* player, const Vector2 wind_size, const float dt, int* game_state);                        // Update player status
void DrawPlayer(Player* player, const Vector2 wind_size, const Vector2 mousepos);                                   // Draw Player
void DrawPlayerHUD(Player* player, const Vector2 wind_size, const Vector2 mousepos, int game_status, bool paused);  // Draw Player Heads-Up Display

// Bullet
void UpdateBullets(Bullet* bullet, const Entity* ent, const Vector2* target, const Vector2* wind_size);

#endif
