#include "../libs/game.h"
#include "../libs/gameMeh.h"

void runGameLoop(int screenHeight, int screenWidth)
{
    struct Character character = {100, 100, 32, 5, {character.x, character.y, 45, 45}, false, false};
    struct Target target = {200, 200, 90, 100, false, 0, {target.x, target.y, 90, 90}, true, false};
    struct Gun gun = {character.x, character.y, 7, 10, {gun.gunX, gun.gunY, 50, 50}, false};

    Music backgroundMusic;
    backgroundMusic = LoadMusicStream("../music/mus1.mp3");
    PlayMusicStream(backgroundMusic);
    UpdateMusicStream(backgroundMusic);

    loadTextures();

    bool debugMode = false;
    bool playGame = true;

    while (playGame && !WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK); // Очистка экрана

        // Основной алгоритм игры
        draw_gun(&character, &target, &gun);
        draw_char(&character);
        draw_target(&target);
        if (IsKeyPressed(KEY_H))
        {
                debugMode = !debugMode;

            if (debugMode)
            {
            DrawText("Debug Mode", 10, 30, 20, GREEN);
            DrawText("Press 'H' to toggle hitbox display", 10, 50, 20, GREEN);
            DrawText("Press 'R' to reload gun", 10, 70, 20, GREEN);
            }

            character.drHitbox = debugMode;
            gun.drHitbox = debugMode;
            target.drHitbox = debugMode;
        }       


        move(&character);
        shoot(&gun, &target);

        if (IsKeyPressed(KEY_H))
        {
            debugMode = !debugMode;
        }

        if (debugMode)
        {
            if (character.drHitbox)
            {
                DrawRectangleLines(character.charHitbox.x, character.charHitbox.y, character.charHitbox.width, character.charHitbox.height, GREEN);
            }

            if (target.drHitbox)
            {
                DrawRectangleLines(target.targetHitbox.x, target.targetHitbox.y, target.targetHitbox.width, target.targetHitbox.height, RED);
            }

            if (gun.drHitbox)
            {
                DrawRectangleLines(gun.gunHitbox.x, gun.gunHitbox.y, gun.gunHitbox.width, gun.gunHitbox.height, BLUE);
            }
        }

        DrawFPS(10, 10);
        DrawText(TextFormat("Ammo: %d", gun.ammo), 10, screenHeight - 30, 20, WHITE);

        EndDrawing();
    }
}

void game()
{
    int screenWidth = 1000;
    int screenHeight = 1000;

    struct Choice choice;
    struct Gun gun;
    struct Character character;
    struct Target target;

    InitWindow(screenWidth, screenHeight, "Dwarf Game");
    SetTargetFPS(60);

    int menuChoice = 0;
    bool showText = false; // Флаг для отображения надписи "PISKA POPKA"
    bool showSettings = false;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK); // Очистка экрана

        if (!showText)
        {
            menuChoice = drawMenu(screenHeight, screenWidth, &choice);

            if (menuChoice == 1)
            {
                runGameLoop(screenHeight, screenWidth); // Запустить основной алгоритм игры
            }
            else if(menuChoice == 2)
            {   
                showSettings = true;
            }
            else if (menuChoice == 3)
            {
                break; // Выход из игры
            }
            else if (menuChoice == 4)
            {
                showText = true; // Показать надпись "PISKA POPKA"
            }
        }

        // Отобразить надпись "PISKA POPKA", если флаг showText установлен в true
        if (showText)
        {
            ClearBackground(BLACK);
            DrawText("PISKA POPKA", screenWidth / 2 - 400, screenHeight/2, 120, WHITE);
            DrawText("press 'space' to exit in main menu", 10, screenHeight - 300, 20, WHITE);

            if (IsKeyPressed(KEY_SPACE))
            {
                showText = false; // Скрыть надпись "PISKA POPKA"
            }
        }

        while(showSettings)
        {
            ClearBackground(BLACK);
            settings_logic(screenWidth, screenHeight, &choice, &gun, &character, &target);

            if (IsKeyPressed(KEY_SPACE))
            {
                showSettings = false; // Скрыть надпись "PISKA POPKA"
            }
        }
        EndDrawing();
    }

    CloseWindow();
}