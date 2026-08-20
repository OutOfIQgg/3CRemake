#define RAYGUI_IMPLEMENTATION
#define RAYGUI_NO_ICONS
#include "Player.h"
#include "Save.h"

// Current GameState
static int cur_state = CCCiC_STATE_MAIN_MENU;
static bool debug = false;

int main(void)
{
    int wind_width = 800, wind_height = 600;
    InitWindow(wind_width, wind_height, "Circle Chasing Circle");
    SetExitKey(0);

    Player player = {
        .ent.pos = (Vector2){wind_width/2.f, wind_height/2.f},
        .ent.vel = Vector2Zero(),
        .radius = 15.f,
        .rotation = .0f,
        .speed = 1.f,
        .points = 0,
        .controls = {KEY_W, KEY_A, KEY_S, KEY_D, KEY_SPACE},
        .color = {0xFF, 0xFF, 0xFF, 0xFF},
        .health = 100,
        .spdbst = 1,
        .pntbst = 1,
        .dmgbst = 1,
        .hpboost = 1,
        .discount = false
    };

    Vector2 wind_size = (Vector2){wind_width, wind_height};

    Dot* dot[16];
    InitDots(wind_size, dot, 16);

    bool paused = false;
    bool shouldquit = false;

    // GUI stuff
    GameState stateholdover;

    int default_color = GuiGetStyle(DEFAULT, BACKGROUND_COLOR);

    // High score
    uint64_t high_score = LoadFromFile(0, SaveFileName);
    
    while (!WindowShouldClose() && !shouldquit)
    {
        Vector2 mousepos = GetMousePosition();
        float dt = GetFrameTime();
        if (cur_state == CCCiC_STATE_GAME)
        {
            player.speed = 150.f * dt;
            if (!paused)
            {
                UpdatePlayer(&player, wind_size, dt, &cur_state);
                UpdateDotsBasedOnPlayer(wind_size, &player, dot, 16);
            }

            if (IsKeyPressed(KEY_ESCAPE)) paused = !paused;
            
            // Check if the window lost focus
            if (!IsWindowFocused()) paused = true;
        }

        if (player.points > high_score) SaveToFile(&player.points, 0, SaveFileName);
        
        GuiEnable();
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(WHITE));

        BeginDrawing();
            ClearBackground(BLACK);
            if (cur_state == CCCiC_STATE_MAIN_MENU)
            {
                for (int i = 0; i < 3; i++) DrawText("CIRCLE CHASING", i * 325 + 10, wind_height / 3.6, 36, WHITE);

                // Display high points
                DrawText(TextFormat("HIGHEST POINTS: %d", high_score), 10, 10, 26, WHITE);
                
                GuiSetStyle(DEFAULT, TEXT_SIZE, 16);

                if (GuiButton((Rectangle){10, 36, 60, 20}, "CLEAR")) { SaveToFile(0, 0, SaveFileName); high_score = LoadFromFile(0, SaveFileName); }

                GuiSetStyle(DEFAULT, TEXT_SIZE, 26);

                if (GuiButton((Rectangle){(wind_size.x / 2) - 80, (wind_size.y / 2) - 30, 160, 60}, "PLAY")) cur_state = CCCiC_STATE_GAME;
                if (GuiButton((Rectangle){(wind_size.x / 2) - 80, (wind_size.y / 2 - 30) * 1.3, 160, 60}, "OPTIONS")) { stateholdover = cur_state; cur_state = CCCiC_STATE_OPTIONS; }
                if (GuiButton((Rectangle){(wind_size.x / 2) - 80, (wind_size.y / 2 - 30) * 1.6, 160, 60}, "QUIT")) shouldquit = !shouldquit;
            }
            else if (cur_state == CCCiC_STATE_GAME)
            {
                DrawDots(dot, 16);
            
                DrawPlayer(&player, wind_size, mousepos);
                DrawPlayerHUD(&player, wind_size, mousepos, cur_state, paused);
                GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, default_color);
                
                // Debug ain't doing NOTHING other than show player position ToT
                if (debug)
                {
                    DrawText(TextFormat("player position: %.2f, %.2f", player.ent.pos.x, player.ent.pos.y), 10, 10, 26, WHITE);
                }

                if (paused)
                {
                    DrawText("PAUSED!", 10, wind_height / 4.3, 36, WHITE);
                    DrawRectangle(0, 0, wind_size.x, wind_size.y, (Color){0, 0, 0, 100});
                    if (GuiButton((Rectangle){10, wind_height / 3.3f, 120, 40}, "RESUME")) paused = !paused;
                    if (GuiButton((Rectangle){10, wind_height / 2.5f, 120, 40}, "OPTIONS")) { stateholdover = cur_state; cur_state = CCCiC_STATE_OPTIONS; }
                    if (GuiButton((Rectangle){10, wind_height / 2, 120, 40}, "QUIT")) shouldquit = !shouldquit;
                }
            }
            else if (cur_state == CCCiC_STATE_OPTIONS)
            {
                // Polishing later
                if (GuiButton((Rectangle){20, wind_height / 1.3, 120, 40}, "RETURN")) cur_state = stateholdover;
            }
        EndDrawing();
    }

    CloseWindow();
}
