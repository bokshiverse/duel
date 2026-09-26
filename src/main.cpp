#include <iostream>

#include "raylib.h"
#include "screen.h"

Color darkRed = (Color){100, 0, 0, 255};

enum SCREEN
{
    LOADING,
    HOME
};

enum OPTION
{
    CREATE_ROOM,
    JOIN_ROOM,
    SETTINGS
};

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Duel");

    InitAudioDevice();

    ToggleFullscreen();

    SetTargetFPS(60);

    SCREEN CURRENT_SCREEN = LOADING;
    OPTION CURRENT_OPTION = CREATE_ROOM;

    Font katsunoFont =
        LoadFontEx(
            "assets/fonts/katsuno-japan-demo.regular.ttf",
            200,
            nullptr,
            0
        );

    Font poppinsFont =
        LoadFontEx(
            "assets/fonts/poppins.regular.ttf",
            200,
            nullptr,
            0
        );

    Font poppinsBlackFont =
        LoadFontEx(
            "assets/fonts/poppins.black.ttf",
            200,
            nullptr,
            0
        );

    Music bgm =
        LoadMusicStream("assets/audio/bgm.ogg");

    bgm.looping = true;
    SetMusicVolume(bgm, 0.1f);

    Sound switchbg =
        LoadSound("assets/audio/switch.ogg");

	Sound loadingbg =
        LoadSound("assets/audio/loading.ogg");


    Texture2D wallpaper =
        LoadTexture("assets/images/wallpaper4.png");

    Screen screen;

    float alpha = 0.0f;
    float fadeDuration = 5.0f;

    float elapsedTime = 0.0f;
    float loadingDuration = 6.0f;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
		PlaySound(loadingbg);

        if (CURRENT_SCREEN == LOADING)
        {
            elapsedTime += dt;

            if (elapsedTime >= loadingDuration)
            {
                CURRENT_SCREEN = HOME;
                PlayMusicStream(bgm);
            }
        }

        if (CURRENT_SCREEN == HOME)
        {
            if (IsKeyPressed(KEY_DOWN))
            {
                if (CURRENT_OPTION == CREATE_ROOM)
                    CURRENT_OPTION = JOIN_ROOM;
                else if (CURRENT_OPTION == JOIN_ROOM)
                    CURRENT_OPTION = SETTINGS;
                else
                    CURRENT_OPTION = CREATE_ROOM;

                PlaySound(switchbg);
            }

            if (IsKeyPressed(KEY_UP))
            {
                if (CURRENT_OPTION == CREATE_ROOM)
                    CURRENT_OPTION = SETTINGS;
                else if (CURRENT_OPTION == JOIN_ROOM)
                    CURRENT_OPTION = CREATE_ROOM;
                else
                    CURRENT_OPTION = JOIN_ROOM;

                PlaySound(switchbg);
            }

            UpdateMusicStream(bgm);
        }

        if (alpha < 1.0f)
        {
            alpha += dt / fadeDuration;

            if (alpha > 1.0f)
                alpha = 1.0f;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        if (CURRENT_SCREEN == LOADING)
        {
            DrawTextEx(
                katsunoFont,
                "DUEL",
                {
                    screen.getScreenWidth() / 2 - 255,
                    screen.getScreenHeight() / 2 - 255
                },
                255,
                1,
                Fade(MAROON, alpha)
            );

            DrawTextEx(
                poppinsFont,
                "by BOKSHIVERSE",
                {
                    (screen.getScreenWidth() - 270) / 2,
                    screen.getScreenHeight() - 100
                },
                32,
                1,
                WHITE
            );
        }
        else if (CURRENT_SCREEN == HOME)
        {
            DrawTexturePro(
                wallpaper,
                {
                    0,
                    0,
                    (float)wallpaper.width,
                    (float)wallpaper.height
                },
                {
                    0,
                    0,
                    (float)GetScreenWidth(),
                    (float)GetScreenHeight()
                },
                {
                    0,
                    0
                },
                0.0f,
                WHITE
            );

            Color createBg =
                CURRENT_OPTION == CREATE_ROOM ? WHITE : BLACK;

            Color createText =
                CURRENT_OPTION == CREATE_ROOM ? BLACK : WHITE;

            Color joinBg =
                CURRENT_OPTION == JOIN_ROOM ? WHITE : BLACK;

            Color joinText =
                CURRENT_OPTION == JOIN_ROOM ? BLACK : WHITE;

            Color settingsBg =
                CURRENT_OPTION == SETTINGS ? WHITE : BLACK;

            Color settingsText =
                CURRENT_OPTION == SETTINGS ? BLACK : WHITE;

            DrawRectangle(
                1450,
                721,
                500,
                100,
                createBg
            );

            DrawRectangle(
                1450,
                821,
                500,
                100,
                joinBg
            );

            DrawRectangle(
                1450,
                921,
                500,
                100,
                settingsBg
            );

            DrawTextEx(
                poppinsBlackFont,
                "CREATE ROOM",
                {
                    1500,
                    735
                },
                65,
                1,
                createText
            );

            DrawTextEx(
                poppinsBlackFont,
                "JOIN ROOM",
                {
                    1500,
                    835
                },
                65,
                1,
                joinText
            );

            DrawTextEx(
                poppinsBlackFont,
                "SETTINGS",
                {
                    1500,
                    935
                },
                65,
                1,
                settingsText
            );
        }

        EndDrawing();
    }

    UnloadTexture(wallpaper);

    UnloadFont(katsunoFont);
    UnloadFont(poppinsFont);
    UnloadFont(poppinsBlackFont);

    UnloadSound(switchbg);
    UnloadSound(loadingbg);
    UnloadMusicStream(bgm);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
