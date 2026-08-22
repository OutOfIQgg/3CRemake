#include "raygui.h"
#include "Player.h"

void UpdatePlayer(Player* player, const Vector2 wind_size, const float dt, int* game_state)
{
    player->ent.vel = (Vector2){
        (IsKeyDown(player->controls[3]) * (player->speed * player->spdbst)) -
        (IsKeyDown(player->controls[1]) * (player->speed * player->spdbst)),
        (IsKeyDown(player->controls[2]) * (player->speed * player->spdbst)) -
        (IsKeyDown(player->controls[0]) * (player->speed * player->spdbst))
    };

    player->ent.pos.x += player->ent.vel.x;
    player->ent.pos.y += player->ent.vel.y;

    player->ent.pos.x = Clamp(player->ent.pos.x, player->radius, wind_size.x - player->radius);
    player->ent.pos.y = Clamp(player->ent.pos.y, player->radius, wind_size.y - player->radius);

    for (int i = 0; i <= 5; i++)
    {
        if (player->uduration[i] > 0)
        {
            player->uduration[i] -= dt;

            if (player->uduration[i] <= 0)
            {
                switch (i)
                {
                    case 0:
                        player->spdbst = 1;    
                    break;

                    case 1:
                        player->pntbst = 1;
                    break;

                    case 2:
                        player->dmgbst = 1;
                    break;

                    case 3:
                        player->dfnsbst = 1;
                    break;

                    case 4:
                        player->hpboost = 1;
                    break;

                    case 5:
                        player->discount = false;
                    break;
                    
                    default:
                    break;
                }
            }
        }
    }

    player->maxhealth = 100 * player->hpboost;
    player->health = Clamp(player->health, 0, player->maxhealth);
    if (player->health <= 0) *(game_state) = CCCiC_STATE_DEAD;
}

void DrawPlayer(Player* player, const Vector2 wind_size, const Vector2 mousepos)
{
    // Player Circle
    DrawCircleV(player->ent.pos, player->radius, player->color);
    DrawText("P", player->ent.pos.x, player->ent.pos.y, 16, GRAY);

    /* Old status viewing (mostly Gemini but has a few personal touches. Rebuilding cuz it's UGLY and inconvenient)
    // Also because that's where the old HUD is. Muesume, I guess
    static bool stat_wind_open = false;
    static Rectangle pau = (Rectangle){10, 10, 220, 200};

    if (!stat_wind_open)
    {
        GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
        if (GuiButton((Rectangle){10, 40, 50, 50}, "P&U")) stat_wind_open = true;
    }
    else
    {
        static bool is_dragged = false;
        GuiSetStyle(DEFAULT, TEXT_SIZE, 15);
        if (GuiWindowBox(pau, "POINTS AND UPGRADES")) stat_wind_open = false;

        // Scroll bar
        static Vector2 scrolloffset = (Vector2){0, 0};
        static Rectangle scrollrect = (Rectangle){0};

        Rectangle scrollbounds = (Rectangle){pau.x + 5, pau.y + 25, pau.width - 10, pau.height - 35};
        Rectangle scrollcontents = (Rectangle){0,0, pau.width - 30, 400};

        GuiScrollPanel(scrollbounds, NULL, scrollcontents, &scrolloffset, &scrollrect);

        BeginScissorMode(scrollbounds.x, scrollbounds.y, scrollbounds.width, scrollbounds.height);

        float itemstartX = scrollbounds.x + scrolloffset.x;
        float itemstartY = scrollbounds.y + scrolloffset.y;

        DrawText("----- UPGRADES -----", itemstartX + 15, itemstartY + 15, 16, BLACK);
        
        // Display things
        DrawText(TextFormat("SPEEDUP: %.2f %d", player->uduration[0], player->spdup), itemstartX + 10, itemstartY + 35, 16, BLACK);
        DrawText(TextFormat("DPOINTS: %.2f %d", player->uduration[1], player->doubp), itemstartX + 10, itemstartY + 60, 16, BLACK);

        EndScissorMode();

        // Dragging
        if ((mousepos.x > pau.x && mousepos.x < pau.x + pau.width) && (mousepos.y > pau.y && mousepos.y < pau.y + 20) && IsMouseButtonDown(0))
        {
            is_dragged = true;
        }

        if (is_dragged)
        {
            Vector2 mousedt = GetMouseDelta();
            pau.x += mousedt.x;
            pau.y += mousedt.y;

            if (IsMouseButtonReleased(0)) is_dragged = false;
        }
    }
    */

    /* Old
    if (player.spdup > 1) DrawText(TextFormat("Speed Up: %.2f", player.uduration[0]), 10, 40, 26, (Color){255, 255, 255, 150});
    if (player.doubp > 1) DrawText(TextFormat("Double Points: %.2f", player.uduration[1]), 10, 80, 26, (Color){255, 255, 255, 150});
    */
}

// Sophisticated asf :sob:
void DrawPlayerHUD(Player* player, const Vector2 wind_size, const Vector2 mousepos, int game_stat, bool paused)
{
    // Status display
    static int linestarty = 565;

    // Check if mouse is in the line's borders
    // Let's not neglect pause check :P
    if (!paused)
    {
        if (mousepos.y > linestarty) linestarty = 445;
        else linestarty = 565;
    }

    // Status graphics
    DrawLineEx((Vector2){ 0, linestarty }, (Vector2){ wind_size.x, linestarty }, 10.f, (Color){0, 110, 105, 125});
    DrawRectangle(0, linestarty + 5, wind_size.x, linestarty, (Color){0, 0, 0, 105});
    DrawText("STATUS", 25, linestarty - 5, 14, BLACK);
    
    // Health
    // DrawRectangle(10, linestarty + 105, player->health * 4, 30, (Color){155, 155, 190, 150});
    // DrawRectangleLines(10, linestarty + 105, 400, 30, (Color){120, 120, 140, 120});
    DrawText(TextFormat("HEALTH: %d / %d", player->health, player->maxhealth), 10, linestarty + 105, 28, GREEN);
    
    // Points
    DrawText(TextFormat("POINTS: %d", player->points), 10, linestarty + 15, 24, (Color){155, 155, 150, 135});

    // Upgrade list
    Rectangle scrollrec = { wind_size.x - 320, linestarty + 20, 300, 135 };
    static Rectangle scrollcontrec = { 0, 0, 285, 155 };
    static Rectangle scrollview = {0};
    static Vector2 panelscroll = { 99, 0 };
    Vector2 contentpos = { panelscroll.x + scrollrec.x, panelscroll.y + scrollrec.y };

    GuiSetStyle(DEFAULT, BACKGROUND_COLOR, 0x0F0F0D99);
    GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, 0x0F0F0D99);
    
    GuiScrollPanel(scrollrec, NULL, scrollcontrec, &panelscroll, &scrollview);
    
    BeginScissorMode(scrollview.x, scrollview.y, scrollview.width, scrollview.height);
    // This is where content goes (they rely on scrollview + scrollrec aliased as contentpos)
    DrawText(TextFormat("SPEED BOOST: %.1f x%d", player->uduration[0], player->spdbst), contentpos.x + 10, contentpos.y + 10, 20, WHITE);
    DrawText(TextFormat("POINT BOOST: %.1f x%d", player->uduration[1], player->pntbst), contentpos.x + 10, contentpos.y + 30, 20, WHITE);
    DrawText(TextFormat("DAMAGE BOOST: %.1f x%d", player->uduration[2], player->dmgbst), contentpos.x + 10, contentpos.y + 50, 20, WHITE);
    DrawText(TextFormat("DEFENSE BOOST: %.1f x%d", player->uduration[3], player->dfnsbst), contentpos.x + 10, contentpos.y + 70, 20, WHITE);
    DrawText(TextFormat("HP BOOST: %.1f x%d", player->uduration[4], player->hpboost), contentpos.x + 10, contentpos.y + 90, 20, WHITE);
    DrawText(TextFormat("DISCOUNT: %.1f", player->uduration[5]), contentpos.x + 10, contentpos.y + 110, 20, WHITE);
    DrawText("What are you looking for? (More soon dw :P)", contentpos.x + 15, contentpos.y + 135, 12, WHITE);
    EndScissorMode();
}

void UpdateBullets(Bullet* bullet, const Entity* ent, const Vector2* target, const Vector2* wind_size)
{
    if ((bullet->ent.pos.x < 0 || bullet->ent.pos.x > wind_size->x) && (bullet->ent.pos.y < 0 && bullet->ent.pos.y > wind_size->y) && bullet->active == true) bullet->active = false; 

    float angle = atan2f(target->y - ent->pos.y, target->x - ent->pos.x);

    bullet->ent.vel = (Vector2){
        cosf(angle) * bullet->spd, sinf(angle) * bullet->spd
    };
}
