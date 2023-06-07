#include "raylib/src/raylib.h"

#define MAX_INPUT_CHARS 9

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "My Application");

    SetTargetFPS(60);

    char answer[MAX_INPUT_CHARS + 1] = "\0";
    int answerLength = 0;
    bool showAnswer = false;

    while (!WindowShouldClose())
    {
        if (!showAnswer)
        {
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                if (answerLength > 0)
                {
                    answerLength--;
                    answer[answerLength] = '\0';
                }
            }
            else if (IsKeyPressed(KEY_ONE))
            {
                if (answerLength < MAX_INPUT_CHARS)
                {
                    answer[answerLength] = '1';
                    answerLength++;
                }
            }
            else if (IsKeyPressed(KEY_TWO))
            {
                if (answerLength < MAX_INPUT_CHARS)
                {
                    answer[answerLength] = '2';
                    answerLength++;
                }
            }

            // Добавьте условия для остальных клавиш, если нужно

            if (IsKeyPressed(KEY_ENTER))
            {
                showAnswer = true;
            }
        }
        else
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                answer[0] = '\0';
                answerLength = 0;
                showAnswer = false;
            }
        }

        BeginDrawing();

        ClearBackground(PINK);

        if (!showAnswer)
        {
            DrawText("Paxnet?", 10, 10, 20, BLACK);
            DrawText("Answers:", 10, 40, 20, BLACK);
            DrawText("1) yes", 10, 70, 20, BLACK);
            DrawText("2) no", 10, 100, 20, BLACK);

            DrawRectangleLines(200, 70, 200, 40, BLACK);
            DrawText(TextFormat("%s|", answer), 210, 80, 20, BLACK);
        }
        else
        {
            if (strcmp(answer, "1") == 0)
            {
                DrawText("OLYA PERNULA!", 10, 150, 20, BLACK);
            }
            else if (strcmp(answer, "2") == 0)
            {
                DrawText("net olya ne pernula =(", 10, 180, 20, BLACK);
            }
            else
            {
                DrawText("Invalid answer", 10, 150, 20, BLACK);
            }
            DrawText("Press Enter to return to the menu", 10, 210, 20, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

    
