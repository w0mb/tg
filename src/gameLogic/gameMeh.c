#include "../libs/gameMeh.h"
#include "../libs/filesPath.h"

const char* texturePaths[] = {
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

    if (character->drHitbox == true)
    {
        DrawRectangleLines(character->x, character->y, character->charHitbox.width, character->charHitbox.height, GREEN);
    }
}

void draw_target(struct Target* target)
{
    if (target->visible)
    {
        drawTexturedRect((Rectangle){target->x, target->y, target->size, target->size},
                        textures[TEXTURE_TARGET], WHITE);

        if (target->drHitbox == true)
        {
            DrawRectangleLines(target->x, target->y, target->targetHitbox.width, target->targetHitbox.height, RED);
        }
    }
}

void draw_gun(struct Character* character, struct Target* target, struct Gun* gun)
{
    gun->gunX = character->x + character->charHitbox.width / 2 - textures[TEXTURE_GUN].width / 2;
    gun->gunY = character->y + character->charHitbox.height / 2 - textures[TEXTURE_GUN].height / 2;

    drawTexturedRect((Rectangle){gun->gunX, gun->gunY, textures[TEXTURE_GUN].width, textures[TEXTURE_GUN].height},
                    textures[character->flipX ? TEXTURE_GUN_MIRRORED : TEXTURE_GUN], WHITE);

    if (gun->drHitbox == true)
    {
        DrawRectangleLines(gun->gunX, gun->gunY, gun->gunHitbox.width, gun->gunHitbox.height, BLUE);
    }
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