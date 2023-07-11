#include "../libs/menu.h"
#include "../libs/gameMeh.h"
#include "../libs/filesPath.h"

int drawMenu(int screenWidth, int screenHeight, struct Choice* choice)
{
    DrawText("play", screenWidth / 2, screenHeight / 2, 100, WHITE);
    DrawText("settings", screenWidth / 2, screenHeight / 2 + 100, 100, WHITE);
    DrawText("exit", screenWidth / 2, screenHeight / 2 + 200, 100, WHITE);
    DrawText("pisa_popa", screenWidth / 2, screenHeight / 2 + 300, 100, WHITE);

    if (IsKeyPressed(KEY_S) && choice->y < screenHeight / 2 + 300)
    {
        choice->y += 100;
    }
    else if (IsKeyPressed(KEY_W) && choice->y > screenHeight / 2)
    {
        choice->y -= 100;
    }

    // Wrap the selection around if it goes out of bounds
    if (choice->y > screenHeight / 2 + 300)
    {
        choice->y = screenHeight / 2;
    }
    else if (choice->y < screenHeight / 2)
    {
        choice->y = screenHeight / 2 + 300;
    }

    // Draw the selection box around the chosen option
    choice->x = screenWidth / 2 - 125; // Offset the selection box

    DrawRectangleLines(choice->x, choice->y, 450, 100, WHITE);

    if (IsKeyPressed(KEY_ENTER))
    {
        if (choice->x == screenWidth / 2 - 125 && choice->y == screenHeight / 2)
        {
            return 1; // Return 1 for "play"
        }
        else if (choice->x == screenWidth / 2 - 125 && choice->y == screenHeight / 2 + 100)
        {
            return 2;
        }
        else if (choice->x == screenWidth / 2 - 125 && choice->y == screenHeight / 2 + 200)
        {
            return 3; // Return 3 for "exit"
        }
        else if (choice->x == screenWidth / 2 - 125 && choice->y == screenHeight / 2 + 300)
        {
            // DrawText("PISA_POPA", screenWidth/2, screenHeight/2, 100, RED);
            return 4; // Return 4 for "pisa_popa"
        }
    }

    return 0; // Return 0 to indicate no menu item was selected
}

int settings(int screenWidth, int screenHeight, struct Choice *choice)
{
    int settingsChoice = 0;

    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("debug mode", screenWidth / 2, screenHeight / 2, 70, WHITE);
    DrawText("resolution", screenWidth / 2, screenHeight / 2 + 100, 70, WHITE);
    DrawText("1920x1080", screenWidth / 2, screenHeight / 2 + 200, 50, WHITE);
    DrawText("1000x1000", screenWidth / 2, screenHeight / 2 + 300, 50, WHITE);

    if (IsKeyPressed(KEY_S) && choice->y < screenHeight / 2 + 300)
    {
        choice->y += 100;
    }
    else if (IsKeyPressed(KEY_W) && choice->y > screenHeight / 2)
    {
        choice->y -= 100;
    }

    // Wrap the selection around if it goes out of bounds
    if (choice->y > screenHeight / 2 + 300)
    {
        choice->y = screenHeight / 2;
    }
    else if (choice->y < screenHeight / 2)
    {
        choice->y = screenHeight / 2 + 300;
    }

    // Draw the selection box around the chosen option
    choice->x = screenWidth / 2 - 125; // Offset the selection box

    DrawRectangleLines(choice->x, choice->y, 450, 100, WHITE);

    if (IsKeyPressed(KEY_ENTER))
    {
        if (choice->x == screenWidth / 2 - 125 && choice->y == screenHeight / 2)
        {
            settingsChoice = 1; // Set settingsChoice to 1 for "debug mode"
        }
        else if (choice->x == screenWidth / 2 - 125 && choice->y == screenHeight / 2 + 200)
        {
            settingsChoice = 2; // Set settingsChoice to 2 for "fullHD"
        }
        else if (choice->x == screenWidth / 2 - 125 && choice->y == screenHeight / 2 + 300)
        {
            settingsChoice = 3; // Set settingsChoice to 3 for "1000x1000 defolt debug mode"
        }
    }

    EndDrawing();

    return settingsChoice;
}

void settings_logic(int screenWidth, int screenHeight, struct Choice *choice, struct Gun *gun, struct Character *character, struct Target *target)
{
    int settingsChoice = 0;

    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("debug mode", screenWidth / 2, screenHeight / 2, 70, WHITE);
    DrawText("resolution", screenWidth / 2, screenHeight / 2 + 100, 70, WHITE);
    DrawText("1920x1080", screenWidth / 2, screenHeight / 2 + 200, 50, WHITE);
    DrawText("1000x1000", screenWidth / 2, screenHeight / 2 + 300, 50, WHITE);

    if (IsKeyPressed(KEY_S) && choice->y < screenHeight / 2 + 300)
    {
        choice->y += 100;
    }
    else if (IsKeyPressed(KEY_W) && choice->y > screenHeight / 2)
    {
        choice->y -= 100;
    }

    // Wrap the selection around if it goes out of bounds
    if (choice->y > screenHeight / 2 + 300)
    {
        choice->y = screenHeight / 2;
    }
    else if (choice->y < screenHeight / 2)
    {
        choice->y = screenHeight / 2 + 300;
    }

    // Draw the selection box around the chosen option
    choice->x = screenWidth / 2 - 125; // Offset the selection box

    DrawRectangleLines(choice->x, choice->y, 450, 100, WHITE);

    if (IsKeyPressed(KEY_ENTER))
    {
        if (choice->x == screenWidth / 2 - 125 && choice->y == screenHeight / 2)
        {
            settingsChoice = 1; // Set settingsChoice to 1 for "debug mode"
        }
        else if (choice->x == screenWidth / 2 - 125 && choice->y == screenHeight / 2 + 200)
        {
            settingsChoice = 2; // Set settingsChoice to 2 for "fullHD"
        }
        else if (choice->x == screenWidth / 2 - 125 && choice->y == screenHeight / 2 + 300)
        {
            settingsChoice = 3; // Set settingsChoice to 3 for "1000x1000 defolt debug mode"
        }
    }

    EndDrawing();

    // Применение выбранных настроек
    switch (settingsChoice)
    {
        case 1:
            gun->drHitbox = true;
            target->drHitbox = true;
            character->drHitbox = true;
            break;
        case 2:
            // Изменение разрешения на 1920x1080
            screenWidth = 1920;
            screenHeight = 1080;
            SetWindowSize(screenWidth, screenHeight);
            SetTargetFPS(60); // Установка желаемого FPS
            break;
        case 3:
            // Изменение разрешения на 1000x1000
            screenWidth = 1000;
            screenHeight = 1000;
            SetWindowSize(screenWidth, screenHeight);
            SetTargetFPS(60); // Установка желаемого FPS
            break;
        default:
            break;
    }
}
