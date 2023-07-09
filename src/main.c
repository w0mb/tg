#include "../raylib/src/raylib.h"

struct Character
{
    int x;
    int y;
    int size;
    int speed;
    Rectangle charHitbox;
    bool flipX;
};

struct Choice
{
    int x;
    int y;
};

struct Target
{
    int x;
    int y;
    int size;
    int hp;
    bool respawn;
    float respawnTimer;
    Rectangle targetHitbox;
    bool visible;
};

struct Gun
{
    int gunX;
    int gunY;
    int ammo;
    int damage;
    Rectangle gunHitbox;
};

#define TEXTURES_COUNT 5
enum TextureIndex
{
    TEXTURE_CHARACTER,
    TEXTURE_CHARACTER_MIRRORED,
    TEXTURE_GUN,
    TEXTURE_GUN_MIRRORED,
    TEXTURE_TARGET
};

Texture2D textures[TEXTURES_COUNT];
const char* texturePaths[TEXTURES_COUNT] = {
    "../png/char.png",
    "../png/char1.png",
    "../png/gun.png",
    "../png/gun1.png",
    "../png/target.png"
};

void loadTextures()
{
    for (int i = 0; i < TEXTURES_COUNT; i++)
    {
        textures[i] = LoadTexture(texturePaths[i]);
    }
}

void unloadTextures()
{
    for (int i = 0; i < TEXTURES_COUNT; i++)
    {
        UnloadTexture(textures[i]);
    }
}

void drawTexturedRect(Rectangle rect, Texture2D texture, Color color)
{
    DrawTextureRec(texture, (Rectangle){0, 0, rect.width, rect.height}, (Vector2){rect.x, rect.y}, color);
}

void draw_char(struct Character* character)
{
    drawTexturedRect((Rectangle){character->x, character->y, character->size, character->size},
                     textures[character->flipX ? TEXTURE_CHARACTER_MIRRORED : TEXTURE_CHARACTER], WHITE);

    DrawRectangleLines(character->x, character->y, character->charHitbox.width, character->charHitbox.height, GREEN);
}

void draw_target(struct Target* target)
{
    if (target->visible)
    {
        drawTexturedRect((Rectangle){target->x, target->y, target->size, target->size},
                         textures[TEXTURE_TARGET], WHITE);

        DrawRectangleLines(target->x, target->y, target->targetHitbox.width, target->targetHitbox.height, RED);
    }
}

void draw_gun(struct Character* character, struct Target* target, struct Gun* gun)
{
    gun->gunX = character->x + character->charHitbox.width / 2 - textures[TEXTURE_GUN].width / 2;
    gun->gunY = character->y + character->charHitbox.height / 2 - textures[TEXTURE_GUN].height / 2;

    drawTexturedRect((Rectangle){gun->gunX, gun->gunY, textures[TEXTURE_GUN].width, textures[TEXTURE_GUN].height},
                     textures[character->flipX ? TEXTURE_GUN_MIRRORED : TEXTURE_GUN], WHITE);

    DrawRectangleLines(gun->gunX, gun->gunY, gun->gunHitbox.width, gun->gunHitbox.height, BLUE);
}

void move(struct Character* character)
{
    if (IsKeyDown(KEY_A))
    {
        character->x -= character->speed;
        character->flipX = true;
    }

    if (IsKeyDown(KEY_D))
    {
        character->x += character->speed;
        character->flipX = false;
    }

    if (IsKeyDown(KEY_W))
    {
        character->y -= character->speed;
    }

    if (IsKeyDown(KEY_S))
    {
        character->y += character->speed;
    }
}

void shoot(struct Gun* gun, struct Target* target)
{
    if (IsKeyPressed(KEY_SPACE) && gun->ammo > 0)
    {
        gun->ammo--;

        for (int i = 0; i < 50; i++)
        {
            DrawCircle(gun->gunX + i, gun->gunY, 4, ORANGE);

            if (CheckCollisionPointRec((Vector2){gun->gunX + i, gun->gunY}, target->targetHitbox))
            {
                target->hp -= gun->damage;

                if (target->hp <= 0)
                {
                    target->visible = false;
                    target->respawn = true;
                    target->respawnTimer = GetTime() + 4.0f; // Set the respawn timer to 4 seconds
                }
            }
        }
    }
}

void menuLogic()
{

}

int menu(int screenWidth, int screenHeight, struct Choice* choice)
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
            // settings();
            // Do something for "settings"
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


void game()
{
    int screenWidth = 1000;
    int screenHeight = 1000;

    struct Choice choice;

    struct Character character = {100, 100, 32, 5, {character.x, character.y, 45, 45}, false};
    struct Target target = {200, 200, 90, 100, false, 0, {target.x, target.y, 90, 90}, true};
    struct Gun gun = {character.x, character.y, 7, 10, {gun.gunX, gun.gunY, 50, 50}};

    Music backgroundMusic;
    backgroundMusic = LoadMusicStream("../music/mus1.mp3");
    PlayMusicStream(backgroundMusic);
    UpdateMusicStream(backgroundMusic);

    InitWindow(screenWidth, screenHeight, "Dwarf Game");
    SetTargetFPS(60);

    loadTextures();

    int menuChoice = 0;
    bool playGame = false; // Флаг для определения, нужно ли запускать игру
    bool showText = false; // Флаг для отображения надписи "PISKA POPKA"

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK); // Очистка экрана

        if (!playGame)
        {
            menuChoice = menu(screenHeight, screenWidth, &choice);

            if (menuChoice == 1)
            {
                playGame = true; // Установить флаг в true, чтобы запустить игру
            }
            else if (menuChoice == 3)
            {
                break;
            }
            else if (menuChoice == 4)
            {
                showText = true; // Показать надпись "PISKA POPKA"
            }
        }
        else
        {
            // Основной алгоритм игры
            draw_char(&character);
            draw_gun(&character, &target, &gun);
            draw_target(&target);

            move(&character);
            shoot(&gun, &target);

            DrawFPS(10, 10);
            DrawText(TextFormat("Ammo: %d", gun.ammo), 10, screenHeight - 30, 20, WHITE);

            if (IsKeyPressed(KEY_SPACE))
            {
                showText = false; // Скрыть надпись "PISKA POPKA"
            }
        }

        // Отобразить надпись "PISKA POPKA", если флаг showText установлен в true
        if (showText)
        {
            ClearBackground(BLACK);
            DrawText("PISKA POPKA", screenWidth / 2 - 400, screenHeight/2, 150, WHITE);
        }

        EndDrawing();
    }

    unloadTextures();
    UnloadMusicStream(backgroundMusic);

    CloseWindow();
}




int main()
{
    game();
    return 0;
}