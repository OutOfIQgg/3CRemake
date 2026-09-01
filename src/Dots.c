#include "Dots.h"

DotSpawnEntry point_dot_chances[] = {
    { CCCiC_DOT_TYPE_TINY_POINT,    95 },
    { CCCiC_DOT_TYPE_MED_POINT,     75 },
    { CCCiC_DOT_TYPE_BIG_POINT,     60 },
    { CCCiC_DOT_TYPE_LARGE_POINT,   30 },
    { CCCiC_DOT_TYPE_XLARGE_POINT,  25 },
    { CCCiC_DOT_TYPE_XXLARGE_POINT, 5  },

    // Upgrades
    { CCCiC_DOT_TYPE_DOUB_SPEED,    35 },
    { CCCiC_DOT_TYPE_DOUB_POINTS,   25 },
    { CCCiC_DOT_TYPE_DOUB_DAMAGE,   45 },
    { CCCiC_DOT_TYPE_DOUB_DEFENSE,  20 },
    { CCCiC_DOT_TYPE_DOUB_HEALTH,   35 },
    { CCCiC_DOT_TYPE_DOUB_DISCOUNT, 10 },
};

void InitDots(const Vector2 wind_size, Dot* dot, unsigned int amount)
{
    for (int i = 0; i < amount; i++)
    {
        DotType type = SpawnFromTable(point_dot_chances, 6);

        float padding = 20.f;
        dot[i].ent.pos.x = GetRandomValue(padding, wind_size.x - padding);
        dot[i].ent.pos.y = GetRandomValue(padding, wind_size.y - padding);

        dot[i].type = type;
        dot[i].duration = 0;
        dot[i].color = WHITE;

        switch (type)
        {
            case CCCiC_DOT_TYPE_TINY_POINT:
            {
                dot[i].radius = 1.7f;
                dot[i].pointgain = 10;
                dot[i].text = "10";
                break;
            }
            case CCCiC_DOT_TYPE_MED_POINT:
            {        
                dot[i].radius = 2.4f;
                dot[i].pointgain = 25;
                dot[i].text = "25";
                break;
            }
            case CCCiC_DOT_TYPE_BIG_POINT:
            {
                dot[i].radius = 3.2f;
                dot[i].pointgain = 40;
                dot[i].text = "40";
                break;
            }
            case CCCiC_DOT_TYPE_LARGE_POINT:
            {
                dot[i].radius = 4.5f;
                dot[i].pointgain = 65;
                dot[i].text = "65";
                break;
            }
            case CCCiC_DOT_TYPE_XLARGE_POINT:
            {
                dot[i].radius = 5.6f;
                dot[i].pointgain = 80;
                dot[i].text = "80";
                break;
            }
            case CCCiC_DOT_TYPE_XXLARGE_POINT:
            {
                dot[i].radius = 6.5f;
                dot[i].pointgain = 125;
                dot[i].text = "125";
                break;
            }

        default:

        break;
        }
    }
}

void GenDots(const Vector2 wind_Size, Dot* dot)
{
    float padding = 20.f;
    
    DotType type = SpawnFromTable(point_dot_chances, (sizeof(point_dot_chances) / sizeof(point_dot_chances[0])));

    dot->ent.pos.x = GetRandomValue(padding, wind_Size.x - padding);
    dot->ent.pos.y = GetRandomValue(padding, wind_Size.y - padding);

    dot->type = type;
    dot->duration = 0;

    if (dot->type & CCCiC_DOT_TYPE_TINY_POINT)
    {
        dot->color = WHITE;
    }
    else if (dot->type & CCCiC_DOT_TYPE_DOUB_SPEED)
    {
        dot->radius = 4.f;
        dot->duration = 30.f;
    }

    switch (dot->type)
    {
        // Points
        case CCCiC_DOT_TYPE_TINY_POINT:
        {
            dot->radius = 1.7f;
            dot->pointgain = 10;
            break;
        }
        case CCCiC_DOT_TYPE_MED_POINT:
        {        
            dot->radius = 2.4f;
            dot->pointgain = 25;
            break;
        }
        case CCCiC_DOT_TYPE_BIG_POINT:
        {
            dot->radius = 3.2f;
            dot->pointgain = 40;
            break;
        }
        case CCCiC_DOT_TYPE_LARGE_POINT:
        {
            dot->radius = 4.5f;
            dot->pointgain = 65;
            break;
        }
        case CCCiC_DOT_TYPE_XLARGE_POINT:
        {
            dot->radius = 5.6f;
            dot->pointgain = 80;
            break;
        }
        case CCCiC_DOT_TYPE_XXLARGE_POINT:
        {
            dot->radius = 6.5f;
            dot->pointgain = 125;
            break;
        }

        // Upgrades
        case CCCiC_DOT_TYPE_DOUB_SPEED:
        {
            dot->color = BLUE;
            break;
        }
        case CCCiC_DOT_TYPE_DOUB_POINTS:
        {
            dot->color = ORANGE;
            break;
        }
        case CCCiC_DOT_TYPE_DOUB_DAMAGE:
        {
            dot->color = RED;
            break;
        }
        case CCCiC_DOT_TYPE_DOUB_DEFENSE:
        {
            dot->color = (Color){0, 255, 255, 255}; // CYAN (maybe)
            break;
        }
        case CCCiC_DOT_TYPE_DOUB_HEALTH:
        {
            dot->color = GREEN;
            break;
        }
        case CCCiC_DOT_TYPE_DOUB_DISCOUNT:
        {
            dot->color = PINK;
            dot->duration = 60.f;
            break;
        }

        default:
        break;
    }
}

void UpdateDotsBasedOnPlayer(const Vector2 wind_size, Player* player, Dot* dot, unsigned int amount)
{
    for (int i = 0; i < amount; i++)
    {
        float dx = player->ent.pos.x - dot[i].ent.pos.x;
        float dy = player->ent.pos.y - dot[i].ent.pos.y;
        float distnsq = dx * dx + dy * dy;

        float radsum = player->radius + dot[i].radius;
        float radsumsq = radsum * radsum;

        if (distnsq < radsumsq)
        {
            if (dot[i].type & CCCiC_DOT_TYPE_TINY_POINT)
            {
                player->points += dot[i].pointgain * player->pntbst;
            }
            else if ((dot[i].type & CCCiC_DOT_TYPE_DOUB_SPEED) && dot[i].duration > 0)
            {
                switch (dot[i].type)
                {
                    case CCCiC_DOT_TYPE_DOUB_SPEED:
                    {
                        player->uduration[0] += dot[i].duration;
                        if (player->spdbst >= 1 && player->spdbst < 3) player->spdbst++;
                        break;
                    }
                    case CCCiC_DOT_TYPE_DOUB_POINTS:
                    {
                        player->uduration[1] += dot[i].duration;
                        if (player->pntbst >= 1 && player->pntbst < 10) player->pntbst++;
                        break;
                    }
                    case CCCiC_DOT_TYPE_DOUB_DAMAGE:
                    {
                        player->uduration[2] += dot[i].duration;
                        if (player->dmgbst >= 0 && player->dmgbst < 15) player->dmgbst++;
                        break;
                    }
                    case CCCiC_DOT_TYPE_DOUB_DEFENSE:
                    {
                        player->uduration[3] += dot[i].duration;
                        if (player->dfnsbst >= 0 && player->dfnsbst < 15) player->dfnsbst++;
                        break;
                    }
                    case CCCiC_DOT_TYPE_DOUB_HEALTH:
                    {
                        player->uduration[4] += dot[i].duration;
                        if (player->hpboost >= 0 && player->hpboost < 35) player->hpboost++;
                        // Will probably change this... Unless it's the only way.
                        player->health += 20;
                        break;
                    }
                    case CCCiC_DOT_TYPE_DOUB_DISCOUNT:
                    {
                        player->uduration[5] += dot[i].duration;
                        player->discount = true;
                        break;
                    }
                    default:
                    break;
                }
            }
            GenDots(wind_size, &dot[i]);
        }
    }
}

void DrawDots(Dot* dot, unsigned int amount)
{
    for (int i = 0; i < amount; i++)
    {
        DrawCircleV(dot[i].ent.pos, dot[i].radius, dot[i].color);
        if (dot[i].type & CCCiC_DOT_TYPE_TINY_POINT) DrawText(dot[i].text, dot[i].ent.pos.x, dot[i].ent.pos.y, 16, (Color){123, 123, 123, 249});
    }
}

// Helper functions
DotType SpawnFromTable(DotSpawnEntry* table, unsigned int size)
{
    int total_weight = 0;
    for (int i = 0; i < size; i++)
    {
        total_weight += table[i].weight;
    }

    int roll = GetRandomValue(0, total_weight);

    int cumulative = 0;
    for (int i = 0; i < size; i++)
    {
        cumulative += table[i].weight;
        if (roll < cumulative)
        {
            return table[i].type;
        }
    }

    return table[0].type;
}
