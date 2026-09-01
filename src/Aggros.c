#include "Aggros.h"

void InitEnemy(AggroEnt* enm, const Vector2 wind_size, unsigned int amount)
{
    for (unsigned int i = 0; i < amount; i++)
    {
        uint8_t dir = GetRandomValue(1, 4);
        // 1 is top, 2 is left, 3 is bottom, 4 is right

        // For enemies who are big (like bosses) so that small enemies like chasers won't take a while to get to the screen
        uint8_t distance = 30;
        enm[i].brainless = true;
        //* Basic inits for testing
        enm[i].color = (Color){255, 155, 155, 255};
        enm[i].ent.vel = Vector2Zero();
        enm[i].type = 0;
        enm[i].health = 100;
        enm[i].maxhealth = 100;
        enm[i].rotation = 0.f;
        enm[i].speed = 35.f;

        // */
        switch (dir)
        {
            case 1:
            {
                enm[i].ent.pos.y = wind_size.y + distance;
                enm[i].ent.pos.x = GetRandomValue(-40, wind_size.x + 40);
                break;
            }

            case 2:
            {
                enm[i].ent.pos.y = GetRandomValue(-40, wind_size.y + 40);
                enm[i].ent.pos.x = wind_size.x + distance;
                break;
            }

            case 3:
            {
                enm[i].ent.pos.y = -distance;
                enm[i].ent.pos.x = GetRandomValue(-40 , wind_size.x + 40);
                break;
            }

            case 4:
            {
                enm[i].ent.pos.y = GetRandomValue(-40 , wind_size.y + 40);
                enm[i].ent.pos.x = -distance;
                break;
            }

            default:
                enm[i].ent.pos = (Vector2){ -30, -30 };
            break;
        }
    }
}

void UpdateEnemy(AggroEnt* enm, const Player* player, Dot* dots, const Vector2 wind_size, const float dt, unsigned int amount)
{
    for (unsigned int i = 0; i < amount; i++)
    {
        // Update velocity
        Vector2 pdir2enm = Vector2Subtract(player->ent.pos, enm[i].ent.pos);

        Vector2 nrmpdir2enm = Vector2Normalize(pdir2enm);

        enm[i].ent.vel = (Vector2){
            nrmpdir2enm.x * enm[i].speed, nrmpdir2enm.y * enm[i].speed
        };

        // Update position
        if (!enm[i].brainless)
        {
            enm[i].ent.pos.x += enm[i].ent.vel.x * dt;
            enm[i].ent.pos.y += enm[i].ent.vel.y * dt;
        }
    }
}

void DrawEnemy(AggroEnt* enm, unsigned int amount)
{
    for (unsigned int i = 0; i < amount; i++)
    {
        DrawCircleV(enm[i].ent.pos, 12.f, (Color){255, 155, 155, 255});
    }
}
