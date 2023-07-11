#pragma once
#include "../../raylib/src/raylib.h"
#define TEXTURES_COUNT 5

Texture2D textures[TEXTURES_COUNT];

struct Character
{
    int x;
    int y;
    int size;
    int speed;
    Rectangle charHitbox;
    bool flipX;
    bool drHitbox;
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
    bool drHitbox;
};

struct Gun
{
    int gunX;
    int gunY;
    int ammo;
    int damage;
    Rectangle gunHitbox;
    bool drHitbox;
};

enum TextureIndex
{
    TEXTURE_CHARACTER,
    TEXTURE_CHARACTER_MIRRORED,
    TEXTURE_GUN,
    TEXTURE_GUN_MIRRORED,
    TEXTURE_TARGET
};



void loadTextures();
void unloadTextures();
void drawTexturedRect(Rectangle rect, Texture2D texture, Color color);
void draw_char(struct Character* character);
void draw_target(struct Target* target);
void draw_gun(struct Character* character, struct Target* target, struct Gun* gun);
void move(struct Character* character);
void shoot(struct Gun* gun, struct Target* target);