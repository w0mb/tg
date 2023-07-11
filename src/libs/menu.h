#ifndef MENU_H
#define MENU_H

struct Choice; // Forward-декларация структуры Choice
struct Gun; // Forward-декларация структуры Gun
struct Character; // Forward-декларация структуры Character
struct Target; // Forward-декларация структуры Target

int drawMenu(int screenWidth, int screenHeight, struct Choice* choice);
int settings(int screenWidth, int screenHeight, struct Choice *choice);
void settings_logic(int screenWidth, int screenHeight, struct Choice *choice, struct Gun *gun, struct Character *character, struct Target *target);

#endif /* MENU_H */
